/*
Create a Thermostat class that controls the temperature of a house.
✔ Private attributes: currentTemp, minTemp, maxTemp
✔ A constructor to initialize values
✔ Encapsulated functions:
•	setTemperature(double temp) → Only sets the temp if it's between minTemp and maxTemp
•	increaseTemp(double value) → Raises temp within limit
•	decreaseTemp(double value) → Lowers temp within limit
•	displayTemp() → Prints the temperature

*/

#include <iostream>
#include <string>
using namespace std;

// Creating Object Of Thermostat 
class Thermostat {
private: 
 double currenttemp;
 double maxtemp;
 double mintemp;
public : 
// Creating Constructor
Thermostat(double ctemp , double hightemp , double lowtemp) : currenttemp(ctemp) , maxtemp(hightemp),mintemp(lowtemp){}
// Creating Functions
void settemp(double temp){
    if (temp <= maxtemp && temp >= mintemp ){
        currenttemp = temp;
        cout << "Temperature set to be " << currenttemp << " degree Celsius. \n";
    }
    else if (temp > maxtemp){
        cout << "Temperture cannot exceed maximum temperature of " << maxtemp << ".\n";
    }
    else if (temp < mintemp){
        cout << "Temperture cannot be lower minimum temperature of " << maxtemp << ".\n";
    }
}
void increasetemp(double temp){
    currenttemp += temp;
    if (currenttemp <= maxtemp && currenttemp >= mintemp ){
        cout << "Increased value of temperature by " << temp << " degree Celsius. \n";
        cout << "Temperature set to be " << currenttemp << " degree Celsius. \n";
    }
    else if (currenttemp > maxtemp){
        cout << "Temperture cannot exceed maximum temperature of " << maxtemp << ".\nPlease increase temperature within limit.\n";
        currenttemp -= temp;
    }
}
void decreasetemp(double temp){
    currenttemp -= temp;
    if (currenttemp <= maxtemp && currenttemp >= mintemp ){
        cout << "Decreased value of temperature by " << temp << " degree Celsius. \n";
        cout << "Temperature set to be " << currenttemp << " degree Celsius. \n";
    }
    else if (currenttemp < mintemp){
        cout << "Temperture cannot be lower minimum temperature of " << maxtemp << ".\nPlease increase temperature within limit.\n";
        currenttemp += temp;
    }
}
double displaytemp(){
    return currenttemp;
}
};
 int main() {
    int option;
    double usertemp;
   Thermostat house1(26,36.5,20);
   cout << "\t\t\t\t Digital Thermostat  \n";
    do {
        cout << "1. Display Temperature \n" << "2. Increase Temprature \n" << "3. Decrease Temperature \n" << "4. Set Temperature\n" << "5. Exit"; 
        cout << "\nSelect the option to perform operation :  ";
        cin >> option;
        switch (option)
        {
        case 1 :
            cout << "Current temperature is " << house1.displaytemp() << " degree Celsius.\n\n";
            break;
        case 2 :
            cout << "Enter the value of temperature you want to increase : ";
            cin >> usertemp;
            house1.increasetemp(usertemp);             
            break;
        case 3 :
            cout << "Enter the value of temperature you want to decrease : ";
            cin >> usertemp;
            house1.decreasetemp(usertemp);    
            break;
        case 4 :
            cout << "Please enter value to set the temperature : ";
            cin >> usertemp;
            house1.settemp(usertemp);
            break;
         case 5 :
            cout << "Exiting the System \n\n";
            break;
        default:
            cout << "Please Select a valid option \n\n";
            break;
        }
}
while (option != 5);
}