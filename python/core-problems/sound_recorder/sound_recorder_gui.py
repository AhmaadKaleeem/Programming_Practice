import sounddevice as sd
import soundfile as sf
import os
import queue
import numpy as np
from utilities_sound_recorder import trim_silence, normalize

class SoundRecorder:
    def __init__(self):
        self.fs = 44100
        self.channels = 1
        self.recording_data = None
        self.dynamic_stream = None
        self.q = queue.Queue()
        self.chunks = []

    def set_channels(self, channels):
        self.channels = channels

    def record_fixed_time(self, duration):
        self.recording_data = sd.rec(int(self.fs * duration), samplerate=self.fs, channels=self.channels, dtype='float32')
        sd.wait()
        self.recording_data = normalize(self.recording_data)
        return self.recording_data

    def start_dynamic(self):

        self.chunks = []
        self.q = queue.Queue()
        def callback(indata, frames, time_info, status):
            self.q.put(indata.copy())
        self.dynamic_stream = sd.InputStream(samplerate=self.fs, channels=self.channels, callback=callback, dtype='float32')
        self.dynamic_stream.start()

    def stop_dynamic(self):
        if self.dynamic_stream:
            self.dynamic_stream.stop()
            self.dynamic_stream.close()
        while not self.q.empty():
            self.chunks.append(self.q.get())
        if self.chunks:
            data = np.concatenate(self.chunks, axis=0)
            data = normalize(data)
            self.recording_data = data
            return data
        return None

    def save(self, data, filename):
        sf.write(filename, data, self.fs)

    def playback(self, filename):
        data, fs = sf.read(filename, dtype='float32')
        sd.play(data, fs)
        sd.wait()

    def normalize_file(self, filename):
        data, fs = sf.read(filename)
        data = normalize(data)
        outname = f"normalized_{os.path.basename(filename)}"
        sf.write(outname, data, fs)
        return outname

    def trim_silence_file(self, filename, threshold=0.02):
        data, fs = sf.read(filename)
        data = trim_silence(data, threshold=threshold)
        outname = f"trimmed_{os.path.basename(filename)}"
        sf.write(outname, data, fs)
        return outname

    def delete_file(self, filename):
        os.remove(filename)

    def available_recordings(self):
        return [f for f in os.listdir(".") if f.lower().endswith(".wav")]