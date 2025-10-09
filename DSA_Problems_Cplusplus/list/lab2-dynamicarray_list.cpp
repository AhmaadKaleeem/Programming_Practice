#include <iostream>
using namespace std;

class DynamicList {
private:
    int* array;
    int size;
    int capacity;
    
    void resize() {
        capacity *= 2;
        int* newArray = new int[capacity];
        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        cout << "Array resized to capacity: " << capacity << endl;
    }

public:
    DynamicList() {
        capacity = 2; // Start with small capacity
        size = 0;
        array = new int[capacity];
    }
    
    // Destructor to free memory
    ~DynamicList() {
        delete[] array;
    }
    
    void insert(int user_value) {
        if (size >= capacity) {
            resize(); // Dynamically resize when needed
        }
        array[size] = user_value;
        size++;
        cout << "Successfully Inserted " << user_value << endl;
    }
    
    void remove(int value) {
        int index = -1;
        for (int i = 0; i < size; i++) {
            if (array[i] == value) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Value " << value << " not found in the list." << endl;
            return;
        }
        
        for (int i = index; i < size - 1; i++) {
            array[i] = array[i + 1];
        }
        size--;
        cout << "Deleted " << value << " successfully." << endl;
    }

    void search(int value) {
        for (int i = 0; i < size; i++) {
            if (array[i] == value) {
                cout << "Value " << value << " found at position " << i << "." << endl;
                return;
            }
        }
        cout << "Value " << value << " not found." << endl;
    }

    void display() {
        if (size == 0) {
            cout << "List is empty." << endl;
            return;
        }
        cout << "List elements: ";
        for (int i = 0; i < size; i++) {
            cout << array[i] << " ";
        }
        cout << " (Size: " << size << ", Capacity: " << capacity << ")" << endl;
    }
    
    int getSize() {
        return size;
    }
    
    int getCapacity() {
        return capacity;
    }
};

int main() {
    DynamicList myList;

    cout << "=== Dynamic Array List Demo ===" << endl;
    
    // Test insertion and dynamic resizing
    myList.insert(10);
    myList.insert(20);
    myList.insert(30); // This will trigger resize
    myList.insert(40);
    myList.insert(50); // This will trigger another resize
    myList.display();

    // Test searching
    myList.search(20);
    myList.search(50);
    myList.search(100);

    // Test removal
    myList.remove(20);
    myList.display();

    myList.remove(50);
    myList.display();

    myList.remove(100); // Value not found

    return 0;
}