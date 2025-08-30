from plates import is_valid

def test_length():
    assert is_valid("CS") == True
    assert is_valid("C") == False
    assert is_valid("COMPUTER") == False 

def test_start_with_letters():
    assert is_valid("CS50") == True
    assert is_valid("50CS") == False  

def test_numbers_position():
    assert is_valid("CS50") == True  
    assert is_valid("CS05") == False  
    assert is_valid("CS5O") == False  

def test_alphanumeric():
    assert is_valid("CS50!") == False  
    assert is_valid("CS50") == True   
