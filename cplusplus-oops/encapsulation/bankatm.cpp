/*
Create a BankAccount class with:
✔ Private attributes: accountNumber, balance, pin
✔ A constructor to initialize values
✔ Encapsulated functions:
•	setPin(int newPin) → Changes PIN only if it's 4 digits
•	deposit(double amount) → Adds money if amount > 0
•	withdraw(double amount, int enteredPin) → Allows withdrawal only if the PIN is correct
•	displayBalance(int enteredPin) → Shows balance only if PIN is correct

*/

#include <iostream>
#include <string>
using namespace std;

// Creating Object Of BankAccount

class BankAccount{
// Encapsulating Private Attributes
private:
     const int accountnumber;
     double balance;
     int pin;
public:
  // Creating Constructor
  BankAccount(int accno, double bal, int userpin) : accountnumber(accno),balance(bal),pin(userpin) {}

  // Creating Functions
  void setpin(int newpin) {
    if ((pin >= 1000 && pin <=9999)){
        pin = newpin;
        cout << "Your pin have been successfully changed. \n\n";
    }
    else {
        cout << "Error! Pin must consist of 4 digits and doesn't start with a 0 digit. \n\n";
    }
}
  void deposit(double amount){
    if (amount > 0) {
        balance += amount;
        cout << "You have successfuly deposited Rs. " << amount << ".\n\n";
    }
    else {
       cout << "Error! Deposit money must be greater than 0. \n\n";
    }
    }
   
  void withdraw(double amount,int entpin){
    if (entpin == pin) {
       if(amount > 0 && balance >=amount ){
        balance -= amount;
        cout << "You have successfuly withdraw Rs. " << amount << ".\n\n";
       }
       else if (amount<=0){
        cout << "Please enter amount greatr than 0.\n\n";
       }
       else if (balance < amount){
        cout << "Your account doesn't have sufficient funds. \nPlease try depositing monrey into account.\n";
        cout << "You have balance of Rs. " << balance << ".\n\n";
       }
    }
    else {
       cout << "Error! Please enter correct pin. \n\n";
    }
    }

    void dispaybalance (int entpin){
        if (entpin == pin) {
            cout << "Dear, You have Rs. " << balance<< " in your account against account number " << accountnumber << ".\n\n";
        }
        else {
            cout << "Error! Please enter correct pin.\n\n";
        }
    }
  
};  

int main() {
    int option,pin;
    double money;
    BankAccount acc1(123456,0,5520);
    cout << "\t\t\t\t Banking Management  \n";
    do {cout << "1. Deposit Money \n" << "2. Withdraw Money \n" << "3. Change Pin \n" << "4. Display Balance \n" << "5. Exit"; 
   cout << "\nSelect the option to perform operation :  ";
   cin >> option;
   if (option == 1) {
    cout << "Enter the money to deposit : ";
    cin >> money;
    acc1.deposit(money);
   }
   else if (option==2) {
    cout << "Enter the money to withdraw : ";
    cin >> money;
    cout << "Enter your 4 digit pin : ";
    cin >> pin;
    acc1.withdraw(money,pin);
   }
   else if (option==3) {
   cout << "Enter your 4 digit pin : ";
   cin >> pin;
   acc1.setpin(pin);
   }
   else if (option==4) {
    cout << "Enter your 4 digit pin :";
    cin >> pin;
    acc1.dispaybalance(pin);
   }
   else if (option==5) {
   cout << "Exiting the system ";
   }
   else {
  cout << "Enter a valid option from 1 to 5 \n";
   }
    }
    while (option != 5);


}