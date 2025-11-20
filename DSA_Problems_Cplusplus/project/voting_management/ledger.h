#pragma once
#include"libraries.h"
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

  string get_time();

  string calculate_hash() const;
};

class Ledger
{
private:
  LedgerBlock *head;
  LedgerBlock *tail;
  int size;
  string get_last_hash() const;

public:
  Ledger();
  ~Ledger();

  void add_block(const string &candidiate,const string &voter, string &type);
  bool verify_ledger() const;
  void display_ledger() const;
};