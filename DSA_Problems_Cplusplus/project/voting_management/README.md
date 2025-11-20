# Election Management System

## Overview

The **Election Management System** is a comprehensive C++ application designed to manage and facilitate democratic elections in Pakistan. The system supports both **MNA (Member of National Assembly)** and **MPA (Member of Provincial Assembly)** voting, providing a complete digital solution for voter registration, candidate management, vote casting, and result tallying.

This project demonstrates advanced data structures and algorithms including linked lists, queues, hash maps, and blockchain-inspired ledger systems to ensure secure and transparent election management.

## Features

### Core Functionality
- **Voter Registration**: Complete voter registration system with CNIC validation and constituency assignment
- **Candidate Management**: Add and manage candidates for both National Assembly (MNA) and Provincial Assembly (MPA) seats
- **Vote Casting**: Secure voting mechanism with validation to prevent duplicate voting
- **Vote Tallying**: Real-time vote counting and result compilation
- **Admin Panel**: Comprehensive administrative interface for election management
- **Blockchain-Inspired Ledger System**: Immutable vote recording with hash-based verification
- **Vote Queue**: Queue-based vote processing system for efficient vote management
- **Results Display**: View vote counts and current election winners

### Security Features
- Password-protected voter authentication
- Admin authentication system
- CNIC validation for voter eligibility
- Duplicate vote prevention
- Ledger verification for vote integrity

### Geographic Support
The system supports all Pakistani constituencies:
- **National Assembly (NA)**: 266 constituencies across Pakistan
- **Provincial Assemblies (PA)**:
  - Punjab (PP): 297 constituencies
  - Sindh (PS): 130 constituencies
  - Khyber Pakhtunkhwa (PK): 115 constituencies
  - Balochistan (PB): 51 constituencies
  - Islamabad: 3 NA seats (no provincial assembly)

## Project Structure

```
voting_management/
├── CMakeLists.txt           # CMake build configuration
├── README.md                # This file
├── .gitignore              # Git ignore rules
├── run_main.cpp            # Main entry point with menu system
├── election.h              # Election class header
├── election.cpp            # Election management implementation
├── voter.h                 # Voter class header
├── voter.cpp               # Voter registration and management
├── voter_management.h      # VoterManager class header
├── voter_management.cpp    # Voter database management
├── admin_panel.h           # Admin class header
├── admin_panel.cpp         # Administrative functions
├── vote_queue.h            # VoteQueue class header
├── vote_queue.cpp          # Queue-based vote processing
├── ledger.h                # Ledger class header (blockchain-inspired)
├── ledger.cpp              # Immutable vote ledger implementation
├── libraries.h             # Common header includes
└── static_data.h           # Constituency data and mappings
```

## System Requirements

### Minimum Requirements
- **CMake**: Version 3.10 or higher
- **C++ Compiler**: Supporting C++17 standard or later
  - GCC 7+ on Linux
  - Clang 5+ on macOS
  - MSVC 2017+ or MinGW on Windows
- **Operating System**: Windows, Linux, or macOS

### Recommended
- 4 GB RAM
- 100 MB free disk space

## Building the Project

The project uses **CMake** as its build system. Follow the platform-specific instructions below:

### Windows

```bash
# Navigate to the project directory
cd DSA_Problems_Cplusplus/project/voting_management

# Create build directory
mkdir build
cd build

# Configure the project
cmake ..

# Build the project
cmake --build .
```

The executable will be created at: `build/Release/elections.exe`

### Linux / macOS

```bash
# Navigate to the project directory
cd DSA_Problems_Cplusplus/project/voting_management

# Create build directory
mkdir build
cd build

# Configure the project
cmake ..

# Build the project
make
```

The executable will be created at: `build/elections`

### Clean Build

To perform a clean build, remove the build directory and rebuild:

```bash
rm -rf build
mkdir build
cd build
cmake ..
make  # or cmake --build . on Windows
```

## Running the Application

### Linux / macOS

```bash
# From the build directory
./elections

# Or from the project root
./build/elections
```

### Windows

```bash
# From the build directory
.\Release\elections.exe

# Or from the project root
.\build\Release\elections.exe
```

## Usage Instructions

### Main Menu

Upon running the application, you'll see the main menu:

```
==== Election Management System ====
1. Register Voter
2. Login as Voter
3. Login as Admin
4. Results
5. Exit
```

### Registering a Voter

1. Select option **1** from the main menu
2. Enter your full name
3. Enter your 13-digit CNIC (Computerized National Identity Card number)
4. Enter your age (must be 18 or older)
5. Enter your National Assembly constituency number (NA 1-266)
6. The system will automatically determine your province
7. Enter your Provincial Assembly constituency number (if applicable)
   - Note: Islamabad voters only vote for National Assembly
8. Set a password for your account
9. Your voter ID will be automatically generated

### Voting Process

1. Select option **2** from the main menu
2. Enter your CNIC
3. Enter your password
4. You'll see the voter menu:
   ```
   ==== Voter Menu ====
   1. Cast MNA Vote
   2. Cast MPA Vote
   3. View MNA Candidates
   4. View MPA Candidates
   5. Back to Main Menu
   ```
5. View candidates before voting (options 3 or 4)
6. Cast your votes (options 1 or 2)
   - Each voter can cast one MNA vote and one MPA vote
   - The system prevents duplicate voting

### Admin Panel

