import pytest
from fuel import convert, gauge


def test_convert_valid():
    assert convert("1/2") == 50
    assert convert("3/4") == 75
    assert convert("0/1") == 0
    assert convert("1/1") == 100

def test_convert_errors():
    try:
        convert("3/0")
    except ZeroDivisionError:
        pass
    else:
        assert False, "Expected ZeroDivisionError"
    try:
        convert("5/3")
    except ValueError:
        pass
    else:
        assert False, "Expected ValueError"

    try:
        convert("a/b")
    except ValueError:
        pass
    else:
        assert False, "Expected ValueError"
def test_gauge():
    assert gauge(0) == "E"
    assert gauge(1) == "E"
    assert gauge(99) == "F"
    assert gauge(100) == "F"
    assert gauge(50) == "50%"
    assert gauge(75) == "75%"
