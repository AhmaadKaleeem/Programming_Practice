# Election Management System

A comprehensive C++ Election Management System designed to handle voting processes. This system provides secure voter registration, authentication, vote casting, and result management with blockchain-inspired ledger verification and stimulates real-world Pakistan election workflow.

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
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)

## Features

1. **Dual Election System**: Support for both National Assembly (MNA) and Provincial Assembly (MPA) elections with separate voting processes
2. **Secure Voter Registration**: Comprehensive CNIC validation (13-digit Pakistani identity number) with automatic province and constituency determination
3. **Authentication System**: Password-protected voter and admin login mechanisms ensuring secure access
4. **Constituency Management**: Automatic mapping of 266 National Assembly and 297+ Provincial Assembly seats across all provinces (Punjab, Sindh, KPK, Balochistan, Islamabad)
5. **Vote Queue System**: Efficient vote processing using queue data structure for ordered vote handling
6. **Blockchain-Inspired Ledger**: Immutable vote recording with hash verification for election integrity and transparency
7. **Real-time Results**: Live vote counting and winner determination for both MNA and MPA elections
8. **Admin Panel**: Comprehensive administrative controls for candidate management and result verification
9. **Data Integrity**: Built-in ledger verification system to prevent vote tampering and ensure election security
10. **User-Friendly Interface**: Console-based menu system with clear navigation for voters and administrators

## System Requirements

- **CMake**: Version 3.10 or higher
- **C++ Compiler**: Supporting C++17 standard or later
- **Operating System**: Windows, Linux, or macOS
- **Memory**: Minimum 512 MB RAM
- **Storage**: 50 MB free disk space

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
   cmake ..
   ```

4. **Build the project**

   On Linux/macOS:

   ```bash
   make
   ```

   On Windows (or any platform):

   ```bash
   cmake --build .
   ```

5. **Run the application**
   ```bash
   ./elections
   ```

## Usage

### Main Menu

When you launch the application, you'll see the main menu with the following options:

1. **Register Voter**: Create a new voter account with CNIC validation and password setup
2. **Login as Voter**: Access voter portal to view profile and cast votes
3. **Login as Admin**: Administrative access for candidate management and system oversight
4. **Results**: View election results including vote counts and current winners
5. **Exit**: Close the application

### Voter Menu

After successful voter login, you have access to:

- **View Profile**: Display your voter information including CNIC, name, age, and constituency details (NA and Provincial seats)
- **View Constituency**: See detailed information about your National Assembly and Provincial Assembly constituencies
- **Cast MNA Vote**: Vote for your preferred National Assembly candidate (one-time vote)
- **Cast MPA Vote**: Vote for your preferred Provincial Assembly candidate (one-time vote)
- **Logout**: Return to the main menu

**Note**: Each voter can cast only one vote for MNA and one vote for MPA. The system prevents double voting.

### Admin Panel

Admin authentication provides access to:

- **Add MNA Candidates**: Register new candidates for National Assembly elections with name, symbol, CNIC, and constituency details
- **Add MPA Candidates**: Register new candidates for Provincial Assembly elections with proper provincial seat allocation
- **View Ledger**: Display the blockchain-inspired ledger showing all recorded votes with timestamps and hash verification
- **Display Results**: Show comprehensive election results including:
  - Vote counts for all candidates
  - Current winners for both NA and Provincial seats
  - Real-time tallying of votes

**Default Admin Credentials**: The system comes with pre-configured admin access (credentials are set in the admin authentication module).

## Project Structure

The project consists of the following source files organized in a modular architecture:

```
voting_management/
├── run_main.cpp          # Main application entry point
├── election.h            # Election class declaration
├── election.cpp          # Election logic implementation
├── voter.h               # Voter class declaration
├── voter.cpp             # Voter registration and management
├── voter_management.h    # Voter manager class declaration
├── voter_management.cpp  # Voter storage and authentication
├── admin_panel.h         # Admin class declaration
├── admin_panel.cpp       # Admin authentication and operations
├── vote_queue.h          # Vote queue data structure declaration
├── vote_queue.cpp        # Queue implementation for votes
├── ledger.h              # Blockchain ledger declaration
├── ledger.cpp            # Ledger implementation with hashing
├── libraries.h           # Common library includes
├── static_data.h         # Static data for constituencies and mappings
└── CMakeLists.txt        # Build configuration
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

