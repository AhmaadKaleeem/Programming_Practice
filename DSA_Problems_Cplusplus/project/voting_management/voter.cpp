#include "voter.h"
#include <functional>
// Constuuctor
Voter::Voter() : voter_age(0), voter_name("Null"),voter_password("Null"),check_vote(false),voter_cnic("Null"),next(nullptr) { voter_id = auto_generate_voter_id(); }
  
void Voter::register_voter(){
  cout << "--- Registering Voter ---\n";

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, voter_name);

    input_cnic();

    cout << "Enter Age: ";
    cin >> voter_age;

    while (!validate_age())
    {
        cout << "Re-enter Age: ";
        cin >> voter_age;
    }

    cout << "Set Password: ";
     cin.ignore();
    getline(cin, voter_password);


    voter_id = auto_generate_voter_id();

    cout << "Voter Registered Successfully!\n";

    display_voter();
}


string Voter::auto_generate_voter_id(){
  hash<string> hash_voterid;
  size_t hash_value = hash_voterid(voter_cnic); // Hashing cnic as cnic will be unique
  hash_value = hash_value % 100000;
  return "VTR" + to_string(hash_value);
  }

  bool Voter::validate_age(){
  if(voter_age>=18){
    return true;
  }
  else {
  cout << "Error! Voter Must Be At Least 18 Year Old\n";
  return false;
  }
  }

  bool Voter::validate_cnic(){
    if (voter_cnic.length()!= 13){
        cout << "Error! CNIC Must Consist Of 13 Digits\n";
       return false;
    }
    else {
        for (char c : voter_cnic){
            if(c < '0' || c > '9'){
                cout << "Error! CNIC Must Consist of 13 Digits\n";
                return false;
            }
        }
    return true;
    }

  }      

  void Voter::input_cnic(){
    cout << "Enter Your CNIC: ";
    cin.ignore();
    getline(cin,voter_cnic);
    if(!validate_cnic()){
        cout << "Again ";
        input_cnic();
    }
  }       

  void Voter::display_voter(){
  cout << "============================================= Voter Information =============================================\n";
  cout << "Name -> " <<  setw(5) << voter_name << "\nID -> " <<  setw(5) << voter_id << "\n";
  cout << "CNIC -> " << setw(5) << voter_cnic << "\nAge -> "  << setw(5) << voter_age << "\n";
  cout << "Casted Vote -> " << setw(5) << (check_vote ? "Yes" : "No") << "\n";
}  
  
