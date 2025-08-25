/*
📌 Problem Statement:
Write a program that tajes an array of N integers as input and finds the maximum and minimum elements in the array.
📌 Example Input:
Enter size of array: 5  
Enter elements: 3 8 1 7 2  
📌 Example Output: 
Max = 8, Min = 1
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

// checjing max and minimum in an array

int max = array[0];
int min = array[0];

for (int j = 1 ; j<size; j++)
{
    if (array[j]>max){
        max = array[j];
    }

}

for (int j = 1 ; j<size; j++)
{
    if (array[j]<min){
        min = array[j];
    }

}
 cout << "Maximum is = " << max  << "\n" ;
 cout << "Minimum is = " << min << "\n";

    return 0;
}