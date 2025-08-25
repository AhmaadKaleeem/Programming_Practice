# In a file called adieu.py, implement a program that prompts the user for names, one per line,
# until the user inputs control-d. Assume that the user will input at least one name.
# Then bid adieu to those names, separating two names with one and, three names with two commas and one and, and 𝑛 names with 𝑛 −1 commas and one and.
import inflect
bind = inflect.engine()
names = []
exitted = False

while not exitted:
    try:
     user_input = input()
     names.append(user_input)
    except EOFError:
      exitted = True
      pass
names_joined = bind.join(names)
print(f'Adieu, adieu, to {names_joined}' )
