#include <iostream>
#include <string>
#include <limits>      
#include <cctype>      
#include <vector>     
#include <algorithm>  
#include <iomanip>    
#include <fstream>   
using namespace std;

//Base class of the program
class Player
{
protected:
public:
    //Components of Player common for all 3 Player.
    string First_name;
    string Last_name;
    int Age;
    string Team;
    string Country;
    int Win;
    int Lost;
    int No_of_matches;

    Player() //Default Constructor
    {
        First_name = "";
        Last_name = "";
        Age = 0;
        Team = "";
        Country = "";
        Win = 0;
        Lost = 0;
        No_of_matches = 0;
    }

    //Parameterized Constructor
    Player(string first_name, string last_name, int age, string team, string country, int win, int lost, int no_of_matches)
    {
        First_name = first_name;
        Last_name = last_name;
        Age = age;
        Team = team;
        Country = country;
        Win = win;
        Lost = lost;
        No_of_matches = no_of_matches;
    }

    ~Player() {} //Destructor

    virtual void displaymain()
    {
        cout << "\t\t\t\t**********************************" << endl;
        cout << "\t\t\t\tWELCOME TO Player ANALYZER PROGRAM" << endl;
        cout << "\t\t\t\t**********************************" << endl;

        cout << "\t\t\t\tPlease Choose the Player by pressing the number next to it : " << endl
             << endl;
        cout << "\t\t\t\t1) Football" << endl;
        cout << "\t\t\t\t2) Cricket" << endl;
        cout << "\t\t\t\t0) To exit the program " << endl
             << endl;
        cout << "\t\t\t\tEnter your choice: ";
    }
};

//Base class for football ---> Inherited from class "Player"
class Football : public Player
{
protected:
public:
    string Position;
    int Pass_Accuracy;
    int Red_card;
    int Draw;

    Football() //Default Constructor for Football class
    {
        Position = "";
        Pass_Accuracy = 0;
        Red_card = 0;
        Draw = 0;
    }

    //Parameterized Constructor for Football class
    Football(string first_name, string last_name, int age, string team, string country, int win, int lost, int no_of_matches, string position, int pass_accuracy, int red_card, int draw) : Player(first_name, last_name, age, team, country, win, lost, no_of_matches)
    {
        Position = position;
        Pass_Accuracy = pass_accuracy;
        Red_card = red_card;
        Draw = draw;
    }

    ~Football() {} //Deconstructor for Football class

    void displaymain() override
    {
        cout << "\t\t\t\t**********************************" << endl;
        cout << "\t\t\t\tWELCOME TO Player ANALYZER PROGRAM" << endl;
        cout << "\t\t\t\t**********************************" << endl
             << endl
             << endl;
        cout << "\t\t\t\t>>>>>> Welcome to Football <<<<<<" << endl
             << endl;
        cout << "\t\t\t\t1. View Teams " << endl;
        cout << "\t\t\t\t2. View Players " << endl;
        cout << "\t\t\t\t3. Stats " << endl;
        cout << "\t\t\t\t4. Standings " << endl;
        cout << "\t\t\t\t5. Return to Main Menu" << endl;
        cout << "\t\t\t\t0. EXIT" << endl
             << endl;
        cout << "\t\t\t\tEnter your choice: ";
    }

    void Team_display_f() //For diplaying the teams of football
    {
        fstream team_f("team_f.txt");
        string f;
        if (!team_f)
            cout << "Error" << endl;
        else
        {
            while (!team_f.eof())
            {
                getline(team_f, f);
                cout << f << endl;
            }
        }
    }

    void Standings_display_f() //For displaying the standings of football
    {
        fstream standings_f("standings_f.txt");
        string f;
        if (!standings_f)
            cout << "Error" << endl;
        else
        {
            while (!standings_f.eof())
            {
                getline(standings_f, f);
                cout << f << endl;
            }
        }
    }
};

//Attack class (Inherited from Football class --> Will contain all the components of Football as well as its parent class Player)
class Attack : public Football
{
protected:
public:
    int Goals;
    float Shot_accuracy;
    int Assist;

    Attack() // Default Constructor for Attack class
    {
        Goals = 0;
        Shot_accuracy = 0;
        Assist = 0;
    }

    // Parameterized Constructor for Attack class
    Attack(string first_name, string last_name, int age, string team, string country, int win, int lost, string position, int no_of_matches, int assist, int pass_accuracy, int red_card, int draw, int goals, float shot_accurracy) : Football(first_name, last_name, age, team, country, win, lost, no_of_matches, position, pass_accuracy, red_card, draw)
    {
        Assist = assist;
        Goals = goals;
        Shot_accuracy = shot_accurracy;
    }

    ~Attack() {} // Destructor for Attack class

    void Display_stats_f_a(vector<Attack>& A)
    {
        fstream stats_f_a("attack.txt");
        vector<int> id;
        A.clear();
        
        string line;
        while (getline(stats_f_a, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                Attack temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Position >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Goals >> temp.Shot_accuracy >> temp.Assist >> temp.Pass_Accuracy >> temp.Red_card)
                {
                    id.push_back(tempId);
                    A.push_back(temp);
                }
            }
        }
        
        cout << "SNO F.Name    L.Name        Pos  AGE TEAM               COUNTRY      App  Goals S.Accu Ass P.Accu RCd" << endl
             << endl
             << endl;
             
        for (size_t i = 0; i < A.size(); i++)
        {
            cout << left << setw(4) << id[i] << setw(10) << A[i].First_name << setw(14) << A[i].Last_name << setw(5) << A[i].Position << setw(4) << A[i].Age << setw(19) << A[i].Team << setw(13) << A[i].Country << setw(5) << A[i].No_of_matches << setw(6) << A[i].Goals << setw(7) << A[i].Shot_accuracy << setw(4) << A[i].Assist << setw(7) << A[i].Pass_Accuracy << setw(3) << A[i].Red_card << endl;
            cout << "-----------------------------------------------------------------------------------------------------" << endl;
        }
    }

    void Search_player_f_a(vector<Attack>& A, string name)
    {
        fstream psearch_a("attack.txt");
        vector<int> id;
        A.clear();
        
        string line;
        while (getline(psearch_a, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                Attack temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Position >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Goals >> temp.Shot_accuracy >> temp.Assist >> temp.Pass_Accuracy >> temp.Red_card)
                {
                    id.push_back(tempId);
                    A.push_back(temp);
                }
            }
        }

        bool found = false;
        for (size_t i = 0; i < A.size(); i++)
        {
            if (name == A[i].First_name || name == A[i].Last_name)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            cout << "SNO F.Name    L.Name        Pos  AGE TEAM                  COUNTRY      App  Goals S.Accu Ass P.Accu RCd" << endl
                 << endl
                 << endl;
                 
            for (size_t i = 0; i < A.size(); i++)
            {
                if (name == A[i].First_name || name == A[i].Last_name)
                {
                    cout << left << setw(4) << id[i] << setw(10) << A[i].First_name << setw(14) << A[i].Last_name << setw(5) << A[i].Position << setw(4) << A[i].Age << setw(22) << A[i].Team << setw(13) << A[i].Country << setw(5) << A[i].No_of_matches << setw(6) << A[i].Goals << setw(7) << A[i].Shot_accuracy << setw(4) << A[i].Assist << setw(7) << A[i].Pass_Accuracy << setw(3) << A[i].Red_card << endl;
                    cout << "---------------------------------------------------------------------------------------------------------" << endl;
                }
            }
        }
        else
        {
            cout << "This player does not exist" << endl << endl;
        }
    }

    void Player_display_f_a(vector<Attack>& A)
    {
        fstream player_f_a("attack.txt");
        vector<int> id;
        A.clear();
        
        string line;
        while (getline(player_f_a, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                Attack temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Position >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Goals >> temp.Shot_accuracy >> temp.Assist >> temp.Pass_Accuracy >> temp.Red_card)
                {
                    id.push_back(tempId);
                    A.push_back(temp);
                }
            }
        }
        
        cout << "FORWARD : " << endl << endl;
        cout << "SNO F.Name    L.Name        Pos  AGE TEAM               COUNTRY" << endl << endl;
        
        for (size_t i = 0; i < A.size(); i++)
        {
            cout << left << setw(4) << id[i] << setw(10) << A[i].First_name << setw(14) << A[i].Last_name << setw(5) << A[i].Position << setw(4) << A[i].Age << setw(19) << A[i].Team << setw(13) << A[i].Country << endl;
            cout << "----------------------------------------------------------------------" << endl;
        }
        cout << endl;
    }
};

//Midfield class (Inherited from Football class --> Will contain all the components of Football as well as its parent class Player)
class MidField : public Football
{
protected:
public:
    int Goals;
    float Shot_accuracy;
    int Assist;

    MidField() //Default Constructor for Midfield class
    {
        Goals = 0;
        Shot_accuracy = 0;
        Assist = 0;
    }

    //Parameterized Constructor for Midfield class
    MidField(string first_name, string last_name, int age, string team, string country, int win, int lost, string position, int no_of_matches, int assist, int pass_accuracy, int red_card, int draw, int goals, float shot_accurracy) : Football(first_name, last_name, age, team, country, win, lost, no_of_matches, position, pass_accuracy, red_card, draw)
    {
        Goals = goals;
        Shot_accuracy = shot_accurracy;
        Assist = assist;
    }

    ~MidField() {} //Destructor for Midfield class

    void Display_stats_f_m(vector<MidField>& Mf)
    {
        fstream stats_f_m("midfield.txt");
        vector<int> id;
        Mf.clear();
        
        string line;
        while (getline(stats_f_m, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                MidField temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Position >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Goals >> temp.Shot_accuracy >> temp.Assist >> temp.Pass_Accuracy >> temp.Red_card)
                {
                    id.push_back(tempId);
                    Mf.push_back(temp);
                }
            }
        }
        
        cout << "SNO F.Name    L.Name        Pos  AGE TEAM                  COUNTRY      App  Goals S.Accu Ass P.Accu RCd" << endl
             << endl
             << endl;
             
        for (size_t i = 0; i < Mf.size(); i++)
        {
            cout << left << setw(4) << id[i] << setw(10) << Mf[i].First_name << setw(14) << Mf[i].Last_name << setw(5) << Mf[i].Position << setw(4) << Mf[i].Age << setw(22) << Mf[i].Team << setw(13) << Mf[i].Country << setw(5) << Mf[i].No_of_matches << setw(6) << Mf[i].Goals << setw(7) << Mf[i].Shot_accuracy << setw(4) << Mf[i].Assist << setw(7) << Mf[i].Pass_Accuracy << setw(3) << Mf[i].Red_card << endl;
            cout << "--------------------------------------------------------------------------------------------------------" << endl;
        }
    }

    void Search_player_f_m(vector<MidField>& Mf, string name)
    {
        fstream psearch_m("midfield.txt");
        vector<int> id;
        Mf.clear();
        
        string line;
        while (getline(psearch_m, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                MidField temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Position >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Goals >> temp.Shot_accuracy >> temp.Assist >> temp.Pass_Accuracy >> temp.Red_card)
                {
                    id.push_back(tempId);
                    Mf.push_back(temp);
                }
            }
        }

        bool found = false;
        for (size_t i = 0; i < Mf.size(); i++)
        {
            if (name == Mf[i].First_name || name == Mf[i].Last_name)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            cout << "SNO F.Name    L.Name        Pos  AGE TEAM                  COUNTRY      App  Goals S.Accu Ass P.Accu RCd" << endl
                 << endl
                 << endl;
                 
            for (size_t i = 0; i < Mf.size(); i++)
            {
                if (name == Mf[i].First_name || name == Mf[i].Last_name)
                {
                    cout << left << setw(4) << id[i] << setw(10) << Mf[i].First_name << setw(14) << Mf[i].Last_name << setw(5) << Mf[i].Position << setw(4) << Mf[i].Age << setw(22) << Mf[i].Team << setw(13) << Mf[i].Country << setw(5) << Mf[i].No_of_matches << setw(6) << Mf[i].Goals << setw(7) << Mf[i].Shot_accuracy << setw(4) << Mf[i].Assist << setw(7) << Mf[i].Pass_Accuracy << setw(3) << Mf[i].Red_card << endl;
                    cout << "--------------------------------------------------------------------------------------------------------" << endl;
                }
            }
        }
        else
        {
            cout << "This player does not exist" << endl << endl;
        }
    }

    void Player_display_f_m(vector<MidField>& Mf)
    {
        fstream player_f_m("midfield.txt");
        vector<int> id;
        Mf.clear();
        
        string line;
        while (getline(player_f_m, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                MidField temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Position >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Goals >> temp.Shot_accuracy >> temp.Assist >> temp.Pass_Accuracy >> temp.Red_card)
                {
                    id.push_back(tempId);
                    Mf.push_back(temp);
                }
            }
        }
        
        cout << "MID-FIELD : " << endl << endl;
        cout << "SNO F.Name    L.Name        Pos  AGE TEAM                  COUNTRY" << endl << endl;
        
        for (size_t i = 0; i < Mf.size(); i++)
        {
            cout << left << setw(4) << id[i] << setw(10) << Mf[i].First_name << setw(14) << Mf[i].Last_name << setw(5) << Mf[i].Position << setw(4) << Mf[i].Age << setw(22) << Mf[i].Team << setw(13) << Mf[i].Country << endl;
            cout << "-----------------------------------------------------------------------" << endl;
        }
        cout << endl;
    }
};
//Defence class (Inherited from Football class --> Will contain all the components of Football as well as its parent class Player)
class Defence : public Football
{
protected:
public:
    int Goals;
    int Tackles_won;
    int Clearance;
    int Blocked_shots;
    int Assist;

