#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

class Player {
protected:
    string name, position;
    int age;
    static int playerCount;

public:
    Player(const string& n, int a, const string& pos) : name(n), age(a), position(pos) {
        playerCount++;
    }
    virtual void displayStats() const = 0;
    string getName() const { return name; }
    string getPosition() const { return position; }
    int getAge() const { return age; }
    static int getPlayerCount() { return playerCount; }
    virtual int getPerformanceMetric() const = 0;
    virtual string serialize() const = 0;
    virtual ~Player() {}
};

int Player::playerCount = 0;

class FootballPlayer : public Player {
private:
    int goals, assists, passes;

public:
    FootballPlayer(string n, int a, string pos, int g, int as, int p)
        : Player(n, a, pos), goals(g), assists(as), passes(p) {}

    void displayStats() const override {
        cout << left << setw(15) << name << setw(10) << age << setw(15) << position
             << setw(10) << goals << setw(10) << assists << setw(10) << passes << endl;
    }

    int getGoals() const { return goals; }
    int getPerformanceMetric() const override { return goals + assists; }

    string serialize() const override {
        return name + "," + to_string(age) + "," + position + "," + to_string(goals) + "," + to_string(assists) + "," + to_string(passes);
    }
};

class CricketPlayer : public Player {
private:
    int runs, wickets;
    float strikeRate;

public:
    CricketPlayer(string n, int a, string pos, int r, int w, float sr)
        : Player(n, a, pos), runs(r), wickets(w), strikeRate(sr) {}

    void displayStats() const override {
        cout << left << setw(15) << name << setw(10) << age << setw(15) << position
             << setw(10) << runs << setw(10) << wickets << setw(10) << fixed << setprecision(2) << strikeRate << endl;
    }

    int getPerformanceMetric() const override { return runs + wickets * 10; }

    string serialize() const override {
        return name + "," + to_string(age) + "," + position + "," + to_string(runs) + "," + to_string(wickets) + "," + to_string(strikeRate);
    }
};

class Team {
private:
    string teamName;
    vector<shared_ptr<Player>> players;
    int wins, losses, draws;

public:
    Team(string name) : teamName(name), wins(0), losses(0), draws(0) {}

    void addPlayer(shared_ptr<Player> p) {
        players.push_back(p);
    }

    void displayTeam() const {
        cout << "\nTeam: " << teamName << endl;
        for (size_t i = 0; i < players.size(); ++i)
            players[i]->displayStats();
    }

    void setRecord(int w, int l, int d) {
        wins = w; losses = l; draws = d;
    }

    int getPoints() const {
        return wins * 3 + draws;
    }

    string getTeamName() const { return teamName; }

    vector<shared_ptr<Player>> getPlayers() const { return players; }

    string serialize() const {
        string data = teamName + "," + to_string(wins) + "," + to_string(losses) + "," + to_string(draws) + "\n";
        for (size_t i = 0; i < players.size(); ++i)
            data += players[i]->serialize() + "\n";
        return data;
    }
};

vector<shared_ptr<Player>> footballPlayers, cricketPlayers;
vector<shared_ptr<Team>> footballTeams, cricketTeams;

// Utility Functions
void displayTopPlayers(vector<shared_ptr<Player>>& players, int count) {
    sort(players.begin(), players.end(), [](const shared_ptr<Player>& a, const shared_ptr<Player>& b) {
        return a->getPerformanceMetric() > b->getPerformanceMetric();
    });
    for (int i = 0; i < count && i < players.size(); ++i)
        players[i]->displayStats();
}

void filterByPosition(const vector<shared_ptr<Player>>& players, const string& pos) {
    for (const auto& player : players) {
        if (player->getPosition() == pos)
            player->displayStats();
    }
}

void searchPlayerByName(const vector<shared_ptr<Player>>& players, const string& name) {
    bool found = false;
    for (const auto& player : players) {
        if (player->getName() == name) {
            player->displayStats();
            found = true;
        }
    }
    if (!found) cout << "Player not found.\n";
}

void displayLeaderboard(vector<shared_ptr<Team>>& teams) {
    sort(teams.begin(), teams.end(), [](const shared_ptr<Team>& a, const shared_ptr<Team>& b) {
        return a->getPoints() > b->getPoints();
    });
    cout << left << setw(20) << "Team" << "Points\n";
    for (const auto& team : teams)
        cout << left << setw(20) << team->getTeamName() << team->getPoints() << endl;
}

void deleteTeam(vector<shared_ptr<Team>>& teams, const string& name) {
    auto it = remove_if(teams.begin(), teams.end(), [&](const shared_ptr<Team>& team) {
        return team->getTeamName() == name;
    });
    if (it != teams.end()) {
        teams.erase(it, teams.end());
        cout << "Team '" << name << "' deleted successfully.\n";
    } else {
        cout << "Team not found.\n";
    }
}

