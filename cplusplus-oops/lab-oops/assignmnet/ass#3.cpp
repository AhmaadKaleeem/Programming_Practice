
#include <iostream>
#include <vector>
#include <string>
using namespace std;
// Base Class with pure virtual functions
class Person{
private:
string name;
int age;
long long cnic;
public:
Person(){
    name = "default";
    age = 0;
    cnic = 0;
}
// Making class Abstract through pure virtual function
 virtual string display_role() = 0;
 virtual void displaydata(){
    display_info();
 };
virtual ~Person() {}  
protected :
void set_basic_info(string name,int age,long long cnic) {
     this -> name = name;
     this -> age = age;
     this -> cnic = cnic;
}

void display_info(){
    cout << "--------------------------------- Personal Information --------------------------------------------- \n ";
    cout << "Name: " << name << ". \n";
    cout << "Age: "  << age  << ".\n";
    cout << "Cnic: " << cnic << ".\n"; 
}

};
// Derived Class inheriting publicly frpm person making member function of person public in derived class 
class Student : public Person {
private:
    string studentid;
    string dept;
public:
   Student(){
    studentid = "Not Specified ";
    dept = "Not Specified";
   }
   // Function overloading
   void setdata(string name, int age,long long cnic,string dept){
        set_basic_info(name,age,cnic);
        this -> dept = dept; 
    }

    void setdata(string name,int age,long long cnic,string studentid , string dept){
        set_basic_info(name,age,cnic);
        this-> studentid = studentid;
        this -> dept = dept; 
    }
    
// Function Oveeriding
   void displaydata() override{
    display_info();
    cout << "Student Id: " << studentid << ".\n";
    cout << "Department: " << dept << ".\n";
   }
    
    string display_role() override {
    return "I am a Student";
    }
    virtual ~Student() {};
                
};

// Derived Class inheriting protectedly frpm person making member function of person protected in derived class 

class Teacher : protected Person {
private:
 string emp_id;
 string subject;
 int salary;
 public:
    Teacher(){
      salary = 0;
      }
    void setdata(string name, int age,long long cnic,string emp_id ,string subject) {
        set_basic_info(name,age,cnic);
        this -> subject = subject;
        this-> emp_id = emp_id;
    }
    void setdata(string name, int age,long long cnic,string emp_id ,string subject,int salary) {
        set_basic_info(name,age,cnic);
        this-> emp_id = emp_id;
        this -> subject = subject;
        this -> salary = salary;
    }
    
   void displaydata() override{
    display_info();
    cout << "Employee Id: " << emp_id << ".\n";
    cout << "Subject: " << subject << ".\n";
    cout << "Salary: " << salary << ".\n";   
}
    
    string display_role() override {
    return "I am a Professor";
    }
    // Using this ptr to expose class type and using static cast
    Person* get_type() {
        return static_cast<Person*>(this);
    }

 virtual ~Teacher(){};

};
// Derived Class inheriting privately frpm person making member function of person private in derived class 

class Staff : private Person {
private:
    string staffid;
    string designation;
public:
   Staff(){
    staffid = "Not Specified";
   }
   void setdata(string name, int age,long long cnic,string designation) {
        set_basic_info(name,age,cnic);
        this-> designation = designation;
    }
   
  
    void setdata(string name,int age,long long cnic,string staffid , string designation){
        set_basic_info(name,age,cnic);
        this-> staffid = staffid;
        this -> designation = designation; 
    }
    

   void displaydata() override{
    display_info();
    cout << "Staff Id: " << staffid << ".\n";
    cout << "Designation: " << designation << ".\n";
   }
    
    string display_role() override {
    return  "I am a Staff Member";
    }
    virtual ~Staff() {};

      Person* get_type() {
        return static_cast<Person*>(this);
    }
};
// Using Pionter vector of base class refering to derived class in order for polymorphism
void Add_student(vector<Person*>& humans){
    string name, dept,studentid;
    int age,optionn ; long long cnic;
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "Enter your Name: ";
    cin.ignore();
    getline(cin,name);
    cout << "Enter the Age: ";
    cin  >> age;
    cout << "Enter your CNIC: ";
    cin >> cnic;
    cout << "Enter your Department: ";
    cin.ignore();
    getline(cin,dept);
    cout << "Thanks for Entering Your Information. Proceeding Next...\n";
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "1.New Student with No Student Id\n" << "2.Old/New Student with Student Id\n";
    cout << "Enter your Student Type: ";
    cin >> optionn;
    Student* student = new Student();
    if(optionn==1){
    student->setdata(name,age,cnic,dept);
    humans.push_back(student);
    cout << "Added New Student Successfully.......\n";
    }
    else if (optionn==2){
    cout << "Enter your Student Id: ";
    cin.ignore();
    getline(cin,studentid);
    student->setdata(name,age,cnic,studentid,dept);
    humans.push_back(student);
    cout << "Added New Student Successfully.......\n";
    }
    else if (optionn >2 || optionn <1){
        cout << "Enter Valid Option 1 - 2 ";
    }
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "------------------------------------------------------------------------------------------------\n";  

}

