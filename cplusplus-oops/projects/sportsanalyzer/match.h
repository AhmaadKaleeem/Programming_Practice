#pragma once
#include <string>
using namespace std;

class Match {
private:
    string team_A , team_B;
    int score_A, score_B;
    string winner;
    string date;

public:
    Match();
    Match(string t_A = "", string t_B = "", int s_A = 0, int s_B = 0, string date = "");
    void decide_winner();
    void displaymatch() const;
};
