#include  <iostream>
using namespace std;
class Node{
    public:
    int data;
    Node* next ;
    Node() {data = 0 ; next = nullptr;}
    Node(int value ) : data(value) , next (nullptr){}
    
};
int main(){
Node* Node1 = new Node();
Node* Node2 = new Node(20);
Node1->data  = 10;
cout << Node1->data ;
cout << Node2->data;
}