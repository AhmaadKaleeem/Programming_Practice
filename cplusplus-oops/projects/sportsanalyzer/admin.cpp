#include "Admin.h"
#include "Tournment.h"
#include "cricketplayer.h"
#include "footballplayer.h"
#include "Utility.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<Tournament> tournaments;

bool Admin::login() { 
    string username, password;
    // Asking User Input for Admin Login
    cout << "Enter Admin username: ";
    getline(cin, username);
    cout << "Enter Password: ";
    getline(cin, password);
   
    ifstream admincheck("admin_credentials.txt");
    string stored_username, stored_pass;
    bool found = false;
   
    if (!admincheck.is_open()) {
        cout << "Error! Could not open file\n";
        return false;
    }
    while (admincheck >> stored_username >> stored_pass) {
        if (stored_username == username && stored_pass == password) {
            log_tofile("Admin logged in: " + username);
            found = true;
            break;
        }
    }
   // Closing File
    admincheck.close();
   
    if (!found) {
        cout << "Invalid credentials.\n";
        return false;
    }

    return true;
}


void Admin::log_tofile(const string& action) {
    Utility::log_adminaction(action);
}
// helper function that searches&   returns a pointer to the tournament that matches the given name.
Tournament* findTournament(const string& name) {
    for (auto& t : tournaments)
    {      
        if (t.getname() == name)
        return &t;
    }
        return nullptr;
}

void Admin::adminmenu() {
    int choice;
    do {
        cout << "\n============ Admin Panel ============\n";
        cout << "1. Add Tournament\n";
        cout << "2. Delete Tournament\n";
        cout << "3. Add Team\n";
        cout << "4. Delete Team\n";
        cout << "5. Add Player\n";
        cout << "6. Add Match Score\n";
        cout << "7. Add Player Stats\n";
        cout << "8. View Tournament Info\n";
        cout << "9. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addTournament(); break;
            case 2: deleteTournament(); break;
            case 3: addTeam(); break;
            case 4: deleteTeam(); break;
            case 5: addPlayerToTeam(); break;
            case 6: addMatch(); break;
            case 7: addStats(); break;
            case 8: displayTournaments(); break;
            case 9: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 9);
}

// Declaring Admin Panel Functions

void Admin::addTournament() {
    string name, sport;
    cout << "Enter Tournament Name: ";
    getline(cin, name);
   // Asking Sport and Validating
    while (true) {
    cout << "Enter sport (cricket/football): ";
    getline(cin, sport);

    if (Utility::isValidSport(sport)) {
        break;
    } else {
        cout << "Invalid sport. Please enter 'cricket' or 'football'.\n";
    }
}

    tournaments.emplace_back(name, sport); // using for efficient code , directly call constructor otherwise we haave to create an obj temp then push back
    log_tofile("Tournament added: " + name + " (" + sport + ")");
}

void Admin::deleteTournament() {
    string name;
    cout << "Enter Tournament Name to delete: ";
    getline(cin, name);
    for (auto it = tournaments.begin(); it != tournaments.end(); ++it) {
        if (it->getname() == name) {
            tournaments.erase(it);
            log_tofile("Tournament deleted: " + name);
            cout << "Tournament deleted successfully.\n";
            return;
        }
    }
    cout << "Tournament not found.\n";
}

void Admin::addTeam() {
    string tname, teamname;
    cout << "Enter Tournament Name: ";
    getline(cin, tname);

    Tournament* t = findTournament(tname);
    if (!t) {
        cout << "Tournament not found.\n";
        return;
    }

    cout << "Enter Team Name: ";
    getline(cin, teamname);

    if (t->teamExists(teamname)) {
        cout << "Team already exists in this tournament.\n";
        return;
    }

    Team newTeam(teamname, t->getsport());
    t->addteam(newTeam);

    log_tofile("Team added: " + teamname + " in Tournament " + tname);
    cout << "Team added successfully.\n";
}


