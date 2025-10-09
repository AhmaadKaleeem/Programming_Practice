#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class SinglyLinkedList {
private:
    Node* head;
    int size;

public:
    SinglyLinkedList() {
        head = nullptr;
        size = 0;
    }
    
    // Destructor to free memory
    ~SinglyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    void insert(int user_value) {
        Node* newNode = new Node(user_value);
        
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
        cout << "Successfully Inserted " << user_value << endl;
    }
    
    void insertAtBeginning(int user_value) {
        Node* newNode = new Node(user_value);
        newNode->next = head;
        head = newNode;
        size++;
        cout << "Successfully Inserted " << user_value << " at beginning" << endl;
    }
    
    void insertAtPosition(int user_value, int position) {
        if (position < 0 || position > size) {
            cout << "Invalid position!" << endl;
            return;
        }
        
        if (position == 0) {
            insertAtBeginning(user_value);
            return;
        }
        
        Node* newNode = new Node(user_value);
        Node* temp = head;
        
        for (int i = 0; i < position - 1; i++) {
            temp = temp->next;
        }
        
        newNode->next = temp->next;
        temp->next = newNode;
        size++;
        cout << "Successfully Inserted " << user_value << " at position " << position << endl;
    }
    
    void remove(int value) {
        if (head == nullptr) {
            cout << "List is empty. Cannot remove " << value << endl;
            return;
        }
        
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            cout << "Deleted " << value << " successfully." << endl;
            return;
        }
        
        Node* current = head;
        Node* previous = nullptr;
        
        while (current != nullptr && current->data != value) {
            previous = current;
            current = current->next;
        }
        
        if (current == nullptr) {
            cout << "Value " << value << " not found in the list." << endl;
            return;
        }
        
        previous->next = current->next;
        delete current;
        size--;
        cout << "Deleted " << value << " successfully." << endl;
    }
    
    void search(int value) {
        Node* temp = head;
        int position = 0;
        
        while (temp != nullptr) {
            if (temp->data == value) {
                cout << "Value " << value << " found at position " << position << "." << endl;
                return;
            }
            temp = temp->next;
            position++;
        }
        cout << "Value " << value << " not found." << endl;
    }
    
    void display() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        
        cout << "List elements: ";
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << " (Size: " << size << ")" << endl;
    }
    
    void displayReverse(Node* node) {
        if (node == nullptr) {
            return;
        }
        displayReverse(node->next);
        cout << node->data << " ";
    }
    
    void displayInReverse() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        cout << "List elements in reverse: ";
        displayReverse(head);
        cout << endl;
    }
    
    int getSize() {
        return size;
    }
    
    bool isEmpty() {
        return head == nullptr;
    }
};

int main() {
    SinglyLinkedList myList;

    cout << "=== Singly Linked List Demo ===" << endl;
    
    myList.insert(10);
    myList.insert(20);
    myList.insert(30);
    myList.display();
    
    myList.insertAtBeginning(5);
    myList.display();
    
    myList.insertAtPosition(15, 2);
    myList.display();
    
    myList.search(20);
    myList.search(50);
    myList.search(5);

    myList.remove(20);
    myList.display();

    myList.remove(5);
    myList.display();

    myList.remove(50); 
    
 
    myList.displayInReverse();
    
    cout << "List size: " << myList.getSize() << endl;
    cout << "Is list empty? " << (myList.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}