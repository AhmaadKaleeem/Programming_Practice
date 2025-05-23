#include <iostream>
#include <string>
using namespace std;

class Employee {
protected:
    string name;
    double taxRate;
public:
    Employee(string n, double tr) : name(n), taxRate(tr) {}

    string getName() {
        return name;
    }

    virtual double calcSalary() = 0;  

    virtual ~Employee() {} 
};


class SalariedEmp : public Employee {
private:
    double salary;
public:
    SalariedEmp(string n, double tr, double sal)
        : Employee(n, tr), salary(sal) {}

    double calcSalary() override {
        double tax = salary * taxRate;
        return salary - tax;
    }
};

class HourlyEmp : public Employee {
private:
    int hours;
    double hourlyRate;
public:
    HourlyEmp(string n, double tr, int h, double hr)
        : Employee(n, tr), hours(h), hourlyRate(hr) {}

    double calcSalary() override {
        double grossPay = hours * hourlyRate;
        double tax = grossPay * taxRate;
        return grossPay - tax;
    }
};


class CommEmp : public Employee {
private:
    double sales;
    double commRate;
public:
    CommEmp(string n, double tr, double s, double cr)
        : Employee(n, tr), sales(s), commRate(cr) {}

    double calcSalary() override {
        double grossPay = sales * commRate;
        double tax = grossPay * taxRate;
        return grossPay - tax;
    }
};


void generatePayroll(Employee* emp[], int size) {
    cout << "Name\tNet Salary\n\n";
    for (int i = 0; i < size; i++) {
        cout << emp[i]->getName() << '\t'
             << emp[i]->calcSalary() << '\n';
    }
}


int main() {
    Employee* emp[3];

    emp[0] = new SalariedEmp("Aamir", 0.05, 15000);
    emp[1] = new HourlyEmp("Faakhir", 0.06, 160, 50);
    emp[2] = new CommEmp("Fuaad", 0.04, 150000, 0.10);

    generatePayroll(emp, 3);

    // Free memory
    for (int i = 0; i < 3; i++) {
        delete emp[i];
    }

    return 0;
}
