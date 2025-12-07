#pragma once
#include "libraries.h"
#include "election.h"
using namespace std;

class Election;
class Admin
{

public:
    Admin(Election *e);
    bool authenticate_admin();
    void admin_panel();
    unordered_map<string, string> intialize_credentionals();
    unordered_map<string, string> login_admin;
    Election *election;

};