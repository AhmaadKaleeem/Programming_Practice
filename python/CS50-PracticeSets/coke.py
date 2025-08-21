# Intializing coke price nd taking inputs
price = 50
total_paid = 0
# Loop TO Valiade Coin Inputs
print(f"Amount Due: {price - total_paid}")
while total_paid <= 50 :
    insertedcoin = int(input("Insert Coin: "))
    if insertedcoin == 25 or insertedcoin == 10 or insertedcoin == 5:
        total_paid += insertedcoin
    if total_paid >= 50:
       break
    print(f"Amount Due: " , price - total_paid)

change = total_paid-price
print(f"Change Owed: {change}")


