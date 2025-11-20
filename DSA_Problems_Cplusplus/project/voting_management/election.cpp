#include "election.h"
#include "libraries.h"
#include "static_data.h"
using namespace std;
// constuctor
Election::Election(VoterManager *vm) : manage_votes(vm)
{
  mna_votes.clear();
  mpa_votes.clear();
}

bool Election::validate_candidate_cnic(const string &cnic)
{

  if (cnic.length() != 13)
  {
    cout << "Error! CNIC Must Consist Of 13 Digits\n";
    return false;
  }
  else
  {
    for (char c : cnic)
    {
      if (!isdigit(c))
      {
        cout << "Error! CNIC Must Consist of 13 Digits\n";
        return false;
      }
    }
    return true;
  }
}

bool Election::validate_national_assembly_seat(int seat_no)
{
  if (seat_no <= 0 || seat_no >= 267)
  {
    return false;
  }
  return true;
}

bool Election::validate_provincial_seat(Province p, int seat_no)
{
  switch (p)
  {
  case PUNJAB:
    if (seat_no <= 0 || seat_no >= 298)
    {
      return false;
    }
    return true;

  case SINDH:
    if (seat_no <= 0 || seat_no >= 169)
    {
      return false;
    }
    return true;

  case KPK:
    if (seat_no <= 0 || seat_no >= 116)
    {
      return false;
    }
    return true;

  case BALOCHISTAN:
    if (seat_no <= 0 || seat_no >= 52)
    {
      return false;
    }
    return true;

  default:
    return false;
    break;
  }
}

void Election::add_mna_candidate(const string &name, const string &symbol, const string &cnic)
{
  int na;

  if (!validate_candidate_cnic(cnic))
    return;
  cout << "Enter NA Seat Number : ";
  cin >> na;
  if (!validate_national_assembly_seat(na))
  {
    cout << "Invalid NA Seat!\n";
    return;
  }
  for (const Candidate &c : mna_candidates)
  {
    if (cnic == c.cnic && name == c.name && na == c.constituency_na)
    {
      cout << "Candidate Already Exists\n";
      return;
    }
  }
  string temp = "";
  char temp_c = '0';
  mna_candidates.push_back(Candidate(name, symbol, cnic, na, na_area_names[na], -1, temp, temp, temp_c));
  cout << "Candidate Registered For NA -> " << na << setw(10) << "Area -> " << na_area_names[na] << "\n";
  mna_votes[cnic] = 0;
}

void Election::add_mpa_candidate(const string &name, const string &symbol, const string &cnic)
{
  int p;
  if (!validate_candidate_cnic(cnic))
    return;
  Candidate c_temp;
  select_candidate_province(c_temp);
  cout << "Enter P" << c_temp.province_name << " Seat Number: ";
  cin >> p;
  if (!validate_provincial_seat(province, p))
  {
    cout << "Invalid Seat Number!\n";
    return;
  }

  for (const Candidate &c : mpa_candidates)
  {
    if (cnic == c.cnic && name == c.name && p == c.provisional_pp)
    {
      cout << "Candidate Already Exists\n";
      return;
    }
  }

  mpa_candidates.push_back(Candidate(name, symbol, cnic, -1, "", p, (*candidate_selected_area)[p],
                                     c_temp.candidate_province, c_temp.province_name));
  cout << "Candidate Registered For P" << c_temp.candidate_province << " -> " << p << setw(10) << "Area -> " << (*candidate_selected_area)[p] << "\n";
  mpa_votes[cnic] = 0;
}

void Election::display_mna() const
{
  int index = 1;
  cout << "====================== MNA CANDIDATES ======================\n";
  for (const Candidate &c : mna_candidates)
  {
    cout << index++ << ". " << c.name
         << " | " << setw(10) << c.symbol
         << " | NA-" << c.constituency_na
         << " | Area: " << c.na_area << "\n";
  }
}
void Election::display_mpa() const
{
  int index = 1;
  cout << "====================== MPA CANDIDATES ======================\n";
  for (const Candidate &c : mpa_candidates)
  {
    cout << index++ << ". " << c.name
         << " | " << setw(10) << c.symbol
         << " | " << " P" << c.province_name << "-" << c.provisional_pp
         << " | Area: " << c.p_area << "\n";
  }
}

