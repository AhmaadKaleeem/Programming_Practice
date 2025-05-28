#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Player.h"
#include "match.h"
#include "team.h"
using namespace std;

namespace Utility {
    void log_adminaction(const string& action);  
    void saveplayer_tofile(const Player& p);     
    void loadplayers_fromile(vector<Player*>& players);  
    void savematch_tofile(const Match& m);       
    void loadmatches_fromfile(vector<Match*>& matches); 
    bool isValidSport(const string& sport);
    static bool save_team_to_file(const Team& team, const string& filename);
    static bool load_team_from_file(Team& team, const string& filename);
}


