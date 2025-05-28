#pragma once
#include <string>
#include "Team.h"

using namespace std;

class Match {
    string tournamentName;
    string teamA;
    string teamB;
    int scoreA;
    int scoreB;

public:
    Match(const string& tourn, const string& a, const string& b, int sa, int sb);
    
    string getTournament() const;
    string getTeamA() const;
    string getTeamB() const;
    int getScoreA() const;
    int getScoreB() const;

    void display() const;
};
