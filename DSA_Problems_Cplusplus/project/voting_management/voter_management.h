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
    bool authenticate_voter(const string& id, const string & pass);
    void display_all_voters();        
    bool check_cnic(const string & id);    
    bool check_voter(const string& cnic ); 
};
