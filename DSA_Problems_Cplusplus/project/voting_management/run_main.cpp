#include "libraries.h"
#include "election.h"
using namespace std;
int main()
{
    VoterManager voterManager;
    Election election(&voterManager);
    Admin admin(&election);

    int choice;
    do
    {
        cout << "==== Election Management System ====\n";
        cout << "1. Register Voter\n2. Login as Voter\n3. Login as Admin\n4. Results \n5. Exit\n";
        cin >> choice;

        switch (choice)
        {
        case 1:
            voterManager.add_voter();
            break;
        case 2:
        {
            string cnic, password;
            cin.ignore();
            cout << "Enter CNIC: ";
            getline(cin, cnic);
            cout << "Enter Password: ";
            getline(cin, password);
            if (voterManager.authenticate_voter(cnic, password))
            {
                election.voter_menu(cnic);
            }
            else
            {
                cout << "Invalid Credentials\n";
            }
            break;
        }
        case 3:
            if (admin.authenticate_admin())
            {
                admin.admin_panel();
            }
            break;
        case 4:
            int res_choice;
            do
            {
                cout << "\n==== Election Results Menu ====\n";
                cout << "1. View Vote Counts (All Candidates, All Seats)\n";
                cout << "2. View Current Winners (NA & Provincial Seats)\n";
                cout << "3. Back to Main Menu\n";
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
            } 
            while (res_choice != 3);
            break;
        
    case 5:
        cout << "Election Ended. Exiting the Election...\n";
        break;
    default:
        cout << "Invalid Choice\n";
    }
}
while (choice != 5)    ;
}
