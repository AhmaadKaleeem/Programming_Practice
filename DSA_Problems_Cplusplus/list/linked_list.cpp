// Linked List Dynamically
#include  <iostream>
#include <iomanip>
#include <vector>
using namespace std;
template <typename t>
class Node{
    private:
    t data;
    Node<t>* next ;
   public:
    Node() : data(t()) , next (nullptr){}
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

 Node<t>* current;
 Node<t>* head;
 int size;

public:
 LinkedList() {
    head = current = nullptr; 
    size = 0;
 }
 
 ~ LinkedList(){
  clear_list();
  
 }
 
 void insert_at_end(t user_value){

    Node<t>* new_node = new Node<t> (user_value);  
  if(head==nullptr){

    current = head = new_node;
   
  }
  else {
    current -> set_next_node(new_node);
    current = new_node;

  }
   size++;
  cout << "Successfully inserted " << user_value << " at end of list. \n";

 }

 void insert_at_start(t user_value){
    Node<t>* new_node = new Node<t> (user_value);  
  if(head==nullptr){
    current = head = new_node;
    
  }
  else {
    new_node ->set_next_node (head);
     head = new_node;
  
  }
    size++;
  cout << "Successfully inserted " << user_value << " at start of list. \n";

 }
 
 
 void insert(t user_value, int index){
   if (index > size  || index < 0){
    cout << "Please insert at valid index number \n";
    return; 
  }
  else{
   
    if (index == 0) {
        insert_at_start(user_value);
        return;
    }
    else if (index == size) {
        insert_at_end(user_value);
        return;
    }
    else {
    Node<t>* new_node = new Node<t>(user_value);
    Node<t>* temp = head;
    Node<t>* prev = nullptr;
    for(int i = 0 ; i<index;i++){
      prev = temp;
      temp = temp->get_next_node();
    }
    new_node -> set_next_node(temp);
    prev-> set_next_node(new_node);
    size++;
    cout << "Successfully inserted " << user_value << " at " << index <<"th index of list. \n";
    }
   
  }

 }
 
 
 int get_lenght(){
  return size;
}

 void remove_at_start(){
  if(head == nullptr){
    cout << "List empty! Cannot remove from list \n";
  }
   else if(head->get_next_node() == nullptr){
    delete head;
    head = nullptr;
    current = nullptr;
    size--;
   cout << "Successfully, Removed value from start of list. \n";
  }
  else{
  Node<t>* temp = head ;
  head = head->get_next_node();
  delete temp;
  size--;
  cout << "Successfully, Removed value from start of list. \n";
}
}
 
void remove_at_end(){
  if(head == nullptr){
    cout << "List empty! Cannot remove from list \n";
  }
  else if(head->get_next_node() == nullptr){
    delete head;
    head = nullptr;
    current = nullptr;
    size--;
  cout << "Successfully, Removed value from end of list. \n";

  }
  else{
  Node<t>* temp = head ;
   Node<t>* prev = nullptr ;
  while(temp->get_next_node() != nullptr){
    prev = temp;
  temp = temp->get_next_node();
 }
 prev->set_next_node(nullptr);
 current = prev;
 delete temp;
 size --;
   cout << "Successfully, Removed value from end of list. \n";

}
}

 void remove_value(t user_value){
  Node<t>* temp = head;
  Node<t>* prev = nullptr;
  while(temp!= nullptr  &&  temp->get_node_value()!= user_value){
     prev = temp;
    temp = temp->get_next_node();
  }
  
  if(temp == nullptr){
    cout << "Value " << user_value <<" not found ! Cannot remove from list \n";
    return;
  }
  else if(temp == head){
    head = head->get_next_node();
  }
  else{
    prev->set_next_node(temp->get_next_node());
  }

  if (temp == current) {
        current = prev;
    }
  
    delete temp;
    size--;
    cout << "Successfully removed value " << user_value << " from the list.\n";
 }

 void remove_at(int index){
  if (size == 0) {
        cout << "List is empty. Cannot remove.\n";
        return;
    }
   else if (index < 0 || index >= size){
    cout << "No " << index << "th value in the list \n";
       return;
  }
  else if (index == 0){
  remove_at_start();
     return;
 }
 else {
   Node<t>* temp = head;
  Node<t>* prev = nullptr;
  for(int i = 0;i < index; i++){
     prev = temp;
    temp = temp->get_next_node();
  }

    prev->set_next_node(temp->get_next_node());
     if (temp == current) {
        current = prev;
    }
    delete temp;
    size--;
    cout << "Successfully removed value at index  " << index << " from the list.\n";
 
 }
}

 void find(t user_value){
 vector<int> indexes ;
 Node<t>* temp = head;
 for(int i=0;i < size;i++){
  if(temp->get_node_value() == user_value)
   { indexes.push_back(i);
  }
  temp= temp->get_next_node();
 }
 if(indexes.empty()) {cout << "Cannot find " << user_value << " in list.\n";}
 else{
  int size = indexes.size();
  cout << "Element " << user_value << " found at index : ";
 while(size != 0){
  cout << indexes[size-1] << setw(2);
 size--; 
}
cout << "\n";
 }
 }

 void display(){
  Node<t>* temp = head;
  cout << "-- List Values -- \n";
  while(temp != nullptr){
    cout << "| "<< temp->get_node_value() << " |"<< setw(10) ;
    temp = temp->get_next_node();
  }
  cout << "\n";

}

 void clear_list(){
  Node<t>* current_node = head;
   Node<t>* next_node = nullptr;
   while(current_node != nullptr){
    next_node = current_node->get_next_node();
    delete current_node;
    current_node = next_node;
   }
   current = head = nullptr; size=0;
  cout << "Successfully Cleared List.\n";
 }

 void get_element_at(int index){
  if (index >= size || index < 0 ){
    cout <<  index << " is not a valid index in list.\n";
    return;
  }
 Node<t>* temp = head;
 for(int i=0;i < index;i++){
  temp= temp->get_next_node();
 }
 cout << "Value at index " << index << " is : " << temp->get_node_value() <<endl;
 }
};

int main(){
    LinkedList<int> L1;
    LinkedList<string> L2;
    L1.insert_at_end(50);
    L1.insert_at_end(20);
    L1.insert_at_start(5000);
    L1.insert_at_start(2000);                            
    L2.insert_at_end("500");
    L2.insert_at_end("Ahmad");
    cout << L1.get_lenght() << endl;
    L1.display();
    L1.remove_at_start();
    L1.remove_at_end();
    L1.insert_at_end(5644);
    L1.display();
    L1.remove_value(25);
     L1.insert_at_start(25);
    L1.insert_at_start(2525);
    L1.remove_value(5644);
     L1.insert_at_start(2525);
     L1.insert(25,3);
      L1.insert_at_start(2525);
       L2.clear_list();
    L1.display();
     L1.remove_at(1);
     L1.find(1);
  L1.find(25);
    L1.display();
   
    
}