#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <iomanip>
class Voter
{
public:
  string voter_id;
  string voter_name;
  string voter_cnic;
  int voter_age;
  string voter_password;
  bool check_vote;
  Voter *next;

  Voter();
  void register_voter(); 
  string auto_generate_voter_id(); 
  bool validate_age();             
  bool validate_cnic();            
  void input_cnic();               
  void display_voter();   
  
};