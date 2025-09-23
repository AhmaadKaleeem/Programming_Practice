// /* Write a Dart program that:
// Asks the user to input the length and width of a rectangle.
// Calculates and prints the:
// Area = length × width
// Perimeter = 2 × (length + width)
// 📌 Sample Output:

// Enter length: 5
// Enter width: 3
// Area: 15
// Perimeter: 16
// */

import 'dart:io';

void main() {
  stdout.write('Enter the lenght: ');
  double lenght = double.parse(stdin.readLineSync()!);
  stdout.write('Enter the width: ');
  double width = double.parse(stdin.readLineSync()!);
  double area = lenght * width;
  double perimeter = 2 * (lenght + width);
  print('Area: $area');
  print('Perimeter: $perimeter');
}