// File I/O Functions
void saveData(const string& filename, const vector<shared_ptr<Team>>& teams) {
    ofstream out(filename);
    if (!out) {
        cout << "Error: Unable to save data to " << filename << ".\n";
        return;
    }
    for (const auto& team : teams) {
        out << "#TEAM\n" << team->serialize();
    }
    out.close();
    cout << "Data saved to " << filename << ".\n";
}

void loadData(const string& filename, vector<shared_ptr<Player>>& players, vector<shared_ptr<Team>>& teams, bool isCricket) {
    ifstream in(filename);
    if (!in) return;

    string line;
    shared_ptr<Team> currentTeam = nullptr;
    while (getline(in, line)) {
        if (line == "#TEAM") {
            getline(in, line);
            string name;
            int w, l, d;
            stringstream ss(line);
            getline(ss, name, ',');
            ss >> w; ss.ignore(); ss >> l; ss.ignore(); ss >> d;
            currentTeam = make_shared<Team>(name);
            currentTeam->setRecord(w, l, d);
            teams.push_back(currentTeam);
        } else {
            string name, pos;
            int age, s1, s2;
            float s3;
            stringstream ss(line);
            getline(ss, name, ',');
            ss >> age; ss.ignore();
            getline(ss, pos, ',');
            ss >> s1; ss.ignore(); ss >> s2; ss.ignore(); ss >> s3;
            shared_ptr<Player> p;
            if (isCricket)
                p = make_shared<CricketPlayer>(name, age, pos, s1, s2, s3);
            else
                p = make_shared<FootballPlayer>(name, age, pos, s1, s2, (int)s3);
            players.push_back(p);
            currentTeam->addPlayer(p);
        }
    }
    in.close();
    cout << "Loaded from " << filename << ".\n";
}

// Admin Authentication
bool authenticateAdmin() {
    string user, pass;
    cout << "Enter admin username: "; cin >> user;
    cout << "Enter password: "; cin >> pass;

    // Example of hashed password check (replace with actual hashing logic)
    string hashedPassword = "1234"; // Replace with hashed value
    return user == "admin" && pass == hashedPassword;
}

// User Menu
void sportUserMenu(bool isCricket) {
    int ch;
    vector<shared_ptr<Player>>& players = isCricket ? cricketPlayers : footballPlayers;
    vector<shared_ptr<Team>>& teams = isCricket ? cricketTeams : footballTeams;
    string input;
    do {
        cout << "\n--- User Menu ---\n";
        cout << "1. View All Teams\n2. Search Player\n3. Filter by Position\n4. Top 10 Players\n5. Leaderboard\n6. Delete a Team\n0. Back\nChoice: ";
        cin >> ch;
        switch (ch) {
            case 1: for (const auto& team : teams) team->displayTeam(); break;
            case 2: cout << "Name: "; cin.ignore(); getline(cin, input); searchPlayerByName(players, input); break;
            case 3: cout << "Position: "; cin.ignore(); getline(cin, input); filterByPosition(players, input); break;
            case 4: displayTopPlayers(players, 10); break;
            case 5: displayLeaderboard(teams); break;
            case 6: cout << "Enter team name to delete: "; cin.ignore(); getline(cin, input); deleteTeam(teams, input); break;
        }
    } while (ch != 0);
}

