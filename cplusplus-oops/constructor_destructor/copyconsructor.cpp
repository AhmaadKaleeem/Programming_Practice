/*
Create a Laptop class with attributes: brand and RAM.
Implement three constructors:
Default constructor
Parameterized constructor
Copy constructor that copies data from another object
In main(), create an object using the parameterized constructor, then create another object using the copy constructor. Print the values.

*/
#include <iostream>
#include <string>
using namespace std;

class Laptop {
public:
    string brand;
    string ram;
// Implementing Three Constructors
Laptop(){
    brand = "HP";
    ram = "8 GB";
}

Laptop(string brand_input, string ram_input) : brand(brand_input), ram(ram_input){}

Laptop (const Laptop &hello ) : brand(hello.brand) , ram(hello.ram){}

void printspecs(){
    cout << "Brand is " << brand << " , with RAM " << ram << ". \n";
}
};

int main ( ) {
   Laptop hello;
   Laptop helloo("Lenovo","16 GB");
   Laptop hellooo = helloo;

   // As Constructor are called, now outputing specs
   hello.printspecs();
   helloo.printspecs();
   hellooo.printspecs();
   
   

}

