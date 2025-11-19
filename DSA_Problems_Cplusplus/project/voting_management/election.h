#pragma once
#include "voter_management.h"
#include "vote_queue.h"
#include "ledger.h"
#include <voter.h>
#include <libraries.h>
using namespace std;
class Election
{
public:
    Election(VoterManager *vm);
    void add_mpa_candidate(const string &name, const string &symbol, const string &cnic);
    void add_mna_candidate(const string &name, const string &symbol, const string &cnic);
    void display_mpa() const;
    void display_mna() const;
    void authenticate_voter(const string &cnic, const string &password);
    void cast_mpa_vote(const string &cnic);
    void cast_mna_vote(const string &cnic);
    void tally_mna_results();
    void tally_mpa_results();
    int get_mna_candidate_votes(const string &c_cnic, const string &c_name) const;
    int get_mpa_candidate_votes(const string &c_cnic, const string &c_name) const;
    void winner_mpa() const;
    void add_mna_admin();
    void add_mpa_admin();
    void verify_ledger_admin();
    void display_ledger();
    void winner_mna() const;

private:
    string mna_winner_cnic;
    string mpa_winner_cnic;
    bool has_voter_voted_mna(const string &cnic) const;
    bool has_voter_voted_mpa(const string &cnic) const;
    void record_mna_vote(const string &candidate_name);
    void record_mpa_vote(const string &candidate_name);
    bool validate_candidate_cnic(const string &cnic);
    

    struct Candidate
    {

        string name;
        string symbol;
        string cnic;
        int constituency_na;
        int provisional_pp;

        Candidate(const string &c_name, const string &c_symbol, const string &c_cnic, int c_na, int c_pp) : name(c_name), symbol(c_symbol), cnic(c_cnic), constituency_na(c_na), provisional_pp(c_pp) {}
    };
    Ledger ledger;
    Province province;
    char province_name;
    VoterManager *manage_votes; // manage voter
    VoteQueue queue_votes;      // obkect to store votes
    unordered_map<string, int> mpa_votes;
    unordered_map<string, int> mna_votes;
    vector<Candidate> mna_candidates;
    vector<Candidate> mpa_candidates;

    unordered_map<int, string> *candidate_selected_area = nullptr;
    bool validate_provincial_seat(Province p, int seat);
    bool validate_national_assembly_seat(int seat);
    void select_candidate_province();
  
};