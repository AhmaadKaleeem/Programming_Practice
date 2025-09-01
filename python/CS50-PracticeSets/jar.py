class Jar:
    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError("Negative Integer")
        self.__capacity = capacity
        self.__availble_cookies = 0
    def __str__(self):
        return("🍪" * self.__availble_cookies)

    def deposit(self, n):
        if self.__availble_cookies + n > self.__capacity:
                raise ValueError("Jar Capacity Exceeded")
        self.__availble_cookies += n
        
    def withdraw(self, n):
        if self.__availble_cookies - n < 0 :
                raise ValueError("Not Enough Cookies")
        self.__availble_cookies -= n

    @property
    def capacity(self):
        return self.__capacity

    @property
    def size(self):
        return self.__availble_cookies
        