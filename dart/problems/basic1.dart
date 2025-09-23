/*  Problem 1: Greeting with Age (Easy)
Write a program that:
Takes input: your name and age.
Prints a greeting message like:
Hello, Ahmad! You are 21 years old.
🔧 */
import 'dart:io';

void main() {
  stdout.write('Enter your name: ');
  String name = stdin.readLineSync()!;
  stdout.write('Enter your age: ');
  int age = int.parse(stdin.readLineSync()!);
  print('Hello, $name! You are $age years old.');
}
