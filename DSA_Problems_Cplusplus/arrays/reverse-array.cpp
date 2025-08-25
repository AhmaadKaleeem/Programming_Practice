/*
📌 Problem Statement:
Write a program that reverses an array of N integers in place, without using an extra array.

📌 Example Input:
Enter size of array: 5  
Enter elements: 1 2 3 4 5  
📌 Example Output:

Reversed array: 5 4 3 2 1
*/

#include <iostream>
using namespace std;

int main(){

int size;
cout << "Enter the size of array : " ;
cin>>size;

int array[size];
cout << "Enter the elements of array : " ;
for (int i =0; i<size; i++) // using loop to Take Inputs
{
    cin >> array[i];
}

// Reverse the loop to reverse array
cout << "Reversed Array : ";
for (int j = size-1 ; j>=0 ;j--){
    cout << array[j] << " ";
}

    return 0;
}