void Admin::deleteTeam() {
    string tname, teamname;
    cout << "Enter Tournament Name: ";
    getline(cin, tname);
    Tournament* t = findTournament(tname);
    if (!t) { 
        cout << "Tournament not found.\n"; 
        return; 
    }
    cout << "Enter Team Name to delete: ";
    getline(cin, teamname); 

    if(t->teamExists(teamname)) {
        t->deleteteam(teamname);
        log_tofile("Team deleted: " + teamname + " from Tournament " + tname);
        cout << "Team deleted successfully.\n";
    } else {
        cout << "Team not found.\n";
    }
}

void Admin::addPlayerToTeam() {
    string tname, teamname, pname;
    int age;
    cout << "Enter Tournament Name: ";
    getline(cin, tname);
    Tournament* t = findTournament(tname);
    if (!t) { cout << "Tournament not found.\n"; return; }

    cout << "Enter Team Name: ";
    getline(cin, teamname);
    Team* team = t->findTeam(teamname);
    if (!team) { cout << "Team not found.\n"; return; }

    cout << "Enter Player Name: ";
    getline(cin, pname);
    cout << "Enter Age: ";
    cin >> age;
    cin.ignore();

    Player* p = nullptr;
    if (t->getsport() == "Cricket") {
        p = new CricketPlayer(pname, age, teamname);
    } else if (t->getsport() == "Football") {
        p = new FootballPlayer(pname, age, teamname);
    }

    if (p) {
        team->addPlayer(*p);
        log_tofile("Added player " + pname + " to team " + teamname + " in tournament " + tname);
        cout << "Player added successfully.\n";
    } else {
        cout << "Unsupported sport.\n";
    }
}

void Admin::addMatch() {
    string teamA, teamB, date;
    int scoreA, scoreB;

    cout << "Enter Team A: ";
    getline(cin, teamA);
    cout << "Enter Team B: ";
    getline(cin, teamB);
    cout << "Enter Score A: ";
    cin >> scoreA;
    cout << "Enter Score B: ";
    cin >> scoreB;
    cin.ignore();
    cout << "Enter Date: ";
    getline(cin, date);

    Match m(teamA, teamB, scoreA, scoreB, date);
    m.decide_winner();
    m.displaymatch();

    Utility::savematch_tofile(m);
    log_tofile("Match added: " + teamA + " vs " + teamB);
}

void Admin::addStats() {
    string tname, teamname, pname;
    cout << "Enter Tournament Name: ";
    getline(cin, tname);

    Tournament* t = findTournament(tname);
    if (!t) { 
    cout << "Tournament not found.\n"; 
    return; 
    } 

    cout << "Enter Team Name: ";
    getline(cin, teamname);
    Team* team = t->findTeam(teamname);
    if (!team) { cout << "Team not found.\n"; return; }

    cout << "Enter Player Name: ";
    getline(cin, pname);

    for (Player* p : team->getPlayers()) {
        if (p->getName() == pname) {
            if (t->getsport() == "Cricket") {
                CricketPlayer* cp = dynamic_cast<CricketPlayer*>(p);
                if (cp) {
                    int runs, wickets;
                    cout << "Enter runs: "; cin >> runs;
                    cout << "Enter wickets: "; cin >> wickets;
                    cin.ignore();
                    cp->addruns(runs);
                    cp->addwickets(wickets);
                    log_tofile("Updated stats for Cricket Player: " + pname);
                    return;
                }
            } else if (t->getsport() == "Football") {
                FootballPlayer* fp = dynamic_cast<FootballPlayer*>(p);
                if (fp) {
                    int goals, assists;
                    cout << "Enter goals: "; cin >> goals;
                    cout << "Enter assists: "; cin >> assists;
                    cin.ignore();
                    for (int i = 0; i < goals; ++i) fp->scoregoal();
                    for (int i = 0; i < assists; ++i) fp->addassist();
                    log_tofile("Updated stats for Football Player: " + pname);
                    return;
                }
            }
            cout << "Unsupported sport.\n";
            return;
        }
    }
    cout << "Player not found.\n";
}

void Admin::displayTournaments() {
    for (const auto& t : tournaments) {
        t.displaytournament();
    }
}
