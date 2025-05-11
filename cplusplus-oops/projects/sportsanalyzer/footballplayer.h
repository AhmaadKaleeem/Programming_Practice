#pragma once
#include "Player.h"
using namespace std;

class FootballPlayer : public Player {
private:
    int goals;
    int assists;
    int yellow_cards;

public:
    FootballPlayer();
    FootballPlayer(string name = "", int age = 0, string team = "");
    void scoregoal();
    void addassist();
    void display() const override;
};
