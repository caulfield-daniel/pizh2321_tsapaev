import pytest
from roman import Roman

def test_initialization_with_arabic():
    assert Roman(1).arabic == 1
    assert Roman(3999).arabic == 3999

def test_initialization_with_roman():
    assert Roman("I").arabic == 1
    assert Roman("MMMCMXCIX").arabic == 3999

def test_invalid_arabic_initialization():
    with pytest.raises(ValueError):
        Roman(0)
    with pytest.raises(ValueError):
        Roman(4000)
    with pytest.raises(ValueError):
        Roman(-1)

def test_invalid_roman_initialization():
    with pytest.raises(TypeError):
        Roman(10.5)

def test_addition():
    assert (Roman(1) + Roman(1)).arabic == 2
    assert (Roman(1) + 2).arabic == 3
    assert (Roman(3998) + 1).arabic == 3999

def test_subtraction():
    assert (Roman(2) - Roman(1)).arabic == 1
    assert (Roman(3) - 1).arabic == 2
    with pytest.raises(ValueError):
        Roman(1) - 2

def test_multiplication():
    assert (Roman(2) * Roman(3)).arabic == 6
    assert (Roman(3) * 2).arabic == 6
    with pytest.raises(ValueError):
        Roman(2000) * 3

def test_division():
    assert (Roman(6) // Roman(2)).arabic == 3
    assert (Roman(6) // 2).arabic == 3
    with pytest.raises(ValueError):
        Roman(1) // 2

def test_to_roman():
    assert Roman.to_roman(1) == "I"
    assert Roman.to_roman(3999) == "MMMCMXCIX"
    with pytest.raises(ValueError):
        Roman.to_roman(0)
    with pytest.raises(ValueError):
        Roman.to_roman(4000)

def test_to_arabic():
    assert Roman.to_arabic("I") == 1
    assert Roman.to_arabic("MMMCMXCIX") == 3999
