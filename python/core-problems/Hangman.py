# Word Selection
# Randomly pick a word loaded  from a file).
# Word should be hidden as underscores (_) at the start.
# Gameplay Loop
# Player guesses one letter at a time.
# If correct → reveal letter(s) in the word.
# If incorrect → lose one attempt.
# Attempts / Lives
# Player has n attempts (Acc to difficulty level, 6 - Hard , 8 Medium , 10 Easy)
# Show remaining attempts after each guess.
# End Conditions
# Win: player reveals all letters.
# Lose: attempts reach 0 → show the full word.
# Replay Option
# After game ends → ask if player wants to play again.
# Load words from a text file (words.txt).
from random import choice
import os
import sys

def main():
 run_game()

# Function To Load Words From File and If File Not Found, Generate a New File 
def load_words():
 pathname = "python/core-problems/words.txt"
 if os.path.exists(pathname):
  with open(pathname,'r') as word_list_file:
        word_list = word_list_file.read()
        word_list = word_list.split()
        word_list = [w.lower() for w in word_list]
        return word_list
 else:
         print("Error! File Containing Words Not Found") 
         print('Generating a New Words File ') 
         new_words = ['apple', 'grape', 'peach', 'mango', 'berry', 'about', 'above', 'abuse', 'actor', 'acute', 'admit', 'adopt', 'adult', 'after', 'again', 'agent', 'agree', 'ahead', 'alarm', 'album', 'alert', 'alike', 'alive', 'allow', 'alone', 'along', 'alter', 'among', 'anger', 'Angle', 'angry', 'apart', 'apple', 'apply', 'arena', 'argue', 'arise', 'array', 'aside', 'asset', 'audio', 'audit', 'avoid', 'award', 'aware', 'badly', 'baker', 'bases', 'basic', 'basis', 'beach', 'began', 'begin', 'begun', 'being', 'below', 'bench', 'billy', 'birth', 'black', 'blame', 'blind', 'block', 'blood', 'board', 'boost', 'booth', 'bound', 'brain', 'brand', 'bread', 'break', 'breed', 'brief', 'bring', 'broad', 'broke', 'brown', 'build', 'built', 'buyer', 'cable', 'calif', 'carry', 'catch', 'cause', 'chain', 'chair', 'chart', 'chase', 'cheap', 'check', 'chest', 'chief', 'child', 'china', 'chose', 'civil', 'claim', 'class', 'clean', 'clear', 'click', 'clock', 'close', 'coach', 'coast', 'could', 'count', 'court', 'cover', 'craft', 'crash', 'cream', 'crime', 'cross', 'crowd', 'crown', 'curve', 'cycle', 'daily', 'dance', 'dated', 'dealt', 'death', 'debut', 'delay', 'depth', 'doing', 'doubt', 'dozen', 'draft', 'drama', 'drawn', 'dream', 'dress', 'drill', 'drink', 'drive', 'drove', 'dying', 'eager', 'early', 'earth', 'eight', 'elite', 'empty', 'enemy', 'enjoy', 'enter', 'entry', 'equal', 'error', 'event', 'every', 'exact', 'exist', 'extra', 'faith', 'false', 'fault', 'fiber', 'field', 'fifth', 'fifty', 'fight', 'final', 'first', 'fixed', 'flash', 'fleet', 'floor', 'fluid', 'focus', 'force', 'forth', 'forty', 'forum', 'found', 'frame', 'frank', 'fraud', 'fresh', 'front', 'fruit', 'fully', 'funny', 'giant', 'given', 'glass', 'globe', 'going', 'grace', 'grade', 'grand', 'grant', 'grass', 'great', 'green', 'gross', 'group', 'grown', 'guard', 'guess', 'guest', 'guide', 'happy', 'harry', 'heart', 'heavy', 'hence', 'henry', 'horse', 'hotel', 'house', 'human', 'ideal', 'image', 'index', 'inner', 'input', 'issue', 'japan', 'jimmy', 'joint', 'jones', 'judge', 'known', 'label', 'large', 'laser', 'later', 'laugh', 'layer', 'learn', 'lease', 'least', 'leave', 'legal', 'level', 'lewis', 'light', 'limit', 'links', 'lives', 'local', 'logic', 'loose', 'lower', 'lucky', 'lunch', 'lying', 'magic', 'major', 'maker', 'march', 'maria', 'match', 'maybe', 'mayor', 'meant', 'media', 'metal', 'might', 'minor', 'minus', 'mixed', 'model', 'money', 'month', 'moral', 'motor', 'mount', 'mouse', 'mouth', 'movie', 'music', 'needs', 'never', 'newly', 'night', 'noise', 'north', 'noted', 'novel', 'nurse', 'occur', 'ocean', 'offer', 'often', 'order', 'other', 'ought', 'paint', 'panel', 'paper', 'party', 'peace', 'peter', 'phase', 'phone', 'photo', 'piece', 'pilot', 'pitch', 'place', 'plain', 'plane', 'plant', 'plate', 'point', 'pound', 'power', 'press', 'price', 'pride', 'prime', 'print', 'prior', 'prize', 'proof', 'proud', 'prove', 'queen', 'quick', 'quiet', 'quite', 'radio', 'raise', 'range', 'rapid', 'ratio', 'reach', 'ready', 'refer', 'right', 'rival', 'river', 'robin', 'roger', 'roman', 'rough', 'round', 'route', 'royal', 'rural', 'scale', 'scene', 'scope', 'score', 'sense', 'serve', 'seven', 'shall', 'shape', 'share', 'sharp', 'sheet', 'shelf', 'shell', 'shift', 'shirt', 'shock', 'shoot', 'short', 'shown', 'sight', 'since', 'sixth', 'sixty', 'sized', 'skill', 'sleep', 'slide', 'small', 'smart', 'smile', 'smith', 'smoke', 'solid', 'solve', 'sorry', 'sound', 'south', 'space', 'spare', 'speak', 'speed', 'spend', 'spent', 'split', 'spoke', 'sport', 'staff', 'stage', 'stake', 'stand', 'start', 'state', 'steam', 'steel', 'stick', 'still', 'stock', 'stone', 'stood', 'store', 'storm', 'story', 'strip', 'stuck', 'study', 'stuff', 'style', 'sugar', 'suite', 'super', 'sweet', 'table', 'taken', 'taste', 'taxes', 'teach', 'teeth', 'terry', 'texas', 'thank', 'theft', 'their', 'theme', 'there', 'these', 'thick', 'thing', 'think', 'third', 'those', 'three', 'threw', 'throw', 'tight', 'times', 'tired', 'title', 'today', 'topic', 'total', 'touch', 'tough', 'tower', 'track', 'trade', 'train', 'treat', 'trend', 'trial', 'tried', 'tries', 'truck', 'truly', 'trust', 'truth', 'twice', 'under', 'undue', 'union', 'unity', 'until', 'upper', 'upset', 'urban', 'usage', 'usual', 'valid', 'value', 'video', 'virus', 'visit', 'vital', 'voice', 'waste', 'watch', 'water', 'wheel', 'where', 'which', 'while', 'white', 'whole', 'whose', 'woman', 'women', 'world', 'worry', 'worse', 'worst', 'worth', 'would']
         new_words = [ w.lower() for w in new_words]
         with open(pathname,'w') as new_word_list_file:
          for word in new_words:
           new_word_list_file.write(f"{word}\n")
          print("New Words File Generated, Moving Into Game.....\n")
 return new_words

