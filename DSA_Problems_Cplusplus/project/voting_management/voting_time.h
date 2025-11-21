#pragma once
#include "libraries.h"
using namespace std;

// Voting Times
const int vote_year = 2025;
const int vote_month = 11;
const int vote_day = 22;
const int voting_start_time_hour = 4; // 3 am
const int voting_end_time_hour = 17; // 5 pm

bool is_voting_time();
void display_voting_schedule();