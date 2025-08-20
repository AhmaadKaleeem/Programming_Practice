def main():
    dollars = dollars_to_float(input("How much was the meal? "))
    percent = percent_to_float(input("What percentage would you like to tip? "))
    tip = dollars * percent
    print(f"Leave ${tip:.2f}")

# Function to convert str dollar input into float data-type
def dollars_to_float(d):
      # Using Str Replcae Function To Remove Dollar Sign
      return float(d.replace("$",""))

# Function to convert str percentage input into float data-type
def percent_to_float(p):
      # Using Str Replcae Function To Remove Percentage Sign and convert it to float
      return float(p.replace("%",""))/ 100

main()