void Add_Teacher(vector<Person*>& humans){
    string name,empid,subject;
    int age,optionn ,salary; long long cnic;
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "Enter your Name: ";
    cin.ignore();
    getline(cin,name);
    cout << "Enter the Age: ";
    cin  >> age;
    cout << "Enter your CNIC: ";
    cin >> cnic;
    cout << "Enter your Subject: ";
    cin.ignore();
    getline(cin,subject);
    cout << "Enter your Employee Id: ";
    cin >> empid;
    cout << "Thanks for Entering Your Information. Proceeding Next...\n";
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "1.Proceed without Teacher Salary\n" << "2.Proceed with Teacher Salary\n";
    cout << "Enter the option: ";
    cin >> optionn;
    Teacher* teacher = new Teacher();
    if(optionn==1){
    teacher->setdata(name,age,cnic,empid,subject);
    // Error due to protected inheritance because of protected can be used inside base class and derived and cannot be accessed outside class
    humans.push_back(teacher->get_type());
    cout << "Added New Teacher Successfully.......\n";
    }
    else if (optionn==2){
    cout << "Enter your Salary: ";
    cin >> salary;
    teacher->setdata(name,age,cnic,empid,subject,salary);
    // Error Reason on line 204
    humans.push_back(teacher->get_type());
    cout << "Added New Teacher Successfully.......\n";
    }
    else if (optionn >2 || optionn <1){
        cout << "Enter Valid Option 1 - 2 ";
    }
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "------------------------------------------------------------------------------------------------\n";  

}

void Add_Staff(vector<Person*>& humans){
    string name, designation,staffid;
    int age,optionn ; long long cnic;
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "Enter your Name: ";
    cin.ignore();
    getline(cin,name);
    cout << "Enter the Age: ";
    cin  >> age;
    cout << "Enter your CNIC: ";
    cin >> cnic;
    cout << "Enter your Designation: ";
    cin.ignore();
    getline(cin,designation);
    cout << "Thanks for Entering Your Information. Proceeding Next...\n";
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "1.New Staff with No Staff Id\n" << "2.Old/New Staff with Staff Id\n";
    cout << "Enter your Staff Type: ";
    cin >> optionn;
    Staff* staff = new Staff();
    if(optionn==1){
    staff->setdata(name,age,cnic,designation);
        // Error due to private inheritance because of private can be used inside base class cannot be accessed outside class
    humans.push_back(staff->get_type());
    cout << "Added New Staff Successfully.......\n";
    }
    else if (optionn==2){
    cout << "Enter your Staff Id: ";
    cin.ignore();
    getline(cin,staffid);
    staff->setdata(name,age,cnic,staffid,designation);
    // Error on 257
    humans.push_back(staff->get_type());
    cout << "Added New Staff Successfully.......\n";
    }
    else if (optionn >2 || optionn <1){
        cout << "Enter Valid Option 1 - 2 ";
    }
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "------------------------------------------------------------------------------------------------\n";  

}

void Display_Students(const vector<Person*>& humans) {
    cout << "------------------ List of Students ------------------\n";
    for (const auto& p : humans) {
        if (p->display_role() == "I am a Student") {
            p->displaydata();
            cout << endl;
            

        }
    }
  cout << "------------------------------------------------------------------------------------------------\n";  
  cout << "------------------------------------------------------------------------------------------------\n";
}
void Display_Teachers(const vector<Person*>& humans) {
    cout << "------------------ List of Teachers ------------------\n";
    for (const auto& p : humans) {
        if (p->display_role() == "I am a Professor") {
            p->displaydata();
            cout << endl;
          

        }
    }
   cout << "------------------------------------------------------------------------------------------------\n";  
   cout << "------------------------------------------------------------------------------------------------\n"; 
}
void Display_Staff(const vector<Person*>& humans) {
    cout << "------------------ List of Staff Members ------------------\n";
    for (const auto& p : humans) {
        if (p->display_role() == "I am a Staff Member") {
            p->displaydata();
            cout << endl;
        }
    }
     cout << "------------------------------------------------------------------------------------------------\n";  
     cout << "------------------------------------------------------------------------------------------------\n";
}


int main(){
    vector <Person*> human;
    int option;
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "----------------------- Welcome to Air University Management System ----------------------------\n";
    do {
        cout << "1. Add Student\n" << "2. Add Faculity\n" << "3. Add Staff Member\n";
        cout << "4. Display Students\n" << "5. Display Faculity\n" << "6. Display Staff Members\n" << "7.Exit\n";
        cout << "Enter the option to proceed : ";
        cin >>option;
        if (option == 1) Add_student(human);
        if (option == 2) Add_Teacher(human);
        if (option == 3) Add_Staff(human);
        if (option == 4) Display_Students(human);
        if (option == 5) Display_Teachers(human);
        if (option == 6) Display_Staff(human);

        if (option == 7){
            for (Person* p : human) 
            delete p; // Virtual destructor: avoids memory leaks
            break;
        }
        else if (option > 7 || option < 1) {
            cout << "Enter valid argument between 1-7\n";
            break;
        }
    } while(option!=7);
}