from twttr import shorten
def test_vowels():
   for i in ["A","E","I","O","U","a","e","i","o","u"]:
    assert  shorten(i) == ""
def test_sentences():
     assert shorten('Hello') == "Hll"
     assert shorten('twitter') == "twttr"
     assert shorten('AHMAD') == "HMD"
     assert shorten('MAD1') == "MD1"
     assert shorten('1Mad') == "1Md"
     assert shorten("Hello!") == "Hll!"
     assert shorten("What's up?") == "Wht's p?"