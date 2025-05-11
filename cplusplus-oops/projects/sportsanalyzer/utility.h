#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Player.h"
#include "match.h"
using namespace std;

namespace Utility {
    void log_adminaction(const string& action);  
    void saveplayer_tofile(const Player& p);     
    void loadplayers_fromile(vector<Player*>& players);  
    void savematch_tofile(const Match& m);       
    void loadmatches_fromfile(vector<Match*>& matches); 
}
