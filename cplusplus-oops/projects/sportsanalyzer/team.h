#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Player.h"

using namespace std;

class Team {
    string name, sport;
    int wins, points;
    vector<shared_ptr<Player>> players;

public:
    Team(const string& name = "", const string& sport = "");
    string get_name() const;
    string get_sport() const;
    int get_wins() const;
    int get_points() const;
    const vector<shared_ptr<Player>>& get_players() const;

    void add_player(shared_ptr<Player> player);
    void remove_player(const string& pname);
    void record_win();
    void update_points(int pts);

    void set_name(const string& n) { name = n; }
    void set_wins(int w) { wins = w; }
    void set_points(int p) { points = p; }
    void setsport(const string& s) { sport = s; }

    void display_team() const;

    friend class UtilityHandler;  // optionally for direct access
};