    Defence() //Default constructor for Defence class
    {
        Goals = 0;
        Tackles_won = 0;
        Clearance = 0;
        Blocked_shots = 0;
        Assist = 0;
    }

    //Parameterized Constructor for Defence class
    Defence(string first_name, string last_name, int age, string team, string country, int win, int lost, string position, int no_of_matches, int assist, int pass_accuracy, int red_card, int draw, int goals, int tackles_won, int clearance, int blocked_shots) : Football(first_name, last_name, age, team, country, win, lost, no_of_matches, position, pass_accuracy, red_card, draw)
    {
        Goals = goals;
        Tackles_won = tackles_won;
        Clearance = clearance;
        Blocked_shots = blocked_shots;
        Assist = assist;
    }

    ~Defence() {} //Destructor for Defence class

    void Display_stats_f_d(vector<Defence>& D)
    {
        fstream stats_f_d("DEFENDERS.txt");
        vector<int> id;
        D.clear();
        
        string line;
        while (getline(stats_f_d, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                Defence temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Position >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Tackles_won >> temp.Clearance >> temp.Blocked_shots >> temp.Red_card >> temp.Goals >> temp.Pass_Accuracy)
                {
                    id.push_back(tempId);
                    D.push_back(temp);
                }
            }
        }
        
        cout << "SNO F.NAME    L.NAME        POS  AGE TEAM                  COUNTRY      APP  TACKLE CLEARANCE BLK.SHOT RC Goals P.ACC" << endl
             << endl
             << endl;
             
        for (size_t i = 0; i < D.size(); i++)
        {
            cout << left << setw(4) << id[i] << setw(10) << D[i].First_name << setw(14) << D[i].Last_name << setw(5) << D[i].Position << setw(4) << D[i].Age << setw(22) << D[i].Team << setw(13) << D[i].Country << setw(5) << D[i].No_of_matches << setw(7) << D[i].Tackles_won << setw(10) << D[i].Clearance << setw(9) << D[i].Blocked_shots << setw(3) << D[i].Red_card << setw(6) << D[i].Goals << setw(7) << D[i].Pass_Accuracy << endl;
            cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
        }
    }

    void Search_player_f_d(vector<Defence>& D, string name)
    {
        fstream psearch_d("DEFENDERS.txt");
        vector<int> id;
        D.clear();
        
        string line;
        while (getline(psearch_d, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                Defence temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Position >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Tackles_won >> temp.Clearance >> temp.Blocked_shots >> temp.Red_card >> temp.Goals >> temp.Pass_Accuracy)
                {
                    id.push_back(tempId);
                    D.push_back(temp);
                }
            }
        }

        bool found = false;
        for (size_t i = 0; i < D.size(); i++)
        {
            if (name == D[i].First_name || name == D[i].Last_name)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            cout << "F.NAME    L.NAME        POS  AGE TEAM                  COUNTRY      APP  TACKLE CLEARANCE BLK.SHOT RC Goals P.ACC" << endl
                 << endl
                 << endl;
                 
            for (size_t i = 0; i < D.size(); i++)
            {
                if (name == D[i].First_name || name == D[i].Last_name)
                {
                    cout << left << setw(10) << D[i].First_name << setw(14) << D[i].Last_name << setw(5) << D[i].Position << setw(4) << D[i].Age << setw(22) << D[i].Team << setw(13) << D[i].Country << setw(5) << D[i].No_of_matches << setw(7) << D[i].Tackles_won << setw(10) << D[i].Clearance << setw(9) << D[i].Blocked_shots << setw(3) << D[i].Red_card << setw(6) << D[i].Goals << setw(7) << D[i].Pass_Accuracy << endl;
                    cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                }
            }
        }
        else
        {
            cout << "This player does not exist" << endl << endl;
        }
    }

    void Player_display_f_d(vector<Defence>& D)
    {
        fstream player_f_d("DEFENDERS.txt");
        vector<int> id;
        D.clear();
        
        string line;
        while (getline(player_f_d, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                Defence temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Position >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Tackles_won >> temp.Clearance >> temp.Blocked_shots >> temp.Red_card >> temp.Goals >> temp.Pass_Accuracy)
                {
                    id.push_back(tempId);
                    D.push_back(temp);
                }
            }
        }
        
        cout << "DEFENCE : " << endl << endl;
        cout << "SNO F.Name    L.Name        Pos  AGE TEAM                  COUNTRY" << endl << endl;
        
        for (size_t i = 0; i < D.size(); i++)
        {
            cout << left << setw(4) << id[i] << setw(10) << D[i].First_name << setw(14) << D[i].Last_name << setw(5) << D[i].Position << setw(4) << D[i].Age << setw(22) << D[i].Team << setw(13) << D[i].Country << endl;
            cout << "-----------------------------------------------------------------------" << endl;
        }
        cout << endl;
    }
};

//GoalKeeper class (Inherited from Football class --> Will contain all the components of Football as well as its parent class Player)
class GoalKeeper : public Football
{
protected:
public:
    int Clean_sheets;
    int Saves_made;
    int Goals_conceeded;

    GoalKeeper() //Default constructor for Goalkeeper class
    {
        Clean_sheets = 0;
        Saves_made = 0;
        Goals_conceeded = 0;
    }

    //Parameterized Constructor for Goalkeeper class
    GoalKeeper(string first_name, string last_name, int age, string team, string country, int win, int lost, string position, int no_of_matches, int assist, int pass_accuracy, int red_card, int draw, int clean_sheets, int saves_made, int goals_conceeded) : Football(first_name, last_name, age, team, country, win, lost, no_of_matches, position, pass_accuracy, red_card, draw)
    {
        Clean_sheets = clean_sheets;
        Saves_made = saves_made;
        Goals_conceeded = goals_conceeded;
    }

    ~GoalKeeper() {} //Destructor for Goalkeeper class

    void Search_player_f_gk(vector<GoalKeeper>& Gk, string name)
    {
        fstream psearch_gk("gk.txt");
        vector<int> id;
        Gk.clear();
        
        string line;
        while (getline(psearch_gk, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                GoalKeeper temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Position >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Clean_sheets >> temp.Saves_made >> temp.Goals_conceeded >> temp.Red_card)
                {
                    id.push_back(tempId);
                    Gk.push_back(temp);
                }
            }
        }

        bool found = false;
        for (size_t i = 0; i < Gk.size(); i++)
        {
            if (name == Gk[i].First_name || name == Gk[i].Last_name)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            cout << "SNO F.Name    L.Name        Pos  AGE TEAM                  COUNTRY      App  Cln.S Saves G.Con RCd" << endl
                 << endl
                 << endl;
                 
            for (size_t i = 0; i < Gk.size(); i++)
            {
                if (name == Gk[i].First_name || name == Gk[i].Last_name)
                {
                    cout << left << setw(4) << id[i] << setw(10) << Gk[i].First_name << setw(14) << Gk[i].Last_name << setw(5) << Gk[i].Position << setw(4) << Gk[i].Age << setw(22) << Gk[i].Team << setw(13) << Gk[i].Country << setw(5) << Gk[i].No_of_matches << setw(6) << Gk[i].Clean_sheets << setw(6) << Gk[i].Saves_made << setw(6) << Gk[i].Goals_conceeded << setw(3) << Gk[i].Red_card << endl;
                    cout << "-----------------------------------------------------------------------------------------------------" << endl;
                }
            }
        }
        else
        {
            cout << "This player does not exist" << endl << endl;
        }
    }

    void Player_display_f_gk(vector<GoalKeeper>& Gk)
    {
        fstream player_f_gk("gk.txt");
        vector<int> id;
        Gk.clear();
        
        string line;
        while (getline(player_f_gk, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                GoalKeeper temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Position >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Clean_sheets >> temp.Saves_made >> temp.Goals_conceeded >> temp.Red_card)
                {
                    id.push_back(tempId);
                    Gk.push_back(temp);
                }
            }
        }
        
        cout << "GOAL-KEEPERS : " << endl << endl;
        cout << "SNO F.Name    L.Name        Pos  AGE TEAM                  COUNTRY" << endl << endl;

        for (size_t i = 0; i < Gk.size(); i++)
        {
            cout << left << setw(4) << id[i] << setw(10) << Gk[i].First_name << setw(14) << Gk[i].Last_name << setw(5) << Gk[i].Position << setw(4) << Gk[i].Age << setw(22) << Gk[i].Team << setw(13) << Gk[i].Country << endl;
            cout << "-----------------------------------------------------------------------" << endl;
        }
        cout << endl;
    }

    void Display_stats_f_gk(vector<GoalKeeper>& Gk)
    {
        fstream stats_f_gk("gk.txt");
        vector<int> id;
        Gk.clear();
        
        string line;
        while (getline(stats_f_gk, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                GoalKeeper temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Position >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Clean_sheets >> temp.Saves_made >> temp.Goals_conceeded >> temp.Red_card)
                {
                    id.push_back(tempId);
                    Gk.push_back(temp);
                }
            }
        }
        
        cout << "SNO F.Name    L.Name        Pos  AGE TEAM                  COUNTRY      App  Cln.S Saves  G.Con  RCd" << endl
             << endl
             << endl;
             
        for (size_t i = 0; i < Gk.size(); i++)
        {
            cout << left << setw(4) << id[i] << setw(10) << Gk[i].First_name << setw(14) << Gk[i].Last_name << setw(5) << Gk[i].Position << setw(4) << Gk[i].Age << setw(22) << Gk[i].Team << setw(13) << Gk[i].Country << setw(5) << Gk[i].No_of_matches << setw(6) << Gk[i].Clean_sheets << setw(7) << Gk[i].Saves_made << setw(7) << Gk[i].Goals_conceeded << setw(3) << Gk[i].Red_card << endl;
            cout << "-----------------------------------------------------------------------------------------------------" << endl;
        }
    }
};

//Base class for cricket ---> Inherited from class "Player"
class Cricket : public Player
{
protected:
public:
    int Innings;
    int Runs;
    float Batting_strike_rate;
    float Batting_average;
    int Fours;
    int Sixes;
    string Best_Batting_figure;

