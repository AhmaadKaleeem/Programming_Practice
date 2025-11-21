#pragma once
#include "libraries.h"
using namespace std;

class Voter;
class VoterManager
{
public:
  VoterManager();
  Voter *head;
  unordered_map<string, Voter *> voter_mapping;
  void add_voter();
  void search_voter(string cnic);
  bool authenticate_voter(const string &id, const string &pass);
  void display_all_voters();
  bool check_cnic(const string &id);
  bool check_voter(const string &cnic);
  Voter *get_voter(const string &cnic);
};
