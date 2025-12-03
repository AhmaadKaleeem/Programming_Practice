#include "libraries.h"
#include "election.h"
#include "console_color.h"
#include "utilities.h"
#include "voting_time.h"
using namespace std;

int main()
{
    VoterManager voterManager;
    Election election(&voterManager);
    Admin admin(&election);

    int choice;
    system("cls");
    election.load_all_data();
    this_thread::sleep_for(chrono::seconds(3));
    do
    {

        system("cls");
        yellow();
        cout << "*******************************************\n";
        cout << "**                                       **\n";
        cout << "**";
        green();
        cout << "    Pakistan Digital Election 2025 ";
        yellow();
        cout << "    **\n";
        cout << "**                                       **\n";
        cout << "*******************************************\n";
        red();
        cout << "\nReminder Alert! Follow the Following Schedule For Voting\n";
        blue();
        display_voting_schedule();
        black();
        cout << "+---------------------------------------+\n";
        cout << "| 1. Register Voter                     |\n";
        cout << "| 2. Login as Voter                     |\n";
        cout << "| 3. Login as Admin                     |\n";
        cout << "| 4. Results                            |\n";
        cout << "| 5. Exit                               |\n";
        cout << "+---------------------------------------+\n";
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
            cout << "      VOTER REGISTRATION \n";
            cout << "========================================\n";
            reset();
            voterManager.add_voter();
            cout << "\nPress Enter to return to main menu...";
            cin.ignore();
            cin.get();
            break;
        case 2:
        {
            system("cls");
            green();
            cout << "========================================\n";
            cout << "         VOTER LOGIN \n";
            cout << "========================================\n";
            reset();

            string cnic, password;
            cin.ignore();
            blue();
            cout << "Enter CNIC: ";
            reset();
            getline(cin, cnic);
            blue();
            cout << "Enter Password: ";
            reset();
            password = hide_password();
            if (voterManager.authenticate_voter(cnic, password))
            {
                system("cls");
                election.voter_menu(cnic);
            }
            else
            {
                red();
                cout << "Invalid Credentials\n";
                reset();
            }
            break;
        }
        case 3:
            system("cls");
            if (admin.authenticate_admin())
            {
                admin.admin_panel();
            }
            break;
        case 4:

            int res_choice;
            do
            {
                system("cls");
                yellow();
                cout << "========================================\n";
                cout << "    ELECTION RESULTS \n";
                cout << "========================================\n";
                reset();
                blue();
                cout << "1. View Vote Counts (All Candidates)\n";
                cout << "2. View Current Winners\n";
                cout << "3. Back to Main Menu\n";
                reset();

                blue();
                cout << "Enter Choice: ";
                reset();
                cin >> res_choice;
                if (!check_valid_int())
                {
                    continue;
                }

                switch (res_choice)
                {
                case 1:
                    system("cls");
                    green();
                    cout << "\n--- Vote Counts ---\n";
                    reset();
                    election.display_all_votes();
                    cout << "\nPress Enter to continue...";
                    cin.ignore();
                    cin.get();
                    break;

                case 2:
                    system("cls");
                    green();
                    cout << "\n--- Current Winners ---\n";
                    reset();
                    election.display_winners_till_now();
                    cout << "\nPress Enter to continue...";
                    cin.ignore();
                    cin.get();
                    break;

                case 3:
                    yellow();
                    cout << "Returning to Main Menu...\n";
                    reset();
                    cout << "\nPress Enter to return to main menu...";
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
            } while (res_choice != 3);
            break;

        case 5:
            system("cls");
            green();
            cout << "========================================\n";
            cout << "          Exiting the System\n";
            cout << "========================================\n";
            reset();
            election.save_all_data();
            cout << "\nPress Enter to exit...";
            cin.ignore();
            cin.get();
            break;

        default:
            red();
            cout << "Invalid Choice\n";
            reset();
            cout << "\nPress Enter to return to menu...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 5);
}
