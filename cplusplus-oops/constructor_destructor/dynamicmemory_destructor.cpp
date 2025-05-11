/*
Create a BankAccount class with attributes accountHolder and balance.
Use a constructor to initialize attributes dynamically (new keyword).
Use a destructor to delete memory (delete keyword).
In main(), create an object and observe when memory is freed.
*/

#include <iostream>
#include <string>
using namespace std;

class BankAccount{
    public:
            string name;
            double balance;;
    // Using Constructor To Intialize
    BankAccount() {
        name = "Unknown";
        balance = 0.0;
    }
      BankAccount ( string username ,  double user_balance ) : name(username),balance(user_balance){}
    
      void printdetails() {
        cout << "BankAccount Holder Name : " << name << ", Balance " << balance << "\n";
      }

      ~ BankAccount(){
        cout << "Deleted Bank Acoount of " <<name;
      }
      
    };
    
    int main ( ) {

        int n ;
        string name; double balance;
        cout << "Enter Number of Accounts : ";
        cin >> n;
        BankAccount* bankaccounts = new BankAccount[n];
    for (int i = 0 ; i<n ; i++ ){
       cout << "Enter Name For Account # " << i +1  ; 
       cin.ignore();
       getline(cin,name);
       cout << "Enter Balance For Account # " << i +1  ;
       cin >> balance;
       bankaccounts[i]=BankAccount(name,balance);
    }

    for (int i =0;i<n ; i++){
        bankaccounts[i].printdetails();
    }
    delete[] bankaccounts;
    }