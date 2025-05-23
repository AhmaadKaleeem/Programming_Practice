#pragma once
#include <string>
using namespace std;

class Tournament;

class User {
public:
    void usermenu();
    void teams_intournment();
    void players_inteam();
    void filter_by_pos();
    void top_players();
    void search_player();
    void view_leaderboard();

private:
    Tournament* select_tournment(const string& sport);
};
