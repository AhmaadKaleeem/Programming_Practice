#pragma once
#include "libraries.h"
using namespace std;

// Voting Times
const int vote_year = 2025;
const int vote_month = 12;
const int vote_day = 2;
const int voting_start_time_hour = 2; // 2 am
const int voting_end_time_hour = 17; // 5 pm

bool is_voting_time();
void display_voting_schedule();
 
