#ifdef _WIN32
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0A00
    #endif
    #include <winsock2.h>
    #include <windows.h>
#endif

// Include all C++ standard libraries and httplib FIRST
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <ctime>
#include <sstream>
#include <limits>

#include "include/httplib.h"
#include "include/json.hpp"

// NOW define macros AFTER all standard library includes
#define system(x) ((void)0)
#define SetConsoleTextAttribute(x, y) ((void)0)
#define GetStdHandle(x) ((void*)0)

#undef STD_OUTPUT_HANDLE
#define STD_OUTPUT_HANDLE ((DWORD)-11)

// Add using declarations for static_data.h
using std::string;
using std::vector;
using std::unordered_map;

// Your project headers
#include "static_data.h"
#include "voter.h"
#include "voter_management.h"
#include "vote_queue.h"
#include "ledger.h"
#include "election.h"
#include "admin_panel.h"
#include "voting_time.h"

// Override console color functions AFTER including headers
#undef red
#undef green
#undef blue
#undef yellow
#undef black
#undef reset

#define red()
#define green()
#define blue()
#define yellow()
#define black()
#define reset()

using json = nlohmann::json;
using namespace httplib;
using namespace std;

VoterManager* voterManager = nullptr;
Election* election = nullptr;
Admin* admin = nullptr;

void enableCORS(Response& res) {
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
}

string generateToken(const string& identifier) {
    return "TOKEN_" + identifier + "_" + to_string(time(nullptr));
}

