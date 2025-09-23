/*
1- Write a program that:
Stores your name, age, hobbies (List), and marks (Map).
Prints them with string interpolation.
Uses if/else and switch to categorize age (Teen, Adult, Senior).
Loops through hobbies and prints them.

2- Write 3 functions:
Add two numbers.
Greet a user (with optional title).
Display student info (with named parameters).

3- Practice null safety:
Create a nullable variable.
Use null-aware operator ??.
Use late keyword
 */

void main() {
  List<String> name = [];
  List<int> age = [];
  List<String> hobby = [];
  Map<int, String> marks = {};

  name.addAll(["Ahmad,Ali"]);
  age.addAll([18, 35]);
  hobby.addAll(["Coding, Gaming"]);
  marks.addAll({52: "PF", 60: "PF"});
  print(name);
}
