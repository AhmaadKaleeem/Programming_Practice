# Election Management System

## Project Overview

The **Election Management System** is a comprehensive C++ application designed to manage voting processes for both National Assembly (MNA) and Provincial Assembly (MPA) elections in Pakistan. This system provides secure voter registration, authentication, voting capabilities, and real-time result tracking with blockchain-inspired ledger verification.

The application supports multi-province elections across Punjab, Sindh, KPK, Balochistan, and Islamabad, managing both NA (National Assembly) and PP (Provincial Parliament) constituencies with automated validation and result tallying.

## Features

- ✅ **Voter Registration System**
  - Auto-generated unique voter IDs
  - CNIC validation (Pakistani ID format)
  - Age verification (18+ years requirement)
  - Province and constituency auto-detection
  - Password-protected accounts

- ✅ **Authentication & Security**
  - Secure voter login with CNIC and password
  - Admin panel with credential verification
  - Blockchain-inspired ledger for vote integrity
  - Hash-based verification system

- ✅ **Voting System**
  - Separate MNA (National Assembly) voting
  - Separate MPA (Provincial Assembly) voting
  - One-time voting enforcement per voter per category
  - Queue-based vote processing
  - Real-time candidate display with symbols

- ✅ **Admin Panel**
  - Add/manage MNA candidates
  - Add/manage MPA candidates
  - View all registered candidates
  - Tally election results
  - Verify ledger integrity
  - View complete voting ledger

- ✅ **Results & Analytics**
  - Live vote counting
  - Display all candidate votes
  - Automatic winner determination
  - Province-wise result segregation
  - Constituency-based tracking

- ✅ **Data Integrity**
  - Blockchain-inspired ledger system
  - Cryptographic hash verification
  - Tamper-proof vote recording
  - Timestamped transactions

## Build Instructions

This project uses **CMake** as its build system and requires a C++17 compatible compiler.

### Prerequisites

- CMake 3.10 or higher
- C++17 compatible compiler:
  - GCC 7+ (Linux/macOS)
  - Clang 5+ (macOS)
  - MSVC 2017+ (Windows)
  - MinGW-w64 (Windows alternative)

### Building on Linux/macOS

1. **Clone or navigate to the project directory:**
   ```bash
   cd DSA_Problems_Cplusplus/project/voting_management
   ```

2. **Create a build directory:**
   ```bash
   mkdir build
   ```

3. **Navigate to the build directory:**
   ```bash
   cd build
   ```

4. **Generate build files with CMake:**
   ```bash
   cmake ..
   ```

5. **Build the project:**
   ```bash
   make
   ```

6. **Run the executable:**
   ```bash
   ./elections
   ```

### Building on Windows

#### Using MinGW or MSYS2

1. **Navigate to the project directory:**
   ```cmd
   cd DSA_Problems_Cplusplus\project\voting_management
   ```

2. **Create a build directory:**
   ```cmd
   mkdir build
   ```

3. **Navigate to the build directory:**
   ```cmd
   cd build
   ```

4. **Generate build files:**
   ```cmd
   cmake ..
   ```

5. **Build the project:**
   ```cmd
   cmake --build .
   ```

6. **Run the executable:**
   ```cmd
   elections.exe
   ```

#### Using Visual Studio

1. **Navigate to the project directory:**
   ```cmd
   cd DSA_Problems_Cplusplus\project\voting_management
   ```

2. **Create a build directory:**
   ```cmd
   mkdir build
   ```

3. **Navigate to the build directory:**
   ```cmd
   cd build
   ```

4. **Generate Visual Studio solution:**
   ```cmd
   cmake ..
   ```

5. **Build the project:**
   ```cmd
   cmake --build . --config Release
   ```

6. **Run the executable:**
   ```cmd
   Release\elections.exe
   ```

### Alternative: One-line Build

For convenience, you can combine steps:

**Linux/macOS:**
```bash
mkdir -p build && cd build && cmake .. && make && cd .. && ./build/elections
```

**Windows (MinGW):**
```cmd
mkdir build && cd build && cmake .. && cmake --build . && cd .. && build\elections.exe
```

## Usage Instructions

### Main Menu

When you run the application, you'll see the main menu:

```
==== Election Management System ====
1. Register Voter
2. Login as Voter
3. Login as Admin
4. Results
5. Exit
```

### Voter Registration (Option 1)

1. Select option `1` to register a new voter
2. Enter your personal details:
   - Full name
   - CNIC (13-digit Pakistani ID)
   - Age (must be 18 or older)
   - Password
3. Select your National Assembly (NA) constituency
4. Select your Provincial Parliament (PP) constituency
5. Your unique Voter ID will be auto-generated

### Voter Login (Option 2)

1. Select option `2` to login as a voter
2. Enter your CNIC
3. Enter your password
4. Once authenticated, you'll access the voter menu:

#### Voter Menu Options:
```
1. Cast MNA Vote (National Assembly)
2. Cast MPA Vote (Provincial Assembly)
3. View Election Results
4. Logout
```

**Casting Votes:**
- View available candidates with their symbols
- Select your preferred candidate by number
- Each voter can vote once for MNA and once for MPA
- Votes are recorded in the ledger immediately

### Admin Login (Option 3)

**Default Admin Credentials:**
- Username: `Admin123` / Password: `admin456`
- Username: `ahmad` / Password: `Ahmad28`
- Username: `sherbaz` / Password: `Sherbaz85`
- Username: `haris` / Password: `Haris85`
- Username: `muhiz` / Password: `Muhiz07`

