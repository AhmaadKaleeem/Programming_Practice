#include "libraries.h"
#include "console_color.h"
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

bool check_name(const string& name){
  if (name.empty()){
    red();
    cout << "Error! No Name Provided.\n";
    reset();
    return false;
  }
  for(char c : name){
     if (isdigit(c))
      {
        red();
        cout << "Error! Name Only Contains Alphabets.\n";
        reset();
        return false;
      }
  }
  return true;
}

bool check_valid_int()
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        red();
        cout << "Invalid input\n";
        reset();
        return false;  
    }
    return true;
}