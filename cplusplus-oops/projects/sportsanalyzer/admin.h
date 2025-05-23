#pragma once
#include <string>
using namespace std;

class Admin {
public:
    bool login();  
    void adminmenu(); 
    void log_tofile(const string& action);  

private:
    void addTournament();
    void deleteTournament();
    void addTeam();
    void deleteTeam();
    void addPlayerToTeam();
    void addMatch();
    void addStats();
    void displayTournaments();
};
