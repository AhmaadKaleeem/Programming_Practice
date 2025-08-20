# In a file called camel.py, implement a program that prompts the user for the name of a variable in camel case and outputs the corresponding name in snake case. 
# #Assume that the user’s input will indeed be in camel case.

# Asking CamelCase Input
camelcase = input("camelCase: ")
# Intilaizing Output String
result  = ""
# Using loop to iterate in string

for char in camelcase : 
    # Handling the camel case into snake case
    if char.isupper():
        result += ("_" + char.lower())
    else :
      result += char.lower()
      
print("snake_Case: " + result)
        