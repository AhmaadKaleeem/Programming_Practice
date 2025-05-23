#pragma once
#include <vector>
#include "Team.h"
using namespace std;

class Tournament {
private:
    string name;
    string sport;
    vector<Team> teams;

public:
    Tournament();
    Tournament(string name = "", string sport = "");
    void addteam(const Team& newteam);
    void displaytournament() const;
    Team* findTeam(const string& name);
    void deleteteam(const string& name); 
    string getname() const;
    string getsport() const;
    bool teamExists(const string& teamname) const;
    vector<Team>& getTeams();

};
