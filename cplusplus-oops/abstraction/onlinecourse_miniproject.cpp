/*
Abstract Class: User

Pure virtual function: accessCourse()

Derived Classes:

Student → accessCourse(): prints enrolled course list

Instructor → accessCourse(): prints course material upload options

Add constructor and member functions as needed.
Build main() to create users and call accessCourse().
*/
#include <iostream>
using namespace std;
class User{
public:
    virtual void accesscourse() = 0 ;
}; 

class Student : public User{
    private :
    string stdname;
    string cousres[3] ;
    public:
     Student  (string username) : stdname(username) {}
};