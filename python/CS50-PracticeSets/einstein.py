# In a file called einstein.py, implement a program in Python that prompts the user for mass as an integer
# (in kilograms) and then outputs the equivalent number of Joules as an integer. Assume that the user will input an integer.

# taking mass input from user (in kg )  having int datatype
mass = int(input("Please Enter The Mass TO Calculate Energy : "))

# Applying Formula E=mc2
energy = int(300000000 * 300000000 * mass)

#prnting result
print("Energy is :", energy)