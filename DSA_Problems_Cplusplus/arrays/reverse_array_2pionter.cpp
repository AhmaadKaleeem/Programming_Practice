/*
📌 Problem Statement:
Write a program that reverses an array of N integers in place, without using an extra array.

📌 Example Input:
Enter size of array: 7  
Enter elements: 1 2 3 4 5 5 7   
📌 Example Output:
Reversed array: 7 5 5 4 3 2 1
*/

#include <iostream>
using namespace std;

int main(){

int size;
cout << "Enter the size of array : " ;
cin>>size;
int array[size];
cout << "Enter Elements: ";
for (int i = 0 ; i < size ; i++){
    cin >> array[i] ;
    cout << " ";
}

for(int i = 0, j = size -1; i < j; i++,j--){
    swap(array[i],array[j]);
}

cout << "Reversed Array : ";
for (int f = 0 ; f < size ; f++){
    cout << array[f] << " ";
}
    return 0;
}
