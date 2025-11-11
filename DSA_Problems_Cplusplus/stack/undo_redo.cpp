#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

template <typename t>
class StackNode{
private:
 t data;
 StackNode* next;  
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
    if (is_empty()) {
        return t();
    }
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

class TextEditor {
private:
    string currentText;    
    Stack<string> undoStack; 
    Stack<string> redoStack; 

public:
    TextEditor() { currentText = ""; }

    void type(string newText) {
        undoStack.push(currentText);   
        while (!redoStack.is_empty())      
            redoStack.pop();
        currentText += newText;
        cout << "Typed: \"" << newText << "\"" << endl;
    }

    void undo() {
        if (undoStack.is_empty()) {
            cout << "Nothing to undo!" << endl;
            return;
        }
        redoStack.push(currentText);    
        currentText = undoStack.view_top();
        undoStack.pop();    
        cout << "Undo done!" << endl;
    }

    void redo() {
        if (redoStack.is_empty()) {
            cout << "Nothing to redo!" << endl;
            return;
        }
        undoStack.push(currentText);    
        currentText = redoStack.view_top();
        redoStack.pop();    
        cout << "Redo done!" << endl;
    }

    void show() {
        cout << "\n--------------------------------" << endl;
        cout << "Current Text: ";
        if (currentText.empty()) cout << "[Empty]" << endl;
        else cout << "\"" << currentText << "\"" << endl;
        cout << "--------------------------------\n" << endl;
    }

    void stats() {
        cout << "\nCharacters: " << currentText.length()
             << " | Undo: " << undoStack.get_size()
             << " | Redo: " << redoStack.get_size() << endl;
    }
};

int main() {
    TextEditor editor;
    string command;

    cout << "\n=============================" << endl;
    cout << " STACK-BASED TEXT EDITOR" << endl;
    cout << "=============================\n" << endl;
    cout << "Commands:\n";
    cout << " type <text> - add text\n";
    cout << " undo        - undo last action\n";
    cout << " redo        - redo undone action\n";
    cout << " show        - display current text\n";
    cout << " stats       - show info\n";
    cout << " exit        - quit editor\n\n";

    while (true) {
        cout << "editor> ";
        getline(cin, command);

        if (command == "exit" || command == "quit") {
            cout << "\nGoodbye!" << endl;
            break;
        }
        else if (command.substr(0, 5) == "type ") {
            string text = command.substr(5);
            editor.type(text);
        }
        else if (command == "undo") editor.undo();
        else if (command == "redo") editor.redo();
        else if (command == "show") editor.show();
        else if (command == "stats") editor.stats();
        else cout << "Unknown command! Try again." << endl;
    }

    return 0;
}