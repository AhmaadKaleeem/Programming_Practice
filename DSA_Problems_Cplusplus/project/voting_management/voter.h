#pragma once
#include "libraries.h"
#include "admin_panel.h"
#include "provinces.h"
using namespace std;

class Voter
{
public:
  string voter_id;
  string voter_name;
  string voter_cnic;
  string voter_password;
  int voter_age;
  int na;
  int provisional_p;
  Province province;
  bool check_vote;
  Voter *next;
  static unordered_map<int,string> na_area_names;
  static unordered_map<int,string> pp_area_names;
  static unordered_map<int,string> ps_area_names;
  static  unordered_map<int,string> pk_area_names;
  static unordered_map<int,string> pb_area_names;
   unordered_map<int, string> *selected_area = nullptr;
 

  Voter();
  void register_voter(); 
  string auto_generate_voter_id(); 
  bool validate_age();             
  bool validate_cnic();            
  void input_cnic();               
  void display_voter();   
  bool validate_provincial_seat(Province p ,int seat);
  bool validate_national_assembly_seat(int seat);

};