# Function to Select Random Word 
def word_selection():
      words =  load_words()
      return choice(words)

# Function to Get Username
def get_username(): 
 while True:
  user_name = input("Please, Enter Your Name: ").strip() # Igmoring Spaces
  if not user_name.isalpha():
     print("Error! Please Enter a Valid Alphabetic String")
     continue
  else:
     return user_name  

# Selecting Difficulty
def get_difficulty_level():
 while True:
   user_input = input("\nSelect a Level: ").strip().lower()
   if not user_input.isalpha():
       print("Error! Please Enter a Valid Alphabetic String")
       continue
   if not user_input in ['easy','medium','hard']:
      print("Error! Select a Valid Difficulty Level (Easy,Medium,Hard)")
      continue
   else:
     if user_input == "easy":
        return 10
     if user_input == "medium":
        return 8
     if user_input == "hard":
        return 6  

# Simple Menu For User
def start_menu(name_user):
 print('---------------------------------------- Hangman - Guess Word Now ----------------------------------------')
 print(f"Welcome '{name_user.title()}' To Hangman")
 print(f"{name_user.title()}, Select Level of Difficulty\n")
 print("-- Easy \n-- Medium \n-- Hard")
 
# Game Logic
def game_logic(attempts,word_selected,guessed,name_user):
    words_guessed = ''
    while attempts != 0 or guessed == len(word_selected):
       print('\nWord: '+ words_guessed +' _ ' * (len(word_selected) - len(words_guessed)))
       user_guess = input("Guess a Letter: ").lower().strip()
       if not user_guess.isalpha() or len(user_guess) != 1:
          print ("Error! Enter a Single Alphabetic Letter")
          continue
       if user_guess == word_selected[guessed]:
          words_guessed += user_guess
          guessed += 1
          print("----- Right Guess -----")
       else:
          attempts -=1
          print("----- Wrong Guess -----")
       print(f"Attemps Left: {attempts}")
       get_winner(attempts,word_selected,guessed,name_user)


# Selecting Winner
def get_winner(attempts,word_selected,guessed,user_name):
   print('---------------------------------------- Final Results ----------------------------------------')
   if attempts == 0:
      print(f"\nHard Luck, {user_name}! Better Luck Next Time")
      print(f"{user_name}, The Word Was {word_selected}")
   elif guessed == len(word_selected):
       print(f"\nCongratulations, {user_name}! Played Well. See You Next Time ")
       
def replay_game():
       while True:
         replay_game = input("\nDo You Want To Play Game Again(Y/N): ")
         replay_game= replay_game.lower()
         if replay_game == 'y':
             main()
         elif replay_game == 'n':
             print("Exiting The Game ....")
             break
         else :
             print("Error! Please Enter Valid Input (Y/N)")
             continue
 
             
# Running Game
def run_game():
 guessed = 0
 word_selected = word_selection()
 print(word_selected)
 name_user = get_username()
 start_menu(name_user)
 attempts = get_difficulty_level()
 game_logic(attempts,word_selected,guessed,name_user)
 replay_game()
 
 

if __name__ == "__main__":
    main()