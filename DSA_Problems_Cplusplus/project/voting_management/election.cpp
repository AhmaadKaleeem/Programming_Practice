#include "election.h"
#include <libraries.h>
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

  mna_candidates.push_back(Candidate(name, symbol, cnic, na, -1));
  cout << "Candidate Registered For NA -> " << na << setw(10) << "Area -> " << Voter::na_area_names[na] << "\n";
  mna_votes[cnic] = 0;
}

void Election::add_mpa_candidate(const string &name, const string &symbol, const string &cnic)
{
  int p;
  if (!validate_candidate_cnic(cnic))
    return;
  select_candidate_province();
  cout << "Enter P" << province_name << " Seat Number: ";
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

  mpa_candidates.push_back(Candidate(name, symbol, cnic, -1, p));
  cout << "Candidate Registered For P" << province_name << " -> " << p << setw(10) << "Area -> " << (*candidate_selected_area)[p] << "\n";
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
         << " | NA-" << c.constituency_na << "\n";
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
         << " | " << province_name << "P-" << c.provisional_pp << "\n";
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
    cout << "Your registered provincial seat is invalid: P" << province_name << "-" << voter_pp << "\n";
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

void Election::select_candidate_province()
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
      province_name = 'P';
      this->candidate_selected_area = &Voter::pp_area_names;
      flag = false;
      break;
    case 2:
      province = SINDH;
      province_name = 'S';
      this->candidate_selected_area = &Voter::ps_area_names;
      flag = false;
      break;
    case 3:
      province = KPK;
      province_name = 'K';
      this->candidate_selected_area = &Voter::pk_area_names;
      flag = false;
      break;
    case 4:
      province = BALOCHISTAN;
      province_name = 'B';
      this->candidate_selected_area = &Voter::pb_area_names;
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
  getline(cin,name);
  bool flag = false;
  while(!flag){
  cout << "Enter Candidate CNIC: ";
  getline(cin,cnic);
  if(!validate_candidate_cnic(cnic)){
    flag = false;
  }
  else{
  flag = true;
}

}
  cout << "Enter Candidate Symbol : ";
  getline(cin,symbol);
  add_mna_candidate(name,symbol,cnic);
}
void Election::add_mpa_admin(){
  string name, cnic, symbol;
  cout << "Enter Candidate Name: ";
  cin.clear();          
  cin.ignore(1000, '\n'); 
  getline(cin,name);
  bool flag = false;
  while(!flag){
  cout << "Enter Candidate CNIC: ";
  getline(cin,cnic);
  if(!validate_candidate_cnic(cnic)){
    flag = false;
  }
  else{
  flag = true;
}

}
  cout << "Enter Candidate Symbol : ";
   cin.clear();          
  cin.ignore(1000, '\n'); 
  getline(cin,symbol);
  add_mpa_candidate(name,symbol,cnic);
}
void Election::verify_ledger_admin(){
  ledger.verify_ledger();
}
void Election::display_ledger(){
  ledger.display_ledger();
}