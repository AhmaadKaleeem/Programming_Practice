#include "voter_management.h"

VoterManager::VoterManager(): head(nullptr){}

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

if(voter_mapping.find(cnic) == voter_mapping.end()){
     cout << "Error! Voter not found!\n";
     return;
}
cout << "Voter Founded Successfully\n";
voter_mapping[cnic]->display_voter();

}