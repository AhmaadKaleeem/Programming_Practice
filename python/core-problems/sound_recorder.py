import sounddevice as sd
import soundfile as sf
import sys
import numpy as np

# Recording Fixed 3 sec wave
fs = 44100
time = int(input("Enter the Time You Want To Record: "))
chanel = 1
sound_file = "python/core-problems/sound.wav"
print(f"Recording For {time} Seconds")
record_data = sd.rec(int(fs*time),samplerate=fs,channels=chanel , dtype='float32')
sd.wait()
print(f"Recorded For {time} Seconds and Saved at {sound_file}")
sf.write(sound_file,record_data,fs)
# Asking User Either They Want To Playback or Not
try:
 option = int(input("Do You Want To Playback? \n1. Yes \n2.No \nPlease Select: " ))
 if option == 1:
  print("Playing Recording Back ........")
  loadback_data,loadback_fs = sf.read(sound_file,dtype='float32')
  sd.play(loadback_data,fs)
  sd.wait()
  print('Playback Done')
 elif option == 2:
     sys.exit("Exiting The Program.......")
except ValueError:
    sys.exit(0)