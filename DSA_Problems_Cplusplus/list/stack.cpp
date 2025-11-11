#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

template <typename t>
class StackNode{
private:
 t data;
 StackNode* next;  // Piont To Below Top Stack 
public:
  StackNode() : data(t()), next(nullptr) {}
  StackNode(t value) : data(value), next(nullptr) {}
  t get_node_value()
  {
    return data;
  }
  StackNode *get_next_node()
  {
    return next;
  }
  void set_node_value(t value)
  {
    data = value;
  }
  void set_next_node(StackNode* node)
  {
    this->next = node;
  }
};

template <typename t>
class Stack{
private:
   StackNode<t>* top;
   int size;
public:
Stack() : top(nullptr) , size(0){}
~Stack() {
        clear_stack();
    }
int get_size(){
 return size;
} 

bool is_empty(){
 if (top == nullptr){
    return true;
 }
 
  return false;

}
t view_top(){
    return top->get_node_value();
}
void push(t user_value){
    StackNode<t>* new_node = new StackNode<t>(user_value);
 if(is_empty()){
    top = new_node;
    
 }
 else{
  new_node->set_next_node(top);
  top = new_node;
 }
 cout << "Successfully Pushed " << user_value<< " To Stack \n";
 size++;
 }

 void pop(){

    if(is_empty()){
        return;
    }
    else{
        StackNode<t>* temp = top;
        top = temp->get_next_node();
        delete temp;
        cout << "Successfully Popped Value From Stack\n";
      size--;
    }
 }
 void displayall(){
  StackNode<t>* new_temp = top; 
  while(new_temp != nullptr){
    cout << " | " << new_temp->get_node_value() << " | " << setw(4) ; 
    new_temp = new_temp->get_next_node();
  }
 }

 void clear_stack(){
      if(is_empty()){
        return;
    }
    else{
      
      while(!is_empty())
     { 
        StackNode<t>* temp = top; 
        top = temp->get_next_node();
        delete temp;
        size--;
      }
      
    }
    cout << "Stack Cleared Sucessfully.\n";
 }

 void save_to_file(string type_name){
    string filename = type_name + "_Stack.txt";
   ofstream datafile(filename);
   if(!datafile.is_open()){
    cout << "Error! Opening File '" << filename << "' For Saving...\n";
    return;
   }
   else{
    StackNode<t>* temp = top;
    
    while(temp!=nullptr){
        datafile << temp->get_node_value() << endl;
        temp = temp -> get_next_node();
    }
    cout << "\nList Data Saved Successfully ......\n";
    datafile.close();
   }
  }
  void load_from_file(string type_name){
      string filename = type_name + "_Stack.txt";
        ifstream loading_data_file(filename);
        if (loading_data_file.is_open()) {
           
            t input_data;
            while(loading_data_file >> input_data ){
              push(input_data);
            }
            loading_data_file.close();
             cout << "\nFile  Data loaded successfully!\n" << endl;
        }
         else {
            cout << "Error: Could not open the file." << endl;
            return;
        
          }
    }
};

template <typename T>
void get_user_input(T &value) {

    cin >> value;  
}

void get_user_input(string &value) {
    cin.ignore();     
    getline(cin, value);
}

void main_menu(){
  cout << "\n===== Stack Menu =====\n";
  cout << "1. Add Element  \n2. Remove Element \n3. Display Elements \n4. View Top Element \n5. View Stack Lenght \n6. Clear List \n0. Exit\n";
  cout << "===========================\n";
  cout << "Enter Your Choice: ";

}

template<typename t>
void operations(string typeName){
 Stack<t> stack;
 int choice;
 t value;
 char loadChoice;
 cout << "Do You Want To Load Saved Stack Data For Type '" << typeName << "'? (y/n): ";
 cin >> loadChoice;
    if (loadChoice == 'y' || loadChoice == 'Y') {
        stack.load_from_file(typeName);
        if (stack.is_empty())
        cout << "Starting With a New Empty Stack Since No Data Was Found.\n";
    } else {
        cout << "Starting With an Empty Stack.\n";
    }
 do{
  main_menu();
  cin >> choice;
  switch (choice)
  {
  case 1:
   cout << "Enter Value To Be Pushed: " ;
   get_user_input(value);
    stack.push(value);
    stack.displayall();

    break;
  
  case 2:
    stack.pop();
    stack.displayall();

    break;
  
  case 3:
    stack.displayall();
    break;
  
  case 4:
    cout << "Top Element : " << stack.view_top()  << endl;
    break;
  
  case 5:
     cout << "Stack Size : " << stack.get_size()  << endl;
    break;
  
  case 6:
    stack.clear_stack();
    break;
  
  case 0:
    cout << "Exiting to main menu.\n";
    stack.save_to_file(typeName);

    return ;
    break;
  
  default:
  cout << "Invalid Choice\n";
    break;
  }

 }
 while(choice!= 0);

}


int main()
{  
 
  int choice;

  cout << "Select the type of Stack you want to work with:\n";
  cout << "1. Integer \n";
  cout << "2. Double\n";
  cout << "3. String \n";
  cout << "4. Char \n";
  cout << "Enter your choice: ";
  cin >> choice;

  switch (choice)
  {
  case 1:
    operations<int>("int");
    break;
  case 2:
    operations<double>("double");
    break;
  case 3:
    operations<string>("String");
    break;
  case 4:
    operations<char>("Char");
    break;
  default:
    cout << "Invalid type choice. Exiting program.\n";
    break;


  }
}