// Admin Menu
void sportAdminMenu(bool isCricket) {
    int c;
    do {
        cout << "\n--- Admin Menu for " << (isCricket ? "Cricket" : "Football") << " ---\n";
        cout << "1. Add Team\n2. Add Player\n3. Save\n4. Load\n0. Back\nChoice: ";
        cin >> c;
        switch (c) {
            case 1: {
                string name;
                cout << "Team Name: "; cin.ignore(); getline(cin, name);
                shared_ptr<Team> t = make_shared<Team>(name);
                (isCricket ? cricketTeams : footballTeams).push_back(t);
                cout << "Team added.\n";
                break;
            }
            case 2: {
                vector<shared_ptr<Team>>& teams = isCricket ? cricketTeams : footballTeams;
                vector<shared_ptr<Player>>& players = isCricket ? cricketPlayers : footballPlayers;

                if (teams.empty()) {
                    cout << "No teams available. Please add a team first.\n";
                    break;
                }

                string name, pos;
                int age, s1, s2, teamIndex;
                float s3;

                cout << "Enter Player Details:\n";
                cout << "Name: "; cin.ignore(); getline(cin, name);
                cout << "Age: "; cin >> age;
                cout << "Position: "; cin.ignore(); getline(cin, pos);

                if (isCricket) {
                    cout << "Runs: "; cin >> s1;
                    cout << "Wickets: "; cin >> s2;
                    cout << "Strike Rate: "; cin >> s3;
                } else {
                    cout << "Goals: "; cin >> s1;
                    cout << "Assists: "; cin >> s2;
                    cout << "Passes: "; cin >> s3;
                }

                cout << "Available Teams:\n";
                for (size_t i = 0; i < teams.size(); ++i)
                    cout << i + 1 << ". " << teams[i]->getTeamName() << endl;

                cout << "Choose a team (1-" << teams.size() << "): ";
                cin >> teamIndex;

                if (teamIndex < 1 || teamIndex > teams.size()) {
                    cout << "Invalid team selection.\n";
                    break;
                }

                shared_ptr<Player> p;
                if (isCricket)
                    p = make_shared<CricketPlayer>(name, age, pos, s1, s2, s3);
                else
                    p = make_shared<FootballPlayer>(name, age, pos, s1, s2, (int)s3);
                
                players.push_back(p);
                teams[teamIndex - 1]->addPlayer(p);
                cout << "Player added successfully to " << teams[teamIndex - 1]->getTeamName() << ".\n";
                break;
            }
            case 3: saveData(isCricket ? "cricket_data.txt" : "football_data.txt", isCricket ? cricketTeams : footballTeams); break;
            case 4: loadData(isCricket ? "cricket_data.txt" : "football_data.txt", isCricket ? cricketPlayers : footballPlayers, isCricket ? cricketTeams : footballTeams, isCricket); break;
        }
    } while (c != 0);
}

// Main Menu
void mainMenu() {
    int sport;
    loadData("football_data.txt", footballPlayers, footballTeams, false);
    loadData("cricket_data.txt", cricketPlayers, cricketTeams, true);

    do {
        cout << "\nSelect Sport:\n1. Football\n2. Cricket\n0. Exit\nChoice: ";
        cin >> sport;
        if (sport == 0) break;

        bool isCricket = sport == 2;
        int role;
        cout << "1. Admin\n2. User\nChoice: ";
        cin >> role;

        if (role == 1) {
            if (authenticateAdmin()) {
                sportAdminMenu(isCricket);
            } else {
                cout << "Access denied.\n";
            }
        } else {
            sportUserMenu(isCricket);
        }
    } while (sport != 0);

    saveData("football_data.txt", footballTeams);
    saveData("cricket_data.txt", cricketTeams);
}


// Utility Functions
void displayTopPlayersByStat(vector<shared_ptr<Player>>& players, const string& stat) {
    if (stat == "goals") {
        sort(players.begin(), players.end(), [](const shared_ptr<Player>& a, const shared_ptr<Player>& b) {
            return dynamic_pointer_cast<FootballPlayer>(a)->getGoals() > dynamic_pointer_cast<FootballPlayer>(b)->getGoals();
        });
    } else if (stat == "assists") {
        sort(players.begin(), players.end(), [](const shared_ptr<Player>& a, const shared_ptr<Player>& b) {
            return dynamic_pointer_cast<FootballPlayer>(a)->getAssists() > dynamic_pointer_cast<FootballPlayer>(b)->getAssists();
        });
    } else if (stat == "runs") {
        sort(players.begin(), players.end(), [](const shared_ptr<Player>& a, const shared_ptr<Player>& b) {
            return dynamic_pointer_cast<CricketPlayer>(a)->getRuns() > dynamic_pointer_cast<CricketPlayer>(b)->getRuns();
        });
    } else if (stat == "strikeRate") {
        sort(players.begin(), players.end(), [](const shared_ptr<Player>& a, const shared_ptr<Player>& b) {
            return dynamic_pointer_cast<CricketPlayer>(a)->getStrikeRate() > dynamic_pointer_cast<CricketPlayer>(b)->getStrikeRate();
        });
    }

    cout << "\nTop 10 Players by " << stat << ":\n";
    for (int i = 0; i < 10 && i < players.size(); ++i) {
        players[i]->displayStats();
    }
}

void searchPlayerByAgeRange(const vector<shared_ptr<Player>>& players, int minAge, int maxAge) {
    cout << "\nPlayers in Age Range " << minAge << "-" << maxAge << ":\n";
    for (const auto& player : players) {
        if (player->getAge() >= minAge && player->getAge() <= maxAge) {
            player->displayStats();
        }
    }
}

void calculateMVP(const vector<shared_ptr<Player>>& players) {
    if (players.empty()) {
        cout << "No players available to calculate MVP.\n";
        return;
    }

    auto mvp = max_element(players.begin(), players.end(), [](const shared_ptr<Player>& a, const shared_ptr<Player>& b) {
        return a->getPerformanceMetric() < b->getPerformanceMetric();
    });

    cout << "\nMVP Player:\n";
    (*mvp)->displayStats();
}

int main() {
    mainMenu();
    return 0;
}