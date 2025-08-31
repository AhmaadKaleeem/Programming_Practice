# In a file called numb3rs.py, implement a function called validate that expects an IPv4 address as input as a str
# and then returns True or False, respectively, if that input is a valid IPv4 address or not.
import re
import sys


def main():
    print(validate(input("IPv4 Address: ")))


def validate(ip):
  if re.search(r'^((25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)\.){3}(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)$',ip):
      return True
  else:
      return False





if __name__ == "__main__":
    main()