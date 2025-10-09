#include <iostream>
using namespace std;
class List{
private:
 int array[100];
 int size;
public:
 List(){
    size = 0;
 }

 void insert(int user_value){
  if (size >= 100 ){
    cout << "Error! array Size Already Full.";
  }
  else {
    array[size] = user_value;
    size ++ ;
    cout << "Successfully Inserted " << user_value << endl;
  }
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
        cout << endl;
    }
};

int main() {
    List myList;

    myList.insert(10);
    myList.insert(20);
    myList.insert(30);
    myList.display();

    myList.search(20);
    myList.search(50);

    myList.remove(20);
    myList.display();

    myList.remove(50);

    return 0;
}
