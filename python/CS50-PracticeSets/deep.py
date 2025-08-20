# In deep.py, implement a program that prompts the user for the answer to the Great Question of Life, the Universe and Everything,
# outputting Yes if the user inputs 42 or (case-insensitively) forty-two or forty two. Otherwise output No.

# Asking Input From User
question = input("What is the Answer to the Great Question of Life, the Universe and Everything? ").strip()

# Using Std Function and making input always being lowercase as program is case insensitive
question = question.lower()

# Using conditional to print output
if question.isdigit():
    if int(question) == 42:
     print("Yes")
    else:
     print("No")
elif question == "forty-two" or question == "forty two":
    print("Yes")
else:
    print("No")
