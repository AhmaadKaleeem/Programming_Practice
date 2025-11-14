#pragma once
#include <string>
#include <iostream>
#include <unordered_set>
#include "voter_management.h"
#include "vote_queue.h"
using namespace std;
class Election{
public:
    Election(VoterManager* vm);
    void add_mpa_canidate(const string& name);
    void add_mna_canidate(const string& name);
    void display_mpa() const;
    void display_mna() const;
    void authenticate_voter(const string& cnic, const string& password);
    void cast_mpa_vote(const string& cnic );
    void cast_mna_vote(const string& cnic );
    void tally_mna_results() const;
    void tally_mpa_results() const;
    int get_mna_candidate_votes(const std::string& name) const;
    int get_mpa_candidate_votes(const std::string& name) const;


private:
    bool has_voter_voted_mna(const std::string& cnic) const;
    bool has_voter_voted_mpa(const std::string& cnic) const;
    void record_mna_vote(const std::string& candidate_name);
    void record_mpa_vote(const std::string& candidate_name);

    VoterManager* manage_votes;
    VoteQueue queue_votes;
    unordered_map<string,int> mpa_votes;
    unordered_map<string,int> mna_votes;
    unordered_set<string> mna_canidates;
    unordered_set<string> mpa_canidates;

    
};