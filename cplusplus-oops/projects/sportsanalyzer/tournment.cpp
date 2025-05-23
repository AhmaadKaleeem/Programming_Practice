#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "tournment.h"
using namespace std;

bool Tournament::teamExists(const string& teamname) const {
    for (const auto& team : teams) {
        if (team.getname() == teamname) {
            return true;
        }
    }
    return false;
}
