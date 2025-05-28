/*
Write a C++ program to demonstrate the addition of multiple types of data using generic
function or template.
*/

#include <iostream>
#include <string>
using namespace std;

template <typename T>
T add(T a, T b) {
    T c = a + b;
    return c;
}

int main() {

 string str1 = "Ahmad,", str2 = "Kaleem";
 int int1 = 10, int2 = 20;
 double double1 = 3.25, double2 = 55.41828;
 char c1 = 'a',  c2 = 1 ;
    cout << "After Adding: " << add(int1, int2) << ".\n";   
    cout << "After Adding: " << add(double1, double2) << ".\n";
    cout << "After Adding: " << add(str1, str2) << ".\n";
    cout << "After Adding: " << add(c1,c2) << ".\n";

}