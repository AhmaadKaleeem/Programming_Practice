#include "libraries.h"
#include "utilities.h"
using namespace std;

string hide_password()
{
  char c;
  string pass;
  while ((c = _getch()) != '\r') // enter to end loop
  {
    if (c == '\b')
    {
      if (!pass.empty())
      {
        cout << "\b \b";
        pass.pop_back();
      }
    }
    else
    {
      pass += c;
      cout << "*";
    }
  
  
  }
   cout << "\n";
    return pass;
}