    Cricket()
    {
        Innings = 0;
        Runs = 0;
        Batting_strike_rate = 0;
        Batting_average = 0;
        Fours = 0;
        Sixes = 0;
        Best_Batting_figure = "";
    }

    Cricket(string first_name, string last_name, int age, string team, string country, int win, int lost, int no_of_matches, int innings, int runs, float batting_strike_rate, float batting_average, int fours, int sixes, string best_batting_figure) : Player(first_name, last_name, age, team, country, win, lost, no_of_matches)
    {
        Innings = innings;
        Runs = runs;
        Batting_strike_rate = batting_strike_rate;
        Batting_average = batting_average;
        Fours = fours;
        Sixes = sixes;
        Best_Batting_figure = best_batting_figure;
    }

    ~Cricket() {}

    void displaymain() override
    {
        cout << "\t\t\t\t**********************************" << endl;
        cout << "\t\t\t\tWELCOME TO Player ANALYZER PROGRAM" << endl;
        cout << "\t\t\t\t**********************************" << endl
             << endl
             << endl;
        cout << "\t\t\t\t>>>>>>> Welcome to Cricket <<<<<<" << endl
             << endl;
        cout << "\t\t\t\t1. View Teams " << endl;
        cout << "\t\t\t\t2. View Players " << endl;
        cout << "\t\t\t\t3. Stats " << endl;
        cout << "\t\t\t\t4. Standings " << endl;
        cout << "\t\t\t\t5. Return to Main Menu" << endl;
        cout << "\t\t\t\t0. EXIT" << endl
             << endl;
        cout << "\t\t\t\tEnter your Choice: ";
    }

    void Team_display_c()
    {
        fstream team_c("team_c.txt");
        string c;
        if (!team_c)
            cout << "Error" << endl;
        else
        {
            while (!team_c.eof())
            {
                getline(team_c, c);
                cout << c << endl;
            }
        }
    }

    void Standings_display_c()
    {
        fstream standings_c("standings_c.txt");
        string c;
        if (!standings_c)
            cout << "Error" << endl;
        else
        {
            while (!standings_c.eof())
            {
                getline(standings_c, c);
                cout << c << endl;
            }
        }
    }
};

class Batsman : public Cricket
{
protected:
public:
    int Centuries;
    int Fifties;

    Batsman()
    {
        Centuries = 0;
        Fifties = 0;
    }

    Batsman(string first_name, string last_name, int age, string team, string country, int win, int lost, int no_of_matches, int innings, int runs, float batting_strike_rate, float batting_average, int fours, int sixes, string best_batting_figure, int centuries, int fifties) : Cricket(first_name, last_name, age, team, country, win, lost, no_of_matches, innings, runs, batting_strike_rate, batting_average, fours, sixes, best_batting_figure)
    {
        Centuries = centuries;
        Fifties = fifties;
    }

    ~Batsman() {}

    void Player_display_c_bt(vector<Batsman>& Bt)
    {
        fstream player_c_bt("batsman.txt");
        if (!player_c_bt.is_open()) {
    cout << "Error: Unable to open batsman.txt file!" << endl;
    return;
}
        vector<int> id;
        Bt.clear();
        
        string line;
        while (getline(player_c_bt, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                Batsman temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Innings >> temp.Runs >> temp.Batting_strike_rate >> temp.Batting_average >> temp.Fifties >> temp.Centuries >> temp.Best_Batting_figure >> temp.Fours >> temp.Sixes)
                {
                    id.push_back(tempId);
                    Bt.push_back(temp);
                }
            }
        }
        
        cout << "BATSMAN : " << endl << endl;
        cout << "F.Name     L.Name      AGE TEAM                        COUNTRY" << endl << endl << endl;
        
        for (size_t i = 0; i < Bt.size(); i++)
        {
            cout << left << setw(11) << Bt[i].First_name << setw(12) << Bt[i].Last_name << setw(4) << Bt[i].Age << setw(28) << Bt[i].Team << setw(13) << Bt[i].Country << endl;
            cout << "-------------------------------------------------------------------" << endl;
        }
        cout << endl;
    }

    void Search_player_c_bt(vector<Batsman>& Bt, string name)
    {
        fstream psearch_bt("batsman.txt");
        vector<int> id;
        Bt.clear();
        
        string line;
        while (getline(psearch_bt, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                Batsman temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Innings >> temp.Runs >> temp.Batting_strike_rate >> temp.Batting_average >> temp.Fifties >> temp.Centuries >> temp.Best_Batting_figure >> temp.Fours >> temp.Sixes)
                {
                    id.push_back(tempId);
                    Bt.push_back(temp);
                }
            }
        }

        bool found = false;
        for (size_t i = 0; i < Bt.size(); i++)
        {
            if (name == Bt[i].First_name || name == Bt[i].Last_name)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            cout << "F.Name     L.Name      AGE TEAM                        COUNTRY      TM INN RUNS S.R.   Avg   50s  100s Best 4s 6s" << endl << endl << endl;
            
            for (size_t i = 0; i < Bt.size(); i++)
            {
                if (name == Bt[i].First_name || name == Bt[i].Last_name)
                {
                    cout << left << setw(11) << Bt[i].First_name << setw(12) << Bt[i].Last_name << setw(4) << Bt[i].Age << setw(28) << Bt[i].Team << setw(13) << Bt[i].Country << setw(3) << Bt[i].No_of_matches << setw(4) << Bt[i].Innings << setw(5) << Bt[i].Runs << setw(7) << Bt[i].Batting_strike_rate << setw(6) << Bt[i].Batting_average << setw(5) << Bt[i].Fifties << setw(5) << Bt[i].Centuries << setw(5) << Bt[i].Best_Batting_figure << setw(3) << Bt[i].Fours << setw(3) << Bt[i].Sixes << endl;
                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
                }
            }
        }
        else
        {
            cout << "This player does not exist" << endl << endl;
        }
    }

    void Display_stats_c_bt(vector<Batsman>& Bt)
    {
        fstream stats_c_bt("batsman.txt");
        vector<int> id;
        Bt.clear();
        
        string line;
        while (getline(stats_c_bt, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                Batsman temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Innings >> temp.Runs >> temp.Batting_strike_rate >> temp.Batting_average >> temp.Fifties >> temp.Centuries >> temp.Best_Batting_figure >> temp.Fours >> temp.Sixes)
                {
                    id.push_back(tempId);
                    Bt.push_back(temp);
                }
            }
        }
        
        cout << "SNO F.Name     L.Name      AGE TEAM                        COUNTRY      TM INN RUNS S.R.   Avg   50s  100s Best 4s 6s" << endl << endl << endl;
        
        for (size_t i = 0; i < Bt.size(); i++)
        {
            cout << left << setw(4) << id[i] << setw(11) << Bt[i].First_name << setw(12) << Bt[i].Last_name << setw(4) << Bt[i].Age << setw(28) << Bt[i].Team << setw(13) << Bt[i].Country << setw(3) << Bt[i].No_of_matches << setw(4) << Bt[i].Innings << setw(5) << Bt[i].Runs << setw(7) << Bt[i].Batting_strike_rate << setw(6) << Bt[i].Batting_average << setw(5) << Bt[i].Fifties << setw(5) << Bt[i].Centuries << setw(5) << Bt[i].Best_Batting_figure << setw(4) << Bt[i].Fours << setw(3) << Bt[i].Sixes << endl;
            cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        }
    }
};

class Bowler : public Cricket
{
protected:
public:
    int Wickets;
    float Bowling_average;
    int Four_wkt_hauls;
    float Economy;
    string Best_Bowling_figure;

    Bowler()
    {
        Wickets = 0;
        Bowling_average = 0;
        Four_wkt_hauls = 0;
        Economy = 0;
        Best_Bowling_figure = "";
    }

    Bowler(string first_name, string last_name, int age, string team, string country, int win, int lost, int no_of_matches, int innings, int runs, float batting_strike_rate, float batting_average, int fours, int sixes, string best_batting_figure, int wickets, float bowling_average, int four_wkt_haul, float economy, string best_bowling_figure) : Cricket(first_name, last_name, age, team, country, win, lost, no_of_matches, innings, runs, batting_strike_rate, batting_average, fours, sixes, best_batting_figure)
    {
        Wickets = wickets;
        Bowling_average = bowling_average;
        Four_wkt_hauls = four_wkt_haul;
        Economy = economy;
        Best_Bowling_figure = best_bowling_figure;
    }

    ~Bowler() {}

    void Player_display_c_bo(vector<Bowler>& Bo)
    {
        fstream player_c_bo("bowlers.txt");
        vector<int> id;
        Bo.clear();
        
        string line;
        while (getline(player_c_bo, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                Bowler temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Innings >> temp.Wickets >> temp.Economy >> temp.Bowling_average >> temp.Best_Bowling_figure >> temp.Four_wkt_hauls >> temp.Runs >> temp.Batting_strike_rate >> temp.Batting_average >> temp.Best_Batting_figure >> temp.Fours >> temp.Sixes)
                {
                    id.push_back(tempId);
                    Bo.push_back(temp);
                }
            }
        }
        
        cout << "BOWLERS : " << endl << endl;
        cout << "F.Name       L.Name        AGE TEAM                        COUNTRY" << endl << endl << endl;
        
        for (size_t i = 0; i < Bo.size(); i++)
        {
            cout << left << setw(13) << Bo[i].First_name << setw(14) << Bo[i].Last_name << setw(4) << Bo[i].Age << setw(28) << Bo[i].Team << setw(13) << Bo[i].Country << endl;
            cout << "-----------------------------------------------------------------------" << endl;
        }
        cout << endl;
    }

    void Search_player_c_bo(vector<Bowler>& Bo, string name)
    {
        fstream psearch_bo("bowlers.txt");
        vector<int> id;
        Bo.clear();
        
        string line;
        while (getline(psearch_bo, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                Bowler temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Innings >> temp.Wickets >> temp.Economy >> temp.Bowling_average >> temp.Best_Bowling_figure >> temp.Four_wkt_hauls >> temp.Runs >> temp.Batting_strike_rate >> temp.Batting_average >> temp.Best_Batting_figure >> temp.Fours >> temp.Sixes)
                {
                    id.push_back(tempId);
                    Bo.push_back(temp);
                }
            }
        }

        bool found = false;
        for (size_t i = 0; i < Bo.size(); i++)
        {
            if (name == Bo[i].First_name || name == Bo[i].Last_name)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            cout << "F.Name       L.Name        AGE TEAM                        COUNTRY      TM INN W   ECO   Avg   Best 4WH RUNS S.R.   Avg   Best 4s  6s" << endl << endl << endl;
            
            for (size_t i = 0; i < Bo.size(); i++)
            {
                if (name == Bo[i].First_name || name == Bo[i].Last_name)
                {
                    cout << left << setw(13) << Bo[i].First_name << setw(14) << Bo[i].Last_name << setw(4) << Bo[i].Age << setw(28) << Bo[i].Team << setw(13) << Bo[i].Country << setw(3) << Bo[i].No_of_matches << setw(4) << Bo[i].Innings << setw(4) << Bo[i].Wickets << setw(6) << Bo[i].Economy << setw(6) << Bo[i].Bowling_average << setw(5) << Bo[i].Best_Bowling_figure << setw(4) << Bo[i].Four_wkt_hauls << setw(5) << Bo[i].Runs << setw(7) << Bo[i].Batting_strike_rate << setw(6) << Bo[i].Batting_average << setw(5) << Bo[i].Best_Batting_figure << setw(4) << Bo[i].Fours << setw(3) << Bo[i].Sixes << endl;
                    cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
                }
            }
        }
        else
        {
            cout << "This player does not exist" << endl << endl;
        }
    }

    void Display_stats_c_bo(vector<Bowler>& Bo)
    {
        fstream stats_c_bo("bowlers.txt");
        vector<int> id;
        Bo.clear();
        
        string line;
        while (getline(stats_c_bo, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                Bowler temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Innings >> temp.Wickets >> temp.Economy >> temp.Bowling_average >> temp.Best_Bowling_figure >> temp.Four_wkt_hauls >> temp.Runs >> temp.Batting_strike_rate >> temp.Batting_average >> temp.Best_Batting_figure >> temp.Fours >> temp.Sixes)
                {
                    id.push_back(tempId);
                    Bo.push_back(temp);
                }
            }
        }
        
        cout << "SNO F.Name       L.Name        AGE TEAM                        COUNTRY      TM INN W   ECO   Avg   Best 4WH RUNS S.R.   Avg   Best 4s  6s" << endl << endl << endl;
        
        for (size_t i = 0; i < Bo.size(); i++)
        {
            cout << left << setw(4) << id[i] << setw(13) << Bo[i].First_name << setw(14) << Bo[i].Last_name << setw(4) << Bo[i].Age << setw(28) << Bo[i].Team << setw(13) << Bo[i].Country << setw(3) << Bo[i].No_of_matches << setw(4) << Bo[i].Innings << setw(4) << Bo[i].Wickets << setw(6) << Bo[i].Economy << setw(6) << Bo[i].Bowling_average << setw(5) << Bo[i].Best_Bowling_figure << setw(4) << Bo[i].Four_wkt_hauls << setw(5) << Bo[i].Runs << setw(7) << Bo[i].Batting_strike_rate << setw(6) << Bo[i].Batting_average << setw(5) << Bo[i].Best_Batting_figure << setw(4) << Bo[i].Fours << setw(3) << Bo[i].Sixes << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
        }
    }
};