1. Select option **3** from the main menu
2. Enter admin credentials
3. Admin menu options:
   ```
   ==== Admin Panel ====
   1. Add MNA Candidate
   2. Add MPA Candidate
   3. Verify Ledger
   4. Display Ledger
   5. Display All Voters
   6. Search Voter by CNIC
   7. Tally MNA Results
   8. Tally MPA Results
   9. Back to Main Menu
   ```

#### Admin Functions

- **Add Candidates**: Register candidates for MNA or MPA seats with name, symbol, and CNIC
- **Verify Ledger**: Validate the integrity of all recorded votes
- **Display Ledger**: View complete voting history with timestamps and hashes
- **Display Voters**: View all registered voters
- **Search Voter**: Look up voter information by CNIC
- **Tally Results**: Calculate current vote counts and determine winners

### Viewing Results

1. Select option **4** from the main menu
2. Choose from:
   - **View Vote Counts**: See all candidates and their vote tallies
   - **View Current Winners**: See leading candidates for all seats

## File Descriptions

| File | Purpose |
|------|---------|
| `run_main.cpp` | Contains the main() function and primary menu system for user interaction |
| `election.h/cpp` | Core election management class handling candidates, voting logic, and results |
| `voter.h/cpp` | Voter class with registration logic, CNIC validation, and constituency assignment |
| `voter_management.h/cpp` | VoterManager class managing the voter database using linked lists and hash maps |
| `admin_panel.h/cpp` | Admin class providing administrative interface and authentication |
| `vote_queue.h/cpp` | VoteQueue class implementing queue-based vote processing |
| `ledger.h/cpp` | Ledger and LedgerBlock classes implementing blockchain-inspired immutable vote recording |
| `libraries.h` | Common header file including standard C++ libraries |
| `static_data.h` | Contains all constituency data, area names, and NA-to-PA mappings for Pakistan |

## Build System Details

### CMake Configuration

The project uses the following CMake configuration:
- **Minimum CMake Version**: 3.10
- **C++ Standard**: C++17
- **Project Name**: VotingSystem
- **Executable Name**: elections

### Source Files Compiled

All `.cpp` files are compiled into a single executable:
- admin_panel.cpp
- election.cpp
- ledger.cpp
- run_main.cpp
- vote_queue.cpp
- voter_management.cpp
- voter.cpp

## Troubleshooting

### Build Issues

**Problem**: CMake not found
```
Solution: Install CMake from https://cmake.org/download/
          or use package manager: sudo apt-get install cmake (Linux)
                                  brew install cmake (macOS)
```

**Problem**: C++17 compiler not supported
```
Solution: Update your compiler to a version supporting C++17:
          - GCC 7+ on Linux
          - Clang 5+ on macOS
          - MSVC 2017+ or MinGW on Windows
```

**Problem**: Build fails with linking errors
```
Solution: Ensure all source files are present in the project directory
          Perform a clean build: rm -rf build && mkdir build && cd build && cmake .. && make
```

### Runtime Issues

**Problem**: Invalid CNIC error during registration
```
Solution: Ensure your CNIC is exactly 13 digits without any dashes or spaces
```

**Problem**: Invalid constituency number
```
Solution: Verify your NA number is between 1-266 and PA number matches your province:
          - Punjab (PP): 1-297
          - Sindh (PS): 1-130
          - KPK (PK): 1-115
          - Balochistan (PB): 1-51
```

**Problem**: Cannot cast vote
```
Solution: Ensure you haven't already voted for that seat type (MNA or MPA)
          Each voter can only vote once per seat type
```

**Problem**: Admin authentication fails
```
Solution: Check with the system administrator for correct credentials
```

### General Issues

**Problem**: Application crashes on startup
```
Solution: Ensure you're running the correct executable for your platform
          Run from terminal/command prompt to see error messages
```

**Problem**: Build directory contains old files
```
Solution: Clean the build directory: rm -rf build
          Then rebuild from scratch
```

## Data Structures Used

The project demonstrates various data structures:

- **Linked Lists**: For voter management
- **Hash Maps** (`unordered_map`): For fast voter lookup and vote counting
- **Queues**: For vote processing
- **Vectors**: For candidate storage and constituency mappings
- **Blockchain-inspired Chain**: For immutable vote ledger

## Contributing

### How to Contribute

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/your-feature`
3. Make your changes and test thoroughly
4. Commit your changes: `git commit -m "Add your feature"`
5. Push to the branch: `git push origin feature/your-feature`
6. Submit a pull request

### Coding Standards

- Follow C++17 standards
- Use meaningful variable and function names
- Add comments for complex logic
- Test all changes before submitting
- Maintain consistent indentation (spaces preferred)

### Reporting Issues

If you encounter any bugs or have feature requests, please:
1. Check existing issues first
2. Create a detailed issue description
3. Include steps to reproduce (for bugs)
4. Provide system information (OS, compiler version)

## Author

**Ahmead Kaleem**

- Repository: [Programming_Practice](https://github.com/AhmaadKaleeem/Programming_Practice)
- Project Path: `DSA_Problems_Cplusplus/project/voting_management`

## License

This project is part of a programming practice repository and is available for educational purposes.

## Acknowledgments

- Pakistani Election Commission for constituency data
- Data Structures and Algorithms course materials
- Open source C++ community

---

**Note**: This is an educational project designed to demonstrate data structures and algorithms concepts. It is not intended for use in actual elections without proper security auditing and additional features.
