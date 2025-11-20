#include "libraries.h"
#include "voting_time.h"
using namespace std;

bool is_voting_time(){
 time_t now = time(0);
 tm* lts = localtime(&now); // lts pionts to local time structure - builtin struct
 if ((lts->tm_year+1900 == vote_year ) &&(lts->tm_mon + 1 == vote_month)&&(lts->tm_mday == vote_day) &&(lts->tm_hour >= voting_start_time_hour && lts->tm_hour< voting_end_time_hour)){
    return true;
 }
return false;
}

void display_voting_schedule(){
    cout << "\n====================== Voting Schedule " << vote_year << " =========================\n";
    cout << "==  Date: " << setw(2) << setfill('0') << vote_day
         << "            Month: " << setw(2) << setfill('0') << vote_month
         << "           Year: " << vote_year << "             ==\n";
    cout << "==  Starting Hour: " << setw(2) << setfill('0') << voting_start_time_hour << ":00"
         << "                     Ending Hour: " << setw(2) << setfill('0') << voting_end_time_hour << ":00"
         << "    ==\n";

    cout << "=====================================================================\n";
}