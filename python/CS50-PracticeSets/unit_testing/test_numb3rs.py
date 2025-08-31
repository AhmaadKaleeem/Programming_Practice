from numb3rs import validate
def test_wrong_char():
    assert validate("152.045.a45.63") == False
    assert validate("123.045.bbb.52") == False
    assert validate("123.045.aaa.45") == False
    assert validate("123.ccc.a45.33") == False
    assert validate("ddd.111.a45.0") == False
    assert validate("255.111.245.2a") == False
def test_invalid_digits():
    assert validate("1.111.266.69") == False
    assert validate("12.266.1.20") == False
    assert validate("256.2.25.266") == False
    assert validate("1.1.1.1") == True
    assert validate("0.0.0.266") == False
    assert validate("255.111.256.255") == False
    assert validate("255.111.255.255") == True
def test_invalid_syntax():
        assert validate("0.12.156.255") == True
        assert validate("250.111.25.1") == True
        assert validate("10.15.256.255") == False
        assert validate("101.115.2.2") == True
        assert validate("101.115.2.25") == True
        
    