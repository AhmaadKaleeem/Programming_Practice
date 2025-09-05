from datetime import date, datetime
import re
import sys
import inflect


def main():
    current_date = get_current_time()
    user_birth_date = get_user_dob()
    age_time_in_words = calculate_age_in_minutes(user_birth_date, current_date)
    print(age_time_in_words)


def get_current_time():
    return date.today() 


def get_user_dob():
    dob = input("Date of Birth (YYYY-MM-DD): ").strip()
    if not re.search(r"^\d{4}-\d{2}-\d{2}$", dob):
        sys.exit("Invalid date")
    try:
        return datetime.strptime(dob, "%Y-%m-%d").date()
    except ValueError:
        sys.exit("Invalid date")


def calculate_age_in_minutes(dob, current_date):
    delta_days = (current_date - dob).days
    total_minutes = round(delta_days * 24 * 60)

    p = inflect.engine()
    age_in_words = p.number_to_words(total_minutes, andword="")
    age_in_words = age_in_words.capitalize() + " minutes"
    return age_in_words


if __name__ == "__main__":
    main()
