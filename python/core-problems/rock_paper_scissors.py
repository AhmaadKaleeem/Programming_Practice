# Rock-Paper-Scissors

# Requirements (must all be met):
# Player vs Computer
# Player enters: rock, paper, or scissors (cAse-insensitive).
# Computer randomly picks one.
# let the player choose best of N minimum 3 (e.g., best of 5, best of 7).
# Keep score.
# After n rounds, show who won overall.
# Handle Invalid Input
# If player enters anything else → Ask again without crAshing.
# Clean Code
# Follow PEP8 naming.
# Use functions to separate logic (e.g., get_winner()).
from random import choice

def main():
 choice_list = ['rock','paper','scissors']
 user_score = 0
 computer_score = 0
 round_no = 1
 
 # Using Function To Get User Name , Game Rounds To Be Played & Displaying Main Menu
 user_name = get_username()
 game_round = user_best_of_input(user_name)
 main_menu(user_name,game_round)
 
 # Game Logic To Get User Choice and Update Game Scores
 while not game_round == 0:
  user_input = get_user_choice(round_no,choice_list)
  computer_choice = choice(choice_list)
  user_score,computer_score,game_round,round_no = determine_roundwinner(user_name,round_no,user_score,computer_score,user_input,computer_choice,game_round)
        
 # Printing Winner Through Calling Get Winner Function
 print(get_winner(user_score,computer_score,user_name))

# Helper Functions 
def get_username():
 while True:
  user_name = input("Please, Enter Your Name: ")
  if not user_name.isalpha():
     print("Please Enter a Valid Alphabetic String")
     continue
  else:
     return user_name

def user_best_of_input(name_user):
 while True:
   try:
      round_input = int(input(f"\n{name_user.title()}, Select Best Of : "))
      if round_input < 3:
          print("There Can Be Minimum of 3 Round. Input Again....")
          continue
      else:
          return round_input 
   except ValueError:
       print (f"{name_user.title()}, Please Provide Correct Value !")
       continue

def main_menu(name_user,round_input):
 print('---------------------------------------- Rock Paper Scissors ----------------------------------------')
 print(f"Welcome '{name_user.title()}' To Rock-Paper-Scissors")
 print(f"{name_user.title()} Vs Computer, Round Of {round_input}. Lets See Who Wins!")
 
def get_user_choice(game_round,choice_list):
 while True:
   user_input = input(f"Round {game_round} , Enter Your Choice (rock, paper or scissors): ")
   user_input = user_input.lower()
   if not user_input in choice_list:
     print("Please Enter a Valid Choice Between Rock, Paper Or Scissors")
     continue
   else:
     return user_input
   
 
def determine_roundwinner(user_name,round_no,user_score,computer_score,user_input,computer_choice,game_round):
  print(f"\nComputer Chosed {computer_choice}")
  if user_input == computer_choice:
        print("Tied...... Moving To Same Round Again....")
        print(f"Score: {user_name.title()} {user_score} - Computer {computer_score}\n")
  elif (user_input == 'paper' and  computer_choice =='rock')  or (user_input == 'rock' and  computer_choice =='scissors') or (user_input =='scissors' and computer_choice == 'paper'):
        print(f"{user_name.title()} Won This Round")
        user_score += 1
        round_no +=1
        print(f"Score: {user_name.title()} {user_score} - Computer {computer_score}\n")
        game_round -= 1
  else :
        print(f"Computer Won This Round")
        computer_score += 1
        print(f"Score: {user_name.title()} {user_score} - Computer {computer_score}\n")
        game_round -= 1
        round_no +=1
  return user_score,computer_score ,game_round, round_no    

def get_winner(score_a , score_b , name_user):
    if score_a > score_b:
        return (f"We have {name_user.title()} As Winner with Score {score_a} - {score_b} ")
    elif score_a < score_b:
        return (f"We have Computer As Winner with Score {score_b} - {score_a} ")
    elif score_a == score_b:
        return (f"We have Both {name_user.title()} and Computer As Winner with Score {score_a} - {score_b} ")
 
# Main Function
if __name__ == "__main__":
    main()