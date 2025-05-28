#pragma once
#include "Person.h"
using namespace std;

class Player : public Person {
private:
    string position;
    string teamname;
    string sport;
    int stats;

public:
    Player();
    Player(string name = "", int age = 0, string position = "", string sport = "", string team = "");
    void display() const override;
    string get_name() const { return name; }
    void updatestats(int value);
};
