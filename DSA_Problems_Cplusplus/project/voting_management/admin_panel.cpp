#include "libraries.h"
#include "election.h"
#include "admin_panel.h"
using namespace std;

unordered_map<string, string> Admin::intialize_credentionals()
{
    unordered_map<string, string> temp = {
        {"ahmad", "Ahmad28"},
        {"sherbaz", "Sherbaz85"},
        {"haris", "Haris85"},
        {"muhiz", "Muhiz07"},
        {"Admin123", "admin456"}};
    return temp;
}

Admin::Admin(Election *e)
{
    this->login_admin = intialize_credentionals();
    this->election = e;
}

bool Admin::authenticate_admin()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string input_user, input_pass;
    cout << "Enter Admin Username: ";
    getline(cin, input_user);
    cout << "Enter Admin Password: ";
    getline(cin, input_pass);
    if (login_admin.find(input_user) != login_admin.end())
    {
        if (login_admin[input_user] == input_pass)
        {
            cout << "Login Successful! Welcome, " << input_user << ".\n";
            return true;
        }
    }
    cout << "Login Failed. Invalid credentials.\n";
    return false;
}

void Admin::admin_panel()
{
    int choice;
    do
    {
        cout << "\n==== Admin Panel ====\n";
        cout << "1. Add MNA Candidate\n2. Add MPA Candidate\n3. Display All MNA Candidates\n";
        cout << "4. Display All MPA Candidates\n5. Tally All Results\n6. Verify Ledger Integrity\n";
        cout << "7. View Ledger File\n8. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            this->election->add_mna_admin();
            break;
        case 2:
            this->election->add_mpa_admin();
            break;
        case 3:
            this->election->display_mna();
            break;
        case 4:
            this->election->display_mpa();
            break;
        case 5:
            this->election->tally_mna_results();
            this->election->tally_mpa_results();
            break;
        case 6:
            this->election->verify_ledger_admin();
            break;
        case 7:
            this->election->display_ledger();
            break;
        case 8:
            cout << "Exiting Admin Panel....\n";
            break;
        default:
            cout << "Invalid Choice\n";
        }
    } while (choice != 8);
}