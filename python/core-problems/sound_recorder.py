import sounddevice as sd
import soundfile as sf
import numpy as np

# Recording Fixed 3 sec wave
fs = 44100
time = int(input("Enter the Time You Want To Record: "))
chanel = 1
sound_file = "python/core-problems/sound.wav"
print(f"Recording For {time} Seconds")
record_data = sd.rec(int(fs*time),samplerate=fs,channels=chanel , dtype='float32')
sd.wait()
print("Recorded For {time} Seconds")
sf.write(sound_file,record_data,fs)

print("Playing Recording Back ........")
loadback_data,loadback_fs = sf.read(sound_file,dtype='float32')
sd.play(loadback_data,fs)
sd.wait()
print('Playback Done')