#include <iostream>
 using namespace std;

 struct Node{
 public:
 Node* next;
 Node* prev;
 int data;
 Node(int value){
    data = value;
    next = nullptr;
    prev = nullptr;
 }

 };

 class DoubleLinkedList{
 Node* head;
 Node* tail;
 int size;
 Node* current;

 DoubleLinkedList(){
    size = 0;
    head = tail = current = nullptr;
 }

void push_back(int value ){
Node* new_node = new Node(value);
 if(!head){
   head = tail = new_node;
   current = head;
 }
 else {
    tail -> next = new_node;
    new_node -> prev = tail;
    tail = new_node;
    current = tail;
 }
 }

 DoubleLinkedList copy(DoubleLinkedList& other){
  if (other.size == this->size){
    Node* temp = other.head;
    while(temp){
        push_back(temp->data);
        temp = temp -> next;
    }
  }
  else if (other.size != this->size){
    
  }

 }




 };