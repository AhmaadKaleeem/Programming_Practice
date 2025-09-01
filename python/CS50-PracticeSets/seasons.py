# In a file called seasons.py, implement a program that prompts the user for their date of birth in YYYY-MM-DD format and then sings prints how old they are in minutes, rounded to the nearest integer, using English words instead of numerals, just like the song from Rent, without any and between words. Since a user might not know the time at which they were born, assume, for simplicity, that the user was born at midnight (i.e., 00:00:00) on that date. And assume that the current time is also midnight. In other words, even if the user runs the program at noon, assume that it’s actually midnight, on the same date.
import num2words
import datetime
import re
import sys
def main():
    current_date = get_current_time() 
    user_birth_date = get_user_dob()
    age_time_in_words = calculate_age_time(user_birth_date,current_date)
    print(age_time_in_words)

def get_current_time():
    return datetime.date.today()

def get_user_dob():
    dob = input("Date of Birth: ").strip()
    if not re.search(r"^\d{4}-\d{2}-\d{2}$",dob):
        sys.exit("Invalid date")
    return datetime.date.fromisoformat(dob)

def calculate_age_time(dob,current_date):
    age = (current_date - dob).days
    age = round(age * 24 * 60)
    age_in_words = num2words.num2words(age,to="cardinal")
    age_in_words = age_in_words.capitalize().replace("and","")
    return age_in_words

if __name__ == "__main__":
    main()