#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Player {
protected:
    string name;
    int age;
    string team;
    int playerID;

public:
    Player(string name, int age, string team, int playerID)
        : name(name), age(age), team(team), playerID(playerID) {}

    virtual void calculatePerformance() = 0;
    virtual string getRole() = 0;
    virtual void displayDetails() {
        cout << "Name: " << name << ", Age: " << age << ", Team: " << team << endl;
    }
};


class FootballPlayer : public Player {
private:
    int goalsScored;
    int assists;

public:
    FootballPlayer(string name, int age, string team, int playerID, int goalsScored, int assists)
        : Player(name, age, team, playerID), goalsScored(goalsScored), assists(assists) {}

    void calculatePerformance() override {
        cout << "Football Player Performance: Goals Scored: " << goalsScored << ", Assists: " << assists << endl;
    }

    string getRole() override {
        return "Football Player";
    }
};


class CricketPlayer : public Player {
private:
    int runsScored;
    int wicketsTaken;

public:
    CricketPlayer(string name, int age, string team, int playerID, int runsScored, int wicketsTaken)
        : Player(name, age, team, playerID), runsScored(runsScored), wicketsTaken(wicketsTaken) {}

    void calculatePerformance() override {
        cout << "Cricket Player Performance: Runs Scored: " << runsScored << ", Wickets Taken: " << wicketsTaken << endl;
    }

    string getRole() override {
        return "Cricket Player";
    }
};

class Team {
private:
    string teamName;
    vector<Player*> players;

public:
    Team(string teamName) : teamName(teamName) {}

    void addPlayer(Player* player) {
        players.push_back(player);
    }

    void displayTeam() {
        cout << "Team: " << teamName << endl;
        for (Player* player : players) {
            player->displayDetails();
        }
    }

    string getTeamName() {
        return teamName;
    }
};

class Tournament {
private:
    string name;
    vector<Team> teams;

public:
    Tournament(string name) : name(name) {}

    void addTeam(Team team) {
        teams.push_back(team);
    }

    void displayTournament() {
        cout << "Tournament: " << name << endl;
        for (Team& team : teams) {
            team.displayTeam();
        }
    }
};


class StatsManager {
public:
    void updateStats(Player* player) {
        cout << "Updating stats for: " << player->getRole() << endl;
    }

    void getStats(Player* player) {
        cout << "Displaying stats for: " << player->getRole() << endl;
    }
};

class UserInterfaceManager {
public:
    void displaymenu() {
        int choice;
        cout << "1. Admin Menu\n";
        cout << "2. User Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            adminMenu();
        } else if (choice == 2) {
            userMenu();
        } else {
            cout << "Invalid choice.\n";
        }
    }

    void adminMenu() {
        int choice;
        cout << "\nAdmin Menu:\n";
        cout << "1. Add Team\n";
        cout << "2. View Tournament\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTeamMenu();
                break;
            case 2:
                viewTournamentMenu();
                break;
            case 3:
                cout << "Exiting Admin Menu.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }

    void addTeamMenu() {
        string teamName;
        cout << "Enter Team Name: ";
        cin >> teamName;
        Team newTeam(teamName);
        // Logic to add players 
        cout << "Team " << teamName << " added.\n";
    }

    void viewTournamentMenu() {
        // Logic to view tournament details 
        cout << "Viewing Tournament...\n";
    }

    void userMenu() {
        int choice;
        cout << "\nUser Menu:\n";
        cout << "1. View Player Stats\n";
        cout << "2. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewPlayerStats();
                break;
            case 2:
                cout << "Exiting User Menu.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }

    void viewPlayerStats() {
        // Logic to view player stats 
        cout << "Viewing Player Stats...\n";
    }
};

// Main function
int main() {
    UserInterfaceManager uimanager;
    uimanager.displaymenu();
    return 0;
}
