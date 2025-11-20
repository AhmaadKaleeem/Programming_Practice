#include "voter_management.h"
#include"libraries.h"
#include "voter.h"
using namespace std;
VoterManager::VoterManager(): head(nullptr){}

bool VoterManager::check_cnic(const string & id){
if (id.length()!= 13){
        cout << "Error! CNIC Must Consist Of 13 Digits\n";
       return false;
    }
    else {
        for (char c : id){
            if(!isdigit(c)){
                cout << "Error! CNIC Must Consist of 13 Digits\n";
                return false;
            }
        }
    return true;
    }

}     

void VoterManager::add_voter(){
// Creating a New Voter
 Voter* new_voter = new Voter();
 new_voter->register_voter();

 if(voter_mapping.find(new_voter->voter_cnic) != voter_mapping.end()){
    cout << "Error! CNIC Already Registered.\n";
    delete new_voter;
    return;
 }
 voter_mapping[new_voter->voter_cnic] = new_voter;
 new_voter->next = head;
 head = new_voter;
 cout << "Voter Added Successfully to System\n";
}

void VoterManager::display_all_voters(){
cout << "======================================= All Registered Voters =======================================\n\n";
 Voter* temp = head;
 while(temp!=nullptr){
    temp->display_voter();
    temp = temp->next;
 } 
}

void VoterManager::search_voter(string cnic){
if(!check_cnic(cnic)) return;
if(voter_mapping.find(cnic) == voter_mapping.end()){
     cout << "Error! Voter not found!\n";
     return;
}
cout << "Voter Founded Successfully\n";
voter_mapping[cnic]->display_voter();

}

 bool VoterManager::check_voter(const string& cnic ){
    if(!check_cnic(cnic)) return false;
if(voter_mapping.find(cnic) == voter_mapping.end()){
     return false;
}
return true;
 }

bool VoterManager::authenticate_voter(const string& id , const string& password){
   if(!check_cnic(id)) return false;
   if(voter_mapping.find(id) == voter_mapping.end()){
     cout << "Error! Voter not found!\n";
     return false;
}
  if(voter_mapping[id]->voter_password == password){
   return true;
  }
  else {
   return false;
  }

}

Voter* VoterManager::get_voter(const string &cnic) {
    if (!check_cnic(cnic)) return nullptr;
    auto it = voter_mapping.find(cnic);
    if (it == voter_mapping.end()) return nullptr;
    return it->second; 
}