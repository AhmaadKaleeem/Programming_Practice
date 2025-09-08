import sounddevice as sd
import soundfile as sf
import os
import sys
from utilities_sound_recorder import trim_silence,normalize
import re
import queue
import numpy as np

def main():
  run_recoder()
    
def recording():
  fs = 44100
  time = int(input("\nEnter the Time You Want To Record: "))
  chanel = channel_selection()
  print(f"Recording For {time} Seconds")
  record_data = sd.rec(int(fs*time),samplerate=fs,channels=chanel , dtype='float32')
  sd.wait() 
  record_data = normalize(record_data)
  print(f"Recorded For {time} Seconds")
  sound_file = save_with_file_name() 
  sf.write(sound_file,record_data,fs)
  print(f"Saved Recording as {sound_file}\n")
  option = int(input("Do You Want To Playback? \n1. Yes \n2.No \nPlease Select: " ))
  if option == 1:
   print(f"Playing Recording {sound_file}")
   sd.play(record_data,fs)
   sd.wait()
   print('Playback Done\n')
  elif option == 2:
   sys.exit("Exiting The Program.......")

def dynamic_recording():
    fs = 44100
    channels = channel_selection()
    q = queue.Queue()
    chuncks = []
    def callback(indata,frames_count,time_info,status):
        if status:
            print(status)
        q.put(indata.copy())
    print()
    
    print("Recording in Progress.... Press Enter/Ctrl+C/Ctrl+Z To Stop.")
    data = sd.InputStream(samplerate=fs, channels=channels , callback=callback , dtype="float32")
    with data:
        try:
            input()
        except KeyboardInterrupt:
            print("Recording Stopped")
            pass
        except EOFError:
            print("Recording Stopped")
            pass
    while not q.empty():
     chuncks.append(q.get())
    audio = np.concatenate(chuncks, axis=0)
    audio = normalize(audio)
    sound_file = save_with_file_name()
    sf.write(sound_file, audio, fs)
    print(f"Saved Recording as {sound_file}")
    option = int(input("Do You Want To Playback? \n1. Yes \n2.No \nPlease Select: " ))
    if option == 1:
     print(f"Playing Recording {sound_file}")
     sd.play(audio,fs)
     sd.wait()
     print('Playback Done\n')
    elif option == 2:
     sys.exit("Exiting The Program.......")
        
def playback():
   sound_file  = select_recoding_file()
   print(f"Playing Recording {sound_file}")
   loadback_data,loadback_fs = sf.read(sound_file,dtype='float32')
   sd.play(loadback_data,loadback_fs)
   sd.wait()
   print('Playback Done\n')

def normalize_recoding():
    sound_file = select_recoding_file()
    if not sound_file:
          return
    file_data,file_fs = sf.read(sound_file)
    print(f"\nNormalizing {sound_file}")
    file_data = normalize(file_data)
    print(f"{sound_file} Normalized Successfully, Saving Normalizied File...... ")
    sound_file = f"normalized{sound_file}"
    sf.write(sound_file,file_data,file_fs)
    
def trim_recording_silence():
    sound_file = select_recoding_file()
    if not sound_file:
          return
    file_data,file_fs = sf.read(sound_file)
    print(f"\nTrimming Silence -- {sound_file}")
    file_data = trim_silence(file_data,threshold = 0.02)
    print(f"{sound_file} Trimmed Silence Successfully, Saving Trimmed File...... ")
    sound_file = f"modified{sound_file}"
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
    if len(files) == 0:
        print("No Files Availble")
        break
    for s_no,f in enumerate(files):
     print(s_no+1,f)
    user_playback = int(input("Enter Recording No. To Select: "))
    if 1 < user_playback or user_playback > len(files):
        print("Please, Enter Valid Recording No. ") 
        continue
    file_name = files[user_playback-1]
    return file_name

def delete_recording():
    while True:
       file_name = select_recoding_file()
       if not file_name:
           break 
       option = int(input(f"\nAre You Sure to Delete {file_name}? \nEnter 1 To Delete or 0 to Cancel: "))
       if  0 < option > 1:
            print("Error! Please Enter Digits Within Valid Range\n")
            continue
       elif option == 0:
           break
       elif option == 1:
           print(f"\nDeleting {file_name} ....")
           os.remove(file_name)
           print("File Deleted Succesfully")
           break

def channel_selection():
       option = int(input(f"\nChannel Selection\n1. Mono \n2. Stero \nEnter the Channel: "))
       if  0 < option > 1:
            print("Error! Please Enter Digits Within Valid Range\n")
            return
       elif option == 1:
           return 1
       elif option == 2:
           return 2
def run_recoder():
    while True:
        print("-------------------------------------- Sound Recorder --------------------------------------")
        print("< For Recording Audio, Mic is Required > Ensure To Have a Mic Connected Before Proceeding ..... ")
        print("1. Record Audio \n2. Playback Audio \n3. Normalize Recording \n4. Trim Silence \n5. Delete Recording \n0. Exit ")
        option = int(input("Select The Purpose: "))
        if  0 < option > 5:
            print("Error! Please Enter Digits Within Valid Range\n")
            continue
        if option == 1:
            recording_type = int(input("\n1. Dynamic Recording \n2. Fixed Time Recording \nEnter Your Choice: " ))
            if  1< recording_type > 2: 
              print("Enter Valid Digits Choice \n")
              return
            elif recording_type == 2:
                recording()
            elif recording_type == 1:
                dynamic_recording()
        elif option == 2:
            playback()
        elif option == 3:
            normalize_recoding()
            continue
        elif option == 4:
            trim_recording_silence()
            continue
        elif option == 5:
            delete_recording()
            continue
        elif option == 0:
            sys.exit("Exiting The Sound Recorder..........")
            
        
    
if __name__ == '__main__':
    main()