class All_rounder : public Cricket
{
protected:
public:
    int Centuries;
    int Fifties;
    int Wickets;
    float Bowling_average;
    int Four_wkt_hauls;
    float Economy;
    string Best_Bowling_figure;

    All_rounder()
    {
        Centuries = 0;
        Fifties = 0;
        Wickets = 0;
        Bowling_average = 0;
        Four_wkt_hauls = 0;
        Economy = 0;
        Best_Bowling_figure = "";
    }

    All_rounder(string first_name, string last_name, int age, string team, string country, int win, int lost, int no_of_matches, int innings, int runs, float batting_strike_rate, float batting_average, int fours, int sixes, string best_batting_figure, int centuries, int fifties, int wickets, float bowling_average, int four_wkt_hauls, float economy, string best_bowling_figure) : Cricket(first_name, last_name, age, team, country, win, lost, no_of_matches, innings, runs, batting_strike_rate, batting_average, fours, sixes, best_batting_figure)
    {
        Centuries = centuries;
        Fifties = fifties;
        Wickets = wickets;
        Bowling_average = bowling_average;
        Four_wkt_hauls = four_wkt_hauls;
        Economy = economy;
        Best_Bowling_figure = best_bowling_figure;
    }

    ~All_rounder() {}

    void Player_display_c_ar(vector<All_rounder>& Ar)
    {
        fstream player_c_ar("all_rounders.txt");
        vector<int> id;
        Ar.clear();
        
        string line;
        while (getline(player_c_ar, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                All_rounder temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Innings >> temp.Runs >> temp.Batting_strike_rate >> temp.Batting_average >> temp.Fifties >> temp.Centuries >> temp.Best_Batting_figure >> temp.Fours >> temp.Sixes >> temp.Wickets >> temp.Economy >> temp.Bowling_average >> temp.Best_Bowling_figure >> temp.Four_wkt_hauls)
                {
                    id.push_back(tempId);
                    Ar.push_back(temp);
                }
            }
        }
        
        cout << "ALL-ROUNDERS : " << endl << endl;
        cout << "F.Name       L.Name        AGE TEAM                        COUNTRY" << endl << endl << endl;
        
        for (size_t i = 0; i < Ar.size(); i++)
        {
            cout << left << setw(13) << Ar[i].First_name << setw(14) << Ar[i].Last_name << setw(4) << Ar[i].Age << setw(28) << Ar[i].Team << setw(13) << Ar[i].Country << endl;
            cout << "-----------------------------------------------------------------------" << endl;
        }
        cout << endl;
    }

    void Search_player_c_ar(vector<All_rounder>& Ar, string name)
    {
        fstream psearch_ar("all_rounders.txt");
        vector<int> id;
        Ar.clear();
        
        string line;
        while (getline(psearch_ar, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                All_rounder temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Innings >> temp.Runs >> temp.Batting_strike_rate >> temp.Batting_average >> temp.Fifties >> temp.Centuries >> temp.Best_Batting_figure >> temp.Fours >> temp.Sixes >> temp.Wickets >> temp.Economy >> temp.Bowling_average >> temp.Best_Bowling_figure >> temp.Four_wkt_hauls)
                {
                    id.push_back(tempId);
                    Ar.push_back(temp);
                }
            }
        }

        bool found = false;
        for (size_t i = 0; i < Ar.size(); i++)
        {
            if (name == Ar[i].First_name || name == Ar[i].Last_name)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            cout << "F.Name       L.Name        AGE TEAM                        COUNTRY      TM INN RUNS S.R.   Avg   50s 100s Best 4s  6s W   ECO   Avg   Best 4WH" << endl << endl << endl;
            
            for (size_t i = 0; i < Ar.size(); i++)
            {
                if (name == Ar[i].First_name || name == Ar[i].Last_name)
                {
                    cout << left << setw(13) << Ar[i].First_name << setw(14) << Ar[i].Last_name << setw(4) << Ar[i].Age << setw(28) << Ar[i].Team << setw(13) << Ar[i].Country << setw(3) << Ar[i].No_of_matches << setw(4) << Ar[i].Innings << setw(5) << Ar[i].Runs << setw(7) << Ar[i].Batting_strike_rate << setw(6) << Ar[i].Batting_average << setw(4) << Ar[i].Fifties << setw(5) << Ar[i].Centuries << setw(5) << Ar[i].Best_Batting_figure << setw(4) << Ar[i].Fours << setw(3) << Ar[i].Sixes << setw(4) << Ar[i].Wickets << setw(6) << Ar[i].Economy << setw(6) << Ar[i].Bowling_average << setw(5) << Ar[i].Best_Bowling_figure << setw(4) << Ar[i].Four_wkt_hauls << endl;
                    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                }
            }
        }
        else
        {
            cout << "This player does not exist" << endl << endl;
        }
    }

    void Display_stats_c_ar(vector<All_rounder>& Ar)
    {
        fstream stats_c_ar("all_rounders.txt");
        vector<int> id;
        Ar.clear();
        
        string line;
        while (getline(stats_c_ar, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                All_rounder temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Innings >> temp.Runs >> temp.Batting_strike_rate >> temp.Batting_average >> temp.Fifties >> temp.Centuries >> temp.Best_Batting_figure >> temp.Fours >> temp.Sixes >> temp.Wickets >> temp.Economy >> temp.Bowling_average >> temp.Best_Bowling_figure >> temp.Four_wkt_hauls)
                {
                    id.push_back(tempId);
                    Ar.push_back(temp);
                }
            }
        }
        
        cout << "SNO F.Name       L.Name        AGE TEAM                        COUNTRY      TM INN RUNS S.R.   Avg   50s 100s Best 4s  6s W   ECO   Avg   Best 4WH" << endl << endl << endl;
        
        for (size_t i = 0; i < Ar.size(); i++)
        {
            cout << left << setw(4) << id[i] << setw(13) << Ar[i].First_name << setw(14) << Ar[i].Last_name << setw(4) << Ar[i].Age << setw(28) << Ar[i].Team << setw(13) << Ar[i].Country << setw(3) << Ar[i].No_of_matches << setw(4) << Ar[i].Innings << setw(5) << Ar[i].Runs << setw(7) << Ar[i].Batting_strike_rate << setw(6) << Ar[i].Batting_average << setw(4) << Ar[i].Fifties << setw(5) << Ar[i].Centuries << setw(5) << Ar[i].Best_Batting_figure << setw(4) << Ar[i].Fours << setw(3) << Ar[i].Sixes << setw(4) << Ar[i].Wickets << setw(6) << Ar[i].Economy << setw(6) << Ar[i].Bowling_average << setw(5) << Ar[i].Best_Bowling_figure << setw(4) << Ar[i].Four_wkt_hauls << endl;
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        }
    }
};

//Wicket-Keeper class (Inherited from Cricket class --> Will contain all the components of Cricket as well as its parent class Player)
class Wicket_keeper : public Cricket
{
protected:
public:
    int Centuries;
    int Fifties;
    int Stumps;
    int Catches;

    Wicket_keeper() //Default Constructor for Wicket_keeper class;
    {
        Centuries = 0;
        Fifties = 0;
        Stumps = 0;
        Catches = 0;
    }

    //Parameterized constructor for Wicket_keeper class
    Wicket_keeper(string first_name, string last_name, int age, string team, string country, int win, int lost, int no_of_matches, int innings, int runs, float batting_strike_rate, float batting_average, int fours, int sixes, string best_batting_figure, int centuries, int fifties, int stumps, int catches) : Cricket(first_name, last_name, age, team, country, win, lost, no_of_matches, innings, runs, batting_strike_rate, batting_average, fours, sixes, best_batting_figure)
    {
        Centuries = centuries;
        Fifties = fifties;
        Stumps = stumps;
        Catches = catches;
    }

    void Player_display_c_wk(vector<Wicket_keeper>& Wk)
    {
        fstream player_c_wk("WICKETKEEPERS.txt");
        vector<int> id;
        Wk.clear();
        
        string line;
        while (getline(player_c_wk, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                Wicket_keeper temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Innings >> temp.Stumps >> temp.Catches >> temp.Runs >> temp.Batting_strike_rate >> temp.Batting_average >> temp.Fifties >> temp.Centuries >> temp.Best_Batting_figure >> temp.Fours >> temp.Sixes)
                {
                    id.push_back(tempId);
                    Wk.push_back(temp);
                }
            }
        }
        
        cout << "WICKET-KEEPERS : " << endl << endl;
        cout << "F.Name       L.Name        AGE TEAM                        COUNTRY" << endl << endl << endl;
        
