/*
Animal Sounds
Create an abstract class Animal with a pure virtual function makeSound().
Derive classes Dog and Cat, and implement makeSound() in both.

*/
#include <iostream>
using namespace std;
class Animal {
    virtual void makesound() = 0 ;
};

class Dog : Animal {
    public:
  void makesound(){
    cout << "Bark......................\n";
  }
};


class Cat : Animal {
    public:
    void makesound(){
      cout << "Meow......................\n";
    }
  };

  int main() {
   Dog dog;
   Cat cat;
   dog.makesound();
   cat.makesound();
  }