def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")


def is_valid(s):
    if(s.isalnum()):
        lenght = len(s)
        if 2 <=  lenght <= 6:
          if s[0:2].isalpha():
            for  i in range(lenght):
              if s[i].isdigit():
                  if s[i] == "0":
                    return False
                  if not s[i:].isdigit():
                      return False
                  break
            return True
          else: 
              return False
          
        else:
         return False
    else :
     return False


main()