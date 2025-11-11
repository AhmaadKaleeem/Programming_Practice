#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>     
#include <cctype>     
#include <cmath>      

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
    if (is_empty()) {
        cout << "Error: Attempting to view top of empty stack." << endl;
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
            Stack<t> temp_stack;
            while(loading_data_file >> input_data ){
              temp_stack.push(input_data);
            }
            loading_data_file.close();

            while(!temp_stack.is_empty()){
                this->push(temp_stack.view_top());
                temp_stack.pop();
            }

             cout << "\nFile  Data loaded successfully!\n" << endl;
        }
         else {
            cout << "Error: Could not open the file." << endl;
            return;
        
          }
    }
};

class ExpressionAnalyzer {
private:
    bool isOperator(char ch) {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
    }

    int precedence(char op) {
        if (op == '^') return 3;
        if (op == '*' || op == '/') return 2;
        if (op == '+' || op == '-') return 1;
        return 0;
    }

    bool isRightAssociative(char op) { return (op == '^'); }

public:
    bool validateParentheses(const string& exp) {
        Stack<char> brackets;
        for (char ch : exp) {
            if (ch == '(' || ch == '{' || ch == '[')
                brackets.push(ch);
            else if (ch == ')' || ch == '}' || ch == ']') {
                if (brackets.is_empty()) return false;
                
                char top = brackets.view_top();
                brackets.pop();

                if ((ch == ')' && top != '(') ||
                    (ch == '}' && top != '{') ||
                    (ch == ']' && top != '['))
                    return false;
            }
        }
        return brackets.is_empty();
    }

    // --> Step 2: Convert infix to postfix
    string infixToPostfix(const string& infix) {
        Stack<char> ops;
        string postfix = "";

        for (int i = 0; i < infix.length(); i++) {
            char ch = infix[i];
            if (ch == ' ') continue;

            if (isdigit(ch)) {
                while (i < infix.length() && isdigit(infix[i]))
                    postfix += infix[i++];
                postfix += ' ';
                i--;
            }
            else if (ch == '(') ops.push(ch);
            else if (ch == ')') {
            
                while (!ops.is_empty() && ops.view_top() != '(') {
           
                    postfix += ops.view_top();
                    ops.pop();
                    postfix += ' ';
                }
              
                if (!ops.is_empty()) ops.pop(); 
            }
            else if (isOperator(ch)) {
                while (!ops.is_empty() && ops.view_top() != '(' &&
                    ((!isRightAssociative(ch) && precedence(ch) <= precedence(ops.view_top())) ||
                     (isRightAssociative(ch) && precedence(ch) < precedence(ops.view_top())))) { // Corrected logic for right-associativity
                    postfix += ops.view_top();
                    ops.pop();
                    postfix += ' ';
                }
                ops.push(ch);
            }
        }
        while (!ops.is_empty()) {
            postfix += ops.view_top();
            ops.pop();
            postfix += ' ';
        }
        return postfix;
    }

    double evaluatePostfix(const string& postfix) {
        Stack<double> values;

        for (int i = 0; i < postfix.length(); i++) {
            char ch = postfix[i];
            if (ch == ' ') continue;

            if (isdigit(ch)) {
                double num = 0;
                while (i < postfix.length() && isdigit(postfix[i]))
                    num = num * 10 + (postfix[i++] - '0');
                i--;
                values.push(num);
            }
            else if (isOperator(ch)) {
                if (values.get_size() < 2) {
                    cout << "Error: Invalid expression!" << endl;
                    return 0;
                }
                double b = values.view_top();
                values.pop();
                double a = values.view_top();
                values.pop();
                
                double res = 0;
                switch (ch) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/':
                    if (b == 0) { cout << "Error: Division by zero!" << endl; return 0; }
                    res = a / b; break;
                case '^': res = pow(a, b); break;
                }
                values.push(res);
            }
        }
        return values.is_empty() ? 0 : values.view_top();
    }

    void analyze(const string& expression) {
        cout << "\nExpression: " << expression << endl;

        if (!validateParentheses(expression)) {
            cout << " Invalid Expression (Unbalanced Brackets)" << endl;
            return;
        }
        cout << "Parentheses are Balanced" << endl;

        string postfix = infixToPostfix(expression);
        cout << "Postfix Expression: " << postfix << endl;

        double result = evaluatePostfix(postfix);
        cout << "Final Result: " << result << "\n\n";
    }
};


int main() {
    ExpressionAnalyzer analyzer;
    cout << " SIMPLE EXPRESSION ANALYZER \n\n";

    analyzer.analyze("(3 + 5) * (2 - 4)");
    analyzer.analyze("10 + 2 * 6");
    analyzer.analyze("100 / (5 * 2)");
    analyzer.analyze("2 ^ 3 + 4");
    analyzer.analyze("(3 + 5) * (2 - 4");  // invalid

    string input;
    cout << "\nEnter your own expressions (type 'exit' to quit):" << endl;
    while (true) {
        cout << "\n> ";
        getline(cin, input); // Use getline for expressions
        if (input == "exit" || input == "quit") break;
        if (!input.empty()) analyzer.analyze(input);
    }

    cout << "\nGoodbye!" << endl;
    return 0;
}