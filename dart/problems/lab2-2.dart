// Write a dart program to calculate your CGPA and GPA//Take input from user to select operation
// Use switch to perform selection
// //use conditional operators
import 'dart:io';

void main() {
  List<double> obtained_grade_pionts_list = [];
  List<int> credit_hour_list = [];
  List<double> grades_pionts_list = [
    4.0,
    3.7,
    3.3,
    3.0,
    2.7,
    2.3,
    2.0,
    1.7,
    1.3,
    1.0,
    0.0,
  ];
  print('------------------------ CGPA Calculator -------------------');
  print("1. SGPA Calculator");
  print("2. CGPA Calculator");
  stdout.write('Enter Your Desired Choice: ');
  int choice = int.parse(stdin.readLineSync()!);
  switch (choice) {
    case 1:
      stdout.write('Enter Number of Subjects: ');
      int subjects_count = int.parse(stdin.readLineSync()!);
      if (subjects_count < 1) {
        print("There must be minimum 1 subjects ");
      } else {
        for (int i = 1; i <= subjects_count; i++) {
          print("\nEnter Details for Subject # $i");
          stdout.write("Enter the Credit Hours: ");
          int credit_hour = int.parse(stdin.readLineSync()!);
          if (credit_hour > 6 || credit_hour < 1) {
            print("There can be credit hours between 1 - 6");
          } else {
            credit_hour_list.add(credit_hour);
            stdout.write("Enter the Grade Pionts Obtained: ");
            double grade_pionts = double.parse(stdin.readLineSync()!);
            if (grades_pionts_list.contains(grade_pionts)) {
              double obtained_grade_piont = grade_pionts * credit_hour;
              obtained_grade_pionts_list.add(obtained_grade_piont);
            } else {
              print('Enter Valid Grade Pionts');
            }
          }
        }
        double total_obtained = 0.0;
        double total_credits = 0.0;
        for (int i = 0; i < subjects_count; i++) {
          total_obtained += obtained_grade_pionts_list[i];
          total_credits += credit_hour_list[i];
        }

        double sgpa = total_obtained / total_credits;
        print("SGPA: ${sgpa.toStringAsFixed(2)}");
      }
      break;
    case 2:
      stdout.write('Enter Number of Semesters: ');
      int semesters = int.parse(stdin.readLineSync()!);

      if (semesters < 1) {
        print("There must be at least 1 semester.");
      } else {
        List<double> semester_points = [];
        List<int> semester_credits = [];

        for (int s = 1; s <= semesters; s++) {
          stdout.write("Enter SGPA for Semester $s: ");
          double sgpa = double.parse(stdin.readLineSync()!);

          if (sgpa < 0.0 || sgpa > 4.0) {
            print("SGPA must be between 0.0 and 4.0");
          }

          stdout.write("Enter total Credit Hours for Semester $s: ");
          int credits = int.parse(stdin.readLineSync()!);

          if (credits < 1) {
            print("Credit hours must be at least 1");
          }

          semester_points.add(sgpa * credits);
          semester_credits.add(credits);
        }

        double total_points = 0.0;
        int total_credits = 0;

        for (int i = 0; i < semesters; i++) {
          total_points += semester_points[i];
          total_credits += semester_credits[i];
        }

        double cgpa = total_points / total_credits;
        print("Final CGPA: ${cgpa.toStringAsFixed(2)}");
      }
      break;

    default:
      print("Enter Valid Choice");
  }
}
