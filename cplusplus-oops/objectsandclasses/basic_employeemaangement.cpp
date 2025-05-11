/*
Create an Employee class with:
name (string)
ID (int)
salary (float)
Implement member functions:
setDetails(): Takes input for name, ID, and salary.
showDetails(): Displays employee details.
In main(), create an array of employees, input their details, and display them.

*/

#include <iostream>
using namespace std;

class Employee {
public:
     string name;
     int id;
     float salary;

         // member function
   void setDetails(string namee,int idd,float salaryy) {
    name = namee; 
        id = idd;
        salary = salaryy;
   }
   void showDetails(){
    cout << "Employee Name : " << name << ", Salary : " <<  salary << " & ID : " << id << "\n";
   }
};

int main () {
    Employee Name [2];
    
    // Adding Data for Array 1 and 2 manully 
    Name[0].name="Ali";
    Name[0].id=756;
    Name[0].salary=520000;
    Name[1].name="Ali 2";
    Name[1].id=7526;
    Name[1].salary=52020;
    
    // showing manual added details
    cout << "Manually Added Deatails " << "\n\n";
    Name[0].showDetails();
    Name[1].showDetails();
   
    // Using Setter To Add Details
    Name[0].setDetails("Ahmad",786,2000);
    Name[1].setDetails("Ahmad 2",787,20000);

    // Showing Details using Setters
    cout << "\n\n" << "Added Deatails using Setters" << "\n\n";
    Name[0].showDetails();
    Name[1].showDetails();


}