int main() {
    try {
        cout << "========================================" << endl;
        cout << "  Pakistan EMS - API Server" << endl;
        cout << "========================================" << endl;
        
        cout << "[1/6] Creating VoterManager..." << flush;
        voterManager = new VoterManager();
        cout << " OK" << endl;
        
        cout << "[2/6] Creating Election..." << flush;
        election = new Election(voterManager);
        cout << " OK" << endl;
        
        cout << "[3/6] Creating Admin..." << flush;
        admin = new Admin(election);
        cout << " OK" << endl;
        
        cout << "[4/6] Loading data..." << endl;
        election->load_all_data();
        cout << "      Data loaded" << endl;
        
        cout << "[5/6] Creating HTTP server..." << flush;
        Server svr;
        cout << " OK" << endl;
        
        // ==============================================
        // CORS Preflight
        // ==============================================
        svr.Options(".*", [](const Request& req, Response& res) {
            enableCORS(res);
        });
        
        // ==============================================
        // Health Check / Test Endpoint
        // ==============================================
        svr.Get("/api/test", [](const Request& req, Response& res) {
            enableCORS(res);
            json response;
            response["success"] = true;
            response["message"] = "Pakistan EMS API is running";
            response["timestamp"] = (long long)time(nullptr);
            res.set_content(response.dump(), "application/json");
        });
        
        // ==============================================
        // Root Endpoint
        // ==============================================
        svr.Get("/", [](const Request& req, Response& res) {
            res.set_content("Pakistan EMS API - Online", "text/plain");
        });
        
        // ==============================================
        // Get NA Constituency Names (NEW)
        // ==============================================
        svr.Get("/api/constituencies/na-names", [](const Request& req, Response& res) {
            enableCORS(res);
            
            try {
                json response;
                json naNames = json::object();
                
                // Convert na_area_names unordered_map to JSON
                for (const auto& [seat, name] : na_area_names) {
                    naNames[std::to_string(seat)] = name;
                }
                
                response["success"] = true;
                response["data"] = naNames;
                
                cout << "[API] Served NA constituency names (" << na_area_names.size() << " entries)" << endl;
                
                res.set_content(response.dump(), "application/json");
                
            } catch (exception& e) {
                cout << "[ERROR] Get NA names: " << e.what() << endl;
                json response;
                response["success"] = false;
                response["message"] = string("Error: ") + e.what();
                res.status = 500;
                res.set_content(response.dump(), "application/json");
            }
        });
        
        // ==============================================
        // Get PA Constituency Names (NEW)
        // ==============================================
        svr.Get("/api/constituencies/pa-names", [](const Request& req, Response& res) {
            enableCORS(res);
            
            try {
                string province = req.get_param_value("province");
                
                json response;
                json paNames = json::object();
                
                // Select the appropriate map based on province
                const unordered_map<int, string>* selectedMap = nullptr;
                
                if (province == "Punjab") {
                    selectedMap = &pp_area_names;
                } else if (province == "Sindh") {
                    selectedMap = &ps_area_names;
                } else if (province == "KPK") {
                    selectedMap = &pk_area_names;
                } else if (province == "Balochistan") {
                    selectedMap = &pb_area_names;
                }
                
                if (selectedMap) {
                    for (const auto& [seat, name] : *selectedMap) {
                        paNames[std::to_string(seat)] = name;
                    }
                }
                
                response["success"] = true;
                response["data"] = paNames;
                response["province"] = province;
                
                cout << "[API] Served " << province << " PA names (" << paNames.size() << " entries)" << endl;
                
                res.set_content(response.dump(), "application/json");
                
            } catch (exception& e) {
                cout << "[ERROR] Get PA names: " << e.what() << endl;
                json response;
                response["success"] = false;
                response["message"] = string("Error: ") + e.what();
                res.status = 500;
                res.set_content(response.dump(), "application/json");
            }
        });
        
        // ==============================================
        // Get Voting Status
        // ==============================================
        svr.Get("/api/voting/status", [](const Request& req, Response& res) {
            enableCORS(res);
            
            try {
                bool isOpen = is_voting_time();
                
                json response;
                response["success"] = true;
                response["data"]["isVotingOpen"] = isOpen;
                response["data"]["year"] = vote_year;
                response["data"]["month"] = vote_month;
                response["data"]["day"] = vote_day;
                response["data"]["startHour"] = voting_start_time_hour;
                response["data"]["endHour"] = voting_end_time_hour;
                response["data"]["monthName"] = votemonth[vote_month - 1];
                
                res.set_content(response.dump(), "application/json");
                
            } catch (exception& e) {
                cout << "[ERROR] Get voting status: " << e.what() << endl;
                json response;
                response["success"] = false;
                response["message"] = string("Error: ") + e.what();
                res.status = 500;
                res.set_content(response.dump(), "application/json");
            }
        });
        
        // ==============================================
        // Register Voter
        // ==============================================
        svr.Post("/api/voter/register", [](const Request& req, Response& res) {
            enableCORS(res);
            
            try {
                auto body = json::parse(req.body);
                
                string name = body["name"];
                string cnic = body["cnic"];
                int age = body["age"];
                int naSeat = body["naSeat"];
                int paSeat = body.value("paSeat", 0);
                string password = body["password"];
                
                cout << "[REGISTER] " << name << " (CNIC: " << cnic << ", NA-" << naSeat << ")" << endl;
                
                if (voterManager->check_voter(cnic)) {
                    json response;
                    response["success"] = false;
                    response["message"] = "CNIC already registered";
                    res.status = 400;
                    res.set_content(response.dump(), "application/json");
                    return;
                }
                
                Voter* newVoter = new Voter();
                newVoter->voter_name = name;
                newVoter->voter_cnic = cnic;
                newVoter->voter_age = age;
                newVoter->na = naSeat;
                newVoter->provisional_p = paSeat;
                newVoter->voter_password = password;
                newVoter->determine_province_from_na();
                newVoter->voter_id = newVoter->auto_generate_voter_id();
                
                // Add to linked list
                newVoter->next = voterManager->head;
                voterManager->head = newVoter;
                voterManager->voter_mapping[cnic] = newVoter;
                
                // Save to file
                election->save_voters_to_file();
                
                cout << "[SUCCESS] Voter ID: " << newVoter->voter_id << " (Province: " << newVoter->pnames[newVoter->province] << ")" << endl;
                
                json response;
                response["success"] = true;
                response["message"] = "Registration successful";
                response["data"]["voterId"] = newVoter->voter_id;
                response["data"]["province"] = newVoter->pnames[newVoter->province];
                res.set_content(response.dump(), "application/json");
                
            } catch (exception& e) {
                cout << "[ERROR] Registration: " << e.what() << endl;
                json response;
                response["success"] = false;
                response["message"] = string("Registration error: ") + e.what();
                res.status = 500;
                res.set_content(response.dump(), "application/json");
            }
        });
        
        // ==============================================
        // Login Voter
        // ==============================================
        svr.Post("/api/voter/login", [](const Request& req, Response& res) {
            enableCORS(res);
            
            try {
                auto body = json::parse(req.body);
                string cnic = body["cnic"];
                string password = body["password"];
                
                cout << "[LOGIN] Attempt - CNIC: " << cnic << endl;
                
                if (! voterManager->authenticate_voter(cnic, password)) {
                    cout << "[LOGIN] Failed - Invalid credentials for " << cnic << endl;
                    json response;
                    response["success"] = false;
                    response["message"] = "Invalid CNIC or password";
                    res.status = 401;
                    res.set_content(response.dump(), "application/json");
                    return;
                }
                
                Voter* voter = voterManager->get_voter(cnic);
                if (! voter) {
                    cout << "[LOGIN] ERROR - Authenticated but voter not found!" << endl;
                    json response;
                    response["success"] = false;
                    response["message"] = "Voter not found";
                    res.status = 404;
                    res.set_content(response.dump(), "application/json");
                    return;
                }
                
                string token = generateToken(cnic);
                
                cout << "[SUCCESS] Login: " << voter->voter_name << " (ID: " << voter->voter_id << ")" << endl;
                
                json response;
                response["success"] = true;
                response["message"] = "Login successful";
                response["data"]["token"] = token;
                response["data"]["voter"]["voterId"] = voter->voter_id;
                response["data"]["voter"]["name"] = voter->voter_name;
                response["data"]["voter"]["cnic"] = voter->voter_cnic;
                response["data"]["voter"]["age"] = voter->voter_age;
                response["data"]["voter"]["naSeat"] = voter->na;
                response["data"]["voter"]["province"] = voter->pnames[voter->province];
                response["data"]["voter"]["paSeat"] = voter->provisional_p;
                response["data"]["voter"]["hasVotedMNA"] = election->has_voter_voted_mna(cnic);
                response["data"]["voter"]["hasVotedMPA"] = election->has_voter_voted_mpa(cnic);
                
                res.set_content(response.dump(), "application/json");
                
            } catch (exception& e) {
                cout << "[ERROR] Login: " << e.what() << endl;
                json response;
                response["success"] = false;
                response["message"] = string("Login error: ") + e.what();
                res.status = 500;
                res.set_content(response.dump(), "application/json");
            }
        });
        
        // ==============================================
        // Get MNA Candidates (by voter CNIC)
        // ==============================================
        svr.Get("/api/candidates/mna", [](const Request& req, Response& res) {
            enableCORS(res);
            
            try {
                string cnic = req.get_param_value("cnic");
                
                if (cnic.empty()) {
                    // Return all candidates if no CNIC provided
                    json candidatesJson = json::array();
                    
                    for (const auto& c : election->mna_candidates) {
                        json candidate;
                        candidate["name"] = c.name;
                        candidate["symbol"] = c.symbol;
                        candidate["cnic"] = c.cnic;
                        candidate["naSeat"] = c.constituency_na;
                        candidate["area"] = c.na_area;
                        int votes = election->get_mna_candidate_votes(c.cnic, c.name);
                        candidate["votes"] = votes;
                        candidatesJson.push_back(candidate);
                    }
                    
                    json response;
                    response["success"] = true;
                    response["data"]["candidates"] = candidatesJson;
                    
                    res.set_content(response.dump(), "application/json");
                    return;
                }
                
                cout << "[GET MNA CANDIDATES] For CNIC: " << cnic << endl;
                
                Voter* voter = voterManager->get_voter(cnic);
                if (!voter) {
                    json response;
                    response["success"] = false;
                    response["message"] = "Voter not found";
                    res.status = 404;
                    res.set_content(response.dump(), "application/json");
                    return;
                }
                
                int voterNA = voter->na;
                json candidatesJson = json::array();
                
                for (const auto& c : election->mna_candidates) {
                    if (c.constituency_na == voterNA) {
                        json candidate;
                        candidate["name"] = c.name;
                        candidate["symbol"] = c.symbol;
                        candidate["cnic"] = c.cnic;
                        candidate["naSeat"] = c.constituency_na;
                        candidate["area"] = c.na_area;
                        int votes = election->get_mna_candidate_votes(c.cnic, c.name);
                        candidate["votes"] = votes;
                        candidatesJson.push_back(candidate);
                    }
                }
                
                json response;
                response["success"] = true;
                response["data"]["naSeat"] = voterNA;
                response["data"]["candidates"] = candidatesJson;
                
                cout << "[SUCCESS] Found " << candidatesJson.size() << " MNA candidates for NA-" << voterNA << endl;
                
                res.set_content(response.dump(), "application/json");
                
            } catch (exception& e) {
                cout << "[ERROR] Get MNA candidates: " << e.what() << endl;
                json response;
                response["success"] = false;
                response["message"] = string("Error: ") + e.what();
                res.status = 500;
                res.set_content(response.dump(), "application/json");
            }
        });
        
        // ==============================================
        // Get MPA Candidates (by voter CNIC)
        // ==============================================
        svr.Get("/api/candidates/mpa", [](const Request& req, Response& res) {
            enableCORS(res);
            
            try {
                string cnic = req.get_param_value("cnic");
                
                if (cnic.empty()) {
                    json candidatesJson = json::array();
                    
                    for (const auto& c : election->mpa_candidates) {
                        json candidate;
                        candidate["name"] = c.name;
                        candidate["symbol"] = c.symbol;
                        candidate["cnic"] = c.cnic;
                        candidate["paSeat"] = c.provisional_pp;
                        candidate["area"] = c.p_area;
                        candidate["province"] = string(1, c.province_name);
                        int votes = election->get_mpa_candidate_votes(c.cnic, c.name);
                        candidate["votes"] = votes;
                        candidatesJson.push_back(candidate);
                    }
                    
                    json response;
                    response["success"] = true;
                    response["data"]["candidates"] = candidatesJson;
                    
                    res.set_content(response.dump(), "application/json");
                    return;
                }
                
                cout << "[GET MPA CANDIDATES] For CNIC: " << cnic << endl;
                
                Voter* voter = voterManager->get_voter(cnic);
                if (!voter) {
                    json response;
                    response["success"] = false;
                    response["message"] = "Voter not found";
                    res.status = 404;
                    res.set_content(response.dump(), "application/json");
                    return;
                }
                
                int voterPA = voter->provisional_p;
                json candidatesJson = json::array();
                
                for (const auto& c : election->mpa_candidates) {
                    if (c.provisional_pp == voterPA) {
                        json candidate;
                        candidate["name"] = c.name;
                        candidate["symbol"] = c.symbol;
                        candidate["cnic"] = c.cnic;
                        candidate["paSeat"] = c.provisional_pp;
                        candidate["area"] = c.p_area;
                        candidate["province"] = string(1, c.province_name);
                        int votes = election->get_mpa_candidate_votes(c.cnic, c.name);
                        candidate["votes"] = votes;
                        candidatesJson.push_back(candidate);
                    }
                }
                
                json response;
                response["success"] = true;
                response["data"]["paSeat"] = voterPA;
                response["data"]["candidates"] = candidatesJson;
                
                cout << "[SUCCESS] Found " << candidatesJson.size() << " MPA candidates" << endl;
                
                res.set_content(response.dump(), "application/json");
                
            } catch (exception& e) {
                cout << "[ERROR] Get MPA candidates: " << e.what() << endl;
                json response;
                response["success"] = false;
                response["message"] = string("Error: ") + e.what();
                res.status = 500;
                res.set_content(response.dump(), "application/json");
            }
        });
        
        // ==============================================
        // Cast MNA Vote
        // ==============================================
        svr.Post("/api/vote/mna", [](const Request& req, Response& res) {
            enableCORS(res);
            
            try {
                auto body = json::parse(req.body);
                
                string voterCnic = body["voterCnic"];
                string candidateCnic = body["candidateCnic"];
                
                cout << "[VOTE MNA] Voter: " << voterCnic << " -> Candidate: " << candidateCnic << endl;
                
                if (!voterManager->check_voter(voterCnic)) {
                    json response;
                    response["success"] = false;
                    response["message"] = "Voter not found";
                    res.status = 404;
                    res.set_content(response.dump(), "application/json");
                    return;
                }
                
                if (election->has_voter_voted_mna(voterCnic)) {
                    json response;
                    response["success"] = false;
                    response["message"] = "You have already voted for MNA";
                    res.status = 400;
                    res.set_content(response.dump(), "application/json");
                    return;
                }
                
                Election::Candidate* selectedCandidate = nullptr;
                for (auto& c : election->mna_candidates) {
                    if (c.cnic == candidateCnic) {
                        selectedCandidate = &c;
                        break;
                    }
                }
                
                if (!selectedCandidate) {
                    json response;
                    response["success"] = false;
                    response["message"] = "Candidate not found";
                    res.status = 404;
                    res.set_content(response.dump(), "application/json");
                    return;
                }
                
                string type = "MNA";
                election->queue_votes.enqueue(voterCnic, selectedCandidate->name, type);
                election->ledger.add_block(candidateCnic, voterCnic, type);
                election->record_mna_vote(candidateCnic);
                
                election->save_mna_candidates_to_file();
                election->save_votes_to_file();
                election->save_vote_counts_to_file();
                election->save_ledger_to_file();
                
                cout << "[SUCCESS] MNA vote cast for " << selectedCandidate->name << endl;
                
                json response;
                response["success"] = true;
                response["message"] = "MNA vote cast successfully";
                response["data"]["candidateName"] = selectedCandidate->name;
                
                res.set_content(response.dump(), "application/json");
                
            } catch (exception& e) {
                cout << "[ERROR] Cast MNA vote: " << e.what() << endl;
                json response;
                response["success"] = false;
                response["message"] = string("Error: ") + e.what();
                res.status = 500;
                res.set_content(response.dump(), "application/json");
            }
        });
        
        // ==============================================
        // Cast MPA Vote
        // ==============================================
        svr.Post("/api/vote/mpa", [](const Request& req, Response& res) {
            enableCORS(res);
            
            try {
                auto body = json::parse(req.body);
                
                string voterCnic = body["voterCnic"];
                string candidateCnic = body["candidateCnic"];
                
                cout << "[VOTE MPA] Voter: " << voterCnic << " -> Candidate: " << candidateCnic << endl;
                
                if (!voterManager->check_voter(voterCnic)) {
                    json response;
                    response["success"] = false;
                    response["message"] = "Voter not found";
                    res.status = 404;
                    res.set_content(response.dump(), "application/json");
                    return;
                }
                
                if (election->has_voter_voted_mpa(voterCnic)) {
                    json response;
                    response["success"] = false;
                    response["message"] = "You have already voted for MPA";
                    res.status = 400;
                    res.set_content(response.dump(), "application/json");
                    return;
                }
                
                Election::Candidate* selectedCandidate = nullptr;
                for (auto& c : election->mpa_candidates) {
                    if (c.cnic == candidateCnic) {
                        selectedCandidate = &c;
                        break;
                    }
                }
                
                if (!selectedCandidate) {
                    json response;
                    response["success"] = false;
                    response["message"] = "Candidate not found";
                    res.status = 404;
                    res.set_content(response.dump(), "application/json");
                    return;
                }
                
                string type = "MPA";
                election->queue_votes.enqueue(voterCnic, selectedCandidate->name, type);
                election->ledger.add_block(candidateCnic, voterCnic, type);
                election->record_mpa_vote(candidateCnic);
                
                election->save_mpa_candidates_to_file();
                election->save_votes_to_file();
                election->save_vote_counts_to_file();
                election->save_ledger_to_file();
                
                cout << "[SUCCESS] MPA vote cast for " << selectedCandidate->name << endl;
                
                json response;
                response["success"] = true;
                response["message"] = "MPA vote cast successfully";
                response["data"]["candidateName"] = selectedCandidate->name;
                
                res.set_content(response.dump(), "application/json");
                
            } catch (exception& e) {
                cout << "[ERROR] Cast MPA vote: " << e.what() << endl;
                json response;
                response["success"] = false;
                response["message"] = string("Error: ") + e.what();
                res.status = 500;
                res.set_content(response.dump(), "application/json");
            }
        });
        
        // ==============================================
        // Admin Login
        // ==============================================
        svr.Post("/api/admin/login", [](const Request& req, Response& res) {
            enableCORS(res);
            
            try {
                auto body = json::parse(req.body);
                
                string username = body["username"];
                string password = body["password"];
                
                cout << "[ADMIN LOGIN] User: " << username << endl;
                
                bool isValid = false;
                if (admin->login_admin.find(username) != admin->login_admin.end()) {
                    if (admin->login_admin[username] == password) {
                        isValid = true;
                    }
                }
                
                if (! isValid) {
                    cout << "[ADMIN LOGIN] Failed - Invalid credentials" << endl;
                    json response;
                    response["success"] = false;
                    response["message"] = "Invalid admin credentials";
                    res.status = 401;
                    res.set_content(response.dump(), "application/json");
                    return;
                }
                
                string token = generateToken(username);
                
                cout << "[SUCCESS] Admin login: " << username << endl;
                
                json response;
                response["success"] = true;
                response["message"] = "Admin login successful";
                response["data"]["token"] = token;
                response["data"]["username"] = username;
                
                res.set_content(response.dump(), "application/json");
                
            } catch (exception& e) {
                cout << "[ERROR] Admin login: " << e.what() << endl;
                json response;
                response["success"] = false;
                response["message"] = string("Error: ") + e.what();
                res.status = 500;
                res.set_content(response.dump(), "application/json");
            }
        });
        
        // ==============================================
        // Add MNA Candidate (Admin)
        // ==============================================
        svr.Post("/api/admin/candidate/mna", [](const Request& req, Response& res) {
            enableCORS(res);
            
            try {
                auto body = json::parse(req.body);
                
                string name = body["name"];
                string symbol = body["symbol"];
                string cnic = body["cnic"];
                int naSeat = body["naSeat"];
                
                cout << "[ADD MNA CANDIDATE] " << name << " (NA-" << naSeat << ")" << endl;
                
                Election::Candidate newCandidate;
                newCandidate.name = name;
                newCandidate.symbol = symbol;
                newCandidate.cnic = cnic;
                newCandidate.constituency_na = naSeat;
                newCandidate.na_area = na_area_names[naSeat];
                
                election->mna_candidates.push_back(newCandidate);
                election->mna_votes[cnic] = 0;
                election->save_mna_candidates_to_file();
                election->save_vote_counts_to_file();
                
                cout << "[SUCCESS] MNA candidate added" << endl;
                
                json response;
                response["success"] = true;
                response["message"] = "MNA candidate added successfully";
                
                res.set_content(response.dump(), "application/json");
                
            } catch (exception& e) {
                cout << "[ERROR] Add MNA candidate: " << e.what() << endl;
                json response;
                response["success"] = false;
                response["message"] = string("Error: ") + e.what();
                res.status = 500;
                res.set_content(response.dump(), "application/json");
            }
        });
        
        // ==============================================
        // Add MPA Candidate (Admin)
        // ==============================================
        svr.Post("/api/admin/candidate/mpa", [](const Request& req, Response& res) {
            enableCORS(res);
            
            try {
                auto body = json::parse(req.body);
                
                string name = body["name"];
                string symbol = body["symbol"];
                string cnic = body["cnic"];
                int paSeat = body["paSeat"];
                string province = body["province"];
                
                cout << "[ADD MPA CANDIDATE] " << name << " (" << province << "-" << paSeat << ")" << endl;
                
                Election::Candidate newCandidate;
                newCandidate.name = name;
                newCandidate.symbol = symbol;
                newCandidate.cnic = cnic;
                newCandidate.provisional_pp = paSeat;
                newCandidate.province_name = province[0];
                
                if (province == "Punjab") {
                    newCandidate.p_area = pp_area_names[paSeat];
                } else if (province == "Sindh") {
                    newCandidate.p_area = ps_area_names[paSeat];
                } else if (province == "KPK") {
                    newCandidate.p_area = pk_area_names[paSeat];
                } else if (province == "Balochistan") {
                    newCandidate.p_area = pb_area_names[paSeat];
                }
                
                election->mpa_candidates.push_back(newCandidate);
                election->mpa_votes[cnic] = 0;
                election->save_mpa_candidates_to_file();
                election->save_vote_counts_to_file();
                
                cout << "[SUCCESS] MPA candidate added" << endl;
                
                json response;
                response["success"] = true;
                response["message"] = "MPA candidate added successfully";
                
                res.set_content(response.dump(), "application/json");
                
            } catch (exception& e) {
                cout << "[ERROR] Add MPA candidate: " << e.what() << endl;
                json response;
                response["success"] = false;
                response["message"] = string("Error: ") + e.what();
                res.status = 500;
                res.set_content(response.dump(), "application/json");
            }
        });
        svr.Get("/api/admin/candidates/mna", [](const Request& req, Response& res) {
    enableCORS(res);
    
    try {
        cout << "[ADMIN] Fetching all MNA candidates..." << endl;
        
        json candidatesJson = json::array();
        
        for (const auto& c : election->mna_candidates) {
            json candidate;
            candidate["name"] = c.name;
            candidate["symbol"] = c.symbol;
            candidate["cnic"] = c.cnic;
            candidate["naSeat"] = c.constituency_na;
            candidate["area"] = c.na_area;
            int votes = election->get_mna_candidate_votes(c.cnic, c.name);
            candidate["votes"] = votes;
            candidatesJson.push_back(candidate);
        }
        
        json response;
        response["success"] = true;
        response["data"]["candidates"] = candidatesJson;
        response["data"]["count"] = (int)candidatesJson.size();
        
        cout << "[SUCCESS] Returned " << candidatesJson.size() << " MNA candidates" << endl;
        
        res.set_content(response.dump(), "application/json");
        
    } catch (exception& e) {
        cout << "[ERROR] Get all MNA candidates: " << e.what() << endl;
        json response;
        response["success"] = false;
        response["message"] = string("Error: ") + e.what();
        res.status = 500;
        res.set_content(response.dump(), "application/json");
    }
});

// ==============================================
// Get All MPA Candidates (Admin) - NEW ENDPOINT
// ==============================================
svr.Get("/api/admin/candidates/mpa", [](const Request& req, Response& res) {
    enableCORS(res);
    
    try {
        cout << "[ADMIN] Fetching all MPA candidates..." << endl;
        
        json candidatesJson = json::array();
        
        for (const auto& c : election->mpa_candidates) {
            json candidate;
            candidate["name"] = c.name;
            candidate["symbol"] = c.symbol;
            candidate["cnic"] = c.cnic;
            candidate["paSeat"] = c.provisional_pp;
            candidate["area"] = c.p_area;
            candidate["province"] = string(1, c.province_name);
            int votes = election->get_mpa_candidate_votes(c.cnic, c.name);
            candidate["votes"] = votes;
            candidatesJson.push_back(candidate);
        }
        
        json response;
        response["success"] = true;
        response["data"]["candidates"] = candidatesJson;
        response["data"]["count"] = (int)candidatesJson.size();
        
        cout << "[SUCCESS] Returned " << candidatesJson.size() << " MPA candidates" << endl;
        
        res.set_content(response.dump(), "application/json");
        
    } catch (exception& e) {
        cout << "[ERROR] Get all MPA candidates: " << e.what() << endl;
        json response;
        response["success"] = false;
        response["message"] = string("Error: ") + e.what();
        res.status = 500;
        res.set_content(response.dump(), "application/json");
    }
});

        // ==============================================
        // Get Results
        // ==============================================
        svr.Get("/api/results", [](const Request& req, Response& res) {
            enableCORS(res);
            
            try {
                cout << "[RESULTS] Fetching..." << endl;
                
                json mnaCandidates = json::array();
                json mpaCandidates = json::array();
                
                for (const auto& c : election->mna_candidates) {
                    json candidate;
                    candidate["name"] = c.name;
                    candidate["symbol"] = c.symbol;
                    candidate["cnic"] = c.cnic;
                    candidate["naSeat"] = c.constituency_na;
                    candidate["area"] = c.na_area;
                    int votes = election->get_mna_candidate_votes(c.cnic, c.name);
                    candidate["votes"] = votes;
                    mnaCandidates.push_back(candidate);
                }
                
                for (const auto& c : election->mpa_candidates) {
                    json candidate;
                    candidate["name"] = c.name;
                    candidate["symbol"] = c.symbol;
                    candidate["cnic"] = c.cnic;
                    candidate["paSeat"] = c.provisional_pp;
                    candidate["area"] = c.p_area;
                    candidate["province"] = string(1, c.province_name);
                    int votes = election->get_mpa_candidate_votes(c.cnic, c.name);
                    candidate["votes"] = votes;
                    mpaCandidates.push_back(candidate);
                }
                
                json response;
                response["success"] = true;
                response["data"]["mna"] = mnaCandidates;
                response["data"]["mpa"] = mpaCandidates;
                
                res.set_content(response.dump(), "application/json");
                
            } catch (exception& e) {
                cout << "[ERROR] Results: " << e.what() << endl;
                json response;
                response["success"] = false;
                response["message"] = string("Error: ") + e.what();
                res.status = 500;
                res.set_content(response.dump(), "application/json");
            }
        });
        
        // ==============================================
        // Get Voter Statistics (Admin)
        // ==============================================
        svr.Get("/api/admin/stats", [](const Request& req, Response& res) {
            enableCORS(res);
            
            try {
                cout << "[STATS] Fetching..." << endl;
                
                int totalVoters = 0;
                Voter* current = voterManager->head;
                while (current != nullptr) {
                    totalVoters++;
                    current = current->next;
                }
                
                json response;
                response["success"] = true;
                response["data"]["totalVoters"] = totalVoters;
                response["data"]["totalMNACandidates"] = (int)election->mna_candidates.size();
                response["data"]["totalMPACandidates"] = (int)election->mpa_candidates.size();
                response["data"]["mnaVotesCast"] = (int)election->mna_votes.size();
                response["data"]["mpaVotesCast"] = (int)election->mpa_votes.size();
                
                cout << "[SUCCESS] Stats: " << totalVoters << " voters registered" << endl;
                
                res.set_content(response.dump(), "application/json");
                
            } catch (exception& e) {
                cout << "[ERROR] Stats: " << e.what() << endl;
                json response;
                response["success"] = false;
                response["message"] = string("Error: ") + e.what();
                res.status = 500;
                res.set_content(response.dump(), "application/json");
            }
        });
        
        cout << "[6/6] Starting server..." << endl;
        cout << "========================================" << endl;
        cout << "  Server: http://localhost:8080" << endl;
        cout << "  Test:   http://localhost:8080/api/test" << endl;
        cout << "========================================" << endl;
        cout << "Listening...\n" << endl;
        
        if (! svr.listen("0.0.0.0", 8080)) {
            cerr << "[FATAL] Failed to start server on port 8080" << endl;
            return 1;
        }
        
        cout << "Server stopped" << endl;
        
        delete admin;
        delete election;
        delete voterManager;
        
    } catch (const exception& e) {
        cerr << "[FATAL ERROR] " << e.what() << endl;
        return 1;
    }
    
    return 0;
}