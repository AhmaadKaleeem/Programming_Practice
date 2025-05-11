/*
Task:

Create a Car class with the following attributes:
brand (string)
model (string)
price (float)
Implement a member function displayDetails() to print the car's details.
In main(), create two car objects and display their details.


*/


#include <iostream>
using namespace std;

class Car {
 public :
    string brand;
    string model;
    float price;
    
    // member function
    
    void dispalydetails()
    { 
        cout << "Car Brand : " << brand << ", Model : " << model << ", and Price : " << price  << " $ " <<endl;
    }
};

int main( ) {
    Car markx,supra;
    supra.brand = "Toyota" ;   markx.brand = "Toyota" ;
    supra.model = "2000" ;     markx.model = "2008" ;
    supra.price = 70000;       markx.price = 10000;     

    // Calling function to show details

    supra.dispalydetails();
    markx.dispalydetails();
}