#### Admin Panel Options:
```
1. Add MNA Candidate
2. Add MPA Candidate
3. Display All MNA Candidates
4. Display All MPA Candidates
5. Tally All Results
6. Verify Ledger Integrity
7. View Ledger File
8. Exit
```

**Admin Functions:**
- **Add Candidates:** Register new MNA/MPA candidates with CNIC, name, symbol, and constituency
- **View Candidates:** Display all registered candidates
- **Tally Results:** Process all votes and calculate winners
- **Verify Ledger:** Check blockchain integrity of voting records
- **View Ledger:** Display complete voting history with hashes

### View Results (Option 4)

1. Select option `4` from the main menu
2. Choose from results menu:
   - **Vote Counts:** See votes for all candidates across all seats
   - **Current Winners:** View leading candidates for NA and Provincial seats
   - **Back to Main Menu**

## File Descriptions

| File | Description |
|------|-------------|
| `CMakeLists.txt` | CMake build configuration file defining project settings and source files |
| `run_main.cpp` | Main entry point containing the primary menu and application flow |
| `election.h` / `election.cpp` | Core election management class handling candidates, voting, and results |
| `voter.h` / `voter.cpp` | Voter class managing voter data, registration, and validation |
| `voter_management.h` / `voter_management.cpp` | Voter management system handling voter linked list operations |
| `admin_panel.h` / `admin_panel.cpp` | Admin authentication and panel functionality |
| `ledger.h` / `ledger.cpp` | Blockchain-inspired ledger for vote recording and verification |
| `vote_queue.h` / `vote_queue.cpp` | Queue data structure for managing vote processing |
| `static_data.h` | Static data definitions for provinces, constituencies, and areas |
| `libraries.h` | Common header includes for the entire project |

## Build System Details

### CMake Configuration

The project uses the following CMake configuration:

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

### C++ Standard

- **C++17** is required for this project
- Utilizes modern C++ features including:
  - `std::unordered_map` for hash-based lookups
  - `std::vector` for dynamic arrays
  - String handling improvements
  - Structured bindings (if used)

### Executable Name

The compiled executable is named **`elections`** (or `elections.exe` on Windows).

## Troubleshooting

### Build Issues

**Problem:** CMake not found
```
Solution: Install CMake from https://cmake.org/download/ or via package manager
- Linux: sudo apt-get install cmake (Ubuntu/Debian) or sudo yum install cmake (RHEL/CentOS)
- macOS: brew install cmake
- Windows: Download installer from cmake.org or use chocolatey: choco install cmake
```

**Problem:** C++17 not supported
```
Solution: Update your compiler
- GCC: sudo apt-get install g++-7 or higher
- Clang: Install via Xcode Command Line Tools (macOS) or LLVM
- MSVC: Install Visual Studio 2017 or newer
```

**Problem:** "No CMakeLists.txt found"
```
Solution: Ensure you're in the correct directory (voting_management)
Check: ls CMakeLists.txt (Linux/macOS) or dir CMakeLists.txt (Windows)
```

### Runtime Issues

**Problem:** "Invalid Credentials" when logging in
```
Solution: 
- Voters: Ensure you've registered first and are using the correct CNIC and password
- Admins: Use one of the default admin credentials listed in the Usage section
```

**Problem:** "Cannot cast vote - already voted"
```
Solution: Each voter can only vote once for MNA and once for MPA
This is by design to prevent duplicate voting
```

**Problem:** Executable not running
```
Solution (Linux/macOS): Ensure execute permissions: chmod +x build/elections
Solution (Windows): Check if antivirus is blocking the executable
```

### Data Issues

**Problem:** "Invalid CNIC format"
```
Solution: CNIC must be exactly 13 digits without dashes
Example: 3520212345678 (not 35202-1234567-8)
```

**Problem:** "Ledger verification failed"
```
Solution: This indicates potential data corruption
Contact an administrator or rebuild the database
Do not modify ledger files manually
```

### Clean Build

If you encounter persistent build issues, try a clean build:

**Linux/macOS:**
```bash
rm -rf build
mkdir build
cd build
cmake ..
make
```

**Windows:**
```cmd
rmdir /s /q build
mkdir build
cd build
cmake ..
cmake --build .
```

## System Requirements

- **Operating System:** Windows 7+, Linux (any modern distribution), macOS 10.12+
- **RAM:** Minimum 512 MB (1 GB recommended)
- **Storage:** 50 MB free space
- **Compiler:** C++17 compatible
- **CMake:** Version 3.10 or higher

## Project Structure

```
voting_management/
├── CMakeLists.txt           # Build configuration
├── README.md                # This file
├── libraries.h              # Common headers
├── static_data.h           # Province/constituency data
├── run_main.cpp            # Main entry point
├── election.h/.cpp         # Election logic
├── voter.h/.cpp            # Voter entity
├── voter_management.h/.cpp # Voter list management
├── admin_panel.h/.cpp      # Admin functionality
├── ledger.h/.cpp          # Blockchain ledger
├── vote_queue.h/.cpp      # Vote queue structure
└── build/                 # Build directory (generated)
    └── elections          # Compiled executable
```

## License

This project is part of the Programming_Practice repository and is intended for educational purposes.

## Contributors

- Ahmad
- Sherbaz
- Haris
- Muhiz

---

**Note:** This is an educational project demonstrating data structures, algorithms, and system design principles in C++. The voting system implements queue management, linked lists, hash maps, and blockchain-inspired verification.
