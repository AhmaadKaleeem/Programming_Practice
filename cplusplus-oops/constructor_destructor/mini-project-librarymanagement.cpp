/*
Create a Library system that manages books.
Implement a class Book with:
title, author, isbn (book ID)
A constructor to initialize values.
A destructor to print "Book removed: [title]".
Implement another class Library with:
An array of Book objects (max 5).
A function addBook() to store books.
A function showBooks() to display all books.
In main(), add books and display them.
*/
#include <iostream>
#include <string>
using namespace std;

class Book{
    public:
    string title;
    string author;
    int isbn;
// Making Parameterized Constructor

Book(const string& u_title , const string& u_author , const int& u_id) : title(u_title), author(u_author) , isbn(u_id) {}

~Book(){
    cout << "Book Removed : " << title;
}

};

class Library {
private:
    int count ;
    Book books[5];
public :
    void addbook () 
    {
       
    }
};