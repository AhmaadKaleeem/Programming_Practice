#include "Utility.h"
#include "Team.h"
#include "cricketplayer.h"
#include "footballplayer.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace Utility {

Bool isValidSport(const string& sportInput) {
        string sport = sportInput;

        // convert to lowercase
        for (size_t i = 0; i < sport.length(); ++i) {
            sport[i] = tolower(sport[i]);
        }

        if (sport == "cricket" || sport == "football") {
            return true;
        }
        return false;
    }
bool save_team_to_file(const Team& team, const string& filename) {
    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Error: Could not open file " << filename << " for saving.\n";
        return false;
    }

    out << team.get_name() << "\n"
        << team.get_sport() << "\n"
        << team.get_wins() << "\n"
        << team.get_points() << "\n"
        << team.get_players().size() << "\n";

    for (const auto& p : team.get_players()) {
        out << p->get_name() << "," << p->get_age() << "\n";
        if (team.get_sport() == "Cricket") {
            auto cp = dynamic_pointer_cast<CricketPlayer>(p);
            out << cp->get_runs() << "," << cp->get_wickets() << "\n";
        } else if (team.get_sport() == "Football") {
            auto fp = dynamic_pointer_cast<FootballPlayer>(p);
            out << fp->get_goals() << "," << fp->get_assists() << "," << fp->getPosition() << "\n";
        }
    }
    out.close();
    return true;
}

bool load_team_from_file(Team& team, const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Error: Could not open file " << filename << " for loading.\n";
        return false;
    }

    string name, sport;
    int wins, points;
    size_t player_count;

    getline(in, name);
    getline(in, sport);
    in >> wins >> points >> player_count;
    in.ignore();

    team.set_name(name);
    team.setsport(sport);
    team.set_wins(wins);
    team.set_points(points);

    team.get_players().clear(); // Not allowed directly, needs friend or workaround

    for (size_t i = 0; i < player_count; ++i) {
        string line, pname;
        int age;
        getline(in, line);
        stringstream ss(line);
        getline(ss, pname, ',');
        ss >> age;

        if (sport == "Cricket") {
            int runs, wickets;
            in >> runs >> wickets;
            in.ignore();
            auto cp = make_shared<CricketPlayer>(pname, age, name);
            cp->addruns(runs);
            cp->addwickets(wickets);
            team.add_player(cp);
        } else if (sport == "Football") {
            int goals, assists;
            string position;
            in >> goals >> assists;
            in.ignore();
            getline(in, position);
            auto fp = make_shared<FootballPlayer>(pname, age, name);
            fp->setPosition(position);
            for (int g = 0; g < goals; g++) fp->scoregoal();
            for (int a = 0; a < assists; a++) fp->addassist();
            team.add_player(fp);
        }
    }

    in.close();
    return true;
}

}