void Election::authenticate_voter(const string &id, const string &password)
{
  if (manage_votes->authenticate_voter(id, password))
  {
    cout << "Voter Authenticated Successfully\n";
  }
  else
  {
    cout << "Invalid Credentials, Unsuccessful Authentication\n";
  }
}

bool Election::has_voter_voted_mna(const string &cnic) const
{
  VoteNode *temp = queue_votes.front;
  while (temp != nullptr)
  {
    if (temp->cnic == cnic && temp->type == "MNA")
    {
      return true;
    }
    temp = temp->next;
  }
  return false;
}

bool Election::has_voter_voted_mpa(const string &cnic) const
{
  VoteNode *temp = queue_votes.front;
  while (temp != nullptr)
  {
    if (temp->cnic == cnic && temp->type == "MPA")
    {
      return true;
    }
    temp = temp->next;
  }
  return false;
}

void Election::cast_mpa_vote(const string &cnic)
{
  if (!manage_votes->check_voter(cnic))
  {
    cout << "Voter CNIC Not Registered\n";
    return;
  }

  Voter *voter = manage_votes->get_voter(cnic);
  if (!voter)
  {
    cout << "Voter not found \n";
    return;
  }

  if (has_voter_voted_mpa(cnic))
  {
    cout << "Voter Already Voted (MPA/PP)\n";
    return;
  }

  int voter_pp = voter->provisional_p;
  if (!validate_provincial_seat(voter->province, voter_pp))
  {
    cout << "Your registered provincial seat is invalid.\n";
    return;
  }

  vector<const Candidate *> eligible_candidates;
  for (const Candidate &c : mpa_candidates)
  {
    if (c.provisional_pp == voter_pp)
      eligible_candidates.push_back(&c);
  }

  if (eligible_candidates.empty())
  {
    cout << "No provincial candidates registered for P"
         << (voter->province == PUNJAB ? 'P' : (voter->province == SINDH ? 'S' : (voter->province == KPK ? 'K' : 'B')))
         << "-" << voter_pp << "\n";
    return;
  }

  cout << "\n===== Provincial Candidates for P"
       << (voter->province == PUNJAB ? 'P' : (voter->province == SINDH ? 'S' : (voter->province == KPK ? 'K' : 'B')))
       << "-" << voter_pp << " =====\n";
  for (size_t i = 0; i < eligible_candidates.size(); ++i)
  {
    cout << i + 1 << ". " << eligible_candidates[i]->name << " | " << eligible_candidates[i]->symbol
         << " | CNIC: " << eligible_candidates[i]->cnic << "\n";
  }

  int choice;
  cout << "Enter candidate number to cast your Provincial vote: ";
  cin >> choice;
  if (cin.fail())
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input\n";
    return;
  }

  if (choice < 1 || choice > eligible_candidates.size())
  {
    cout << "Invalid choice\n";
    return;
  }

  const Candidate *picked = eligible_candidates[choice - 1];
  string type = "MPA";
  queue_votes.enqueue(cnic, picked->name, type);
  ledger.add_block(picked->cnic, cnic, type);
  record_mpa_vote(picked->cnic);

  cout << "Provincial vote cast successfully for " << picked->name << " - " << voter_pp << "\n";
}

