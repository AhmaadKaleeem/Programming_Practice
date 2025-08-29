# Even so, in a file called lines.py, implement a program that expects exactly one command-line argument, 
# the name (or path) of a Python file, and outputs the number of lines of code in that file, 
# excluding comments and blank lines. If the user does not specify exactly one command-line argument, 
# or if the specified file’s name does not end in .py, or if the specified file does not exist, the program
# should instead exit via sys.exit.

import sys 

def main():
    filename = command_check()
    count = 0
    try:
      with open(filename,'r') as file:
          for line in file:
              line = line.strip()
              if line!= "" and not line.startswith("#"):
                  count += 1
              
    except FileNotFoundError:
        sys.exit('File does not exist')
    print(count)
    
        
        
        

def command_check():
 if  len(sys.argv) < 2  :
     sys.exit("Too few command-line arguments")
 if len(sys.argv) > 2  :
     sys.exit("Too many command-line arguments")
 if not sys.argv[1].endswith(".py"):
     sys.exit("Not a python file")
 return sys.argv[1]
if __name__ ==  "__main__":
    main()
     