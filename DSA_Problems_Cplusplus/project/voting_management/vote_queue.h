#pragma once
#include"libraries.h"
using namespace std;

class VoteNode{
public:
 
 string c_name;
 string cnic;
 string type;
 VoteNode* next;
 VoteNode();
 VoteNode(const string& cnic, const string& canidate ,const string& type);

};

class VoteQueue{
public:
VoteNode* front;
VoteNode* rear;
VoteQueue();
bool is_empty() const;
void enqueue(const string& cnic, const string& canidate,const string& type);
void dequeue() ;
VoteNode* check_top() const;
};