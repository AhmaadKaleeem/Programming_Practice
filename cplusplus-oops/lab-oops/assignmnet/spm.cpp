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
    Staff->setdata(name,age,cnic,designation);
    humans.push_back(staff);
    cout << "Added New Staff Successfully.......\n";
    }
    else if (optionn==2){
    cout << "Enter your Staff Id: ";
    cin.ignore();
    getline(cin,staffid);
    Staff->setdata(name,age,cnic,staffid,designation);
    humans.push_back(staff);
    cout << "Added New Staff Successfully.......\n";
    }
    else if (optionn >2 || optionn <1){
        cout << "Enter Valid Option 1 - 2 ";
    }
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "------------------------------------------------------------------------------------------------\n";  

}