        for (size_t i = 0; i < Wk.size(); i++)
        {
            cout << left << setw(13) << Wk[i].First_name << setw(14) << Wk[i].Last_name << setw(4) << Wk[i].Age << setw(28) << Wk[i].Team << setw(13) << Wk[i].Country << endl;
            cout << "-----------------------------------------------------------------------" << endl;
        }
        cout << endl;
    }

    void Search_player_c_wk(vector<Wicket_keeper>& Wk, string name)
    {
        fstream psearch_wk("WICKETKEEPERS.txt");
        vector<int> id;
        Wk.clear();
        
        string line;
        while (getline(psearch_wk, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                Wicket_keeper temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Innings >> temp.Stumps >> temp.Catches >> temp.Runs >> temp.Batting_strike_rate >> temp.Batting_average >> temp.Fifties >> temp.Centuries >> temp.Best_Batting_figure >> temp.Fours >> temp.Sixes)
                {
                    id.push_back(tempId);
                    Wk.push_back(temp);
                }
            }
        }

        bool found = false;
        for (size_t i = 0; i < Wk.size(); i++)
        {
            if (name == Wk[i].First_name || name == Wk[i].Last_name)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            cout << "F.Name       L.Name        AGE TEAM                        COUNTRY      TM INN C   St  RUNS S.R.   Avg   50s 100s Best 4s  6s" << endl << endl << endl;
            
            for (size_t i = 0; i < Wk.size(); i++)
            {
                if (name == Wk[i].First_name || name == Wk[i].Last_name)
                {
                    cout << left << setw(13) << Wk[i].First_name << setw(14) << Wk[i].Last_name << setw(4) << Wk[i].Age << setw(28) << Wk[i].Team << setw(13) << Wk[i].Country << setw(3) << Wk[i].No_of_matches << setw(4) << Wk[i].Innings << setw(4) << Wk[i].Stumps << setw(4) << Wk[i].Catches << setw(5) << Wk[i].Runs << setw(7) << Wk[i].Batting_strike_rate << setw(6) << Wk[i].Batting_average << setw(4) << Wk[i].Fifties << setw(5) << Wk[i].Centuries << setw(5) << Wk[i].Best_Batting_figure << setw(4) << Wk[i].Fours << setw(3) << Wk[i].Sixes << endl;
                    cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                }
            }
        }
        else
        {
            cout << "This player does not exist" << endl << endl;
        }
    }

    void Display_stats_c_wk(vector<Wicket_keeper>& Wk)
    {
        fstream stats_c_wk("WICKETKEEPERS.txt");
        vector<int> id;
        Wk.clear();
        
        string line;
        while (getline(stats_c_wk, line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                int tempId;
                Wicket_keeper temp;
                
                if (iss >> tempId >> temp.First_name >> temp.Last_name >> temp.Age >> temp.Team >> temp.Country >> temp.No_of_matches >> temp.Innings >> temp.Stumps >> temp.Catches >> temp.Runs >> temp.Batting_strike_rate >> temp.Batting_average >> temp.Fifties >> temp.Centuries >> temp.Best_Batting_figure >> temp.Fours >> temp.Sixes)
                {
                    id.push_back(tempId);
                    Wk.push_back(temp);
                }
            }
        }
        
        cout << "SNO F.Name       L.Name        AGE TEAM                        COUNTRY      TM INN C   St  RUNS S.R.   Avg   50s 100s Best 4s  6s" << endl << endl << endl;
        
        for (size_t i = 0; i < Wk.size(); i++)
        {
            cout << left << setw(4) << id[i] << setw(13) << Wk[i].First_name << setw(14) << Wk[i].Last_name << setw(4) << Wk[i].Age << setw(28) << Wk[i].Team << setw(13) << Wk[i].Country << setw(3) << Wk[i].No_of_matches << setw(4) << Wk[i].Innings << setw(4) << Wk[i].Stumps << setw(4) << Wk[i].Catches << setw(5) << Wk[i].Runs << setw(7) << Wk[i].Batting_strike_rate << setw(6) << Wk[i].Batting_average << setw(4) << Wk[i].Fifties << setw(5) << Wk[i].Centuries << setw(5) << Wk[i].Best_Batting_figure << setw(4) << Wk[i].Fours << setw(3) << Wk[i].Sixes << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
        }
    }
};
void Display_top10_run(vector<Batsman>& Bt, vector<Bowler>& Bo, vector<All_rounder>& Ar, vector<Wicket_keeper>& Wk) {
    fstream bat("batsman.txt"), bowl("bowlers.txt"), allrounder("all_rounders.txt"), wktkeeper("WICKETKEEPERS.txt");

    if (!bat.is_open()) {
        cout << "Error: Unable to open batsman.txt file!" << endl;
        return;
    }
    if (!bowl.is_open()) {
        cout << "Error: Unable to open bowlers.txt file!" << endl;
        return;
    }
    if (!allrounder.is_open()) {
        cout << "Error: Unable to open all_rounders.txt file!" << endl;
        return;
    }
    if (!wktkeeper.is_open()) {
        cout << "Error: Unable to open WICKETKEEPERS.txt file!" << endl;
        return;
    }

    vector<pair<int, string>> players;

    while (!bat.eof()) {
        Batsman b;
        bat >> b.First_name >> b.Last_name >> b.Age >> b.Team >> b.Country >> b.No_of_matches >> b.Innings >> b.Runs;
        players.push_back({b.Runs, b.First_name + " " + b.Last_name + " (" + b.Team + ")"});
    }

    while (!bowl.eof()) {
        Bowler b;
        bowl >> b.First_name >> b.Last_name >> b.Age >> b.Team >> b.Country >> b.No_of_matches >> b.Innings >> b.Runs;
        players.push_back({b.Runs, b.First_name + " " + b.Last_name + " (" + b.Team + ")"});
    }

    while (!allrounder.eof()) {
        All_rounder ar;
        allrounder >> ar.First_name >> ar.Last_name >> ar.Age >> ar.Team >> ar.Country >> ar.No_of_matches >> ar.Innings >> ar.Runs;
        players.push_back({ar.Runs, ar.First_name + " " + ar.Last_name + " (" + ar.Team + ")"});
    }

    while (!wktkeeper.eof()) {
        Wicket_keeper wk;
        wktkeeper >> wk.First_name >> wk.Last_name >> wk.Age >> wk.Team >> wk.Country >> wk.No_of_matches >> wk.Innings >> wk.Runs;
        players.push_back({wk.Runs, wk.First_name + " " + wk.Last_name + " (" + wk.Team + ")"});
    }

     for (size_t i = 0; i < players.size() - 1; ++i) {
        for (size_t j = 0; j < players.size() - i - 1; ++j) {
            if (players[j].first < players[j + 1].first) {
                swap(players[j], players[j + 1]);
            }
        }
    }

    cout << "SNo  Runs  Player (Team)" << endl;
    cout << "-------------------------" << endl;

    for (size_t i = 0; i < min(players.size(), size_t(10)); ++i) {
        cout << left << setw(4) << (i + 1) << setw(6) << players[i].first << players[i].second << endl;
    }
}

void Display_top10_strikerate(vector<Batsman>& Bt, vector<All_rounder>& Ar, vector<Wicket_keeper>& Wk)
{
    fstream bat("batsman.txt"), allrounder("all_rounders.txt"), wktkeeper("WICKETKEEPERS.txt");

    if (!bat.is_open() || !allrounder.is_open() || !wktkeeper.is_open()) {
        cout << "Error opening one or more files!" << endl;
        return;
    }

    vector<pair<float, string>> players;

    while (!bat.eof()) {
        Batsman b;
        bat >> b.First_name >> b.Last_name >> b.Age >> b.Team >> b.Country >> b.No_of_matches >> b.Innings >> b.Runs >> b.Batting_strike_rate >> b.Batting_average >> b.Fifties >> b.Centuries >> b.Best_Batting_figure >> b.Fours >> b.Sixes;
        players.push_back({b.Batting_strike_rate, b.First_name + " " + b.Last_name + " (" + b.Team + ")"});
    }

    while (!allrounder.eof()) {
        All_rounder ar;
        allrounder >> ar.First_name >> ar.Last_name >> ar.Age >> ar.Team >> ar.Country >> ar.No_of_matches >> ar.Innings >> ar.Runs >> ar.Batting_strike_rate >> ar.Batting_average >> ar.Fifties >> ar.Centuries >> ar.Best_Batting_figure >> ar.Fours >> ar.Sixes >> ar.Wickets >> ar.Economy >> ar.Bowling_average >> ar.Best_Bowling_figure >> ar.Four_wkt_hauls;
        players.push_back({ar.Batting_strike_rate, ar.First_name + " " + ar.Last_name + " (" + ar.Team + ")"});
    }

    while (!wktkeeper.eof()) {
        Wicket_keeper wk;
        wktkeeper >> wk.First_name >> wk.Last_name >> wk.Age >> wk.Team >> wk.Country >> wk.No_of_matches >> wk.Innings >> wk.Stumps >> wk.Catches >> wk.Runs >> wk.Batting_strike_rate >> wk.Batting_average >> wk.Fifties >> wk.Centuries >> wk.Best_Batting_figure >> wk.Fours >> wk.Sixes;
        players.push_back({wk.Batting_strike_rate, wk.First_name + " " + wk.Last_name + " (" + wk.Team + ")"});
    }

    for (size_t i = 0; i < players.size() - 1; ++i) {
        for (size_t j = 0; j < players.size() - i - 1; ++j) {
            if (players[j].first < players[j + 1].first) { 
                swap(players[j], players[j + 1]);
            }
        }
    }

    cout << "SNo  Strike Rate  Player (Team)" << endl;
    cout << "-------------------------------" << endl;

    for (size_t i = 0; i < min(players.size(), size_t(10)); ++i) {
        cout << left << setw(4) << (i + 1) << setw(13) << players[i].first << players[i].second << endl;
    }
}

void Display_top10_batavg(vector<Batsman>& Bt, vector<All_rounder>& Ar, vector<Wicket_keeper>& Wk)
{
    fstream bat("batsman.txt"), allrounder("all_rounders.txt"), wktkeeper("WICKETKEEPERS.txt");
    
    if (!bat.is_open() || !allrounder.is_open() || !wktkeeper.is_open()) {
        cout << "Error opening one or more files!" << endl;
        return;
    }

    vector<pair<float, string>> players;

    while (!bat.eof()) {
        Batsman b;
        int id;
        bat >> id >> b.First_name >> b.Last_name >> b.Age >> b.Team >> b.Country >> b.No_of_matches >> b.Innings >> b.Runs >> b.Batting_strike_rate >> b.Batting_average >> b.Fifties >> b.Centuries >> b.Best_Batting_figure >> b.Fours >> b.Sixes;
        players.push_back({b.Batting_average, to_string(id) + " " + b.First_name + " " + b.Last_name + " " + b.Team + " " + to_string(b.No_of_matches)});
    }

    while (!allrounder.eof()) {
        All_rounder ar;
        int id;
        allrounder >> id >> ar.First_name >> ar.Last_name >> ar.Age >> ar.Team >> ar.Country >> ar.No_of_matches >> ar.Innings >> ar.Runs >> ar.Batting_strike_rate >> ar.Batting_average >> ar.Fifties >> ar.Centuries >> ar.Best_Batting_figure >> ar.Fours >> ar.Sixes >> ar.Wickets >> ar.Economy >> ar.Bowling_average >> ar.Best_Bowling_figure >> ar.Four_wkt_hauls;
        players.push_back({ar.Batting_average, to_string(id) + " " + ar.First_name + " " + ar.Last_name + " " + ar.Team + " " + to_string(ar.No_of_matches)});
    }

    while (!wktkeeper.eof()) {
        Wicket_keeper wk;
        int id;
        wktkeeper >> id >> wk.First_name >> wk.Last_name >> wk.Age >> wk.Team >> wk.Country >> wk.No_of_matches >> wk.Innings >> wk.Stumps >> wk.Catches >> wk.Runs >> wk.Batting_strike_rate >> wk.Batting_average >> wk.Fifties >> wk.Centuries >> wk.Best_Batting_figure >> wk.Fours >> wk.Sixes;
        players.push_back({wk.Batting_average, to_string(id) + " " + wk.First_name + " " + wk.Last_name + " " + wk.Team + " " + to_string(wk.No_of_matches)});
    }

    for (size_t i = 0; i < players.size() - 1; ++i) {
        for (size_t j = 0; j < players.size() - i - 1; ++j) {
            if (players[j].first < players[j + 1].first) {
                swap(players[j], players[j + 1]);
            }
        }
    }

    vector<pair<float, string>> unique_players;
    for (size_t i = 0; i < players.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < unique_players.size(); ++j) {
            if (unique_players[j].first == players[i].first) {
                found = true;
                break;
            }
        }
        if (!found) {
            unique_players.push_back(players[i]);
        }
    }

    cout << "SNo  F.Name     L.Name       TEAM                        TM   Bat Avg" << endl << endl << endl;
    
    for (size_t i = 0; i < min(unique_players.size(), size_t(10)); ++i) {
        istringstream iss(unique_players[i].second);
        string id, fname, lname, team, matches;
        iss >> id >> fname >> lname >> team >> matches;
        cout << left << setw(5) << id << setw(11) << fname << setw(13) << lname << setw(28) << team << setw(5) << matches << setw(5) << unique_players[i].first << endl;
        cout << "---------------------------------------------------------------------" << endl;
    }
}

