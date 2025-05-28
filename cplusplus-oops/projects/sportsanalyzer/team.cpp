#include "Team.h"
#include <algorithm>
#include <iostream>

using namespace std;

Team::Team(const string& name, const string& sport)
    : name(name), sport(sport), wins(0), points(0) {}

string Team::get_name() const {
    return name;
}

string Team::get_sport() const {
    return sport;
}

int Team::get_wins() const {
    return wins;
}

int Team::get_points() const {
    return points;
}

const vector<shared_ptr<Player>>& Team::get_players() const {
    return players;
}

void Team::add_player(shared_ptr<Player> player) {
    players.push_back(player);
}

void Team::remove_player(const string& pname) {
    auto it = remove_if(players.begin(), players.end(),
        [&](const shared_ptr<Player>& p) {
            return p->get_name() == pname;
        });
    if (it != players.end()) {
        players.erase(it, players.end());
    }
}

void Team::record_win() {
    wins++;
    points += 2;
}

void Team::update_points(int pts) {
    points += pts;
}

void Team::display_team() const {
    cout << "Team: " << name << " | Sport: " << sport
         << " | Wins: " << wins << " | Points: " << points << endl;
    cout << "Players:\n";
    for (const auto& p : players) {
        p->display();
        cout << "--------------------------\n";
    }
}
