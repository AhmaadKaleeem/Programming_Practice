/* Write a class declaration named Circle with a private member variable named radius. Write
set and get functions to access the radius variable, and a function named getArea that
returns the area of the circle. The area is calculated as 3.14159 * radius * radius. Add a
default constructor to the Circle class, the constructor should initialize the radius member
to 0. */

#include <iostream>
using namespace std;

class Circle {
    private : 
    double radius;

    public :
    Circle() {
      radius = 0;
    }

    void setradius(double r) {
        radius = r ;
    }
    
    double getradius (){
        return radius;
    }
    double getarea() {
        return radius * radius * 3.14159;}
    };
     
    int main (){

        Circle c1;
       double r;
        cout << "Enter the radius : " ;
        cin >> r ;
        c1.setradius(r);
        cout << " Updated Area " << c1.getarea();
           return 0;
    }