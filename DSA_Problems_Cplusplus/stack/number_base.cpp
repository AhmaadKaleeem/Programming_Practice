#include<iostream>
using namespace std;
class Node {
public:
	int data;
	Node* next;

	Node(int val) {
		data = val;
		next = nullptr;
	}
};

class Stack {
	Node* top;
public:
	Stack() {
		top = nullptr;
	}
	void push(int val) {
		Node* newNode = new Node(val);
		if (top == nullptr) {
			top = newNode;
		}
		else {
			newNode->next = top;
			top = newNode;
		}
	}
	void print() {
		Node* temp = top;
		while (temp != nullptr) {
			if (temp->data == 10)
				cout << "A";
			else if (temp->data == 11)
				cout << "B";
			else if (temp->data == 12)
				cout << "C";
			else if (temp->data == 13)
				cout << "D";
			else if (temp->data == 14)
				cout << "E";
			else if (temp->data == 15)
				cout << "F";
			else
				cout << temp->data;
			temp = temp->next;
		}
	}
};

void binary(int val) {
	int temp=val;
	int remainder;
	Stack* newStack = new Stack;
	while (temp > 0) {
		remainder = temp % 2;
		temp = temp / 2;
		newStack->push(remainder);
	}
	newStack->print();
	delete newStack;
}

void octal(int val) {
	Stack* newStack = new Stack;
	int remainder;
	newStack->push(val % 8);
	val = val / 8;
	remainder = val % 8;
	while (val > 0) {
		if (val < 8)
			newStack->push(val);
		else
			newStack->push(remainder);
		remainder = val % 8;
		val = val / 8;
	}
	newStack->print();
	delete newStack;
}

void hexa(int val) {
	Stack* newStack = new Stack;
	int remainder;
	newStack->push(val % 16);
	val = val / 16;
	remainder = val % 16;
	while (val > 0) {
		if (val < 16)
			newStack->push(val);
		else
			newStack->push(remainder);
		remainder = val % 16;
		val = val / 16;
	}
	newStack->print();
	delete newStack;
}
int main() {
	int d, c;
	cout << "Enter a decimal Number: ";
	cin >> d;
	cout << "1. Binary\n2. Octal\n3. HexaDecimal \n";
  cout << "Conversion To : ";
	cin >> c;
	if (c == 2)
		octal(d);
	else if (c == 1)
		binary(d);
  else if(c == 3)
    hexa(d);
	else
		cout << "Invalid Input";
	return 0;
}
