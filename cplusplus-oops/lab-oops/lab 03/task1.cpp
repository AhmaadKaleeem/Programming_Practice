// Create a Car class, where attributes associated with each car are name, registration number,
// manufacture name and year. All attributes should not be accessed directly. One can view the
// details of all cars. Note car attributes cannot be changed by any means after initialization. (Hint
// use constant objects)
#include <iostream>
#include <vector>
using namespace std;

class Car {
private:
     string name;
     string regno;
     string company;
     int year;

public:
 Car(string n, string regNum, string companyname, int yearofmanufacture) :
  name(n), regno(regNum), company(companyname), year(yearofmanufacture){}

string getname() const
{return name;}

