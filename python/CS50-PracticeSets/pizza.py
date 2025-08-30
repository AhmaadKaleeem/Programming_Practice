from tabulate import tabulate
import sys
import csv

def main():
    csv_file_name = command_check()
    try:
      with open(csv_file_name,'r') as csvfile:
          data_reader = csv.reader(csvfile)
          data_reader = list(data_reader)
          header = data_reader[0]
          rows = data_reader[1:]
    except FileNotFoundError:
        sys.exit('File does not exist')

    print(tabulate(rows, headers=header,tablefmt='grid'))


def command_check():
 if  len(sys.argv) < 2  :
     sys.exit("Too few command-line arguments")
 if len(sys.argv) > 2  :
     sys.exit("Too many command-line arguments")
 if not sys.argv[1].endswith(".csv"):
     sys.exit("Not a csv file")
 return sys.argv[1]

if __name__ ==  "__main__":
    main()
