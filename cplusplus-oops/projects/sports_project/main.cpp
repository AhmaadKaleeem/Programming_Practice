#include <iostream>
#include <string>
#include <limits>      
#include <cctype>      
#include <vector>     
#include <algorithm>  
#include <iomanip>    
#include <fstream>   
#include <sstream>
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

    void displaymain()
    {
        cout << "\t\t\t\t------------------------------------" << "\n";
        cout << "\t\t\t\tWELCOME TO Player ANALYZER PROGRAM" << "\n";
        cout << "\t\t\t\t------------------------------------" << "\n";

        cout << "~ Please Choose the Sports ~ " << "\n";
        cout << "1) Football" << "\n";
        cout << "2) Cricket" << "\n";
        cout << "0) Exit the Program" << "\n";
        cout << "\t\t\t\t------------------------------------" << "\n";
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

    void displaymain()
    {
        cout << "\t\t\t\t-------------- Welcome to Football --------------" << "\n" << "\n";
        cout << "1. View Teams " << "\n";
        cout << "t2. View Players " << "\n";
        cout << "3. Stats " << "\n";
        cout << "4. Standings " << "\n";
        cout << "5. Return to Main Menu" << "\n";
        cout << "0. EXIT" << "\n";
        cout << "\t\t\t\t------------------------------------" << "\n";
        cout << "Enter your choice: ";
    }

    void Team_display_f() //For diplaying the teams of football
    {
        fstream teem_f("team_f.txt");
        string f;
        if (!teem_f)
            cout << "Error while opening the file" << "\n";
        else
        {
            while (!teem_f.eof())
            {
                getline(teem_f, f);
                cout << f << "\n";
            }
        }
    }

    void Standings_display_f() //For displaying the standings of football
    {
        fstream standing_f("standings_f.txt");
        string f;
        if (!standing_f)
            cout << "Error" << "\n";
        else
        {
            while (!standing_f.eof())
            {
                getline(standing_f, f);
                cout << f << "\n";
            }
        }
    }
};
