# Clean missing data. 
# Ask 5 questions like an analyst.
# Answer them with Pandas (mean, groupby, filter).
import pandas as pd
df = pd.read_csv("python/Excel-Automation/student_grades.csv")
print("Origional Dataset")
print(df)
# Filling Missing Data
df['Science'] = df['Science'].fillna(df['Science'].mean().round(0))
df['Math'] = df['Math'].fillna(df['Math'].mean().round(0))
df['English'] = df['English'].fillna(df['Math'].mean().round(0))
print ("\nFilling Missing Data")
print(df)    

# Finding Overall Topper
df["Average Marks"] = df[['English','Math','Science']].mean(axis=1).round(0)
print("\nHighest Marks")
topper = df.loc[df['Average Marks'].idxmax()]
print(topper)
#Lowest Marks
print("\nLowest Marks")
lowest = df.loc[df['Average Marks'].idxmin()]
print(lowest)

# Student of Maths Having Similar Marks Then Showing Student ID , Name , Math Marks and Overall Grades
maths_students_having_similar_marks = df[df['Math'] == df['Math'].median(axis=0)]
print("Students With Similar Marks in Maths")
print(maths_students_having_similar_marks[['StudentID','Name','Math','OverallGrade']])

# Student of Science Having Similar Marks Then Showing Student ID , Name , Science Marks and Overall Grades
science_students_having_similar_marks = df[df['Science'] == df['Science'].median(axis=0)]
print("Students With Similar Marks in Science")
print(science_students_having_similar_marks[['StudentID','Name','Science','OverallGrade']])

# Student of English Having Similar Marks Then Showing Student ID , Name , Math Marks and Overall Grades
english_students_having_similar_marks = df[df['English'] == df['English'].median(axis=0)]
print("Students With Similar Marks in Science")
print(english_students_having_similar_marks[['StudentID','Name','English','OverallGrade']])

# Student with 80+ marks in all subjects
brilliant_students = df[(df[['English','Math','Science']] > 80).all(axis=1) ]
print("\nOverall Brilliant Perfoming Students")
print(brilliant_students)

#Sorting By Grades nd Average Maks
print("\nGrade Wise Performance Of Students")
grade_rank = {"A":1, "B":2, "C":3, "D":4, "F":5}
df["GradeRank"] = df["OverallGrade"].map(grade_rank)
df_sorted = df.sort_values(by="GradeRank").drop(columns="GradeRank")
df_sorted = df_sorted.sort_values(by='Average Marks', ascending=False)
print(df_sorted)
df.to_csv("python/Excel-Automation/updated_student_grades.csv")
print("File Saved Successfully")