from bank import value

def test_values():
    assert value("hello") == 0
    assert value("h") == 20
    assert value("fdghs") == 100
def test_case_insensitivity():
    assert value("heLLO") == 0
    assert value("HELLO") == 0
    assert value("H") == 20
    assert value("HDFHYASYFS") == 20
    assert value("FdgYDs") == 100
def test_case_leading_space():
    assert value("       hello") == 0
    assert value("    hesa") == 20
    assert value("                     haHa") == 20
    assert value("                aFdgYDs") == 100
def test_all_errors():
    assert value("       hELlo") == 0
    assert value("       hello") == 0
    assert value("    Hio") == 20
    assert value("    h") == 20
    assert value("                     haHa") == 20
    assert value("                     Audfsy!") == 100
    
    
    
