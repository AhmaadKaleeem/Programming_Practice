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
};
