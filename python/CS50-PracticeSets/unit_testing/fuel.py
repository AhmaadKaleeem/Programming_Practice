
def main():
    fraction = input("Fraction: ")
    try:
        percentage = convert(fraction)
        print(gauge(percentage))
    except (ValueError, ZeroDivisionError) as e:
        print(e)

def convert(fraction) :
    try:
        x, y = fraction.split("/")
        x, y = int(x), int(y)

        if y == 0:
            raise ZeroDivisionError

        if x > y:
            raise ValueError

        percentage = round((x / y) * 100)
        return percentage

    except ValueError:
        raise ValueError("Invalid fraction format")
    except ZeroDivisionError:
        raise ZeroDivisionError("Denominator cannot be zero")


def gauge(percentage):
    if percentage <= 1:
        return "E"
    elif percentage >= 99:
        return "F"
    else:
        return f"{percentage}%"


if __name__ == "__main__":
    main()