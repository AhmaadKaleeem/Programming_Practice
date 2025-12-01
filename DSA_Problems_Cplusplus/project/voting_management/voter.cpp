#include "voter.h"
#include "libraries.h"
#include "static_data.h"
#include "utilities.h"
#include "console_color.h"
using namespace std;

// Constructor
Voter::Voter() : voter_age(0), voter_name("Null"), voter_password("Null"), check_vote(false), voter_cnic("Null"), next(nullptr), provisional_p(0), na(0), voter_id("Null") {}

void Voter::register_voter()
{
  system("cls");
  yellow();
  cout << "=========================================\n";
  cout << "      VOTER REGISTRATION \n";
  cout << "=========================================\n";
  reset();

  clear_buffer();

  do
  {
    blue();
    cout << "Enter Name: ";
    reset();
    getline(cin, voter_name);
  } while (!check_name(voter_name));

  input_cnic();

  blue();
  cout << "Enter Age: ";
  reset();
  cin >> voter_age;
  if (!check_valid_int())
  {
    blue();
    cout << "Enter Age: ";
    reset();
    cin >> voter_age;
  }

  while (!validate_age())
  {
    blue();
    cout << "Re-enter Age: ";
    reset();
    cin >> voter_age;
    if (!check_valid_int())
    {
      continue;
    }
  }

  system("cls");
  green();
  cout << "========================================\n";
  cout << "  NATIONAL ASSEMBLY SEAT SELECTION\n";
  cout << "========================================\n";
  reset();

  blue();
  cout << "Enter NA (1-266): ";
  reset();
  cin >> na;
  if (!check_valid_int())
  {
    blue();
    cout << "Enter NA (1-266): ";
    reset();
    cin >> na;
  }

  while (!validate_national_assembly_seat(na))
  {
    red();
    cout << "Please Enter Valid NA (1-266)\n";
    reset();
    blue();
    cout << "Enter NA: ";
    reset();
    cin >> na;
    if (!check_valid_int())
    {
      continue;
    }
  }

  determine_province_from_na();

  yellow();
  cout << "Your Province: ";
  green();
  cout << pnames[province] << "\n\n";
  reset();

  if (na >= 46 && na <= 48)
  {
    provisional_p = 0;
    green();
    cout << "========================================\n";
    cout << "        ISLAMABAD REGION\n";
    cout << "========================================\n";
    cout << "Islamabad voters vote for National\n";
    cout << "Assembly ONLY\n";
    cout << "No Provincial Assembly seat available\n";
    cout << "Proceeding to Registration Summary...\n";
    reset();
  }
  else
  {
    system("cls");
    green();
    cout << "========================================\n";
    cout << "  PROVINCIAL ASSEMBLY SEAT SELECTION\n";
    cout << "========================================\n";
    reset();

    vector<int> p_options = na_to_provincial[na];

    if (p_options.empty())
    {
      red();
      cout << "No provincial seats available for NA-" << na << "\n";
      reset();
      provisional_p = 0;
    }
    else
    {
      blue();
      cout << "Available Provincial constituencies for NA-" << na << ":\n";
      reset();

      for (int i = 0; i < p_options.size(); ++i)
      {
        int seat_num = p_options[i];
        yellow();
        cout << (i + 1) << ". P" << province_name << "-" << seat_num;
        reset();

        if (selected_area != nullptr && selected_area->find(seat_num) != selected_area->end())
        {
          green();
          cout << " (" << (*selected_area)[seat_num] << ")";
          reset();
        }
        cout << endl;
      }

      int choice;
      bool valid_choice = false;

      while (!valid_choice)
      {
        blue();
        cout << "Select the Provincial constituency by number: ";
        reset();
        cin >> choice;
        if (!check_valid_int())
        {
          continue;
        }

        if (choice >= 1 && choice <= (int)p_options.size())
        {
          provisional_p = p_options[choice - 1];
          green();
          cout << "You selected: P" << province_name << "-" << provisional_p;
          reset();

          if (selected_area != nullptr && selected_area->find(provisional_p) != selected_area->end())
          {
            blue();
            cout << " (" << (*selected_area)[provisional_p] << ")";
            reset();
          }
          cout << endl;
          valid_choice = true;
        }
        else
        {
          red();
          cout << "Invalid selection! Please enter a number between 1 and " << p_options.size() << "\n";
          reset();
        }
      }

      while (!validate_provincial_seat(province, provisional_p))
      {
        red();
        cout << "Please Enter Valid P" << province_name << "\n";
        reset();
        blue();
        cout << "Enter P" << province_name << ": ";
        reset();
        cin >> provisional_p;
        if (!check_valid_int())
        {
          continue;
        }
      }
    }
  }

  clear_buffer();
  blue();
  cout << "Set Password: ";
  reset();
  voter_password = hide_password();

  voter_id = auto_generate_voter_id();

  system("cls");
  green();
  cout << "========================================\n";
  cout << "   Voter Registered Successfully!\n";
  cout << "========================================\n";
  reset();
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
    red();
    cout << "Error! Voter Must Be At Least 18 Years Old\n";
    reset();
    return false;
  }
}

bool Voter::validate_cnic()
{
  if (voter_cnic.length() != 13)
  {
    red();
    cout << "Error!  CNIC Must Consist Of 13 Digits\n";
    reset();
    return false;
  }
  else
  {
    for (char c : voter_cnic)
    {
      if (!isdigit(c))
      {
        red();
        cout << "Error!  CNIC Must Contain Only digits.\n";
        reset();
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
    blue();
    cout << "Enter Your CNIC (13 digits): ";
    reset();
    getline(cin, voter_cnic);
  } while (!validate_cnic());
}

void Voter::display_voter()
{
  yellow();
  cout << "=====================================================\n";
  cout << "          VOTER INFORMATION\n";
  cout << "=====================================================\n";
  reset();

  blue();
  cout << "Name                 : ";
  reset();
  cout << voter_name << "\n";

  blue();
  cout << "Voter ID             : ";
  green();
  cout << voter_id << "\n";
  reset();

  blue();
  cout << "CNIC                 : ";
  reset();
  cout << voter_cnic << "\n";

  blue();
  cout << "Age                  : ";
  reset();
  cout << voter_age << "\n";

  blue();
  cout << "Province             : ";
  green();
  cout << pnames[province] << "\n";
  reset();

  blue();
  cout << "Vote Casted          : ";
  green();
  cout << (check_vote ? "Yes" : "No") << "\n";
  reset();

  if (na_area_names.find(na) != na_area_names.end())
  {
    blue();
    cout << "NA                   : ";
    yellow();
    cout << na << " (" << na_area_names[na] << ")\n";
    reset();
  }
  else
  {
    blue();
    cout << "NA                   : ";
    red();
    cout << na << " (Area Not Found)\n";
    reset();
  }

  if (na < 46 || na > 48)
  {
    if (selected_area != nullptr)
    {
      if (selected_area->find(provisional_p) != selected_area->end())
      {
        blue();
        cout << "Provincial Assembly  : ";
        yellow();
        cout << "P" << province_name << "-" << provisional_p
             << " (" << (*selected_area)[provisional_p] << ")\n";
        reset();
      }
      else
      {
        blue();
        cout << "Provincial Assembly  : ";
        red();
        cout << "P" << province_name << "-" << provisional_p
             << " (Area Not Found)\n";
        reset();
      }
    }
  }
  else
  {
    red();
    cout << "Provincial Assembly  : Not Applicable (Islamabad)\n";
    reset();
  }

  yellow();
  cout << "=====================================================\n";
  reset();
}

void Voter::clear_buffer()
{
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