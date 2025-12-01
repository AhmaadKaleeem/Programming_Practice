#include "libraries.h"
#include "election.h"
#include "utilities.h"
#include "admin_panel.h"
#include "console_color.h"
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
    system("cls");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string input_user, input_pass;

    green();
    cout << "========================================\n";
    cout << "      ADMIN AUTHENTICATION\n";
    cout << "========================================\n";
    reset();

    blue();
    cout << "Enter Admin Username: ";
    reset();
    getline(cin, input_user);

    blue();
    cout << "Enter Admin Password: ";
    reset();
    input_pass = hide_password();

    if (login_admin.find(input_user) != login_admin.end())
    {
        if (login_admin[input_user] == input_pass)
        {
            system("cls");
            green();
            cout << "========================================\n";
            cout << "     Login Successful! Welcome, ";
            cout << input_user << ".\n";
            cout << "========================================\n";
            reset();
            cout << "\nPress Enter to continue...";
            cin.get();
            return true;
        }
    }

    system("cls");
    red();
    cout << "========================================\n";
    cout << "     Login Failed. Invalid Credentials.\n";
    cout << "========================================\n";
    reset();
    cout << "\nPress Enter to return...";
    cin.get();
    return false;
}

void Admin::admin_panel()
{
    int choice;
    do
    {
        system("cls");

        yellow();
        cout << "=========================================\n";
        cout << "          ADMIN PANEL MENU\n";
        cout << "=========================================\n";
        reset();

        black();
        cout << "+---------------------------------------+\n";
        cout << "| 1. Add MNA Candidate                  |\n";
        cout << "| 2. Add MPA Candidate                  |\n";
        cout << "| 3. Display All MNA Candidates         |\n";
        cout << "| 4. Display All MPA Candidates         |\n";
        cout << "| 5. Tally All Results                  |\n";
        cout << "| 6. Verify Ledger Integrity            |\n";
        cout << "| 7. View Ledger File                   |\n";
        cout << "| 8. Exit                               |\n";
        cout << "+---------------------------------------+\n";
        reset();

        blue();
        cout << "Enter Choice: ";
        reset();
        cin >> choice;
        if (!check_valid_int())
        {
            continue;
        }
        switch (choice)
        {
        case 1:
            system("cls");
            green();
            cout << "========================================\n";
            cout << "     ADD MNA CANDIDATE\n";
            cout << "========================================\n";
            reset();
            this->election->add_mna_admin();
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            break;

        case 2:
            system("cls");
            green();
            cout << "========================================\n";
            cout << "     ADD MPA CANDIDATE\n";
            cout << "========================================\n";
            reset();
            this->election->add_mpa_admin();
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            break;

        case 3:
            system("cls");
            blue();
            cout << "========================================\n";
            cout << "     ALL MNA CANDIDATES\n";
            cout << "========================================\n";
            reset();
            this->election->display_mna();
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            break;

        case 4:
            system("cls");
            blue();
            cout << "========================================\n";
            cout << "     ALL MPA CANDIDATES\n";
            cout << "========================================\n";
            reset();
            this->election->display_mpa();
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            break;

        case 5:
            system("cls");
            yellow();
            cout << "========================================\n";
            cout << "     TALLYING RESULTS\n";
            cout << "========================================\n";
            reset();
            this->election->tally_mna_results();
            this->election->tally_mpa_results();
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            break;

        case 6:
            system("cls");
            blue();
            cout << "========================================\n";
            cout << "     VERIFYING LEDGER INTEGRITY\n";
            cout << "========================================\n";
            reset();
            this->election->verify_ledger_admin();
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            break;

        case 7:
            system("cls");
            yellow();
            cout << "========================================\n";
            cout << "     LEDGER FILE\n";
            cout << "========================================\n";
            reset();
            this->election->display_ledger();
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            break;

        case 8:
            system("cls");
            green();
            cout << "========================================\n";
            cout << "     Exiting Admin Panel\n";
            cout << "========================================\n";
            reset();
            cout << "\nPress Enter to return...";
            cin.ignore();
            cin.get();
            break;

        default:
            red();
            cout << "Invalid Choice\n";
            reset();
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 8);
}