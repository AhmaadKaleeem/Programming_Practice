#pragma once
#include <iostream>
using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    Person();
    Person(string name = "", int age = 0);
    virtual void display() const = 0; 
};