void Election::cast_mna_vote(const string &cnic)
{
  if (!manage_votes->check_voter(cnic))
  {
    cout << "Voter CNIC Not Registered\n";
    return;
  }

  // find voter
  Voter *voter = manage_votes->get_voter(cnic);
  if (!voter)
  {
    cout << "Voter not found (unexpected)\n";
    return;
  }

  if (has_voter_voted_mna(cnic))
  {
    cout << "Voter Already Voted (MNA)\n";
    return;
  }

  int voter_na = voter->na;
  vector<const Candidate *> eligible_candidates;
  for (const Candidate &c : mna_candidates)
  {
    if (c.constituency_na == voter_na)
      eligible_candidates.push_back(&c);
  }

  if (eligible_candidates.empty())
  {
    cout << "No candidates registered for NA-" << voter_na << "\n";
    return;
  }

  cout << "\n===== MNA Candidates for NA-" << voter_na << " =====\n";
  for (size_t i = 0; i < eligible_candidates.size(); ++i)
  {
    cout << i + 1 << ". " << eligible_candidates[i]->name << " | " << eligible_candidates[i]->symbol
         << " | CNIC: " << eligible_candidates[i]->cnic << "\n";
  }

  int choice;
  cout << "Enter candidate number to cast your NA vote: ";
  cin >> choice;
  if (cin.fail())
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input\n";
    return;
  }

  if (choice < 1 || choice > eligible_candidates.size())
  {
    cout << "Invalid choice\n";
    return;
  }

  const Candidate *picked = eligible_candidates[choice - 1];
  string type = "MNA";
  queue_votes.enqueue(cnic, picked->name, type);
  ledger.add_block(picked->cnic, cnic, type);
  record_mna_vote(picked->cnic);

  cout << "MNA vote cast successfully for " << picked->name << " (NA-" << voter_na << ")\n";
}

void Election::record_mna_vote(const string &candidate_cnic)
{
  mna_votes[candidate_cnic]++;
}

void Election::record_mpa_vote(const string &candidate_cnic)
{
  mpa_votes[candidate_cnic]++;
}

int Election::get_mna_candidate_votes(const string &c_cnic, const string &c_name) const
{
  int votes;
  for (const Candidate &c : mna_candidates)
  {
    if (c_cnic == c.cnic && c_name == c.name)
    {
      if (mna_votes.find(c_cnic) != mna_votes.end())
      {
        votes = mna_votes.at(c_cnic);
      }
      else
      {
        votes = 0;
      }
    }
    return votes;
  }
  return -1;
}

int Election::get_mpa_candidate_votes(const string &c_cnic, const string &c_name) const
{
  int votes;
  for (const Candidate &c : mpa_candidates)
  {
    if (c_cnic == c.cnic && c_name == c.name)
    {
      if (mpa_votes.find(c_cnic) != mpa_votes.end())
      {
        votes = mpa_votes.at(c_cnic);
      }
      else
      {
        votes = 0;
      }
    }
    return votes;
  }
  return -1;
}

void Election::tally_mna_results()
{
  vector<string> tied_mna_candidates; // in case of same votes
  int highest_votes = 0;
  cout << "============================================= MNA RESULTS =============================================\n";
  for (const Candidate &c : mna_candidates)
  {
    int votes = get_mna_candidate_votes(c.cnic, c.name);
    cout << c.name << setw(10) << c.symbol << setw(10) << "Votes --> " << votes << "\n";
    if (votes > highest_votes)
    {
      mna_winner_cnic = c.cnic;
      highest_votes = votes;
      tied_mna_candidates.clear();
      tied_mna_candidates.push_back(c.cnic);
    }
    else if (votes == highest_votes)
    {
      tied_mna_candidates.push_back(c.cnic);
    }
  }
  srand(time(0));
  if (tied_mna_candidates.size() == 1)
  {
    mna_winner_cnic = tied_mna_candidates[0];
  }
  else
  {
    int random_index = rand() % tied_mna_candidates.size();
    mna_winner_cnic = tied_mna_candidates[random_index];
    cout << "Election Tied! Winner Decided By LOT\n";
  }
  cout << "============================================= MNA SEAT WNNER =============================================\n ";
  winner_mna();
}

void Election::winner_mna() const
{
  for (const Candidate &c : mna_candidates)
  {
    if (c.cnic == mna_winner_cnic)
    {
      int votes = get_mna_candidate_votes(c.cnic, c.name);
      cout << c.name << setw(10) << c.symbol << setw(10) << "Votes --> " << votes << "\n";
    }
  }
}

