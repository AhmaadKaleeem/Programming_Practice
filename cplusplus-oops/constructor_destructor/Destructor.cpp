/*
Create a Book class with attributes: title and author.
Implement a constructor to initialize these attributes.
Implement a destructor that prints "Book destroyed: [title] by [author]".
In main(), create two Book objects and check when the destructor is called.

*/

#include<iostream>
#include<string>
using namespace std;

class Book{
public:
   string title;
   string author;
// Making Constructor Parameterized to intialize values
   Book(string usertitle,string userauthor) : title(usertitle),author (userauthor){}
// Making Destructor
  ~Book(){
  cout << "Book Destroyed: " << title << " by " << author << ".\n";
  }

};

int main () {
    // Making Object and Calling Construcor and Destructor
    Book no1 ("50 Sahdes Of Money", "Mr Ahmad");
    Book no2 ("50 Sahdes Of Cyber Security", "Mr Bilal");
    return 0;
}