#pragma once
#include "libraries.h"
using namespace std;

class LedgerBlock
{
public:
  int index;
  string candidate_cnic;
  string voter_cnic;
  string vote_type;
  string timestamp;
  string current_hash;
  string prev_hash;

  LedgerBlock *next;
  LedgerBlock(int u_index, const string &u_c_cnic, const string &u_vcnic, const string &u_type, const string &u_hash);
  
  // Constructor for rESTORING blocks from file (uses saved timestamp and hash)
  LedgerBlock(int idx, const string &c_cnic, const string &v_cnic,
              const string &t, const string &ts, const string &h, const string &ph);
  string get_time();

  string calculate_hash() const;
};

class Ledger
{

public:
  Ledger();
  ~Ledger();
  LedgerBlock *head;
  LedgerBlock *tail;
  int size;
  string get_last_hash() const;
  void restore_block(int index, const string &candidate_cnic, const string &voter_cnic,
                     const string &type, const string &timestamp,
                     const string &hash, const string &prev_hash); // will be used in filehandling
  void add_block(const string &candidiate, const string &voter, string &type);
  bool verify_ledger() const;
  void display_ledger() const;
};