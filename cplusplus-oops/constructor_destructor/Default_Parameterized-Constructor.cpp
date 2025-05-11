/*Create a Car class with two attributes: brand and price.
Implement two constructors:
A default constructor that sets brand = "Unknown" and price = 0.
A parameterized constructor that sets values based on user input.
In main(), create two objects (one with default constructor, one with parameters) and display their details.*/

#include <iostream>
#include <string>
using namespace std;

// Creating Class Car
class Car {
public:
      string brand;
      double price;
// Default Constructor
    Car(){
        brand = "Unknown";
        price = 0;
    }
// Parameterized Constructor
    Car (string userbrand, double userprice){
        brand = userbrand;
        price = userprice;
    }

    void showdetails(){
        cout << "Car Price " << price <<endl;
        cout << "Car Brand " << brand << endl;
    }
};

int main(){
  
    Car no1 ;
    Car no2 = Car("Toyota Supra", 500000)  ;
    no1.showdetails();
    no2.showdetails();
    return 0;
}

