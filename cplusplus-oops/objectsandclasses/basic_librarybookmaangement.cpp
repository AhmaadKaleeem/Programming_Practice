/*
Create a Book class with attributes:
title (string)
author (string)
price (float)
Implement a member function showDetails() to print book details.
In main(), create an array of 3 books and display their details.

*/

#include <iostream>
using namespace std;

class Book
{
public:
    string title;
    string author;
    float price;

    // member function

    void showDetails()
    {
        cout << "Book Name : " << title << ", price : " << price << " & Author : " << author << "\n";
    }
};

int main()
{
    Book Name[3];

    // Using Array For Input
    Name[0].title = "Why Us?";
    Name[0].author = "Prof. Ali";
    Name[0].price = 500;
    Name[1].title = "Intro to C++";
    Name[1].author = "Mr. Bilal Khan";
    Name[1].price = 100;
    Name[1].title = "intro to Gen Ai";
    Name[1].author = "Ahmad Kaleem";
    Name[1].price = 550;

    for (int i = 0; i < 3; i++)
    {
        Name[i].showDetails();
    }
}