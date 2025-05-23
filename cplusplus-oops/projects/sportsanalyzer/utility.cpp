
#include "Utility.h"

namespace Utility {

    bool isValidSport(const string& sportInput) {
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

}



