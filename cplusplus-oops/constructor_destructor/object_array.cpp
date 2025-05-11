/*
Create a Student class with name and rollNumber.
Use a constructor to initialize these values.
In main(), create an array of objects (3 students) and initialize them using a constructor.
Print details of all students.

*/
#include <iostream>
#include <string>
using namespace std;

class Student{
public:
        string name;
        int rollno;
// Using Constructor To Intialize
  Student (const string &username , const int &user_rollno ) : name(username),rollno(user_rollno){}

  void printdetails() {
    cout << "Student Name : " << name << ", Roll No " << rollno << "\n";
  }
  
};

int main ( ) {
    Student student [3] = {
        Student ("Ali",1), 
        Student ("Mir",2), 
        Student ("Aly",3) 
    };
for (int i = 0 ; i<3 ; i++ ){
    student[i].printdetails();
}

}