void Election::tally_mpa_results()
{
  vector<string> tied_mpa_candidates; // in case of same votes
  int highest_votes = 0;
  cout << "============================================= MPA RESULTS =============================================\n";
  for (const Candidate &c : mpa_candidates)
  {
    int votes = get_mpa_candidate_votes(c.cnic, c.name);
    cout << c.name << setw(10) << c.symbol << setw(10) << "Votes --> " << votes << "\n";
    if (votes > highest_votes)
    {
      mpa_winner_cnic = c.cnic;
      highest_votes = votes;
      tied_mpa_candidates.clear();
      tied_mpa_candidates.push_back(c.cnic);
    }
    else if (votes == highest_votes)
    {
      tied_mpa_candidates.push_back(c.cnic);
    }
  }
  srand(time(0));
  if (tied_mpa_candidates.size() == 1)
  {
    mpa_winner_cnic = tied_mpa_candidates[0];
  }
  else
  {
    int random_index = rand() % tied_mpa_candidates.size();
    mpa_winner_cnic = tied_mpa_candidates[random_index];
    cout << "Election Tied! Winner Decided By LOT\n";
  }
  cout << "============================================= MPA SEAT WNNER =============================================\n ";
  winner_mpa();
}

void Election::winner_mpa() const
{
  for (const Candidate &c : mpa_candidates)
  {
    if (c.cnic == mpa_winner_cnic)
    {
      int votes = get_mpa_candidate_votes(c.cnic, c.name);
      cout << c.name << setw(10) << c.symbol << setw(10) << "Votes --> " << votes << "\n";
    }
  }
}

void Election::select_candidate_province(Candidate &c)
{
  bool flag = true;
  while (flag)
  {
    cout << "Select Province:\n";
    cout << "1. Punjab\n2. Sindh\n3. KPK\n4. Balochistan\n";
    int p_choice;
    cin >> p_choice;
    if (cin.fail())
    {
      cin.clear();            // clear error flag
      cin.ignore(1000, '\n'); // discard invalid input
      cout << "Invalid input. Please enter a number.\n";
      continue;
    }
    switch (p_choice)
    {
    case 1:
      province = PUNJAB;
      c.candidate_province = to_string(province);
      c.province_name = 'P';
      this->candidate_selected_area = &pp_area_names;
      flag = false;
      break;
    case 2:
      province = SINDH;
      c.candidate_province = to_string(province);
      c.province_name = 'S';
      this->candidate_selected_area = &ps_area_names;
      flag = false;
      break;
    case 3:
      province = KPK;
      c.candidate_province = to_string(province);
      c.province_name = 'K';
      this->candidate_selected_area = &pk_area_names;
      flag = false;
      break;
    case 4:
      province = BALOCHISTAN;
      c.candidate_province = to_string(province);
      c.province_name = 'B';
      this->candidate_selected_area = &pb_area_names;
      flag = false;
      break;
    default:
      cout << "Invalid province choice!\n";
      break;
    }
  }
}

void Election::add_mna_admin()
{
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  string name, cnic, symbol;
  cout << "Enter Candidate Name: ";
  getline(cin, name);
  bool flag = false;
  while (!flag)
  {
    cout << "Enter Candidate CNIC: ";
    getline(cin, cnic);
    if (!validate_candidate_cnic(cnic))
    {
      flag = false;
    }
    else
    {
      flag = true;
    }
  }
  cout << "Enter Candidate Symbol : ";
  getline(cin, symbol);
  add_mna_candidate(name, symbol, cnic);
}
void Election::add_mpa_admin()
{
  string name, cnic, symbol;
  cout << "Enter Candidate Name: ";
  cin.clear();
  cin.ignore(1000, '\n');
  getline(cin, name);
  bool flag = false;
  while (!flag)
  {
    cout << "Enter Candidate CNIC: ";
    getline(cin, cnic);
    if (!validate_candidate_cnic(cnic))
    {
      flag = false;
    }
    else
    {
      flag = true;
    }
  }
  cout << "Enter Candidate Symbol : ";
  cin.clear();
  cin.ignore(1000, '\n');
  getline(cin, symbol);
  add_mpa_candidate(name, symbol, cnic);
}
void Election::verify_ledger_admin()
{
  ledger.verify_ledger();
}
void Election::display_ledger()
{
  ledger.display_ledger();
}

