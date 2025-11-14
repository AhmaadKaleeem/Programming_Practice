#pragma once

#include<iostream>
#include <string>
using namespace std;
class VoteNode{
public:
 
 string c_name;
 string cnic;
 VoteNode* next;
 VoteNode();
 VoteNode(const string& cnic, const string& canidate );

};

class VoteQueue{
public:
VoteNode* front;
VoteNode* rear;
VoteQueue();
bool is_empty() const;
void enqueue(const string& cnic, const string& canidate);
void dequeue() ;
VoteNode* check_top() const;
};