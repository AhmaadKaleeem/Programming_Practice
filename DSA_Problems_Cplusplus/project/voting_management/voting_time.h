#pragma once
#include "libraries.h"
using namespace std;

// Voting Times
const int vote_year = 2025;
const int vote_month = 12;
const int vote_day = 7;
const int voting_start_time_hour = 5; // 5 am
const int voting_end_time_hour = 20; // 8 pm
const string votemonth[12] ={"January","February","March","April","May","June","July","August","September","October","November","December"};

bool is_voting_time();
void display_voting_schedule();
 
