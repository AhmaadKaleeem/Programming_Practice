months = [
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
]

while True:
    try:
        date = input("Date: ")
        date = date.strip()

        if "/" in date:
            month, day, year = date.split("/")
            month, day, year = int(month), int(day), int(year)
        elif "," in date:
            monthname, day, year = date.replace(",", "").split()
            month = months.index(monthname) + 1
            day, year = int(day), int(year)
        else:
            raise ValueError

        if not (1 <= month <= 12 and 1 <= day <= 31):
            raise ValueError

      
        print(f"{year:04}-{month:02}-{day:02}")
        break

    except (ValueError, IndexError):
        continue
