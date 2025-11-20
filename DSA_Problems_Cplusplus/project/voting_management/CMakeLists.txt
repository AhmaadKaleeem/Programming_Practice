cmake_minimum_required(VERSION 3.10)
project(VotingSystem)
set(CMAKE_CXX_STANDARD 17)

add_executable( elections
admin_panel.cpp
election.cpp
ledger.cpp
run_main.cpp
vote_queue.cpp
voter_management.cpp
voter.cpp
voting_time.cpp
)