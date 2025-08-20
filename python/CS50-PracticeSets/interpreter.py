# In a file called interpreter.py, implement a program that prompts the user for an arithmetic expression and then calculates
# and outputs the result as a floating-point value formatted to one decimal place. Assume that the user’s input will be formatted as x y z, with one space between x and y and one space between y and z, wherein:
# x is an integer, y is +, -, *, or /, z is an integer

# Taking Input
expression = input ("Tell the expression : ")
# Splitiing string
x , y , z = expression.split()

# coverting into float
x = float(x)
z = float(z)

# Using conditionals to perform desried task
if y == "+":
    result = x + z
elif y == "-":
    result = x - z
elif y == "*":
    result = x * z
elif y == "/":
    if z == 0 :
     print("Denominator cannot be zero.")
     exit()
    else:
        result = x / z
else:
    print("Operator Not Found")
    exit()

print(f"{result:.1f}")


