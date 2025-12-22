class Student {
  String _name;
  int _marks;
  int _rollno;

  Student({required u_name, int u_marks = 0, required int u_rollno})
    : _name = u_name,
      _marks = u_marks,
      _rollno = u_rollno;
  String get name => _name;
  int get marks => _marks;
  int get rollno => _rollno;

  set rollno(int value) {
    if (value > 0) {
      _rollno = value;
    } else {
      print("Roll No cant be less than one\n");
    }
  }

  set marks(int value) {
    if (value >= 0) {
      _marks = value;
    } else {
      print("Marks cant be less than Zero\n");
    }
  }

  set name(String un) {
    _name = un;
  }
}

class StudentManager {
  List<Student> students = [];
  void add_student(Student student) {
    students.add(student);
  }

  double average_calc() {
    double total_marks = 0.0;
    int total_std = 0;
    for (var i in students) {
      total_marks += i.marks;
      total_std += 1;
    }
    double avg = total_marks / total_std;
    return avg;
  }
}
