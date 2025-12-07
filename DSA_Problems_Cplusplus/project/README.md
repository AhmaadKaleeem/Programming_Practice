# 🇵🇰 Pakistan Election Management System

A **Data Structures & Algorithms (DSA) project** in C++ demonstrating core DSA concepts through a real-world election system. Features **dual operation modes**: CLI application and REST API server for web frontend.


##  Table of Contents

- [Overview](#overview)
- [DSA Concepts](#dsa-concepts)
- [Features](#features)
- [System Requirements](#system-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [API Documentation](#api-documentation)
- [Troubleshooting](#troubleshooting)
- [License](#license)

##  Overview

University DSA project implementing Pakistan's election management system in C++.Backend showcases various data structures and can operate in two modes:

###  CLI Mode (Original DSA Demo)
- Console-based interface with color-coded menus
- Direct interaction with data structures
- Perfect for understanding DSA implementation
- Hidden password input for security

###  API Mode (Modern Web Integration)
- HTTP REST server exposing DSA operations
- Powers web frontend (AI-generated UI)
- Same backend logic, different interface
- Demonstrates practical DSA application

> **Note**: Both modes share the **same DSA implementation** and **same data files** (.txt format).

##  DSA Concepts

### Data Structures Implemented

| Structure | File | Purpose | Complexity |
|-----------|------|---------|------------|
| **Linked List** | `voter_management.cpp` | Dynamic voter storage | O(n) traversal |
| **Hash Map** | `voter_management.cpp` | Fast CNIC lookup | O(1) average |
| **Queue** | `vote_queue.cpp` | FIFO vote processing | O(1) enqueue/dequeue |
| **Blockchain** | `ledger.cpp` | Immutable vote ledger | O(n) verification |
| **Vectors** | `election.cpp` | Candidate storage | O(1) access |

### Algorithms Used

- **SHA-256 Hashing**: Blockchain integrity
- **Hash Table Operations**: Collision handling, dynamic resizing
- **CNIC Validation**: Format check, age calculation, province detection
- **Sorting**: Vote count ranking (O(n log n))
- **Search**: Hash-based O(1) lookups, linear search in lists

## Features

### Core Functionality (Both Modes)
- ✅ Dual elections (MNA - 266 seats, MPA - 600+ seats)
- ✅ CNIC validation with auto-province detection
- ✅ Blockchain vote ledger with SHA-256
- ✅ Password-protected authentication
- ✅ Double-vote prevention
- ✅ File-based persistence (.txt files)
- ✅ Admin panel for candidate management
- ✅ Real-time results calculation

### CLI Mode Only
- Color-coded Pakistan green theme
- Interactive menus
- Hidden password input
- Real-time status updates

### API Mode Only
- RESTful JSON endpoints
- CORS support
- HTTP status codes
- Session management

### Web Frontend (AI-Generated)
- Responsive design
- Pakistan flag colors (green & white)
- Real-time updates
- Mobile-friendly
- Toast notifications

## 💻 System Requirements

**Backend:**
- CMake 3.10+
- C++17 compiler (GCC 7+, MinGW-w64, MSVC 2017+)
- 512 MB RAM minimum
- 100 MB disk space

**Frontend (Web Mode):**
- Modern browser (Chrome 90+, Firefox 88+, Safari 14+, Edge 90+)
- HTTP server (Python or Node.js recommended)

## Installation

### 1.Clone Repository
```bash
git clone https://github.com/AhmaadKaleeem/Programming_Practice.git
cd Programming_Practice/DSA_Problems_Cplusplus/project/voting_management
```

### 2.Build Project
```bash
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
```

This builds both executables:
- `elections.exe` (CLI mode)
- `elections_api.exe` (API server mode)

##  Usage

### CLI Mode

```bash
cd build
./elections.exe
```

**Main Menu:**
```
1.Register Voter
2.Login as Voter
3.Login as Admin
4.View Results
5.Exit
```

**Operations:**
- **Register**: Name, CNIC (13 digits), NA seat, PA seat, password
- **Voter**: View profile, cast MNA/MPA votes, see results
- **Admin**: Add candidates, view statistics, verify ledger

### API Server Mode

```bash
cd build
./elections_api.exe
# Server starts on http://localhost:8080
```

### Web Frontend

```bash
cd frontend
python -m http.server 3000
# Visit http://localhost:3000
```

**Access Points:**
- Landing: `http://localhost:3000/index.html`
- Register: `http://localhost:3000/register.html`
- Login: `http://localhost:3000/login.html`
- Admin: `http://localhost:3000/admin-panel.html`
- Results: `http://localhost:3000/results.html`

##  Project Structure

```
voting_management/
│
├── CMakeLists.txt              # Build configuration
│
├── C++ Source Files (DSA Implementation)
│   ├── run_main.cpp            # CLI entry point
│   ├── server.cpp              # API entry point
│   ├── election.h/cpp          # Core election logic
│   ├── voter.h/cpp             # Voter class
│   ├── voter_management.h/cpp  # Linked list + hash map
│   ├── admin_panel.h/cpp       # Admin authentication
│   ├── vote_queue.h/cpp        # Queue (FIFO)
│   ├── ledger.h/cpp            # Blockchain (SHA-256)
│   ├── voting_time.h/cpp       # Time validation
│   ├── utilities.h/cpp         # Helper functions
│   ├── libraries.h             # Common includes
│   ├── console_color.h         # CLI colors
│   └── static_data.h           # Constituency mappings
│
├── frontend/ (AI-Generated Web UI)
│   ├── index.html
│   ├── register.html
│   ├── login.html
│   ├── voter-dashboard.html
│   ├── admin-panel.html
│   ├── results.html
│   ├── css/ (main.css, components.css, forms.css, dashboard.css, results.css)
│   └── js/ (config.js, api.js, auth.js, admin.js, voter.js, utils.js)
│
├── include/
│   └── httplib.h               # cpp-httplib library
│
├── build/
│   ├── elections.exe           # CLI executable
│   └── elections_api.exe       # API server executable
│
└── data/ (Generated at runtime)
    ├── Voters.txt
    ├── MNA_Candidates.txt
    ├── MPA_Candidates.txt
    ├── Votes.txt
    ├── VoteCounts.txt
    └── Ledger.txt
```

##  API Documentation

### Base URL
```
http://localhost:8080
```

### Key Endpoints

**Authentication**
```http
POST /api/register          # Register voter
POST /api/login             # Voter login
POST /api/admin/login       # Admin login
```

**Candidate Management**
```http
POST /api/admin/add-mna-candidate    # Add MNA candidate
POST /api/admin/add-mpa-candidate    # Add MPA candidate
GET  /api/candidates/mna             # Get all MNA candidates
GET  /api/candidates/mpa             # Get all MPA candidates
```

**Voting**
```http
POST /api/vote/mna          # Cast MNA vote
POST /api/vote/mpa          # Cast MPA vote
```

**Results & Admin**
```http
GET /api/results                    # Get election results
GET /api/admin/stats                # Get statistics
GET /api/admin/verify-ledger        # Verify blockchain
GET /api/admin/ledger               # View ledger
```

### Example Request

```http
POST /api/register
Content-Type: application/json

{
  "name": "Ahmad Khan",
  "cnic": "3520212345678",
  "age": 25,
  "naSeat": 117,
  "province": "Punjab",
  "paSeat": 145,
  "password": "securePass123"
}
```

### Example Response

```json
{
  "success": true,
  "message": "Voter registered successfully",
  "data": {
    "voterID": "V001",
    "name": "Ahmad Khan"
  }
}
```


##  Data Persistence

Data stored in plain text files (same for both modes):

**Voters.txt**
```
V001|Ahmad Khan|3520212345678|25|117|Punjab|145|password|false|false
```

**MNA_Candidates.txt**
```
Imran Khan|1234567890123|Bat|117|Islamabad
```

**Ledger.txt** (Blockchain)
```
Block #0
Voter CNIC: 3520212345678
Candidate CNIC: 1234567890123
Vote Type: MNA
Timestamp: 2025-12-07 14:30:00
Hash: abc123def456...
Previous Hash: 000000000000...
---
```

**Data Flow:**
1.**Startup**: Load .txt files → Memory (DSA)
2.**Runtime**: All operations on in-memory structures
3.**Exit**: Save DSA → .txt files
4.**Shared**: Both CLI and API use same files

##  Troubleshooting

### Elections Timings Issue
**Updating Timings** -  The election start and end times are hardcoded in the source file.
```bash
# Navigate to the project directory
cd project/voting_management/

# Open the file (voting_time.h) and update the constant timings and dates
const int voting_start_time_hour = 5;  // 5:00 AM
const int voting_end_time_hour = 20;   // 8:00 PM (Change this value)

#Rebuild the project:
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make

# Restart the api/cli:
./elections
./elections_api
```

### Build Issues

**CMake not found**
```bash
# Windows: Download from cmake.org
# Linux: sudo apt-get install cmake
# macOS: brew install cmake
```

**C++17 compiler error**
```bash
# Install MinGW-w64 (Windows)
# Update GCC (Linux): sudo apt-get install g++-7
# Xcode tools (Mac): xcode-select --install
```

**Build fails**
```bash
# Clean rebuild
rm -rf build
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
```

### CLI Runtime Issues

**"Invalid CNIC"**
```
Must be exactly 13 digits: 3520212345678
NOT: 35202-1234567-8
```

**"Already voted"**
```
By design - one vote per election type
Use different CNIC for testing
```

**No colors in console**
```
Use Windows Terminal or enable ANSI:
reg add HKCU\Console /v VirtualTerminalLevel /t REG_DWORD /d 1
```

### API Runtime Issues

**Port 8080 in use**
```bash
# Windows
netstat -ano | findstr :8080
taskkill /PID <pid> /F

# Linux/Mac
lsof -i :8080
kill -9 <pid>
```

**Frontend can't connect**
```
1.Verify API running: curl http://localhost:8080/
2.Check browser console (F12)
3.Use HTTP server for frontend (not file://)
4.Try Chrome browser
```

**CORS errors**
```
Ensure CORS is enabled in server.cpp
Check API response headers
```

### Data Issues

**Data not saving**
```
1.Use "Exit" option (not Ctrl+C)
2.Check write permissions
3.Verify .txt files in same directory as .exe
```

**Ledger verification fails**
```
Hash mismatch = corruption
Solution: Delete Ledger.txt to reset
```

**Missing candidates/voters**
```
1.Always exit properly (menu option)
2.Check if .txt files exist
3.Verify file paths
```

##  Contributing

Educational contributions welcome! 

**DSA Improvements:**
- Red-Black Tree for balanced storage
- Heap for priority vote processing
- Merge/Quick Sort optimization
- Graph for constituency relationships
- Trie for name-based search

**Backend Improvements:**
- SQLite integration
- Multi-threading
- Unit tests
- Performance benchmarks

**Frontend Improvements:**
- WebSockets for real-time updates
- Chart.js visualizations
- Urdu language support
- Mobile app

##  License

**Educational project** for Data Structures & Algorithms course.

**Author**: Ahmad Kaleem Bhatti  
**Institution**: Air University, Islamabad  
**Course**: Data Structures & Algorithms  
**Year**: 2024-2025

Free for academic use. Attribution required.

##  Acknowledgments

- **cpp-httplib**: Yuji Hirose (REST framework)
- **nlohmann/json**: JSON library
- **Frontend**: AI-generated UI
- **Inspiration**: Election Commission of Pakistan

---
##  Contact & Support

For issues, questions, or suggestions:

- **GitHub Issues**: [Open an issue](https://github.com/AhmaadKaleeem/Programming_Practice/issues)
- **Email**: ahmadkaleeem1@gamil.com
- **Repository**: [Programming_Practice/voting_management](https://github.com/AhmaadKaleeem/Programming_Practice/tree/main/DSA_Problems_Cplusplus/project/voting_management)

---

**Made with 💚 by Ahmad for Pakistan** 🇵🇰  
[GitHub Repository](https://github.com/AhmaadKaleeem/Programming_Practice/tree/main/DSA_Problems_Cplusplus/project/voting_management)