### Voter Registration

The voter registration process includes:

1. **CNIC Validation**: 13-digit national identity card number verification
2. **Age Verification**: Ensures voters meet minimum age requirements
3. **Automatic Province Detection**: Province determined from CNIC prefix
4. **Constituency Assignment**: Automatic NA and Provincial seat assignment based on location
5. **Secure Password**: Password protection for voter accounts
6. **Unique Voter ID**: Auto-generated unique identifier for each voter

### Vote Management

The vote management system features:

- **Vote Queue**: Efficient FIFO (First-In-First-Out) processing of votes
- **Vote Counting**: Real-time tallying of votes for each candidate
- **Immutable Ledger**: Each vote is recorded in a blockchain-inspired ledger with:
  - Voter CNIC (hashed for privacy)
  - Candidate CNIC
  - Timestamp
  - Hash of current block
  - Hash of previous block (chain integrity)
- **Verification System**: Built-in ledger verification to detect any tampering
- **Results Display**: Organized presentation of vote counts and winners

## File Descriptions

| File                   | Purpose                                                                                            |
| ---------------------- | -------------------------------------------------------------------------------------------------- |
| `run_main.cpp`         | Application entry point containing the main menu loop and core program flow                        |
| `election.h`           | Class declaration for Election management with candidate and voting operations                     |
| `election.cpp`         | Implementation of election logic, vote casting, tallying, and result computation                   |
| `voter.h`              | Voter class declaration with properties like CNIC, name, age, constituency                         |
| `voter.cpp`            | Implementation of voter registration, validation, and profile management                           |
| `voter_management.h`   | VoterManager class for maintaining voter database and authentication                               |
| `voter_management.cpp` | Implementation of voter storage using linked list and hash map for quick lookup                    |
| `admin_panel.h`        | Admin class declaration for administrative operations                                              |
| `admin_panel.cpp`      | Implementation of admin authentication and panel functionalities                                   |
| `vote_queue.h`         | VoteQueue class declaration using queue data structure                                             |
| `vote_queue.cpp`       | Queue implementation for ordered vote processing                                                   |
| `ledger.h`             | Blockchain-inspired ledger class declaration with block structure                                  |
| `ledger.cpp`           | Implementation of immutable ledger with hash calculation and verification                          |
| `libraries.h`          | Header file containing all common library includes (iostream, string, vector, unordered_map, etc.) |
| `static_data.h`        | Static data definitions including NA/PA constituency mappings, area names, and province enums      |
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
)
```

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
Solution: Check admin credentials in admin_panel.cpp. Default credentials are hardcoded in the intialize_credentionals() function.
```

**Problem**: Ledger verification fails

```
Solution: This indicates data corruption. Restart the application as ledger is stored in memory and will reset.
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
6. **Commit your changes**: `git commit -m "Add: description of your changes"`
7. **Push to your fork**: `git push origin feature/your-feature-name`
8. **Submit a pull request**: Open a PR with a clear description of your changes

### Areas for Contribution

- Database integration for persistent storage
- GUI implementation using Qt or similar framework
- Multi-language support

## License

This project is developed as a university project for educational purposes. It demonstrates the implementation of data structures (linked lists, queues, hash maps) and object-oriented programming concepts in C++.

**Author**: Ahmad Kaleem Bhatti
**Institution**: Air University  
**Course**: Data Structures and Algorithms (Project)  
**Year**: 2024

---
