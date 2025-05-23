#include "User.h"
#include "Tournment.h"
#include "cricketplayer.h"
#include "footballplayer.h"
#include "Utility.h"
#include <iostream>
#include <algorithm>

using namespace std;

extern vector<Tournament> tournaments;

void toLower(string& s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}

Tournament* User::select_tournment(const string& sport) {
    cout << "Available " << sport << " tournaments:\n";
    for (const auto& t : tournaments) {
        if (toLower(t.getsport()) == sport) {
            cout << "- " << t.get_name() << endl;
        }
    }

    string tname;
    cout << "Enter tournament name: ";
    getline(cin, tname);
    
    for (auto& t : tournaments) {
        if (toLower(t.get_name()) == toLower(tname) && toLower(t.getsport()) == sport) {
            return &t;
        }
    }
    cout << "Tournament not found.\n";
    return nullptr;
}

void User::usermenu() {
    int choice;
    do {
        cout << "\n============ User Menu ============\n";
        cout << "1. View Teams\n";
        cout << "2. View Players\n";
        cout << "3. Filter Players by Position\n";
        cout << "4. View Top 10 Players\n";
        cout << "5. Search Player\n";
        cout << "6. View Leaderboard\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: teams_intournment(); break;
            case 2: players_inteam(); break;
            case 3: filter_by_pos(); break;
            case 4: top_players(); break;
            case 5: search_player(); break;
            case 6: view_leaderboard(); break;
            case 7: cout << "Exiting User Menu.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);
}

void User::teams_intournment() {
    string sport;
    cout << "Enter sport (Cricket/Football): ";
    getline(cin, sport);
    toLower(sport);

    Tournament* t = select_tournment(sport);
    if (!t) return;

    cout << "\nTeams in Tournament '" << t->get_name() << "':\n";
    for (const auto& team : t->get_teams()) {
        cout << "- " << team.get_name() << endl;
    }
}

void User::players_inteam() {
    string sport;
    cout << "Enter sport (Cricket/Football): ";
    getline(cin, sport);
    toLower(sport);

    Tournament* t = select_tournment(sport);
    if (!t) return;

    string teamname;
    cout << "Enter team name: ";
    getline(cin, teamname);

    Team* team = t->findTeam(teamname);
    if (!team) {
        cout << "Team not found.\n";
        return;
    }

    cout << "\nPlayers in Team '" << team->get_name() << "':\n";
    for (auto p : team->get_players()) {
        p->display();
        cout << "--------------------------\n";
    }
}

void User::filter_by_pos() {
    string sport;
    cout << "Enter sport (Football only): ";
    getline(cin, sport);
    toLower(sport);

    if (sport != "football") {
        cout << "Position filter is only available for Football.\n";
        return;
    }

    Tournament* t = select_tournment(sport);
    if (!t) return;

    string position;
    cout << "Enter position to filter (e.g., Midfielder, Goalkeeper): ";
    getline(cin, position);
    toLower(position);

    for (const auto& team : t->get_teams()) {
        for (Player* p : team.get_players()) {
            FootballPlayer* fp = dynamic_cast<FootballPlayer*>(p);
            if (fp && toLower(fp->getPosition()) == position) {
                fp->display();
                cout << "--------------------------\n";
            }
        }
    }
}

void User::top_players() {
    string sport;
    cout << "Enter sport (Cricket/Football): ";
    getline(cin, sport);
    toLower(sport);

    Tournament* t = select_tournment(sport);
    if (!t) return;

    vector<Player*> allPlayers;
    for (auto& team : t->get_teams()) {
        for (Player* p : team.get_players()) {
            allPlayers.push_back(p);
        }
    }

    if (sport == "cricket") {
        sort(allPlayers.begin(), allPlayers.end(), [](Player* a, Player* b) {
            CricketPlayer* ca = dynamic_cast<CricketPlayer*>(a);
            CricketPlayer* cb = dynamic_cast<CricketPlayer*>(b);
            return ca && cb && ca->get_runs() > cb->get_runs();
        });
    } else if (sport == "football") {
        sort(allPlayers.begin(), allPlayers.end(), [](Player* a, Player* b) {
            FootballPlayer* fa = dynamic_cast<FootballPlayer*>(a);
            FootballPlayer* fb = dynamic_cast<FootballPlayer*>(b);
            return fa && fb && fa->get_goals() > fb->get_goals();
        });
    }

    cout << "\nTop 10 Players by ";
    cout << (sport == "cricket" ? "Runs" : "Goals") << ":\n";
    for (size_t i = 0; i < allPlayers.size() && i < 10; ++i) {
        allPlayers[i]->display();
        cout << "--------------------------\n";
    }
}

void User::search_player() {
    string sport;
    cout << "Enter sport (Cricket/Football): ";
    getline(cin, sport);
    toLower(sport);

    Tournament* t = select_tournment(sport);
    if (!t) return;

    string pname;
    cout << "Enter player name to search: ";
    getline(cin, pname);
    toLower(pname);

    bool found = false;
    for (const auto& team : t->get_teams()) {
        for (Player* p : team.get_players()) {
            if (toLower(p->get_name()) == pname) {
                p->display();
                cout << "--------------------------\n";
                found = true;
            }
        }
    }
    if (!found) cout << "Player not found.\n";
}

void User::view_leaderboard() {
    string sport;
    cout << "Enter sport (Cricket/Football): ";
    getline(cin, sport);
    toLower(sport);

    Tournament* t = select_tournment(sport);
    if (!t) return;

    cout << "\nLeaderboard - " << t->get_name() << "\n";
    cout << "Team\t\tWins\tPoints\n";
    cout << "------------------------------\n";
    for (const auto& team : t->get_teams()) {
        cout << team.get_name() << "\t\t" << team.get_wins() << "\t" << team.get_pionts() << endl;
    }
}
