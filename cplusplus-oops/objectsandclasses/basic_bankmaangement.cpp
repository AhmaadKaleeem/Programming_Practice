/*
Create a BankAccount class with attributes:
accountHolderName (string)
accountNumber (int)
balance (float)
Implement member functions:
deposit(amount): Adds amount to balance.
withdraw(amount): Deducts amount from balance if sufficient funds are available.
displayBalance(): Prints current balance.
In main(), create a bank account, deposit money, withdraw money, and display the balance.

*/

#include <iostream>
using namespace std;

class BankAccount{
public: 
    string name;
    int number;
    float balance=0;

  // Member Functions
  void deposit (int amount) {
    balance = balance + amount;
  }
  void withdraw (int amount) {
  if (balance >= amount ){
    balance = balance - amount; }
  } 
  void display ( ) {
   cout << "Balance in your Account is : " << balance;
  }

};

int main() {
 BankAccount No1; 
  int amount,withdraw;
 // Asking User To Make Bank Account 
 No1.name = "Ahmad";
 No1.number = 67435;

// Calling Member Function To Withdraw , Deposit and Show
cout << "Please Enter Deposit Amount : " ;
cin >> amount; 
No1.deposit(amount);

cout << "Please Enter Withdrawal Amount : " ;
cin >> withdraw; 
No1.withdraw(withdraw);

No1.display();



}