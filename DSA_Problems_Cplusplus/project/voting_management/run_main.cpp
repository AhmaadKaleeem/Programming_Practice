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
    do
    {
        system("cls");
        yellow();
        cout << "*******************************************\n";
        cout << "**                                       **\n";
        cout << "**";
        green();
        cout << "  Pakistan Election Management System";
        yellow();
        cout << "  **\n";
        cout << "**                                       **\n";
        cout << "*******************************************\n";
        red();
        cout << "Reminder Alert! Follow the Following Schedule For Voting\n";
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
        cin >> choice;
        reset();

        switch (choice)
        {
        case 1:
            system("cls");
            voterManager.add_voter();
            cout << "\nPress Enter to return to main menu...";
            cin.ignore();
            cin.get();
            break;
        case 2:
        {
            system("cls");
            string cnic, password;
            cin.ignore();
            cout << "Enter CNIC: ";
            getline(cin, cnic);
            cout << "Enter Password: ";
            password = hide_password();
            if (voterManager.authenticate_voter(cnic, password))
            {
                system("cls");
                election.voter_menu(cnic);
            }
            else
            {
                cout << "Invalid Credentials\n";
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
                cout << "\n==== Election Results Menu ====\n";
                cout << "1. View Vote Counts (All Candidates, All Seats)\n";
                cout << "2. View Current Winners (NA & Provincial Seats)\n";
                cout << "3. Back to Main Menu\n";
                cout << "Enter Choice: ";

                cin >> res_choice;

                switch (res_choice)
                {
                case 1:
                    cout << "\n--- Vote Counts ---\n";
                    election.display_all_votes();
                    break;
                case 2:
                    cout << "\n--- Current Winners ---\n";
                    election.display_winners_till_now();
                    break;
                case 3:
                    cout << "Returning to Main Menu...\n";
                    break;
                default:
                    cout << "Invalid Choice\n";
                }
            } while (res_choice != 3);
            break;

        case 5:
            cout << "Election Ended. Exiting the Election...\n";
            break;
        default:
            cout << "Invalid Choice\n";
        }
    } while (choice != 5);
}
