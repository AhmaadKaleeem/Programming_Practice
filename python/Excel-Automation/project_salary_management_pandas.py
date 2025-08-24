# Employee Salary Management with Pandas + Excel
# Features:
# Read employee data from an Excel file (employees.xlsx)
# Columns: Name, BasicSalary, Bonus, Tax
# Automatically calculate Net Salary = Basic + Bonus - Tax.
# Save the final report into a new Excel file (salary_report.xlsx).
# (Optional) Add a filter: show only employees earning more than 60,000.
import pandas as pd

file = pd.read_excel('python/Excel-Automation/employee_data.xlsx')
file['NetSalary'] = file['BasicSalary'] + file['Bonus'] - file['Tax']

file.to_excel("python/Excel-Automation/salary_report.xlsx", index=False)
print("File Saved Succesfully!")

sortedfile = file[file['NetSalary'] >=60000]
print(sortedfile)
