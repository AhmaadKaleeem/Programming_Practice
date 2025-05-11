#pragma once
#include "Player.h"
using namespace std;

class CricketPlayer : public Player {
private:
    int runs;
    int wickets;
    float batting_avg;
    float bowling_avg;

public:
    CricketPlayer();
    CricketPlayer(string name = "", int age = 0, string team = "");
    void addruns(int runs);
    void addwickets(int wickets);
    void display() const override;
};
