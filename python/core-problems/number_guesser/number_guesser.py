# Make a program guess_number.py:
# Generate a random number between 1 and 20 (import random).
# Ask the user to guess until correct.
# Give hints: “Too high” / “Too low”.
# Count attempts and display at the end.
import random
guessed = False
count = 0
number_selected = random.randint(1,20)
while not guessed:
    try:
      userinput = int(input('Guess The Number:'))
      count += 1
      if userinput != number_selected:
        difference = userinput - number_selected
        if difference <= 5 and difference >= -5:
         print('Just Near, Next Can Be The Right Guess')
        elif  difference > 5 or  difference  <-5 :
         print('Not Near, Use Mind And Next Can Be The Right Guess')
      else :
          print("Congrats! You Have Picked Right Number.")
          print(f"You Used {count} Attempts......")
          guessed = True
    except ValueError:
        print("Enter Valid Integer.")
        continue
         

