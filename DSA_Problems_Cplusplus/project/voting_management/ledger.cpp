#include "ledger.h"
#include "libraries.h"
#include "console_color.h"
using namespace std;

LedgerBlock::LedgerBlock(int u_index, const string &u_c_cnic, const string &u_vcnic, const string &u_type, const string &u_hash) : index(u_index), candidate_cnic(u_c_cnic), voter_cnic(u_vcnic), vote_type(u_type), prev_hash(u_hash), next(nullptr)
{
    this->timestamp = get_time();
    this->current_hash = calculate_hash();
}

LedgerBlock::LedgerBlock(int idx, const string &c_cnic, const string &v_cnic,
                         const string &t, const string &ts, const string &h, const string &ph)
    : index(idx), candidate_cnic(c_cnic), voter_cnic(v_cnic), vote_type(t), 
      timestamp(ts), current_hash(h), prev_hash(ph), next(nullptr) {}

string LedgerBlock::get_time()
{
    time_t current_time_now = time(0);
    string current_timestamp = ctime(&current_time_now);
    current_timestamp.pop_back();
    return current_timestamp;
}

void Ledger::restore_block(int index, const string &candidate_cnic, const string &voter_cnic,
                          const string &type, const string &timestamp,
                          const string &hash, const string &prev_hash)
{
    LedgerBlock *new_block = new LedgerBlock(index, candidate_cnic, voter_cnic, type, 
                                             timestamp, hash, prev_hash);
    
    if (head == nullptr)
    {
        head = tail = new_block;
    }
    else
    {
        tail->next = new_block;
        tail = new_block;
    }
    size++;
}

string LedgerBlock::calculate_hash() const
{
    string data = to_string(index) + voter_cnic + candidate_cnic +
                  vote_type + timestamp + prev_hash;

    size_t hashed = hash<string>{}(data);
    return to_string(hashed);
}

Ledger::Ledger()
{
    head = tail = nullptr;
    size = 0;
}

Ledger::~Ledger()
{
    LedgerBlock *temp = head;
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}

string Ledger::get_last_hash() const
{
    if (tail == nullptr)
        return "0";
    else
        return tail->current_hash;
}

void Ledger::add_block(const string &candidiate, const string &voter, string &type)
{
    string last_hash = get_last_hash();
    LedgerBlock *new_block = new LedgerBlock(size, candidiate, voter, type, last_hash);
    if (head == nullptr)
    {
        head = tail = new_block;
    }
    else
    {
        tail->next = new_block;
        tail = new_block;
    }
    size++;
    green();
    cout << "Block Added To Ledger Successfully\n";
    reset();
}

bool Ledger::verify_ledger() const
{
    if (head == nullptr)
    {
        blue();
        cout << "No Ledger Recorded\n";
        reset();
        return true;
    }
    
    yellow();
    cout << "\n========== VERIFYING BLOCKCHAIN INTEGRITY ==========\n";
    reset();
    
    LedgerBlock *current_temp = head;
    LedgerBlock *next_temp = head->next;
    
    while (next_temp != nullptr)
    {
        string temp_hash = current_temp->calculate_hash();
        
        // checking if current block is correct
        if (temp_hash != current_temp->current_hash)
        {
            red();
            cout << "Hash Mismatch! Tampering Detected in Block '" << current_temp->index << "' \n";
            reset();
            return false;
        }
        
        // Check if next block's previous hash matches current block's hash
        if (next_temp->prev_hash != current_temp->current_hash)
        {
            red();
            cout << "Hash Mismatch! Blockchain link broken between Block " << current_temp->index << " and Block " << next_temp->index << "\n";
            reset();
            return false;
        }

        current_temp = next_temp;
        next_temp = next_temp->next;
    }

    // Verifying Last Block
    string last_hash = current_temp->calculate_hash();
    if (last_hash != current_temp->current_hash)
    {
        red();
        cout << "Hash Mismatch! Tampering Detected in Block '" << current_temp->index << "' \n";
        reset();
        return false;
    }
    
    green();
    cout << "========== BLOCKCHAIN VERIFIED SUCCESSFULLY ==========\n";
    reset();
    return true;
}

void Ledger::display_ledger() const
{
    if (head == nullptr)
    {
        system("cls");
        red();
        cout << "\n----- Ledger is Empty -----\n";
        reset();
        return;
    }

    system("cls");
    LedgerBlock *temp = head;

    yellow();
    cout << "\n========== LEDGER RECORDS ==========\n";
    reset();

    while (temp != nullptr)
    {
        black();
        cout << "-------------------------------------\n";
        reset();
        
        blue();
        cout << "Block Index:      ";
        reset();
        cout << temp->index << "\n";
        
        blue();
        cout << "Timestamp:        ";
        reset();
        cout << temp->timestamp << "\n";
        
        blue();
        cout << "Voter CNIC:       ";
        reset();
        cout << temp->voter_cnic << "\n";
        
        blue();
        cout << "Candidate CNIC:   ";
        reset();
        cout << temp->candidate_cnic << "\n";
        
        blue();
        cout << "Vote Type:        ";
        reset();
        cout << temp->vote_type << "\n";
        
        blue();
        cout << "Previous Hash:    ";
        reset();
        cout << temp->prev_hash << "\n";
        
        green();
        cout << "Current Hash:     ";
        reset();
        cout << temp->current_hash << "\n";
        
        black();
        cout << "-------------------------------------\n";
        reset();

        temp = temp->next;
    }

    yellow();
    cout << "========== END OF LEDGER ==========\n";
    reset();
}