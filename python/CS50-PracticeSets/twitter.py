# , implement a program that prompts the user for a str of text and then outputs that same text but with all vowels (A, E, I, O, and U) omitted, whether inputted in uppercase or lowercase.
# Asking input from user
inputtxt = input("Input: ")
new = ""
## Loop to check ndremove vowels
for i in inputtxt:
    if i in ["A","E","I","O","U","a","e","i","o","u"]:
     continue
    else:
     new += i

print ("Output: " + new)    
