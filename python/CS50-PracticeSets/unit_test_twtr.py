# In a file called twttr.py, reimplement Setting up my twttr from Problem Set 2, restructuring your code per the below, wherein shorten expects a str as input and returns that same str but with all vowels (A, E, I, O, and U) omitted, whether inputted in uppercase or lowercase. 

def main():
    inputtxt = input("Input: ")
    new = shorten(inputtxt)
    print(new)


def shorten(word):
   new = ""
   for i in word:
    if not i in ["A","E","I","O","U","a","e","i","o","u"]:
     new += i
   
   return new


if __name__ == "__main__":
    main()