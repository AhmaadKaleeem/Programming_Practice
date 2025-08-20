# In a file called bank.py, implement a program that prompts the user for a greeting. If the greeting starts with “hello”, output $0.
# If the greeting starts with an “h” (but not “hello”), output $20. Otherwise, output $100. Ignore any leading whitespace in the user’s greeting,
# and treat the user’s greeting case-insensitively.

# Prompting User for Greeting as Input and ignoring leading spce
greeting = input ("Greet Us : ").lstrip()

# Making case insenstivive
greeting = greeting.lower()

# Using Conditional to take desired output and using str function to checking startng strin
if greeting.startswith("hello"):
    print("$0")
elif greeting.startswith("h"):
    print("$20")
else:
    print("$100")