from unit_test_twtr import shorten
def test_vowels():
   for i in ["A","E","I","O","U","a","e","i","o","u"]:
    assert  shorten(i) == ""
 
