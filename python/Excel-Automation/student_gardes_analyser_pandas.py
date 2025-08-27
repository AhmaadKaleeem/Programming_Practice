# Load Data → Read grades.csv into Pandas.
# Handle Missing Values → Fill missing marks with subject average.
# Filter Data → Show only students who passed (Passed == "yes").
# Aggregate → Calculate average marks of each students
# Sorting → Sort students by Math marks (descending).
# Save Cleaned Data → Export cleaned DataFrame into cleaned_grades.csv.
import pandas as pd
# Loading CSV File &  Viewing Dataset
dataframe = pd.read_csv('python/Excel-Automation/grades.csv')
print("Origional Dataframe")
print(dataframe)
# Filling Missing Data
dataframe['Science'] = dataframe['Science'].fillna(dataframe['Science'].mean())
dataframe['Math'] = dataframe['Math'].fillna(dataframe['Math'].mean())
dataframe['English'] = dataframe['English'].fillna(dataframe['Math'].mean())
# SHowing Passed Students
passed_students = dataframe[dataframe['Passed'] == 'yes']
print("Passed Students")
print(passed_students)

# Making New Column 
dataframe['Average Marks'] = dataframe[['Math','Science','English']].mean(axis=1).round(3)
print ("Updated Dataset With Average Marks")
print(dataframe) 

# Sorting → Sort students by Math marks (descending).
dataframe = dataframe.sort_values(by='Math', ascending=False)
print(dataframe) 

# Exproting Dataset to new csv file
dataframe.to_csv('python/Excel-Automation/cleaned_grades.csv',index=False)
print("File Saved Successfully")