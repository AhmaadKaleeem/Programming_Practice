#pragma once
#include <vector>
#include "cricketplayer.h"
#include "footballplayer.h"
using namespace std;

class Team {
private:
    string teamname;
    string sport;
    vector<Player*> players;

public:
    Team();
    Team(string name = "", string sport = "");
    void addPlayer(Player* newplayer);
    void displayteam() const;
    string getname() const;
};
