
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Student {
int roll_number;
string name;
double gpa;

Student(int roll, string n, double g) : roll_number(roll), name(n), gpa(g) {}
Student() : roll_number(0), name(""), gpa(0.0) {}

};

struct Node {
Student student;
Node* next;
Node(Student s) : student(s), next(nullptr) {}
};

class StudentLinkedList {
private:
Node* head;
int size;

public:
StudentLinkedList() : head(nullptr), size(0) {}
~StudentLinkedList() {
    clear_list();
}

void insert_at_beginning(Student student) {
    Node* new_node = new Node(student);
    new_node->next = head;
    head = new_node;
    size++;
    cout << "Student " << student.name << " added at beginning" << endl;
}

void insert_at_end(Student student) {
    Node* new_node = new Node(student);
    if (head == nullptr) {
        head = new_node;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }
    size++;
    cout << "Student " << student.name << " added at end" << endl;
}

void insert_at_position(Student student, int position) {
    if (position < 0 || position > size) {
        cout << "Invalid position! Valid range: 0 to " << size << endl;
        return;
    }
    
    if (position == 0) {
        insert_at_beginning(student);
        return;
    }
    
    Node* new_node = new Node(student);
    Node* current = head;
    
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    size++;
    cout << "Student " << student.name << " inserted at position " << position << endl;
}

bool delete_by_roll_number(int roll_number) {
    if (head == nullptr) {
        cout << "List is empty!" << endl;
        return false;
    }
    
    if (head->student.roll_number == roll_number) {
        Node* temp = head;
        cout << "Deleted student: " << head->student.name << endl;
        head = head->next;
        delete temp;
        size--;
        return true;
    }
    
    Node* current = head;
    while (current->next != nullptr) {
        if (current->next->student.roll_number == roll_number) {
            Node* temp = current->next;
            cout << "Deleted student: " << temp->student.name << endl;
            current->next = current->next->next;
            delete temp;
            size--;
            return true;
        }
        current = current->next;
    }
    
    cout << "Student with roll number " << roll_number << " not found!" << endl;
    return false;
}

Student* search_by_roll_number(int roll_number) {
    Node* current = head;
    int position = 0;
    
    while (current != nullptr) {
        if (current->student.roll_number == roll_number) {
            cout << "Found student at position " << position << ": ";
            cout << "Roll: " << current->student.roll_number 
                 << ", Name: " << current->student.name 
                 << ", GPA: " << fixed << setprecision(2) << current->student.gpa << endl;
            return &(current->student);
        }
        current = current->next;
        position++;
    }
    
    cout << "Student with roll number " << roll_number << " not found!" << endl;
    return nullptr;
}

bool update_student(int roll_number, string new_name = "", double new_gpa = -1) {
    Student* student = search_by_roll_number(roll_number);
    
    if (student != nullptr) {
        if (!new_name.empty()) {
            string old_name = student->name;
            student->name = new_name;
            cout << "Updated name from " << old_name << " to " << new_name << endl;
        }
        if (new_gpa >= 0.0) {
            double old_gpa = student->gpa;
            student->gpa = new_gpa;
            cout << "Updated GPA from " << fixed << setprecision(2) 
                 << old_gpa << " to " << new_gpa << endl;
        }
        return true;
    }
    return false;
}

void display_all() {
    if (head == nullptr) {
        cout << "List is empty!" << endl;
        return;
    }
    
    cout << "\n--- All Students ---" << endl;
    Node* current = head;
    int position = 0;
    
    while (current != nullptr) {
        cout << "Position " << position << ": ";
        cout << "Roll: " << current->student.roll_number 
             << ", Name: " << current->student.name 
             << ", GPA: " << fixed << setprecision(2) << current->student.gpa << endl;
        current = current->next;
        position++;
    }
    cout << "Total students: " << size << "\n" << endl;
}

int get_size() {
    return size;
}

bool is_empty() {
    return head == nullptr;
}

Student* find_highest_gpa() {
    if (head == nullptr) {
        cout << "List is empty!" << endl;
        return nullptr;
    }
    
    Node* current = head;
    Student* highest_student = &(head->student);
    
    while (current != nullptr) {
        if (current->student.gpa > highest_student->gpa) {
            highest_student = &(current->student);
        }
        current = current->next;
    }
    
    cout << "Student with highest GPA: " << highest_student->name 
         << " (GPA: " << fixed << setprecision(2) << highest_student->gpa << ")" << endl;
    return highest_student;
}

Student* find_lowest_gpa() {
    if (head == nullptr) {
        cout << "List is empty!" << endl;
        return nullptr;
    }
    
    Node* current = head;
    Student* lowest_student = &(head->student);
    
    while (current != nullptr) {
        if (current->student.gpa < lowest_student->gpa) {
            lowest_student = &(current->student);
        }
        current = current->next;
    }
    
    cout << "Student with lowest GPA: " << lowest_student->name 
         << " (GPA: " << fixed << setprecision(2) << lowest_student->gpa << ")" << endl;
    return lowest_student;
}

void clear_list() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    size = 0;
    cout << "List cleared!" << endl;
}

void search_by_name(string name) {
    Node* current = head;
    int position = 0;
    bool found = false;
    
    cout << "Searching for students with name containing: " << name << endl;
    while (current != nullptr) {
        if (current->student.name.find(name) != string::npos) {
            cout << "Found at position " << position << ": ";
            cout << "Roll: " << current->student.roll_number 
                 << ", Name: " << current->student.name 
                 << ", GPA: " << fixed << setprecision(2) << current->student.gpa << endl;
            found = true;
        }
        current = current->next;
        position++;
    }
    
    if (!found) {
        cout << "No student found with name containing: " << name << endl;
    }
}

};

int main() {
StudentLinkedList student_list;


cout << "=== Student Linked List Demo ===" << endl << endl;

Student s1(101, "Ahmad Khan", 3.8);
Student s2(102, "Sara Ahmed", 3.9);
Student s3(103, "Hassan Ali", 3.5);
Student s4(104, "Fatima Sheikh", 4.0);
Student s5(105, "Omar Malik", 3.2);

student_list.insert_at_beginning(s1);
student_list.insert_at_end(s2);
student_list.insert_at_beginning(s3);
student_list.insert_at_position(s4, 1);
student_list.insert_at_end(s5);

cout << "\nInitial list:" << endl;
student_list.display_all();

cout << "=== Search Operations ===" << endl;
student_list.search_by_roll_number(102);
student_list.search_by_roll_number(999);
student_list.search_by_name("Ahmad");

cout << "\n=== Update Operations ===" << endl;
student_list.update_student(101, "Ahmad Kaleem", 3.95);
student_list.update_student(103, "", 3.7);

cout << "\nAfter updates:" << endl;
student_list.display_all();

cout << "=== GPA Analysis ===" << endl;
student_list.find_highest_gpa();
student_list.find_lowest_gpa();

cout << "\n=== Delete Operations ===" << endl;
student_list.delete_by_roll_number(105);
student_list.delete_by_roll_number(999);

cout << "\nAfter deletion:" << endl;
student_list.display_all();

cout << "List size: " << student_list.get_size() << endl;
cout << "Is empty: " << (student_list.is_empty() ? "Yes" : "No") << endl;

cout << "\n=== Clearing List ===" << endl;
student_list.clear_list();
cout << "Is empty after clearing: " << (student_list.is_empty() ? "Yes" : "No") << endl;

return 0;

}
