

/*
📌 Problem Statement:
Write a program that sorts an array of N integers in ascending order without using built-in sorting functions.

📌 Example Input:
Enter size of array: 5  
Enter elements: 5 2 9 1 3  
📌 Example Output:
Sorted array: 1 2 3 5 9

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

for (int i=0; i<size ; i++)
{ // 15 10 20 25
  for (int j=1;j<size;j++){
   if (array[i]>array[j]){
    array[i]=array[j];
   }
  }
}

for (int k = 0 ; k < size;k++){
    cout << array[k] << " ";
}
    return 0;
}