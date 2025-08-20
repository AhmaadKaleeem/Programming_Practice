# In a file called playback.py, implement a program in Python that prompts the user for input and then outputs that same input, replacing each space with ... (i.e., three periods).

# Taking Input
userinput = input("Enter the input text : ")
# Splitting input text into words
userinput = userinput.split()
# Printing Output With ...
print("...".join(userinput))