# importing libraries
import pandas as pd
import sys
filepath = "python/data_anlysis_visualization/covid_19/Pakistan_Deaths.csv"
filepath2 = "python/data_anlysis_visualization/covid_19/Pakistan_Confirmed_cases.csv"
try:
  death_cases = pd.read_csv(filepath)
  confirmed_cases = pd.read_csv(filepath2)
except FileNotFoundError:
     print("Error! Cannot Find Covid-19 Cases Relevant Dataset Files")
     print("Please Ensure That File Paths are Correct & Files are Present to Contiune Analysis")
     sys.exit(0)
print("Original Data")
print(death_cases.head())
print(death_cases.tail())
print(confirmed_cases.head())    
print(confirmed_cases.tail())    

# Data Cleaning
death_cases = death_cases.rename(columns={"Country/Region" : "Country"})
death_cases = death_cases[death_cases["Country"] == "Pakistan"]

confirmed_cases = confirmed_cases.rename(columns={"Country/Region" : "Country"})
confirmed_cases = confirmed_cases[confirmed_cases["Country"] == "Pakistan"]
# Dropping Unnecassary Colunm
death_cases = death_cases.drop(["Province/State","Lat","Long"], axis = 1)
confirmed_cases = confirmed_cases.drop(["Province/State","Lat","Long"], axis = 1)

# Transpoing and getting count each day
transposing_death_cases = death_cases.melt(id_vars=["Country"] , var_name="Date", value_name="Total_Death_Cases")
transposing_confirmed_cases = confirmed_cases.melt(id_vars=["Country"] , var_name="Date", value_name="Total_Confirmed_Cases")
transposing_confirmed_cases["New_Confirmed_Cases"] = transposing_confirmed_cases['Total_Confirmed_Cases'].diff()
transposing_death_cases["New_Death_Cases"] = transposing_death_cases["Total_Death_Cases"].diff()
transposing_confirmed_cases["New_Confirmed_Cases"] = transposing_confirmed_cases["New_Confirmed_Cases"].fillna(0).astype(int)
transposing_death_cases["New_Death_Cases"] = transposing_death_cases['New_Death_Cases'].fillna(0).astype(int)

print("\nOrganized Data")
print(transposing_death_cases.head())
print(transposing_death_cases.tail())
print(transposing_confirmed_cases.head())    
print(transposing_death_cases.tail())    

# Comvining into a single data set and Finishing Cleanup
combined_covid_data = pd.merge(transposing_confirmed_cases,transposing_death_cases,on=["Country","Date"],how="inner")
combined_covid_data = combined_covid_data[combined_covid_data['Total_Confirmed_Cases'] != 0 ]
combined_covid_data['Date'] = pd.to_datetime(combined_covid_data["Date"])

# REMOVING OUTLINERS
mean_confirmed = combined_covid_data['New_Confirmed_Cases'].mean()
std_confirmed = combined_covid_data['New_Confirmed_Cases'].std()
upper_limit_confirmed = mean_confirmed + (3 * std_confirmed)
lower_limit_confirmed = mean_confirmed - (3 * std_confirmed)
combined_covid_data['Outliner_Confirmed_Cases'] = combined_covid_data["New_Confirmed_Cases"].between(upper_limit_confirmed,lower_limit_confirmed)
combined_covid_data["Outliner_Confirmed_Cases"] = (
    (combined_covid_data["New_Confirmed_Cases"] == 0) &
    (combined_covid_data["Total_Confirmed_Cases"] > 1000)  
)
mean_Death = combined_covid_data['New_Death_Cases'].mean()
std_Death = combined_covid_data['New_Death_Cases'].std()
upper_limit_Death = mean_Death + (3 * std_Death)
lower_limit_Death = mean_Death - (3 * std_Death)
combined_covid_data['Outliner_Death_Cases'] = combined_covid_data["New_Death_Cases"].between(upper_limit_Death,lower_limit_Death)
combined_covid_data["Outliner_Death_Cases"] = (
    (combined_covid_data["New_Death_Cases"] == 0) &
    (combined_covid_data["Total_Death_Cases"] > 1000)  
)
combined_covid_data = combined_covid_data[(combined_covid_data['Outliner_Confirmed_Cases'] != True) & (combined_covid_data['Outliner_Death_Cases'] != True)]
combined_covid_data = combined_covid_data.drop(columns=['Outliner_Death_Cases','Outliner_Confirmed_Cases'])
print("\nCombined Cleaned Data")
print(combined_covid_data.head())
print(combined_covid_data.tail())