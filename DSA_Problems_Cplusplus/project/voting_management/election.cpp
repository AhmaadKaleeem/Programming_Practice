#include "election.h"
#include "libraries.h"
#include "voting_time.h"
#include "console_color.h"
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
  if (is_voting_time())
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

  else
  {
    cout << "Voting is CLOSED\n";
    display_voting_schedule();
  }
}
void Election::cast_mna_vote(const string &cnic)
{
  if (is_voting_time())
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
  else
  {
    cout << "Voting is CLOSED\n";
    display_voting_schedule();
  }
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
        cout << "Provincial Assembly Seat: P" << prov_char << "-" << v->provisional_p << "\n";
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

void Election::save_voters_to_file()
{
  ofstream voter_file("Voters.txt");
  if (voter_file.is_open())
  {
    int count;
    Voter *temp = manage_votes->head;
    while (temp != nullptr)
    {
      voter_file << temp->voter_cnic << "|" << temp->voter_name << "|" << temp->voter_password << "|" << temp->na << "|"
                 << temp->provisional_p << "|" << temp->province_name << "|" << temp->pnames[temp->province] << "|" << temp->voter_id << "|" << temp->check_vote << "\n";
      temp = temp->next;
      count++;
    }
    cout << count << " Voters saved successfully to Voters.txt\n";

    voter_file.close();
  }
  else
  {
    cout << "Error while Opening Voters File For Saving Data\n";
  }
}

void Election::save_mna_candidates_to_file()
{

  ofstream mna_candidate_file("MNA_Candidates.txt");
  if (mna_candidate_file.is_open())
  {
    for (const Candidate &c : mna_candidates)
    {
      mna_candidate_file << c.name << "|" << c.symbol << "|" << c.cnic << "|" << c.na_area << "|" << c.p_area << "|"
                         << c.candidate_province << "|" << c.constituency_na << "|" << c.provisional_pp << "|" << c.province_name << "\n";
      mna_candidate_file.close();
      cout << (int)mna_candidates.size() << "MNA Candidates saved successfully to MNA_Candidates.txt\n";
    }
  }
  else
  {
    cout << "Error while Opening MNA Candidate File For Saving Data\n";
  }
}

void Election::save_mpa_candidates_to_file()
{

  ofstream mpa_candidate_file("MPA_Candidates.txt");
  if (mpa_candidate_file.is_open())
  {
    for (const Candidate &c : mpa_candidates)
    {
      mpa_candidate_file << c.name << "|" << c.symbol << "|" << c.cnic << "|" << c.na_area << "|" << c.p_area << "|"
                         << c.candidate_province << "|" << c.constituency_na << "|" << c.provisional_pp << "|" << c.province_name << "\n";
      mpa_candidate_file.close();
      cout << (int)mpa_candidates.size() << " MPA Candidates saved successfully to MPA_Candidates.txt\n";
    }
  }
  else
  {
    cout << "Error while Opening mpa Candidate File For Saving Data\n";
  }
}

void Election::load_mna_candidates_from_file()
{
  ifstream load_data_file("MNA_Candidates.txt");
  if (load_data_file.is_open())
  {
    string line;
    int count;
    while (getline(load_data_file, line))
    {
      string name, symbol, cnic, na_area, p_area, candidate_province, constituency_na, provisional_pp, province_name;
      if (line.empty())
      {
        continue;
      }
      stringstream ss(line);
      getline(ss, name, '|');
      getline(ss, symbol, '|');
      getline(ss, cnic, '|');
      getline(ss, na_area, '|');
      getline(ss, p_area, '|');
      getline(ss, candidate_province, '|');
      getline(ss, constituency_na, '|'); // coverting to int after
      getline(ss, provisional_pp, '|');  // coverting to int after
      getline(ss, province_name, '|');   // coverting to char after
      char province_name_char = province_name[0];
      int constituency_na_int = stoi(constituency_na);
      int provisional_pp_int = stoi(provisional_pp);
      mna_candidates.push_back(Candidate(name, symbol, cnic, constituency_na_int, na_area, provisional_pp_int, p_area, candidate_province, province_name_char));
      mna_votes[cnic] = 0;
      count++;
    }
    cout << "Successfully Loaded " << count << " MNA Candidates Data \n";
  }
  else
  {
    cout << "Error while Opening MNA Candidate File For Loading Data\n";
  }
}

void Election::load_mpa_candidates_from_file()
{
  ifstream load_data_file("MPA_Candidates.txt");
  if (load_data_file.is_open())
  {
    string line;
    int count;
    while (getline(load_data_file, line))
    {
      string name, symbol, cnic, na_area, p_area, candidate_province, constituency_na, provisional_pp, province_name;
      if (line.empty())
      {
        continue;
      }
      stringstream ss(line);
      getline(ss, name, '|');
      getline(ss, symbol, '|');
      getline(ss, cnic, '|');
      getline(ss, na_area, '|');
      getline(ss, p_area, '|');
      getline(ss, candidate_province, '|');
      getline(ss, constituency_na, '|'); // coverting to int after
      getline(ss, provisional_pp, '|');  // coverting to int after
      getline(ss, province_name, '|');   // coverting to char after
      char province_name_char = province_name[0];
      int constituency_na_int = stoi(constituency_na);
      int provisional_pp_int = stoi(provisional_pp);
      mpa_candidates.push_back(Candidate(name, symbol, cnic, constituency_na_int, na_area, provisional_pp_int, p_area, candidate_province, province_name_char));
      mpa_votes[cnic] = 0;
      count++;
    }
    cout << "Successfully Loaded " << count << " MPA Candidates Data \n";
  }
  else
  {
    cout << "Error while Opening MPA Candidate File For Loading Data\n";
  }
}

void Election::load_voters_from_file()
{
  ifstream load_data_file("Voters.txt");
  if (load_data_file.is_open())
  {
    string line;
    int count = 0;
    while (getline(load_data_file, line))
    {
      if (line.empty())
      {
        continue;
      }
      Voter *new_voter = new Voter();
      stringstream ss(line);
      string temp_string;
      getline(ss, new_voter->voter_cnic, '|');

      getline(ss, new_voter->voter_name, '|');
      getline(ss, new_voter->voter_password, '|');
      getline(ss, temp_string, '|');
      new_voter->voter_age = stoi(temp_string);
      getline(ss, temp_string, '|');
      new_voter->na = stoi(temp_string);
      getline(ss, temp_string, '|');
      new_voter->provisional_p = stoi(temp_string);
      getline(ss, temp_string, '|');
      new_voter->province_name = temp_string[0];
      getline(ss, temp_string, '|');
      getline(ss, new_voter->voter_id, '|');
      getline(ss, temp_string, '|');
      new_voter->check_vote = (temp_string == "1");

      // Reconstruct province enum and selected_area from NA
      new_voter->determine_province_from_na();
      // checking for duplicate voter
      if (manage_votes->voter_mapping.find(new_voter->voter_cnic) != manage_votes->voter_mapping.end())
      {
        delete new_voter;
        continue;
      }

      // Add to linked list
      new_voter->next = manage_votes->head;
      manage_votes->head = new_voter;
      manage_votes->voter_mapping[new_voter->voter_cnic] = new_voter;
      count++;
    }
    load_data_file.close();
    cout << "Loaded " << count << " voters from Voters.txt\n";
  }
  else
  {
    cout << "Error while Opening Voters File For Loading Data\n";
  }
}

void Election::save_votes_to_file()
{
  ofstream vote_file("Votes.txt");
  if (vote_file.is_open())
  {
    VoteNode *temp = queue_votes.front;
    while (temp != nullptr)
    {
      vote_file << temp->cnic << "|" << temp->c_name << "|" << temp->type << "\n";
      temp = temp->next;
    }
    vote_file.close();
    cout << "Voting Records Saved Successfully\n";
  }
  else
  {
    cout << "Error While Opening Votes File For Saving Data\n";
  }
}

void Election::load_votes_from_file()
{
  ifstream vote_file("Votes.txt");
  if (vote_file.is_open())
  {
    string line;
    while (getline(vote_file, line))
    {
      if (line.empty())
      {
        continue;
      }

      string voter_cnic, candidate_name, vote_type;
      stringstream ss(line);

      getline(ss, voter_cnic, '|');
      getline(ss, candidate_name, '|');
      getline(ss, vote_type, '|');

      queue_votes.enqueue(voter_cnic, candidate_name, vote_type);
    }
    vote_file.close();
    cout << "Voting Records Loaded Successfully\n";
  }
  else
  {
    cout << "Error While Opening Voting Records File For Loading Data\n";
  }
}

void Election::save_vote_counts_to_file()
{
  ofstream count_file("VoteCounts.txt");
  if (count_file.is_open())
  {
    count_file << "MNA\n";
    for (const auto &pair : mna_votes)
    {
      count_file << pair.first << "|" << pair.second << "\n"; // first belong to map key ,second to value
    }

    count_file << "MPA\n";
    for (const auto &pair : mpa_votes)
    {
      count_file << pair.first << "|" << pair.second << "\n";
    }

    count_file.close();
    cout << "Vote Counts Saved Successfully\n";
  }
  else
  {
    cout << "Error While Opening Vote Counts File For Saving Data\n";
  }
}

void Election::load_vote_counts_from_file()
{
  ifstream count_file("VoteCounts.txt");
  if (count_file.is_open())
  {
    string line;
    string current_type = "";

    while (getline(count_file, line))
    {
      if (line.empty())
      {
        continue;
      }

      if (line == "MNA")
      {
        current_type = "MNA";
        continue;
      }
      if (line == "MPA")
      {
        current_type = "MPA";
        continue;
      }

      stringstream ss(line);
      string cnic, count_str;

      getline(ss, cnic, '|');
      getline(ss, count_str, '|');
      int count = stoi(count_str);

      if (current_type == "MNA")
      {
        mna_votes[cnic] = count;
      }
      else if (current_type == "MPA")
      {
        mpa_votes[cnic] = count;
      }
    }
    count_file.close();
    cout << "Vote Counts Loaded Successfully\n";
  }
  else
  {
    cout << "Error While Opening Vote Counts File For Loading Datah\n";
  }
}

void Election::save_ledger_to_file()
{
  ofstream ledger_file("Ledger.txt");
  if (ledger_file.is_open())
  {

    LedgerBlock *temp = ledger.head;
    while (temp != nullptr)
    {
      ledger_file << temp->index << "|" << temp->candidate_cnic << "|" << temp->voter_cnic << "|" << temp->vote_type << "|"
                  << temp->timestamp << "|" << temp->current_hash << "|" << temp->prev_hash << "\n";
      temp = temp->next;
    }
    ledger_file.close();
    cout << "Blockchain Ledger Saved Successfully\n";
  }
  else
  {
    cout << "Error While Opening Ledger File For Saving Data\n";
  }
}

void Election::load_ledger_from_file()
{
  ifstream ledger_file("Ledger.txt");
  if (ledger_file.is_open())
  {
    string line;
    while (getline(ledger_file, line))
    {
      if (line.empty())
      {
        continue;
      }

      string index, candidate_cnic, voter_cnic, vote_type, timestamp, current_hash, prev_hash;
      stringstream ss(line);

      getline(ss, index, '|');
      int block_index = stoi(index);
      getline(ss, candidate_cnic, '|');
      getline(ss, voter_cnic, '|');
      getline(ss, vote_type, '|');
      getline(ss, timestamp, '|');
      getline(ss, current_hash, '|');
      getline(ss, prev_hash, '|');

      ledger.restore_block(block_index, candidate_cnic, voter_cnic, vote_type, timestamp, current_hash, prev_hash);
    }
    ledger_file.close();
    cout << "Blockchain Ledger Loaded Successfully\n";
  }
  else
  {
    cout << "Error While Opening Ledger File For Loading Data\n";
  }
}


void Election::save_all_data()
{
  red();
  cout << "\n==========================================\n";
  cout << "     Saving Election System Data    \n";
  cout << "==========================================\n\n";
reset();
  save_voters_to_file();
  save_mna_candidates_to_file();
  save_mpa_candidates_to_file();
  save_votes_to_file();
  save_vote_counts_to_file();
  save_ledger_to_file();
green();
  cout << "\n==========================================\n";
  cout << "   All Data Saved Successfully!    \n";
  cout << "==========================================\n\n";
reset();
}

void Election::load_all_data()
{
    red();
  cout << "\n==========================================\n";
  cout << "    Loading Election System Data...   \n";
  cout << "==========================================\n\n";
reset();
  load_voters_from_file();
  load_mna_candidates_from_file();
  load_mpa_candidates_from_file();
  load_votes_from_file();
  load_vote_counts_from_file();
  load_ledger_from_file();
 green();
  cout << "\n==========================================\n";
  cout << "   All Data Loaded Successfully!    \n";
  cout << "==========================================\n\n";
  reset();
}