void Display_top10_wkt(vector<Bowler>& Bo, vector<All_rounder>& Ar)
{
    fstream bowl("bowlers.txt"), allrounder("all_rounders.txt");
    
    if (!bowl.is_open() || !allrounder.is_open()) {
        cout << "Error opening one or more files!" << endl;
        return;
    }

    vector<pair<int, string>> players;

    while (!bowl.eof()) {
        Bowler b;
        int id;
        bowl >> id >> b.First_name >> b.Last_name >> b.Age >> b.Team >> b.Country >> b.No_of_matches >> b.Innings >> b.Wickets >> b.Economy >> b.Bowling_average >> b.Best_Bowling_figure >> b.Four_wkt_hauls >> b.Runs >> b.Batting_strike_rate >> b.Batting_average >> b.Best_Batting_figure >> b.Fours >> b.Sixes;
        players.push_back({b.Wickets, to_string(id) + " " + b.First_name + " " + b.Last_name + " " + b.Team + " " + to_string(b.No_of_matches)});
    }

    while (!allrounder.eof()) {
        All_rounder ar;
        int id;
        allrounder >> id >> ar.First_name >> ar.Last_name >> ar.Age >> ar.Team >> ar.Country >> ar.No_of_matches >> ar.Innings >> ar.Runs >> ar.Batting_strike_rate >> ar.Batting_average >> ar.Fifties >> ar.Centuries >> ar.Best_Batting_figure >> ar.Fours >> ar.Sixes >> ar.Wickets >> ar.Economy >> ar.Bowling_average >> ar.Best_Bowling_figure >> ar.Four_wkt_hauls;
        players.push_back({ar.Wickets, to_string(id) + " " + ar.First_name + " " + ar.Last_name + " " + ar.Team + " " + to_string(ar.No_of_matches)});
    }

    for (size_t i = 0; i < players.size() - 1; ++i) {
        for (size_t j = 0; j < players.size() - i - 1; ++j) {
            if (players[j].first < players[j + 1].first) {
                swap(players[j], players[j + 1]);
            }
        }
    }

    vector<pair<int, string>> unique_players;
    for (size_t i = 0; i < players.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < unique_players.size(); ++j) {
            if (unique_players[j].first == players[i].first) {
                found = true;
                break;
            }
        }
        if (!found) {
            unique_players.push_back(players[i]);
        }
    }

    cout << "SNo  F.Name     L.Name       TEAM                        TM    Wkt" << endl << endl << endl;
    
    for (size_t i = 0; i < min(unique_players.size(), size_t(10)); ++i) {
        istringstream iss(unique_players[i].second);
        string id, fname, lname, team, matches;
        iss >> id >> fname >> lname >> team >> matches;
        cout << left << setw(5) << id << setw(11) << fname << setw(14) << lname << setw(28) << team << setw(5) << matches << setw(5) << unique_players[i].first << endl;
        cout << "------------------------------------------------------------------" << endl;
    }
}

void Display_top10_bowlavg(vector<Bowler>& Bo, vector<All_rounder>& Ar)
{
    fstream bowl("bowlers.txt"), allrounder("all_rounders.txt");
    
    if (!bowl.is_open() || !allrounder.is_open()) {
        cout << "Error opening one or more files!" << endl;
        return;
    }

    vector<pair<float, string>> players;

    while (!bowl.eof()) {
        Bowler b;
        int id;
        bowl >> id >> b.First_name >> b.Last_name >> b.Age >> b.Team >> b.Country >> b.No_of_matches >> b.Innings >> b.Wickets >> b.Economy >> b.Bowling_average >> b.Best_Bowling_figure >> b.Four_wkt_hauls >> b.Runs >> b.Batting_strike_rate >> b.Batting_average >> b.Best_Batting_figure >> b.Fours >> b.Sixes;
        if (b.Bowling_average != 0) {
            players.push_back({b.Bowling_average, to_string(id) + " " + b.First_name + " " + b.Last_name + " " + b.Team + " " + to_string(b.No_of_matches)});
        }
    }

    while (!allrounder.eof()) {
        All_rounder ar;
        int id;
        allrounder >> id >> ar.First_name >> ar.Last_name >> ar.Age >> ar.Team >> ar.Country >> ar.No_of_matches >> ar.Innings >> ar.Runs >> ar.Batting_strike_rate >> ar.Batting_average >> ar.Fifties >> ar.Centuries >> ar.Best_Batting_figure >> ar.Fours >> ar.Sixes >> ar.Wickets >> ar.Economy >> ar.Bowling_average >> ar.Best_Bowling_figure >> ar.Four_wkt_hauls;
        if (ar.Bowling_average != 0) {
            players.push_back({ar.Bowling_average, to_string(id) + " " + ar.First_name + " " + ar.Last_name + " " + ar.Team + " " + to_string(ar.No_of_matches)});
        }
    }

    for (size_t i = 0; i < players.size() - 1; ++i) {
        for (size_t j = 0; j < players.size() - i - 1; ++j) {
            if (players[j].first > players[j + 1].first) {
                swap(players[j], players[j + 1]);
            }
        }
    }

    vector<pair<float, string>> unique_players;
    for (size_t i = 0; i < players.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < unique_players.size(); ++j) {
            if (unique_players[j].first == players[i].first) {
                found = true;
                break;
            }
        }
        if (!found) {
            unique_players.push_back(players[i]);
        }
    }

    cout << "SNo  F.Name     L.Name       TEAM                        TM    Bowl Avg" << endl << endl << endl;
    
    for (size_t i = 0; i < min(unique_players.size(), size_t(10)); ++i) {
        istringstream iss(unique_players[i].second);
        string id, fname, lname, team, matches;
        iss >> id >> fname >> lname >> team >> matches;
        cout << left << setw(5) << id << setw(11) << fname << setw(14) << lname << setw(28) << team << setw(5) << matches << setw(5) << unique_players[i].first << endl;
        cout << "-----------------------------------------------------------------------" << endl;
    }
}

void Display_top10_eco(vector<Bowler>& Bo, vector<All_rounder>& Ar)
{
    fstream bowl("bowlers.txt"), allrounder("all_rounders.txt");
    
    if (!bowl.is_open() || !allrounder.is_open()) {
        cout << "Error opening one or more files!" << endl;
        return;
    }

    vector<pair<float, string>> players;

    while (!bowl.eof()) {
        Bowler b;
        int id;
        bowl >> id >> b.First_name >> b.Last_name >> b.Age >> b.Team >> b.Country >> b.No_of_matches >> b.Innings >> b.Wickets >> b.Economy >> b.Bowling_average >> b.Best_Bowling_figure >> b.Four_wkt_hauls >> b.Runs >> b.Batting_strike_rate >> b.Batting_average >> b.Best_Batting_figure >> b.Fours >> b.Sixes;
        if (b.Economy != 0) {
            players.push_back({b.Economy, to_string(id) + " " + b.First_name + " " + b.Last_name + " " + b.Team + " " + to_string(b.No_of_matches)});
        }
    }

    while (!allrounder.eof()) {
        All_rounder ar;
        int id;
        allrounder >> id >> ar.First_name >> ar.Last_name >> ar.Age >> ar.Team >> ar.Country >> ar.No_of_matches >> ar.Innings >> ar.Runs >> ar.Batting_strike_rate >> ar.Batting_average >> ar.Fifties >> ar.Centuries >> ar.Best_Batting_figure >> ar.Fours >> ar.Sixes >> ar.Wickets >> ar.Economy >> ar.Bowling_average >> ar.Best_Bowling_figure >> ar.Four_wkt_hauls;
        if (ar.Economy != 0) {
            players.push_back({ar.Economy, to_string(id) + " " + ar.First_name + " " + ar.Last_name + " " + ar.Team + " " + to_string(ar.No_of_matches)});
        }
    }

    for (size_t i = 0; i < players.size() - 1; ++i) {
        for (size_t j = 0; j < players.size() - i - 1; ++j) {
            if (players[j].first > players[j + 1].first) {
                swap(players[j], players[j + 1]);
            }
        }
    }

    vector<pair<float, string>> unique_players;
    for (size_t i = 0; i < players.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < unique_players.size(); ++j) {
            if (unique_players[j].first == players[i].first) {
                found = true;
                break;
            }
        }
        if (!found) {
            unique_players.push_back(players[i]);
        }
    }

    cout << "SNo  F.Name     L.Name       TEAM                        TM    Eco" << endl << endl << endl;
    
    for (size_t i = 0; i < min(unique_players.size(), size_t(10)); ++i) {
        istringstream iss(unique_players[i].second);
        string id, fname, lname, team, matches;
        iss >> id >> fname >> lname >> team >> matches;
        cout << left << setw(5) << id << setw(11) << fname << setw(14) << lname << setw(28) << team << setw(5) << matches << setw(5) << unique_players[i].first << endl;
        cout << "--------------------------------------------------------------------" << endl;
    }
}

void Display_top10_goal(vector<Attack>& A, vector<MidField>& Mf, vector<Defence>& D)
{
    fstream forward("attack.txt"), midf("midfield.txt"), defence("DEFENDERS.txt");

    if (!forward.is_open() || !midf.is_open() || !defence.is_open()) {
        cout << "Error opening one or more files!" << endl;
        return;
    }

    vector<pair<int, string>> players;

    while (!forward.eof()) {
        Attack a;
        forward >> a.First_name >> a.Last_name >> a.Position >> a.Age >> a.Team >> a.Country >> a.No_of_matches >> a.Goals >> a.Shot_accuracy >> a.Assist >> a.Pass_Accuracy >> a.Red_card;
        players.push_back({a.Goals, a.First_name + " " + a.Last_name + " " + a.Position + " " + to_string(a.Age) + " " + a.Team + " " + a.Country + " " + to_string(a.No_of_matches)});
    }

    while (!midf.eof()) {
        MidField mf;
        midf >> mf.First_name >> mf.Last_name >> mf.Position >> mf.Age >> mf.Team >> mf.Country >> mf.No_of_matches >> mf.Goals >> mf.Shot_accuracy >> mf.Assist >> mf.Pass_Accuracy >> mf.Red_card;
        players.push_back({mf.Goals, mf.First_name + " " + mf.Last_name + " " + mf.Position + " " + to_string(mf.Age) + " " + mf.Team + " " + mf.Country + " " + to_string(mf.No_of_matches)});
    }

    while (!defence.eof()) {
        Defence d;
        defence >> d.First_name >> d.Last_name >> d.Position >> d.Age >> d.Team >> d.Country >> d.No_of_matches >> d.Tackles_won >> d.Clearance >> d.Blocked_shots >> d.Red_card >> d.Goals >> d.Pass_Accuracy;
        players.push_back({d.Goals, d.First_name + " " + d.Last_name + " " + d.Position + " " + to_string(d.Age) + " " + d.Team + " " + d.Country + " " + to_string(d.No_of_matches)});
    }

    for (size_t i = 0; i < players.size() - 1; ++i) {
        for (size_t j = 0; j < players.size() - i - 1; ++j) {
            if (players[j].first < players[j + 1].first) {
                swap(players[j], players[j + 1]);
            }
        }
    }

    vector<pair<int, string>> unique_players;
    for (size_t i = 0; i < players.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < unique_players.size(); ++j) {
            if (unique_players[j].first == players[i].first) {
                found = true;
                break;
            }
        }
        if (!found) {
            unique_players.push_back(players[i]);
        }
    }

    cout << "SNo Name                    Pos  Age Club                  Country      GP   Goals" << endl << endl;
    
    for (size_t i = 0; i < min(unique_players.size(), size_t(10)); ++i) {
        istringstream iss(unique_players[i].second);
        string fname, lname, pos, age, team, country, matches;
        iss >> fname >> lname >> pos >> age >> team >> country >> matches;
        cout << left << setw(4) << (i + 1) << setw(10) << fname << setw(14) << lname << setw(5) << pos << setw(4) << age << setw(22) << team << setw(13) << country << setw(5) << matches << setw(6) << unique_players[i].first << endl;
        cout << "----------------------------------------------------------------------------------" << endl;
    }
}

