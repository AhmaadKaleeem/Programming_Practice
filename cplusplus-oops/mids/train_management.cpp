#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Train {
    private:
   const int max_seats = 100 ;
   int seats[100];
   static int totalbookings;
  public:
    Train (){
        intilizeseats();
    }

  void intilizeseats(){
    for (int i = 0 ; i <100 ; i++){
        seats[i] = 0; // Marked 0 as Availble
    }
  }

  void bookseat(){
    int seatno;string name,cnic; 
    cout << "Please Enter Your Name : ";
    cin >> name; 
    cout << "Please Enter Your CNIC (6-Digit) : ";
    cin >> cnic;
    cout << "Please Enter The Seat No For Reservation : ";
    cin >> seatno;

    if (seatno <= max_seats && seatno <=0 ){
        cout << "Enter Valid Seat No 1 - 100\n\n";
    } 
    else {
        if (seats[seatno-1] == 1){
            cout << "This Seat Is Already Reserved.\n\n";
        }
        else if (seats[seatno-1] == 0){
            seats[seatno-1] = 1;
            cout << "Your Seat Is Reserved.\n";
            cout << "Thanks For Reserving Seat No. " << seatno << " For Passenger Name " <<name << " . \n\n";
            totalbookings++;
        }
    }
  

  }

  void cancelseat(){
    int seatno,option;
    cout << "Enter Seat No To Cancel : ";
    cin >> seatno;
    if (seatno <= max_seats && seatno <=0 ){
      cout << "Enter Valid Seat No 1 - 100\n\n";
  } 
  else {
      if (seats[seatno-1] == 1){
          cout << "Cancelling the Seat\n";
          seats[seatno-1] = 0;
          totalbookings --;
      }
      else if (seats[seatno-1] == 0){
          cout << "This Seat Is Not Reserved.\n";
          cout << "Do you Want To Reserve The Seat ? \n Press 1 To Book \n Press 0 To Exit ";
          cout << "Enter the Option";
          cin >> option;
          switch(option) {
            case 1 :
                cout << "Reserving The Seat \n";
                seats[seatno-1] = 1;
                cout << "Your Seat Is Reserved.\n";
                cout << "Thanks For Reserving Seat No. " << seatno << " For Passenger Name " <<name << " . \n\n";
                totalbookings++;
                break;
            case 2 :
                 cout << "Exiting... \n";
                 break;
            default :
               cout << "Enter Valid Option 0 or 1 \n\n";
               break;
          }
      }
  }

  }

};