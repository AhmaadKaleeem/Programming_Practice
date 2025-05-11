#pragma once
#include <iostream>
using namespace std;

class Admin {
public:
    bool login();  
    void adminmenu(); 
    void log_tofile(const string& action); 
};
