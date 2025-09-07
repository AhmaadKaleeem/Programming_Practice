import sounddevice as sd
import soundfile as sf
import os
import sys
from utilities_sound_recorder import trim_silence,normailze
import re
import numpy as np

def main():
  run_recoder()
    
def recording():
  fs = 44100
  time = int(input("\nEnter the Time You Want To Record: "))
  chanel = 1
  print(f"Recording For {time} Seconds")
  record_data = sd.rec(int(fs*time),samplerate=fs,channels=chanel , dtype='float32')
  sd.wait() 
  record_data = normailze(record_data)
  print(f"Recorded For {time} Seconds")
  sound_file = save_with_file_name() 
  sf.write(sound_file,record_data,fs)
  print(f"Saved Recording as {sound_file}\n")

def playback():
   sound_file  = select_recoding_file()
   print(f"Playing Recording {sound_file}")
   loadback_data,loadback_fs = sf.read(sound_file,dtype='float32')
   sd.play(loadback_data,loadback_fs)
   sd.wait()
   print('Playback Done\n')

def normalize_recoding():
    sound_file = select_recoding_file()
    file_data,file_fs = sf.read(sound_file)
    print(f"Normalizing {sound_file}")
    file_data = normailze(file_data)
    print(f"{sound_file} Normalized Successfully, Saving Normalizied File...... ")
    sound_file = f"{sound_file}+_normalized"
    sf.write(sound_file,file_data,file_fs)
def save_with_file_name():
 while True:
    file_name = input("Save Recording As: ").strip()
    if not file_name:
        print("Error! Recording Name Should Have Atleast One Letter")
        continue
    if f"{file_name}.wav" in os.listdir("."):
        file_name = next_file_name(file_name)
    else :
     file_name = f"{file_name}.wav"
    return file_name 

def next_file_name(base, ext=".wav" ):
    files = os.listdir('.')
    # Finding Pattern Using Logical Expressions
    pattern = re.compile(rf"{base}_(\d+){ext}")
    numbers = [int(pattern.match(f).group(1)) for f in files if pattern.match(f)]
    next_num = max(numbers,default=0) + 1
    return f"{base}_{next_num}{ext}"

def select_recoding_file():
  while True:
    files = [f for f in os.listdir(".") if f.endswith(".wav")]
    print("\nRecordings Available")
    for s_no,f in enumerate(files):
     print(s_no+1,f)
    user_playback = int(input("Enter Recording No. To Select: "))
    if 1 < user_playback > len(files):
        print("Please, Enter Valid Recording No. ") 
        continue
    file_name = files[user_playback-1]
    return file_name
   
def run_recoder():
    while True:
        print("-------------------------------------- Sound Recorder --------------------------------------")
        print("< For Recording Audio, Mic is Required > Ensure To Have a Mic Connected Before Proceeding ..... ")
        print("1. Record Audio \n2. Playback Audio \n0. Exit ")
        option = int(input("Select The Purpose: "))
        if  0 < option > 2:
            print("Error! Please Enter Digits Within Valid Range\n")
            continue
        if option == 1:
            recording()
        elif option == 2:
            playback()
        elif option == 0:
            sys.exit("Exiting The Sound Recorder..........")
            
        
    
if __name__ == '__main__':
    main()