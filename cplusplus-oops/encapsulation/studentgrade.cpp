/*
Create a Student class that stores marks securely.
✔ Private attributes: name, marks (array of 5 subjects), averageGrade
✔ A constructor to initialize the name
✔ Encapsulated functions:
•	setMarks(int index, int mark) → Only allows valid marks (0-100)
•	calculateAverage() → Computes the average
•	displayGrades() → Prints all marks and the average
*/
#include <iostream>
#include <string>
#include<array>
using namespace std;

class Student{
private:
   double avggrade;
   string name;
    int marks[5];
public:
  Student( string stdname ) : name(stdname) {}
  
  void setmarks(int index , int usermarks){
    if (usermarks >= 0 && usermarks <=100){
        marks[index] = usermarks;
    }
    else {
        cout << "Invalid Marks, Please Enter Valid Marks 0 - 100 \n\n";
    }
  }

  double calaverage(){
    double average;
    for (int i = 0 ; i < 5 ; i++){
        average += marks[i];
    }
    average = average/5;
    return average;
  }

  void displaymarks(){
    string markssubjects[5] = {"PF","ICT","DB","DLD","OOP"};
    double average=0.0;
    cout << "-------------  Marks  -------------\n";
    for (int i = 0 ; i < 5 ; i++){
       cout << markssubjects[i] << ": " << marks[i] << "\n" ;
    }
    cout << "\n";
    for (int i = 0 ; i < 5 ; i++){
        average += marks[i];
    }
    cout << "-------------  Average  -------------\n";
    cout << "Average: " << average/5 << "\n\n";

  }
};

int main() {
    Student no1("Sameer");
    int marks;
    string markssubjects[5] = {"PF","ICT","DB","DLD","OOP"};
    cout << "----Please Enter Marks ----- \n\n";
    for (int i = 0; i<5 ; i++){
      cout << "Enter Marks For " << markssubjects[i] << ": ";
      cin >> marks;
      no1.setmarks(i,marks);
    }
    cout << "\n";
   no1.displaymarks();
}