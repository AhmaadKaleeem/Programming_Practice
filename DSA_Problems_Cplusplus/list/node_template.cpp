#include  <iostream>
using namespace std;
template <typename t>
struct Node{
    public:
    t data;
    Node<t>* next ;
   
    Node(t value ) : data(value) , next (nullptr){}
    
};
int main(){
Node<int>* Node1 = new Node(10);
Node<int>* Node2 = new Node(20);
Node<string>* Node1s = new Node<string>("Ahmad");
Node<string>* Node2s = new Node<string>("Kaleem");
Node1->data  = 15;
cout << Node1->data << endl;
cout << Node2->data << endl;

Node1s->data  = "Updated - Ahmad";
cout << Node1s->data << endl;
cout << Node2s->data << endl;
}