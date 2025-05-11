/*
📌 Problem 1: Online Shopping Cart 🛒
Create a Product class with:
✔ Private attributes: name, price, stock
✔ A constructor to initialize these values
✔ Encapsulated functions:
•	setPrice(double) → Only positive prices allowed
•	buyItem(int quantity) → Reduces stock if available
•	display() → Shows product details
*/

#include <iostream>
#include <string>
using namespace std;

// Creating Object Of Product

class Product{
// Encapsulating Private Attributes
private:
     string itemname;
     double itemprice;
     int itemstock;

public:
 // Creating  Constructor
   Product(string name , double price ,int quantity) : itemname(name),itemprice(price), itemstock(quantity){}
// Using Function
 void setprice(double set_price) {
   if (set_price >= 0) 
     {itemprice = set_price;}
   else 
     {cout << "Please Enter a Positive Value For Item \n" ; }
 } 

 void buyitems(int userquantity){
   if (userquantity > itemstock) 
   { cout << "Stock Quantity Not Availble. \n";
     cout << "There are Only " << itemstock << " Items Left \n";
   }
   else if (userquantity == 0 )
   {
    cout << "You Should Buy Atleast 1 Item \n";
   }
   else {
    cout << "Bought " << userquantity << " " << itemname << "! \n";
    itemstock -= userquantity;
    cout << "Remaining Stock: " << itemstock << "\n"; 
   }
   }

   void displaydetails() {
    cout << "Item: " << itemname << ", Price: " << itemprice << ", Quantity: " <<itemstock << ". \n";
   }

 };
 int main() {
    int userquantity;
  Product laptops("Laptop", 5000 , 50);
  Product keyboards("Keyboard" , 100 , 200);
  Product graphiccards("Graphic Cards" , 2500 , 20);
  
  laptops.displaydetails();
  laptops.buyitems(40);
  laptops.setprice(5500);
  laptops.displaydetails();
  keyboards.displaydetails();
  keyboards.buyitems(200);
  keyboards.setprice(0);

 }