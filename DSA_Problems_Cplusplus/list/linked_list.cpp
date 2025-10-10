// Linked List Dynamically
#include  <iostream>
#include <iomanip>
#include <vector>
#include <limits> 
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

 LinkedList<t> (const LinkedList<t>& other){
    head = current = nullptr;
    size = 0;
    
    Node<t>* temp = other.head;
    Node<t>* temp_current = nullptr;
    while(temp!=nullptr){

this->insert_at_end(temp->get_node_value());
   temp = temp->get_next_node();

    }
 }
 
 LinkedList<t>& operator=(const LinkedList<t>& other){
 if (this == &other){
  return *this;
 }
 this->clear_list();
 head = current = nullptr;
    size = 0;
    
    Node<t>* temp = other.head;
    Node<t>* temp_current = nullptr;
    while(temp!=nullptr){
     this->insert_at_end(temp->get_node_value());
   temp = temp->get_next_node();

    }
    return *this;

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
 
 
 int get_length(){
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

 void update(int index, t user_value){
  if (index >= size || index < 0 ){
    cout <<  index << " is not a valid index in list.\n";
    return;
  }
 Node<t>* temp = head;
 for(int i=0;i < index;i++){
  temp= temp->get_next_node();
 }
 t prev_value = temp->get_node_value();
 temp->set_node_value(user_value);
 cout << "Updated Value " << prev_value << "at index " << index << " with  " << temp->get_node_value() <<endl;
 }
 

};


void main_menu() {
    cout << "\n===== LinkedList Menu =====\n";
    cout << "1.  Insert at End\n";
    cout << "2.  Insert at Start\n";
    cout << "3.  Insert at Index\n";
    cout << "4.  Remove from Start\n";
    cout << "5.  Remove from End\n";
    cout << "6.  Remove by Value\n";
    cout << "7.  Remove at Index\n";
    cout << "8.  Find a Value\n";
    cout << "9.  Get Element at Index\n";
    cout << "10. Update Element at Index\n";
    cout << "11. Display List\n";
    cout << "12. Get List Length\n";
    cout << "13. Clear List\n";
    cout << "0.  Exit\n";
    cout << "===========================\n";
    cout << "Enter your choice: ";
}

template <typename T>
void operations_on_list() {
    LinkedList<T> list;
    int choice;
    T value;
    int index;

    do {
        main_menu();
        cin >> choice;

        // Clear input buffer in case of non-integer input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1; 
        }

        switch (choice) {
            case 1:
                cout << "Enter value to insert at end: ";
                cin >> value;
                list.insert_at_end(value);
                list.display();
                break;
            case 2:
                cout << "Enter value to insert at start: ";
                cin >> value;
                list.insert_at_start(value);
                list.display();
                break;
            case 3:
                cout << "Enter value: ";
                cin >> value;
                cout << "Enter index: ";
                cin >> index;
                list.insert(value, index);
                list.display();
                break;
            case 4:
                list.remove_at_start();
                cout << "Removed from start.\n";
                list.display();
                break;
            case 5:
                list.remove_at_end();
                cout << "Removed from end.\n";
                list.display();
                break;
            case 6:
                cout << "Enter value to remove: ";
                cin >> value;
                list.remove_value(value);
                list.display();
                break;
            case 7:
                cout << "Enter index to remove: ";
                cin >> index;
                list.remove_at(index);
                list.display();
                break;
            case 8:
                cout << "Enter value to find: ";
                cin >> value;
                list.find(value);
                break;

            case 9:
                cout << "Enter index to get element: ";
                cin >> index;
                list.get_element_at(index);
                break;
            case 10:
                cout << "Enter index to update: ";
                cin >> index;
                cout << "Enter new value: ";
                cin >> value;
                list.update(index, value);
                list.display();
                break;
            case 11:
                list.display();
                break;
            case 12:
                cout << "Current list length: " << list.get_length() << endl;
                break;
            case 13:
                list.clear_list();
                cout << "List cleared.\n";
                list.display();
                break;
            case 0:
                cout << "Exiting to main menu.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void operations_on_string_list() {
    LinkedList<string> list;
    int choice;
    string value;
    int index;

    do {
        main_menu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1; 
        }

        if (choice == 1 || choice == 2 || choice == 3 || choice == 6 || choice == 8 || choice == 10) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1:
                cout << "Enter value to insert at end: ";
                getline(cin, value); 
                list.insert_at_end(value);
                list.display();
                break;
            case 2:
                cout << "Enter value to insert at start: ";
                getline(cin, value); 
                list.insert_at_start(value);
                list.display();
                break;
            case 3:
                cout << "Enter value: ";
                getline(cin, value); 
                cout << "Enter index: ";
                cin >> index;
                list.insert(value, index);
                list.display();
                break;
             case 4:
                list.remove_at_start();
                cout << "Removed from start.\n";
                list.display();
                break;
            case 5:
                list.remove_at_end();
                cout << "Removed from end.\n";
                list.display();
                break;
            case 6:
                cout << "Enter value to remove: ";
                getline(cin, value); 
                list.remove_value(value);
                list.display();
                break;
            case 7:
                cout << "Enter index to remove: ";
                cin >> index;
                list.remove_at(index);
                list.display();
                break;
            case 8:
                cout << "Enter value to find: ";
                getline(cin, value); 
                list.find(value);
                break;
            
            case 9:
                cout << "Enter index to get element: ";
                cin >> index;
                list.get_element_at(index);
                break;
            case 10:
                cout << "Enter index to update: ";
                cin >> index;
                cout << "Enter new value: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, value); 
                list.update(index, value);
                list.display();
                break;
          
            case 11:
                list.display();
                break;
            case 12:
                cout << "Current list length: " << list.get_length() << endl;
                break;
            case 13:
                list.clear_list();
                cout << "List cleared.\n";
                list.display();
                break;
            case 0:
                cout << "Exiting to main menu.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

int main(){
    LinkedList<int> list;
    LinkedList<string> list_string;
    LinkedList<double> list_double;
     int choice;
     

    cout << "Select the type of LinkedList you want to work with:\n";
    cout << "1. Integer \n";
    cout << "2. Double\n";
    cout << "3. String \n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            operations_on_list<int>();
            break;
        case 2:
            operations_on_list<double>();
            break;
        case 3:
            operations_on_string_list();
            break;
        default:
            cout << "Invalid type choice. Exiting program.\n";
            break;
    }

  

}