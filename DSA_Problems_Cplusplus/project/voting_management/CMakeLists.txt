cmake_minimum_required(VERSION 3.10)
project(PakistanEMS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory for single headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# ==================== CONSOLE APP (No httplib needed) ====================
add_executable(elections
    run_main.cpp
    admin_panel.cpp
    election.cpp
    ledger.cpp
    vote_queue.cpp
    voter_management.cpp
    voter.cpp
    voting_time.cpp
    utilities.cpp
)

# ==================== API SERVER (With httplib) ====================
add_executable(elections_api
    server.cpp
    admin_panel.cpp
    election.cpp
    ledger.cpp
    vote_queue.cpp
    voter_management.cpp
    voter.cpp
    voting_time.cpp
    utilities.cpp
)

# Windows configuration with STATIC linking
if(WIN32)
    # Link Windows socket libraries
    target_link_libraries(elections_api PRIVATE ws2_32 wsock32)
    
    # STATIC LINKING - This fixes the DLL issue! 
    target_link_options(elections_api PRIVATE 
        -static 
        -static-libgcc 
        -static-libstdc++
    )
    
    # Define Windows version
    target_compile_definitions(elections_api PRIVATE 
        _WIN32_WINNT=0x0A00 
        WINVER=0x0A00
    )
endif()

message(STATUS "CMake configuration complete")
message(STATUS "Static linking enabled for elections_api")