# Election Management System

A comprehensive C++ Election Management System designed to handle voting processes. This system provides secure voter registration, authentication, vote casting, and result management with blockchain-inspired ledger verification and simulates real-world Pakistan election workflows.

## Table of Contents

- [Features](#features)
- [System Requirements](#system-requirements)
- [Installation](#installation)
- [Usage](#usage)
  - [Main Menu](#main-menu)
  - [Voter Menu](#voter-menu)
  - [Admin Panel](#admin-panel)
- [Project Structure](#project-structure)
- [System Features](#system-features)
  - [Election Types](#election-types)
  - [Voter Registration](#voter-registration)
  - [Vote Management](#vote-management)
- [File Descriptions](#file-descriptions)
- [Build Details](#build-details)
- [Data Persistence](#data-persistence)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)

## Features

1. **Dual Election System**: Support for both National Assembly (MNA) and Provincial Assembly (MPA) elections with separate voting processes
2. **Secure Voter Registration**: Comprehensive CNIC validation (13-digit Pakistani identity number) with automatic province and constituency determination
3. **Authentication System**: Password-protected voter and admin login mechanisms with hidden password input for enhanced security
4. **Constituency Management**: Automatic mapping of 266 National Assembly and 297+ Provincial Assembly seats across all provinces (Punjab, Sindh, KPK, Balochistan, Islamabad)
5. **Vote Queue System**: Efficient vote processing using queue data structure for ordered vote handling
6. **Blockchain-Inspired Ledger**: Immutable vote recording with hash verification for election integrity and transparency with full verification capabilities
7. **Real-time Results**: Live vote counting and winner determination for both MNA and MPA elections
8. **Admin Panel**: Comprehensive administrative controls for candidate management and result verification with color-coded interface
9. **Data Integrity**: Built-in ledger verification system to detect tampering and ensure election security
10. **User-Friendly Interface**: Color-coded console-based menu system with clear navigation and system feedback
11. **Voting Time Validation**: Fixed voting schedule with real-time validation to enforce voting windows (8:00 AM to 5:00 PM)
12. **Data Persistence**: Save and load all election data including voters, candidates, votes, and blockchain ledger to files

## System Requirements

- **CMake**: Version 3.10 or higher
- **C++ Compiler**: Supporting C++17 standard or later (GCC 7+, Clang 5+, or MSVC 2017+)
- **Operating System**: Windows, Linux, or macOS
- **Memory**: Minimum 512 MB RAM
- **Storage**: 50 MB free disk space for data files

## Installation

Follow these steps to build and run the Election Management System:

1. **Clone the repository**

   ```bash
   git clone https://github.com/AhmaadKaleeem/Programming_Practice.git
   cd Programming_Practice/DSA_Problems_Cplusplus/project/voting_management
   ```

2. **Create build directory**

   ```bash
   mkdir build
   cd build
   ```

3. **Configure with CMake**

   ```bash
   cmake -G "MinGW Makefiles" ..
   ```

   Or for other platforms:
   ```bash
   cmake ..
   ```

4. **Build the project**

   On Linux/macOS:

   ```bash
   make
   ```

   On Windows:

   ```bash
   mingw32-make
   ```

5. **Run the application**
   ```bash
   ./elections
   ```

## Usage

### Main Menu

When you launch the application, you'll see the main menu with color-coded options:

1. **Register Voter**: Create a new voter account with CNIC validation, age verification, and password setup
2. **Login as Voter**: Access voter portal to view profile and cast votes
3. **Login as Admin**: Administrative access for candidate management and system oversight
4. **Results**: View election results including vote counts and current winners
5. **Exit**: Close the application and save all system data

### Voter Menu

After successful voter login, you have access to:

- **View My Profile**: Display your voter information including CNIC, name, age, and constituency details (NA and Provincial seats)
- **View My Constituency**: See detailed information about your assigned National Assembly and Provincial Assembly constituencies
- **Cast Vote for MNA**: Vote for your preferred National Assembly candidate (one-time vote only)
- **Cast Vote for MPA**: Vote for your preferred Provincial Assembly candidate (one-time vote only)
- **Logout**: Return to the main menu

**Note**: Each voter can cast only one vote for MNA and one vote for MPA per election. The system prevents double voting automatically.

### Admin Panel

Admin authentication provides access to:

- **Add MNA Candidates**: Register new candidates for National Assembly elections with name, symbol, and CNIC
- **Add MPA Candidates**: Register new candidates for Provincial Assembly elections with proper provincial seat allocation
- **Display All MNA Candidates**: View list of registered MNA candidates with their constituency information
- **Display All MPA Candidates**: View list of registered MPA candidates with their provincial assignment
- **Tally All Results**: Calculate final vote counts and determine winners for both elections
- **Verify Ledger Integrity**: Check blockchain integrity to detect any data tampering or corruption
- **View Ledger File**: Display the complete voting record with all block information and hashes
- **Exit**: Return to main menu

## Project Structure

The project consists of the following source files organized in a modular architecture:

```
voting_management/
├── run_main.cpp             # Main application entry point with menu loop
├── election.h               # Election class declaration
├── election.cpp             # Core election logic, voting operations, and file I/O
├── voter.h                  # Voter class declaration
├── voter.cpp                # Voter registration, validation, and profile management
├── voter_management.h       # Voter manager class declaration
├── voter_management.cpp     # Voter storage using linked list and hash map
├── admin_panel.h            # Admin class declaration
├── admin_panel.cpp          # Admin authentication and panel operations
├── vote_queue.h             # Vote queue data structure declaration
├── vote_queue.cpp           # FIFO queue implementation for vote processing
├── ledger.h                 # Blockchain ledger class declaration
├── ledger.cpp               # Ledger implementation with hash verification
├── voting_time.h            # Voting schedule declarations
├── voting_time.cpp          # Voting time validation functions
├── utilities.h              # Helper function declarations
├── utilities.cpp            # Helper functions including hidden password input
├── libraries.h              # Common library includes and dependencies
├── console_color.h          # Console color functions for UI enhancement
├── static_data.h            # Static data for constituencies and mappings
├── CMakeLists.txt           # CMake build configuration
└── build/                   # Build directory (generated after compilation)
```

## System Features

### Election Types

The system manages two distinct types of elections:

- **MNA (Member of National Assembly)**: National-level representatives with 266 constituencies covering all provinces and territories
- **MPA (Member of Provincial Assembly)**: Provincial-level representatives with province-specific seats:
  - Punjab: 297 seats
  - Sindh: 130 seats
  - Khyber Pakhtunkhwa (KPK): 115 seats
  - Balochistan: 51 seats
  - Islamabad: No provincial assembly (National only)

### Voter Registration

The voter registration process includes:

1. **Name Entry**: User provides full name
2. **CNIC Validation**: 13-digit national identity card number verification
3. **Age Verification**: Ensures voters are at least 18 years old
4. **NA Seat Selection**: User selects their National Assembly constituency (1-266)
5. **Automatic Province Detection**: Province is determined from NA seat number
6. **PA Seat Selection**: User selects their Provincial Assembly seat (if applicable)
7. **Secure Password**: Password protection with hidden input display
8. **Auto-generated Voter ID**: Unique identifier assigned to each voter

### Vote Management

The vote management system features:

- **Vote Queue**: Efficient FIFO (First-In-First-Out) processing of votes
- **Vote Counting**: Real-time tallying of votes for each candidate
- **Immutable Ledger**: Each vote is recorded in a blockchain-inspired ledger with:
  - Block index for sequencing
  - Voter CNIC (for integrity)
  - Candidate CNIC
  - Vote type (MNA or MPA)
  - Timestamp of vote casting
  - Hash of current block
  - Hash of previous block (chain integrity)
- **Verification System**: Built-in ledger verification to detect tampering
- **Voting Time Window**: Restricted voting between 8:00 AM and 5:00 PM on election day
- **Results Display**: Comprehensive presentation of vote counts and winners

## File Descriptions

| File                   | Purpose                                                                                            |
| ---------------------- | -------------------------------------------------------------------------------------------------- |
| `run_main.cpp`         | Application entry point with main menu loop and data loading/saving                               |
| `election.h`           | Class declaration for Election management with voting and file I/O operations                      |
| `election.cpp`         | Implementation of election logic, voting, result calculation, and data persistence                 |
| `voter.h`              | Voter class declaration with registration and validation methods                                   |
| `voter.cpp`            | Implementation of voter registration, validation, and information display                          |
| `voter_management.h`   | VoterManager class for maintaining voter database                                                  |
| `voter_management.cpp` | Implementation of voter storage using linked list and hash map for quick lookup                    |
| `admin_panel.h`        | Admin class declaration for administrative operations                                              |
| `admin_panel.cpp`      | Implementation of admin authentication with color-coded interface                                  |
| `vote_queue.h`         | VoteQueue class declaration using queue data structure                                             |
| `vote_queue.cpp`       | FIFO queue implementation for ordered vote processing                                              |
| `ledger.h`             | Blockchain-inspired ledger class with block restoration support                                    |
| `ledger.cpp`           | Ledger implementation with hash calculation and verification with color output                     |
| `voting_time.h`        | Fixed voting schedule constants and validation function declarations                               |
| `voting_time.cpp`      | Implementation of voting time validation and schedule display                                      |
| `utilities.h`          | Helper function declarations for common operations                                                 |
| `utilities.cpp`        | Implementation of helper functions including hidden password input                                 |
| `libraries.h`          | Centralized include file with all standard and third-party library includes                       |
| `console_color.h`      | Console color functions for color-coded terminal output                                            |
| `static_data.h`        | Static constituency mappings, area names, and province enumerations                                |
| `CMakeLists.txt`       | CMake build configuration specifying C++17 standard and executable generation                      |

## Build Details

The project uses CMake for cross-platform build management:

- **CMake Minimum Version**: 3.10
- **C++ Standard**: C++17
- **Executable Name**: `elections`
- **Build System**: Compatible with Unix Makefiles, Visual Studio, Ninja, and other CMake generators

### Build Configuration

The `CMakeLists.txt` includes:

```cmake
cmake_minimum_required(VERSION 3.10)
project(VotingSystem)
set(CMAKE_CXX_STANDARD 17)
add_executable(elections
    admin_panel.cpp
    election.cpp
    ledger.cpp
    run_main.cpp
    vote_queue.cpp
    voter_management.cpp
    voter.cpp
    voting_time.cpp
    utilities.cpp
)
```

## Data Persistence

The system implements comprehensive data persistence with the following files:

- **Voters.txt**: Stores all registered voters with their credentials and constituency information
- **MNA_Candidates.txt**: Stores all registered MNA candidates with their symbols and constituencies
- **MPA_Candidates.txt**: Stores all registered MPA candidates with their provincial assignments
- **Votes.txt**: Records all cast votes with voter and candidate information
- **VoteCounts.txt**: Maintains current vote counts for all candidates
- **Ledger.txt**: Stores the complete blockchain ledger with all transactions and hashes

Data is automatically loaded when the application starts and saved when exiting. This allows the election system to maintain state across multiple sessions.

## Troubleshooting

### Common Build Issues

**Problem**: CMake not found

```
Solution: Install CMake from https://cmake.org/download/ or use package manager:
- Ubuntu/Debian: sudo apt-get install cmake
- macOS: brew install cmake
- Windows: Download installer from cmake.org
```

**Problem**: C++17 compiler not available

```
Solution: Update your compiler:
- GCC: Requires version 7+
- Clang: Requires version 5+
- MSVC: Requires Visual Studio 2017+
```

**Problem**: Build directory issues

```
Solution: Clean and rebuild:
rm -rf build
mkdir build
cd build
cmake ..
make
```

### Common Runtime Issues

**Problem**: "Invalid CNIC" error during registration

```
Solution: Ensure CNIC is exactly 13 digits with no spaces or dashes
Example: 3520212345678 (not 35202-1234567-8)
```

**Problem**: Cannot find constituency

```
Solution: Verify that your NA seat number is between 1-266 and corresponds to valid constituency mapping
```

**Problem**: "Already voted" message

```
Solution: Each voter can only vote once per election type (MNA and MPA). This is by design to prevent double voting.
```

**Problem**: Admin login fails

```
Solution: Check admin credentials in admin_panel.cpp. Default credentials are hardcoded in the initialize_credentials() function.
```

**Problem**: Ledger verification fails

```
Solution: Hash mismatch indicates data corruption. This should not occur during normal operation.
Check the Ledger.txt file for corruption or restart the application to reload clean data.
```

**Problem**: Voting is CLOSED message

```
Solution: Voting is restricted to the scheduled time window (8:00 AM to 5:00 PM on the election date).
Check voting_time.h to see or modify the voting schedule.
```

**Problem**: Data files are not found on startup

```
Solution: The application will create new data files on first run. If data from a previous session is needed,
ensure Voters.txt, MNA_Candidates.txt, MPA_Candidates.txt, and other data files are in the same directory as the executable.
```

## Contributing

We welcome contributions to improve the Election Management System! Here's how you can contribute:

1. **Fork the repository**: Create your own fork of the project
2. **Create a feature branch**: `git checkout -b feature/your-feature-name`
3. **Make your changes**: Implement your feature or bug fix
4. **Test thoroughly**: Ensure your changes don't break existing functionality
5. **Follow coding standards**:
   - Use consistent indentation (4 spaces)
   - Comment complex logic
   - Follow C++17 best practices
   - Keep modules loosely coupled
6. **Commit your changes**: `git commit -m "Add: description of your changes"`
7. **Push to your fork**: `git push origin feature/your-feature-name`
8. **Submit a pull request**: Open a PR with a clear description of your changes

### Areas for Contribution

- Database integration for persistent storage (SQLite or similar)
- GUI implementation using Qt or similar framework
- Multi-language support
- Performance optimization for large-scale voting
- Enhanced security features
- Mobile application development
- Detailed logging and audit trails
- Advanced election analytics

## License

This project is developed as a university project for educational purposes. It demonstrates the implementation of data structures (linked lists, queues, hash maps) and object-oriented programming concepts in C++.

**Author**: Ahmad Kaleem Bhatti  
**Institution**: Air University  
**Course**: Data Structures and Algorithms (Project)  
**Year**: 2025  
**Last Updated**: November 2025

---

For more information, issues, or feature requests, please visit the [GitHub Repository](https://github.com/AhmaadKaleeem/Programming_Practice).