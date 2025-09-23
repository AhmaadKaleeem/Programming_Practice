// Write a Dart program that takes input from the user for the marks obtained in three subjects: Math,
// Science, and English. Calculate the total marks and average marks obtained by the student.
import 'dart:io';
void main() {
  stdout.write('Enter the marks in Maths: ');
  int marks_maths = int.parse(stdin.readLineSync()!);
  stdout.write('Enter the marks in English: ');
  int marks_english = int.parse(stdin.readLineSync()!);
  stdout.write('Enter the marks in Science: ');
  int marks_science = int.parse(stdin.readLineSync()!);
  int total_marks = marks_maths + marks_english + marks_science;
  double average_marks = total_marks / 3;
  print('Total Marks Obtained By Students: $total_marks');
  print('Average Marks Obtained By Students: $average_marks');
}
