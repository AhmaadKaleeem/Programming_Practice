// Linked List Dynamically
#include  <iostream>
using namespace std;
template <typename t>
class Node{
    private:
    t data;
    Node<t>* next ;
   public:
    Node(t value ) : data(value) , next (nullptr){}
  t get_node_value(){
    return data;
  }
   Node<t>* get_next_node(){
    return next;
  }
  void set_node_value(t value){
    data = value;
  }
  void set_next_node(Node<t>*  node) 
  {
      this -> next = node; 
  }
 
};

template <typename t>
class LinkedList{
private:
 static const int max_size = 10;

 Node<t>* current;
 Node<t>* head;
 int size;

public:
 LinkedList() {
    head = current = nullptr; 
    size = 0;
 }
 void insert_at_end(t user_value){
 if (size < max_size){
    Node<t>* new_node = new Node<t> (user_value);  
  if(head==nullptr){

    current = head = new_node;
    size++;
  }
  else {
    current -> set_next_node(new_node);
    current = new_node;
    size++;
  }

 }
 else
 {
  cout << "List can have maximum " << max_size << " elements and list is full. \n" ;
 }
 }




};

int main(){
    LinkedList<int> L1;
    LinkedList<string> L2;
    L1.insert_at_end(50);
    L1.insert_at_end(20);
    L2.insert_at_end("500");
    L2.insert_at_end("Ahmad");
   
    
}