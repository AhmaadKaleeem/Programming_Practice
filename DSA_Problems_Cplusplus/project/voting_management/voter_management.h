#pragma once
#include <unordered_map>
#include "voter.h"
using namespace std;

class VoterManager {
private:
    Voter* head;   
    unordered_map<string, Voter*> voter_mapping; 

public:
    VoterManager();

    void add_voter();                
    void search_voter(string cnic);   
    void display_all_voters();             
};