void Display_top10_cleansheet(vector<GoalKeeper>& Gk)
{
    fstream gk("gk.txt");
    
    if (!gk.is_open()) {
        cout << "Error opening the file!!" << endl;
        return;
    }

    vector<pair<int, string>> players;

    while (!gk.eof()) {
        GoalKeeper g;
        gk >> g.First_name >> g.Last_name >> g.Position >> g.Age >> g.Team >> g.Country >> g.No_of_matches >> g.Clean_sheets >> g.Saves_made >> g.Goals_conceeded >> g.Red_card;
        players.push_back({g.Clean_sheets, g.First_name + " " + g.Last_name + " " + g.Position + " " + to_string(g.Age) + " " + g.Team + " " + g.Country + " " + to_string(g.No_of_matches)});
    }

    for (size_t i = 0; i < players.size() - 1; ++i) {
        for (size_t j = 0; j < players.size() - i - 1; ++j) {
            if (players[j].first < players[j + 1].first) {
                swap(players[j], players[j + 1]);
            }
        }
    }

    vector<pair<int, string>> unique_players;
    for (size_t i = 0; i < players.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < unique_players.size(); ++j) {
            if (unique_players[j].first == players[i].first) {
                found = true;
                break;
            }
        }
        if (!found) {
            unique_players.push_back(players[i]);
        }
    }

    cout << "SNo Name                    Pos  Age Club                  Country      GP   C.Sheet" << endl << endl;

    for (size_t i = 0; i < min(unique_players.size(), size_t(10)); ++i) {
        istringstream iss(unique_players[i].second);
        string fname, lname, pos, age, team, country, matches;
        iss >> fname >> lname >> pos >> age >> team >> country >> matches;
        cout << left << setw(4) << (i + 1) << setw(10) << fname << setw(14) << lname << setw(5) << pos << setw(4) << age << setw(22) << team << setw(13) << country << setw(5) << matches << setw(6) << unique_players[i].first << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
    }
}

void Display_top10_assist(vector<Attack>& A, vector<MidField>& Mf)
{
    fstream forward("attack.txt");
    fstream midf("midfield.txt");
    
    if (!forward.is_open()) {
        cout << "Error opening attack.txt!!" << endl;
        return;
    }
    if (!midf.is_open()) {
        cout << "Error opening midfield.txt!!" << endl;
        return;
    }

    vector<pair<int, string>> players;

    while (!forward.eof()) {
        Attack a;
        forward >> a.First_name >> a.Last_name >> a.Position >> a.Age >> a.Team >> a.Country >> a.No_of_matches >> a.Goals >> a.Shot_accuracy >> a.Assist >> a.Pass_Accuracy >> a.Red_card;
        players.push_back({a.Assist, a.First_name + " " + a.Last_name + " " + a.Position + " " + to_string(a.Age) + " " + a.Team + " " + a.Country + " " + to_string(a.No_of_matches)});
    }

    while (!midf.eof()) {
        MidField m;
        midf >> m.First_name >> m.Last_name >> m.Position >> m.Age >> m.Team >> m.Country >> m.No_of_matches >> m.Goals >> m.Shot_accuracy >> m.Assist >> m.Pass_Accuracy >> m.Red_card;
        players.push_back({m.Assist, m.First_name + " " + m.Last_name + " " + m.Position + " " + to_string(m.Age) + " " + m.Team + " " + m.Country + " " + to_string(m.No_of_matches)});
    }

    for (size_t i = 0; i < players.size() - 1; ++i) {
        for (size_t j = 0; j < players.size() - i - 1; ++j) {
            if (players[j].first < players[j + 1].first) {
                swap(players[j], players[j + 1]);
            }
        }
    }

    vector<pair<int, string>> unique_players;
    for (size_t i = 0; i < players.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < unique_players.size(); ++j) {
            if (unique_players[j].first == players[i].first) {
                found = true;
                break;
            }
        }
        if (!found) {
            unique_players.push_back(players[i]);
        }
    }

    cout << "SNo Name                    Pos  Age Club                  Country      GP   Assist" << endl << endl;

    for (size_t i = 0; i < min(unique_players.size(), size_t(10)); ++i) {
        istringstream iss(unique_players[i].second);
        string fname, lname, pos, age, team, country, matches;
        iss >> fname >> lname >> pos >> age >> team >> country >> matches;
        cout << left << setw(4) << (i + 1) << setw(10) << fname << setw(14) << lname << setw(5) << pos << setw(4) << age << setw(22) << team << setw(13) << country << setw(5) << matches << setw(6) << unique_players[i].first << endl;
        cout << "-----------------------------------------------------------------------------------" << endl;
    }
}

void Display_top10_defenders(vector<Defence>& D)
{
    fstream defence("DEFENDERS.txt");
    
    if (!defence.is_open()) {
        cout << "Error opening DEFENDERS.txt!!" << endl;
        return;
    }

    vector<pair<int, string>> players;

    while (!defence.eof()) {
        Defence d;
        defence >> d.First_name >> d.Last_name >> d.Position >> d.Age >> d.Team >> d.Country >> d.No_of_matches >> d.Tackles_won >> d.Clearance >> d.Blocked_shots >> d.Red_card >> d.Goals >> d.Pass_Accuracy;
        players.push_back({d.Clearance, d.First_name + " " + d.Last_name + " " + d.Position + " " + to_string(d.Age) + " " + d.Team + " " + d.Country + " " + to_string(d.No_of_matches)});
    }

    // Sort players by clearances (descending)
    for (size_t i = 0; i < players.size() - 1; ++i) {
        for (size_t j = 0; j < players.size() - i - 1; ++j) {
            if (players[j].first < players[j + 1].first) {
                swap(players[j], players[j + 1]);
            }
        }
    }

    // Remove duplicates based on clearance count
    vector<pair<int, string>> unique_players;
    for (size_t i = 0; i < players.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < unique_players.size(); ++j) {
            if (unique_players[j].first == players[i].first) {
                found = true;
                break;
            }
        }
        if (!found) {
            unique_players.push_back(players[i]);
        }
    }

    cout << "SNo Name                    Pos  Age Club                  Country      GP   Clearance" << endl << endl;

    for (size_t i = 0; i < min(unique_players.size(), size_t(10)); ++i) {
        istringstream iss(unique_players[i].second);
        string fname, lname, pos, age, team, country, matches;
        iss >> fname >> lname >> pos >> age >> team >> country >> matches;
        cout << left << setw(4) << (i + 1) << setw(10) << fname << setw(14) << lname << setw(5) << pos << setw(4) << age << setw(22) << team << setw(13) << country << setw(5) << matches << setw(7) << unique_players[i].first << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
    }
}

void Display_top10_leastgoal(vector<GoalKeeper>& Gk)
{
    fstream gk("gk.txt");
    
    if (!gk.is_open()) {
        cout << "Error opening gk.txt!!" << endl;
        return;
    }

    vector<pair<int, string>> players;

    while (!gk.eof()) {
        GoalKeeper g;
        gk >> g.First_name >> g.Last_name >> g.Position >> g.Age >> g.Team >> g.Country >> g.No_of_matches >> g.Clean_sheets >> g.Saves_made >> g.Goals_conceeded >> g.Red_card;
        players.push_back({g.Goals_conceeded, g.First_name + " " + g.Last_name + " " + g.Position + " " + to_string(g.Age) + " " + g.Team + " " + g.Country + " " + to_string(g.No_of_matches)});
    }

    // Sort players by goals conceded (ascending - least goals first)
    for (size_t i = 0; i < players.size() - 1; ++i) {
        for (size_t j = 0; j < players.size() - i - 1; ++j) {
            if (players[j].first > players[j + 1].first) {
                swap(players[j], players[j + 1]);
            }
        }
    }

    // Remove duplicates based on goals conceded count
    vector<pair<int, string>> unique_players;
    for (size_t i = 0; i < players.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < unique_players.size(); ++j) {
            if (unique_players[j].first == players[i].first) {
                found = true;
                break;
            }
        }
        if (!found) {
            unique_players.push_back(players[i]);
        }
    }

    cout << "SNo Name                    Pos  Age Club                  Country      GP   Goals Conceded" << endl << endl;

    for (size_t i = 0; i < min(unique_players.size(), size_t(10)); ++i) {
        istringstream iss(unique_players[i].second);
        string fname, lname, pos, age, team, country, matches;
        iss >> fname >> lname >> pos >> age >> team >> country >> matches;
        cout << left << setw(4) << (i + 1) << setw(10) << fname << setw(14) << lname << setw(5) << pos << setw(4) << age << setw(22) << team << setw(13) << country << setw(5) << matches << setw(6) << unique_players[i].first << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
    }
}
// ---------- FOOTBALL MENUS ----------

void footballStatsTopMenu(vector<Attack>& A, vector<MidField>& Mf, vector<Defence>& D, vector<GoalKeeper>& Gk) {
    while (true) {
        cout << "\t\t\t\t>>>>>> Welcome to Football <<<<<<" << endl << endl;
        cout << "\t\t\t\tX----- View League Leaders -----X" << endl << endl;
        cout << "\t\t\t\t1. Top Goal Scorers" << endl
             << "\t\t\t\t2. Top Assists" << endl
             << "\t\t\t\t3. Cleansheets" << endl
             << "\t\t\t\t4. Top Defenders " << endl
             << "\t\t\t\t5. Least Goals Conceeded" << endl
             << "\t\t\t\t6. Return to Main Menu" << endl
             << "\t\t\t\t0. Exit the program" << endl << endl;
        cout << "\t\t\t\tEnter your choice: ";
        int top;
        cin >> top;
        switch (top) {
            case 1:
                Display_top10_goal(A, Mf, D);
                break;
            case 2:
                Display_top10_assist(A, Mf);
                break;
            case 3:
                Display_top10_cleansheet(Gk);
                break;
            case 4:
                Display_top10_defenders(D);
                break;
            case 5:
                Display_top10_leastgoal(Gk);
                break;
            case 6:
                return;
          
            default:
                cout << "No such option available! Please try again!" << endl;
        }
    }
}
void footballStatsByPositionMenu(vector<Attack>& A, vector<MidField>& Mf, vector<Defence>& D, vector<GoalKeeper>& Gk) {
    while (true) {
        cout << "\t\t\t\t1. Forward" << endl
             << "\t\t\t\t2. Mid-Field" << endl
             << "\t\t\t\t3. Defence " << endl
             << "\t\t\t\t4. Goal-keeper" << endl
             << "\t\t\t\t5. Return to Main Menu" << endl << endl;
        cout << "\t\t\t\tEnter your choice: ";
        int position;
        cin >> position;
        switch (position) {
            case 1:
                for (auto& h : A) {
                    h.Display_stats_f_a(A);
                }
                break;
            case 2:
                for (auto& h : Mf) {
                    h.Display_stats_f_m(Mf);
                }
                break;
            case 3:
                for (auto& h : D) {
                    h.Display_stats_f_d(D);
                }
                break;
            case 4:
                for (auto& h : Gk) {
                    h.Display_stats_f_gk(Gk);
                }
                break;
            case 5:
                return;
            default:
                cout << "No such option available! Please try again!" << endl;
        }
    }
}

