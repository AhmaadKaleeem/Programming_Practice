#include "voter.h"
#include "libraries.h"
#include "static_data.h"
using namespace std;

// Constuuctor
Voter::Voter() : voter_age(0), voter_name("Null"), voter_password("Null"), check_vote(false), voter_cnic("Null"), next(nullptr), provisional_p(0), na(0),voter_id("Null"){}

void Voter::register_voter()
{
  cout << "--- Registering Voter ---\n";
  clear_buffer();
  cout << "Enter Name: ";
  getline(cin, voter_name);

  input_cnic();

  cout << "Enter Age: ";
  cin >> voter_age;

  while (!validate_age())
  {
    cout << "Re-enter Age: ";
    cin >> voter_age;
  }

  cout << "\n === National Assembly Seat Number ===\n";
  cout << "Enter NA - ";
  cin >> na;
  while (!validate_national_assembly_seat(na))
  {
    cout << "Please Enter Valid NA\n";
    cout << "Enter NA - ";
    cin >> na;
  }

  determine_province_from_na();
  cout << "Your Province: " << pnames[province] << "\n\n";
    if (na >= 46 && na <= 48)
  {
    provisional_p = 0;
    cout << "\n=== Islamabad Region ===\n";
    cout << "Islamabad voters vote for National Assembly ONLY\n";
    cout << "No Provincial Assembly seat for Islamabad\n";
    cout << "Proceeding to Registration Summary......\n\n";
  }
  else{
  cout << "\n === Provincial Assembly Seat Number ===\n";
    vector<int> p_options = na_to_provincial[na];

    if (p_options.empty())
    {
      cout << "No provisional seats available for NA-" << na << "\n";
      provisional_p = 0;
    }
    else
    {
      cout << "Available Provisional constituencies for NA-" << na << ":\n";
      for (int i = 0; i < p_options.size(); ++i) {
          int seat_num = p_options[i];
          cout << (i + 1) << ". P" << province_name << "-" << seat_num;
          
          if (selected_area != nullptr && selected_area->find(seat_num) != selected_area->end())
          {
              cout << " (" << (*selected_area)[seat_num] << ")";
          }
          cout << endl;
      }

      int choice;
      bool valid_choice = false;
      
      while (!valid_choice)
      {
        cout << "Select the Provisional constituency by number: ";
        cin >> choice;
        
        if (cin.fail())
        {
          cin.clear();
          cin.ignore(1000, '\n');
          cout << "Invalid input. Please enter a number.\n";
          continue;
        }

        if (choice >= 1 && choice <= (int)p_options.size()) {
            provisional_p = p_options[choice - 1];
            cout << "You selected: P" << province_name << "-" << provisional_p;
            
            if (selected_area != nullptr && selected_area->find(provisional_p) != selected_area->end())
            {
                cout << " (" << (*selected_area)[provisional_p] << ")";
            }
            cout << endl;
            valid_choice = true;
        } else {
            cout << "Invalid selection! Please enter a number between 1 and " << p_options.size() << "\n";
        }
      }

      while (!validate_provincial_seat(province, provisional_p))
      {
        cout << "Please Enter Valid P" << province_name << "\n";
        cout << "Enter P" << province_name << " - ";
        cin >> provisional_p;
      }
    }
  }
  
  clear_buffer();
  cout << "Set Password: ";
  getline(cin, voter_password);

  voter_id = auto_generate_voter_id();

  cout << "Voter Registered Successfully!\n";
  display_voter();
}

bool Voter::validate_national_assembly_seat(int seat_no)
{
  if (seat_no < 1 || seat_no > 266)
  {
    return false;
  }
  return true;
}

bool Voter::validate_provincial_seat(Province p, int seat_no)
{
  switch (p)
  {
  case PUNJAB:
    if (seat_no < 1 || seat_no > 297)
    {
      return false;
    }
    return true;

  case SINDH:
    if (seat_no < 1 || seat_no > 168)
    {
      return false;
    }
    return true;

  case KPK:
    if (seat_no < 1 || seat_no > 115)
    {
      return false;
    }
    return true;

  case BALOCHISTAN:
    if (seat_no < 1 || seat_no > 51)
    {
      return false;
    }
    return true;

  default:
    return false;
    break;
  }
}

string Voter::auto_generate_voter_id()
{
  hash<string> hash_voterid;
  size_t hash_value = hash_voterid(voter_cnic); // Hashing cnic as cnic will be unique
  hash_value = hash_value % 100000;
  return "VTR" + to_string(hash_value);
}

bool Voter::validate_age()
{
  if (voter_age >= 18)
  {
    return true;
  }
  else
  {
    cout << "Error! Voter Must Be At Least 18 Year Old\n";
    return false;
  }
}

bool Voter::validate_cnic()
{
  if (voter_cnic.length() != 13)
  {
    cout << "Error! CNIC Must Consist Of 13 Digits\n";
    return false;
  }
  else
  {
    for (char c : voter_cnic)
    {
      if (!isdigit(c))
      {
       cout << "Error! CNIC Must Contain Only digits.\n";
        return false;
      }
    }
    return true;
  }
}

void Voter::input_cnic()
{
  do
  {
    cout << "Enter Your CNIC: ";
    getline(cin, voter_cnic);
  } while (!validate_cnic());
}

void Voter::display_voter()
{
  cout << "============================================= Voter Information =============================================\n";
  cout << "Name -> " << setw(15) << voter_name << "\nID -> " << setw(15) << voter_id << "\n";
  cout << "CNIC -> " << setw(15) << voter_cnic << "\nAge -> " << setw(15) << voter_age << "\n";
  cout << "Province -> " << setw(15) << pnames[province] << "\nCasted Vote -> " << setw(15) << (check_vote ? "Yes" : "No") << "\n";
  if (na_area_names.find(na) != na_area_names.end())
    cout << "NA -> " << na << setw(25) << "Area -> " << na_area_names[na] << "\n";
else
    cout << "NA -> " << na << setw(25) << "Area -> Not Found\n";

  if (na < 46 || na > 48) 
  {
    if (selected_area != nullptr)
    {
      if (selected_area->find(provisional_p) != selected_area->end())
        cout << "P" << province_name << " -> " << provisional_p
             << setw(25) << "Area -> " << (*selected_area)[provisional_p] << "\n";
      else
        cout << "P" << province_name << " -> " << provisional_p
             << setw(25) << "Area -> Not Found\n";
    }
  }
  else  
  {
    cout << "Islamabad voters vote for National Assembly ONLY\n";
    cout << "No Provincial Assembly seat for Islamabad\n";
  }

}

void Voter::clear_buffer(){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

void Voter::determine_province_from_na()
{
  if (na >= 1 && na <= 45)
  {
    province = KPK;
    province_name = 'K';
    this->selected_area = &pk_area_names;
  }
  else if (na >= 46 && na <= 48)
  {
    province = ISLAMABAD; 
    province_name = 'I';
    this->selected_area = nullptr;
  }
  else if (na >= 49 && na <= 189)
  {
    province = PUNJAB;
    province_name = 'P';
    this->selected_area = &pp_area_names;
  }
  else if (na >= 190 && na <= 250)
  {
    province = SINDH;
    province_name = 'S';
    this->selected_area = &ps_area_names;
  }
  else if (na >= 251 && na <= 266)
  {
    province = BALOCHISTAN;
    province_name = 'B';
    this->selected_area = &pb_area_names;
  }
}