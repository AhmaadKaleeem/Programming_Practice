/*
Suppose you have a Bank Account with an initial amount of $50 and you have to add some
more amount to it. Create a class 'AddAmount' with a data member named 'amount' with
an initial value of $50. Now make two constructors of this class as follows:
o Without any parameter - no amount will be added to the Bank Account.
o Having a parameter which is the amount that will be added to the Bank Account
o Create an object of the 'AddAmount' class and display the final amount in the Bank
Account.
*/

#include <iostream>
using namespace std;

class AddAmount {
private:
    int amount;
public:
    AddAmount() {
        amount = 50;
    }

    AddAmount(int add) {
        amount = 50 + add;
    }

    void displayAmount() {
        cout << "Final Amount in Bank Account: " << amount << " $ " << endl;
    }
};

int main() {
    int amount;
    AddAmount a1; 
    a1.displayAmount();
    cout << "Enter the Amount to be added in Bank Account : ";
    cin >> amount;
    AddAmount a2(amount);
    a2.displayAmount();

    return 0;
}