void footballPlayerMenu(vector<Attack>& A, vector<MidField>& Mf, vector<Defence>& D, vector<GoalKeeper>& Gk) {
    while (true) {
        cout << "\t\t\t\t>>>>>> Welcome to Football <<<<<<" << endl << endl;
        cout << "\t\t\t\tX--------- View Players --------X" << endl << endl;
        cout << "\t\t\t\t1. Search Player " << endl
             << "\t\t\t\t2. View All Players " << endl
             << "\t\t\t\t3. Return to Main Menu" << endl
             << "\t\t\t\t0. Exit the program " << endl << endl;
        cout << "\t\t\t\tEnter your choice: ";
        int player;
        cin >> player;
        if (player == 1) {
            while (true) {
                cout << "\t\t\t\t1. Forward" << endl
                     << "\t\t\t\t2. Mid-Fielder" << endl
                     << "\t\t\t\t3. Defender " << endl
                     << "\t\t\t\t4. Goal-Keeper" << endl
                     << "\t\t\t\t5. Return to Main Menu" << endl << endl;
                cout << "\t\t\t\tEnter your choice: ";
                int category;
                cin >> category;
                string name;
                switch (category) {
                    case 1:
                        cout << "Enter name of the player to search : ";
                        cin >> name;
                        for (auto& h : A){ 
                       h.Search_player_f_a(A, name);}
                        break;
                  case 2:
                        cout << "Enter name of the player to search : ";
                        cin >> name;
                        for (auto& h : Mf) {
                            h.Search_player_f_m(Mf, name);
                        }
                        break;
                  case 3:
                        cout << "Enter name of the player to search : ";
                        cin >> name;
                        for (auto& h : D) {
                         h.Search_player_f_d(D, name);
                    }
                    break;
                  case 4:
                 cout << "Enter name of the player to search : ";
                  cin >> name;
                  for (auto& h : Gk) {
                     h.Search_player_f_gk(Gk, name);
                 }
                 break;
                    case 5:
                    return ;
                    default:
                        cout << "No such option available! Please try again!" << endl;
                }
            }
        }
     else if (player == 2)
         {      
        for (auto& h : A) {
            h.Player_display_f_a(A);
        }
        for (auto& h : Mf) {
            h.Player_display_f_m(Mf);
        }
        for (auto& h : D) {
            h.Player_display_f_d(D);
        }
        for (auto& h : Gk) {
            h.Player_display_f_gk(Gk);
        }

        } else if (player == 3) {
            return;
        } else if (player == 0) {
            exit(0);
        } else {
            cout << "No such option available! Please try again!" << endl;
        }
    }
}
void footballStatsMenu(vector<Attack>& A, vector<MidField>& Mf, vector<Defence>& D, vector<GoalKeeper>& Gk) {
    while (true) {
        cout << "\t\t\t\t>>>>>> Welcome to Football <<<<<<" << endl << endl;
        cout << "\t\t\t\tX---------- View Stats ---------X" << endl << endl;
        cout << "\t\t\t\t1. View Top Players" << endl
             << "\t\t\t\t2. View Stats by Positions " << endl
             << "\t\t\t\t3. Return to Main Menu" << endl
             << "\t\t\t\t0. Exit the program" << endl << endl;
        cout << "\t\t\t\tEnter your choice: ";
        int stat;
        cin >> stat;
        if (stat == 1) {
            footballStatsTopMenu(A, Mf, D, Gk);
        } else if (stat == 2) {
            footballStatsByPositionMenu(A, Mf, D, Gk);
        } else if (stat == 3) {
            return;
        } else if (stat == 0) {
            exit(0);
        } else {
            cout << "No such option available! Please try again!" << endl;
        }
    }
}
void footballMenu(vector<Football>& F, vector<Attack>& A, vector<MidField>& Mf, vector<Defence>& D, vector<GoalKeeper>& Gk) {
    while (true) {
        if (!F.empty()) {
            F[0].displaymain(); 
        } 
        else {
            cout << "No football data available!" << endl;
            return;
        }

        int switch_f;
        cin >> switch_f;
        switch (switch_f) {
            case 1:
                if (!F.empty()) {
                    F[0].Team_display_f(); // Display teams using the first Football object
                }

                break;
            case 2:
                footballPlayerMenu(A, Mf, D, Gk);
                break;
            case 3:
                footballStatsMenu(A, Mf, D, Gk);
                break;
            case 4:
                if (!F.empty()) {
                    F[0].Standings_display_f(); // Display standings using the first Football object
                }
                break;
            case 5:
                return; // Back to main menu
            case 0:
                exit(0);
            default:
                cout << "No such option available! Please Try Again" << endl;
        }
    }
}

// ---------- CRICKET MENUS ----------
void cricketStatsTopMenu(vector<Batsman>& Bt, vector<Bowler>& Bo, vector<All_rounder>& Ar, vector<Wicket_keeper>& Wk) {
    while (true) {
        cout << "\t\t\t\t>>>>>> Welcome to Cricket <<<<<<" << endl << endl;
        cout << "\t\t\t\tX----- View League Leaders -----X" << endl << endl;
        cout << "\t\t\t\t1. Top Run Scorers" << endl
             << "\t\t\t\t2. Highest Batting Strike Rates" << endl
             << "\t\t\t\t3. Highest Batting Average" << endl
             << "\t\t\t\t4. Top Wicket Takers" << endl
             << "\t\t\t\t5. Best Bowling Average" << endl
             << "\t\t\t\t6. Best Economy Rate" << endl
             << "\t\t\t\t7. Return to Previous Menu " << endl
             << "\t\t\t\t0. Exit" << endl << endl;
        cout << "\t\t\t\tEnter your choice: ";
        int field;
        cin >> field;
        switch (field) {
            case 1:
                Display_top10_run(Bt, Bo, Ar, Wk);
                break;
            case 2:
                Display_top10_strikerate(Bt, Ar, Wk);
                break;
            case 3:
                Display_top10_batavg(Bt, Ar, Wk);
                break;
            case 4:
                Display_top10_wkt(Bo, Ar);
                break;
            case 5:
                Display_top10_bowlavg(Bo, Ar);
                break;
            case 6:
                Display_top10_eco(Bo, Ar);
                break;
            case 7:
                return;
           case 0:
                false;
                 break;
            default:
                cout << "No such option available! Please try again!" << endl;
        }
    }
}
void cricketStatsByCategoryMenu(vector<Batsman>& Bt, vector<Bowler>& Bo, vector<All_rounder>& Ar, vector<Wicket_keeper>& Wk) {
    while (true) {
        cout << "1. Batsman" << endl
             << "2. Bowler" << endl
             << "3. All-Rounder " << endl
             << "4. Wicket-Keeper" << endl
             << "5. Return to Main Menu" << endl;
        cout << "Enter your choice: ";
        int category;
        cin >> category;
        switch (category) {
            case 1:
             for( auto h: Bt)
                h.Display_stats_c_bt(Bt);
                break;
            case 2:
             for( auto h: Bo)
                h.Display_stats_c_bo(Bo);
                break;
            case 3:
                for(auto h: Ar)
                h.Display_stats_c_ar(Ar);
                break;
            case 4:
                for(auto h: Wk)
                h.Display_stats_c_wk(Wk);
                break;
            case 5:
                return;
            default:
                cout << "No such option available! Please try again!" << endl;
        }
    }
}

void cricketPlayerMenu(vector<Batsman>& Bt, vector<Bowler>& Bo, vector<All_rounder>& Ar, vector<Wicket_keeper>& Wk) {
    while (true) {
        cout << "\t\t\t\t>>>>>> Welcome to Cricket <<<<<<" << endl << endl;
        cout << "\t\t\t\tX--------- View Players --------X" << endl << endl;
        cout << "\t\t\t\t1. Search Player " << endl
             << "\t\t\t\t2. View All Players " << endl
             << "\t\t\t\t3. Return to Main Menu" << endl
             << "\t\t\t\t0. Exit the program " << endl << endl;
        cout << "\t\t\t\tEnter your choice: ";
        int player;
        cin >> player;
        if (player == 1) {
            while (true) {
                cout << "                                  1. Batsman" << endl
                     << "                                  2. Bowler" << endl
                     << "                                  3. All-Rounder " << endl
                     << "                                  4. Wicket-Keeper" << endl
                     << "                                  5. Return to Main Menu" << endl << endl;
                cout << "                                  Enter your choice: ";
                int category;
                cin >> category;
                string name;
                if (category >= 1 && category <= 4) {
                    cout << "Enter name of the player to search : ";
                    cin >> name;
                }
                switch (category) {
                    case 1:
                        cout << "Enter name of the player to search : ";
                        cin >> name;
                        for (auto& h : Bt) {
                            h.Search_player_c_bt(Bt, name);
                        }
                        break;
                    case 2:
                        cout << "Enter name of the player to search : ";
                        cin >> name;
                        for (auto& h : Bo) {
                            h.Search_player_c_bo(Bo, name);
                        }
                        break;
                    case 3:
                        cout << "Enter name of the player to search : ";
                        cin >> name;
                        for (auto& h : Ar) {
                            h.Search_player_c_ar(Ar, name);
                        }
                        break;
                    case 4:
                        cout << "Enter name of the player to search : ";
                        cin >> name;
                        for (auto& h : Wk) {
                            h.Search_player_c_wk(Wk, name);
                        }
                        break;
                    case 5:
                        return;
                    case 0:
                       false;
                       break;
                    default:
                        cout << "No such option available! Please try again!" << endl;
                }
            }
            
        } else if (player == 2) {
            for (auto& h : Bt) {
                h.Player_display_c_bt(Bt);
            }
            
            for (auto& h : Bo) {
                h.Player_display_c_bo(Bo);
            }
            
            for (auto& h : Ar) {
                h.Player_display_c_ar(Ar);
            }
            
            for (auto& h : Wk) {
                h.Player_display_c_wk(Wk);
            }
        } else if (player == 3) {
            return;
        } else if (player == 0) {
            exit(0);
        } else {
            cout << "No such option available! Please try again!" << endl;
        }
    }
}
void cricketStatsMenu(vector<Batsman>& Bt, vector<Bowler>& Bo, vector<All_rounder>& Ar, vector<Wicket_keeper>& Wk) {
    while (true) {
        cout << "\t\t\t\t>>>>>> Welcome to Cricket <<<<<<" << endl << endl;
        cout << "\t\t\t\tX---------- View Stats ---------X" << endl << endl;
        cout << "\t\t\t\t1. View League Leaders" << endl
             << "\t\t\t\t2. View Stats by Category " << endl
             << "\t\t\t\t3. Return to Main Menu" << endl
             << "\t\t\t\t0. Exit the program" << endl << endl;
        cout << "\t\t\t\tEnter your choice: ";
        int stat;
        cin >> stat;
        if (stat == 1) {
            cricketStatsTopMenu(Bt, Bo, Ar, Wk);
        } else if (stat == 2) {
            cricketStatsByCategoryMenu(Bt, Bo, Ar, Wk);
        } else if (stat == 3) {
            return;
        } else if (stat == 0) {
             
                       false;
                       break;
        } else {
            cout << "No such option available! Please try again!" << endl;
        }
    }
}

void cricketMenu(Cricket& C, vector<Batsman>& Bt, vector<Bowler>& Bo, vector<All_rounder>& Ar, vector<Wicket_keeper>& Wk) {
    while (true) {
        C.displaymain(); // Display the main cricket menu
        int switch_c;
        cin >> switch_c;

        switch (switch_c) {
            case 1:
                C.Team_display_c(); // Display cricket teams
                break;
            case 2:
                cricketPlayerMenu(Bt, Bo, Ar, Wk); // Navigate to player menu
                break;
            case 3:
                cricketStatsMenu(Bt, Bo, Ar, Wk); // Navigate to stats menu
                break;
            case 4:
                C.Standings_display_c(); // Display cricket standings
                break;
            case 5:
                return; // Return to the main menu
            case 0:
                       false;
                       break;
            default:
                cout << "No such option available! Please Try Again" << endl;
        }
    }
}

int main()
{   
    Player S;
    Cricket C;
vector<Football> F;
vector<Attack> A;
vector<MidField> Mf;
vector<Defence> D;
vector<GoalKeeper> Gk;
vector<Batsman> Bt;
vector<Bowler> Bo;
vector<All_rounder> Ar;
vector<Wicket_keeper> Wk;

    while (true) {
        S.displaymain();
        int num;
        cin >> num;

        switch (num) {
            case 1:
                footballMenu(F, A, Mf, D, Gk);
                break;
            case 2:
                cricketMenu(C, Bt, Bo, Ar, Wk);
                break;
          
            default:
                cout << "No such option available! Please Try Again" << endl;
        }
    }
    return 0;
}

