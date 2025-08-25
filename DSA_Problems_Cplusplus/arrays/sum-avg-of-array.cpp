/*
Problem Statement:
Write a C++ program that calculates the sum and average of all elements in an array.

Example:
Input: arr[] = {4, 5, 6, 7}
Output: Sum = 22, Average = 5.5
*/


#include <iostream>
using namespace std;

int main(){

int size;
float count;
cout << "Enter the size of array : " ;
cin>>size;

int array[size];
cout << "Enter the elements of array : " ;
for (int i =0; i<size; i++) // using loop to Take Inputs
{
    cin >> array[i];
} 

// Finding sum and average

for (int j = 0; j<size ; j++){
    count += array[j] ;
}

 cout << "Sum is " << count << "\n";
 cout << "Average is " << count/size;
 
   return 0;
}
