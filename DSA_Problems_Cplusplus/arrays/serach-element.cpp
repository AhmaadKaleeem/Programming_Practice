
/*
📌 Problem Statement:
Write a program that searches for a given element in an array using the linear search algorithm and prints whether the element is found.

📌 Example Input:
Enter size of array: 6  
Enter elements: 10 20 30 40 50 60  
Enter element to search: 40  
📌 Example Output:
Element found at index 3
📌 Example Input (if not found):

Enter element to search: 25  
📌 Example Output:
Element not found

*/

#include <iostream>
using namespace std;

int main(){

int size,search,count=0;
cout << "Enter the size of array : " ;
cin  >> size;

int array[size];
cout << "Enter the elements of array : " ;
for (int i =0; i<size; i++) // using loop to Take Inputs
{
    cin >> array[i];
}

cout << "Enter the element to search : " ;
cin  >> search ;

for (int i = 0 ; i<size ; i++ )
{
  if (array[i]==search){
    cout << "Element found at index " << i <<endl; // not breaking array that element might occur twice
   count++;
    break;
  }
}
if (count==0){
  cout << "Element not found.";
}
return 0 ;
}