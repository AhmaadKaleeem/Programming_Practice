import pytest
from datetime import date
from seasons import calculate_age_in_minutes


def test_one_day_old():
    dob = date(1999, 12, 31)
    today = date(2000, 1, 1)
    result = calculate_age_in_minutes(dob, today)
    assert "One thousand, four hundred forty minutes" in result


def test_one_year_old():
    dob = date(1999, 1, 1)
    today = date(2000, 1, 1)
    result = calculate_age_in_minutes(dob, today)
    assert "Five hundred twenty-five thousand, six hundred minutes" in result


def test_multiple_years_old():
    dob = date(1995, 1, 1)
    today = date(2000, 1, 1)
    result = calculate_age_in_minutes(dob, today)
    allowed_chars = set("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ -,")
    for char in result.replace(" minutes", ""):
        assert char in allowed_chars
