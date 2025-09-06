import sounddevice as sd
import soundfile as sf
import numpy as np

# Creating a sample wave
fs = 44100
time = 1
t = np.linspace(0,time,int(fs*time),endpoint=False)
audio_wave = 0.5 * np.sin(2 * np.pi * 440 * t)

print("Playing Tone ........")
sd.play(audio_wave,fs)
sd.wait()
print('Done')