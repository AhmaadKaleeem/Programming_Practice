import sys
import csv

def main():
    command_check()
    input_file = sys.argv[1]
    output_file = sys.argv[2]

    try:
        with open(input_file, "r") as infile:
            reader = csv.DictReader(infile)
            with open(output_file, "w", newline="") as outfile:
                fieldnames = ["first", "last", "house"]
                writer = csv.DictWriter(outfile, fieldnames=fieldnames)
                writer.writeheader()
                for row in reader:
                    last, first = row["name"].split(", ")
                    writer.writerow({"first": first, "last": last, "house": row["house"]})
    except FileNotFoundError:
        sys.exit(f"Could not read {input_file}")


def command_check():
 if  len(sys.argv) < 3  :
     sys.exit("Too few command-line arguments")
 if len(sys.argv) > 3  :
     sys.exit("Too many command-line arguments")
 if not sys.argv[1].endswith(".csv"):
     sys.exit(f"Could Not read {sys.argv[1]} ")

if __name__ ==  "__main__":
    main()