void Election::display_all_votes()
{
  cout << "==================== ALL MNA VOTES ====================\n";
  for (const Candidate &c : mna_candidates)
  {
    int votes = get_mna_candidate_votes(c.cnic, c.name);
    cout << "NA-" << c.constituency_na << " | " << c.name
         << " | " << setw(10) << c.symbol
         << " | Area: " << c.na_area
         << " | Votes: " << votes << "\n";
  }

  cout << "\n==================== ALL MPA VOTES ====================\n";
  for (const Candidate &c : mpa_candidates)
  {
    int votes = get_mpa_candidate_votes(c.cnic, c.name);
    cout << "P" << c.province_name << "-" << c.provisional_pp << " | " << c.name
         << " | " << setw(10) << c.symbol
         << " | Area: " << c.p_area << " | " << c.candidate_province << " | Votes: " << votes << "\n";
  }
}
void Election::display_winners_till_now()
{
  cout << "==================== CURRENT MNA WINNERS ====================\n";

  for (const Candidate &c : mna_candidates)
  {
    int votes = get_mna_candidate_votes(c.cnic, c.name);

    bool is_winner = true;
    for (const Candidate &other : mna_candidates)
    {
      if (other.constituency_na == c.constituency_na)
      {
        int other_votes = get_mna_candidate_votes(other.cnic, other.name);
        if (other_votes > votes)
        {
          is_winner = false;
          break;
        }
      }
    }

    if (is_winner)
    {
      cout << "NA-" << c.constituency_na
           << " | " << c.name
           << " | " << setw(10) << c.symbol
           << " | Area: " << c.na_area
           << " | Votes: " << votes << "\n";
    }
  }

  cout << "\n==================== CURRENT MPA WINNERS ====================\n";

  for (const Candidate &c : mpa_candidates)
  {
    int votes = get_mpa_candidate_votes(c.cnic, c.name);

    bool is_winner = true;
    for (const Candidate &other : mpa_candidates)
    {
      if (other.provisional_pp == c.provisional_pp)
      {
        int other_votes = get_mpa_candidate_votes(other.cnic, other.name);
        if (other_votes > votes)
        {
          is_winner = false;
          break;
        }
      }
    }

    if (is_winner)
    {
      cout << "P" << c.province_name << "-" << c.provisional_pp << " | " << c.name
           << " | " << setw(10) << c.symbol << " | Area: " << c.p_area << " | " << c.candidate_province
           << " | Votes: " << votes << "\n";
    }
  }
}

void Election::voter_menu(const string &cnic)
{
  int choice;
  do
  {
    cout << "\n==== Voter Menu ====\n";
    cout << "1. View My Profile\n";
    cout << "2. View My Constituency (NA / PP)\n";
    cout << "3. Cast Vote for MNA\n";
    cout << "4. Cast Vote for MPA\n";
    cout << "5. Logout\n";
    cout << "Enter Choice: ";

    cin >> choice;

    switch (choice)
    {
    case 1:
    {
      Voter *v = manage_votes->get_voter(cnic);
      if (v)
      {
        v->display_voter();
      }
      break;
    }
    case 2:
    {
      Voter *v = manage_votes->get_voter(cnic);
      if (v)
      {
        cout << "National Assembly Seat: NA-" << v->na << "\n";
        char prov_char = (v->province == PUNJAB ? 'P' : (v->province == SINDH ? 'S' : (v->province == KPK ? 'K' : 'B')));
        cout << "YProvincial Assembly Seat: P" << prov_char << "-" << v->provisional_p << "\n";
      }
      break;
    }
    case 3:
      cast_mna_vote(cnic);
      break;
    case 4:
      cast_mpa_vote(cnic);
      break;
    case 5:
      cout << "Logging out...\n";
      break;
    default:
      cout << "Invalid Choice\n";
    }
  } while (choice != 5);
}
