/*

Create an abstract class PaymentMethod with a function pay().
Implement two classes CreditCard and Cash, overriding pay() accordingly.

*/

#include <iostream>
using namespace std;

class PaymentMethod{
public:
    virtual void pay() = 0;
};

class CreditCard : public PaymentMethod{
    public :
    void pay() override {
        cout << "Payed With Credit Card\n";
        cout << "Thanks For Your Payment \n ";
    }
};


class Cash : public PaymentMethod{
    public :
    void pay() override {
        cout << "Payed With Cash \n";
        cout << "Thanks For Your Payment \n ";
    }
};

int main(){
    int option;
CreditCard paycc;
Cash paycash;

cout << "You are One Step Close To Complete Your Payment. \n";
cout << "1. Cash Payment \n" << "2. Credit Card Payment \n";
cout << "Enter Your Payemnt Type: ";
cin >> option;
switch (option)
{
case 1:
     paycash.pay();
    break;
case 2:
     paycc.pay();
     break;
default:
  cout << "Enter Valid Option \n";
    break;
}

}