#include <ledger.h>
#include <libraries.h>
using namespace std;

LedgerBlock::LedgerBlock(int u_index, const string &u_c_cnic, const string &u_vcnic, const string &u_type, const string &u_hash) : index(u_index), candidate_cnic(u_c_cnic), voter_cnic(u_vcnic), vote_type(u_type), prev_hash(u_hash), next(nullptr)
{
    this->timestamp = get_time();
    this->current_hash = calculate_hash();
}
string LedgerBlock::get_time()
{
    time_t current_time_now = time(0);
    string current_timestamp = ctime(&current_time_now);
    current_timestamp.pop_back();
    return current_timestamp;
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
    cout << "Block Added To Ledger Successfully\n";
}

bool Ledger::verify_ledger() const
{
    if (head == nullptr)
    {
        cout << "No Ledger Recorded\n";
        return true;
    }
    LedgerBlock *current_temp = head;
    LedgerBlock *next_temp = head->next;
    while (next_temp != nullptr)
    {
        string temp_hash = current_temp->calculate_hash();
        // checking if current block is correct
        if (temp_hash != current_temp->current_hash)
        {
            cout << "Hash Mismatch! Tampering Detected in Block '" << current_temp->index << "' \n";
            return false;
        }
        // Check if next block's previous hash matches current block's hash
        if (next_temp->prev_hash != current_temp->current_hash)
        {
            cout << "Hash Mismatch! Blockchain link broken between Block " << current_temp->index << " and Block " << next_temp->index << "\n";
            return false;
        }

        current_temp = next_temp;
        next_temp = next_temp->next;
    }

    // Verifing Last Block
    string last_hash = current_temp->calculate_hash();
    if (last_hash != current_temp->current_hash)
    {
        cout << "Hash Mismatch! Tampering Detected in Block '" << current_temp->index << "' \n";
        return false;
    }
    cout << "Hash Mismatch! Tampering Detected in Block '" << current_temp->index << "' \n";
    return false;

      
}
void Ledger::display_ledger() const
{
    if (head == nullptr)
    {
        cout << "\n----- Ledger is Empty -----\n";
        return;
    }

    LedgerBlock *temp = head;

    cout << "\n========== LEDGER RECORDS ==========\n";

    while (temp != nullptr)
    {
        cout << "\n-------------------------------------\n";
        cout << "Block Index:      " << temp->index << "\n";
        cout << "Timestamp:        " << temp->timestamp << "\n";
        cout << "Voter CNIC:       " << temp->voter_cnic << "\n";
        cout << "Candidate CNIC:   " << temp->candidate_cnic << "\n";
        cout << "Vote Type:        " << temp->vote_type << "\n";
        cout << "Previous Hash:    " << temp->prev_hash << "\n";
        cout << "Current Hash:     " << temp->current_hash << "\n";
        cout << "-------------------------------------\n";

        temp = temp->next;
    }

    cout << "========== END OF LEDGER ==========\n";
}
