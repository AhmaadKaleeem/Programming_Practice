import pandas as pd
data = {
    'Emp Id': [101,102,103],
    'Department': ['CS','CS','IT'],
     'Age': [25,23,25],
     'Salary': [256000,150000,240000]
}
frame = pd.DataFrame(data)
print(frame[['Department','Salary']])