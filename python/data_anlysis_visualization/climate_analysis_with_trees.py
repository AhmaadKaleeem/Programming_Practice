import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
import numpy as np
import pickle

temperature_data = pd.read_csv("python/data_anlysis_visualization/tempreture_1901_2016_pakistan.csv")
trees_data = pd.read_csv("python/data_anlysis_visualization/treecover_loss__ha.csv")

# Data Inspection
print("origional Data")
print(temperature_data.head())
print(temperature_data.tail())
print(trees_data.head())
print(trees_data.tail())

# Striping Columns, Renaming Colunmn, Removing Unnecessary  iso Column From trees_data and Cleaning Data By Ranging It From  2001 - 2015 with  6 Months (Jan, Feb, June, July, Nov, Dec) 
temperature_data.columns = temperature_data.columns.str.strip()
trees_data.columns = trees_data.columns.str.strip()

trees_data = trees_data.rename(columns={"umd_tree_cover_loss__year" : "Year"})
trees_data = trees_data[["Year","umd_tree_cover_loss__ha","gfw_gross_emissions_co2e_all_gases__Mg"]]

temperature_data = temperature_data[(temperature_data["Year"] <=2015) & (temperature_data["Year"] >=2001) ]
trees_data = trees_data[(trees_data["Year"] <=2015) & (trees_data["Year"] >=2001) ]
temperature_data = temperature_data[temperature_data["Month"].isin(["January",'February','June','July','November','December'])]

print("\nAfter Cleaning of Data")
print(temperature_data.head())
print(temperature_data.tail())
print(trees_data.head())
print(trees_data.tail())

plt.figure(figsize=(10,5))
plt.plot(trees_data["Year"],trees_data["umd_tree_cover_loss__ha"])
plt.title("Tress Loss Cover 2001 - 2015")
plt.xlabel("Year")
plt.ylabel("Tree Cover Loss (hect)")
plt.grid(True)
plt.show()
# Merging Into New Dataset For Analysis
climate_change = pd.merge(temperature_data,trees_data, on="Year", how="inner")
print("\nNew Combined Data")
print(climate_change)

# Tree Loss Trends 2001-2008
print("\n2001-2008 Tree Loss Trend")
first_eight_years = climate_change[(climate_change["Year"] >=2001) & (climate_change["Year"] <=2008) ]
first_eight_years = first_eight_years.sort_values(by='umd_tree_cover_loss__ha', ascending=False)
print(first_eight_years)

# Last 8 Year Data Sorted From Maximum To Minimum Trees Loss 
print("\n2008-2015 Tree Loss Trend")
last_eight_years = climate_change[(climate_change["Year"] >=2008) & (climate_change["Year"] <=2015) ]
last_eight_years = last_eight_years.sort_values(by='umd_tree_cover_loss__ha', ascending=False)
print(last_eight_years)

# 2003 - 2006 Trend and temperature comparision  Month Wise
three_year_temp =  climate_change[(climate_change["Year"] >=2003) & (climate_change["Year"] <=2006) ]
three_year_temp = three_year_temp.sort_values(by='Temperature - (Celsius)', ascending=False)
for month in ['January','February','June','July','November','December']:
 selected = three_year_temp[three_year_temp["Month"] == month]
 print(f"\n{month} Climate From 2003-2006")
 print(selected)

# Year with Highest and Their Temp Differ From Last Year
index_highest_cutting_year = climate_change['umd_tree_cover_loss__ha'].idxmax()
max_year = climate_change.loc[index_highest_cutting_year, "Year"]
highest_cutting_year = climate_change.loc[climate_change["Year"] == max_year ]
print(f"\nYear With Highest Tree Cutting : {max_year}")
print(highest_cutting_year)

prev_year = max_year - 1
before_highest_cutting_year = climate_change.loc[climate_change["Year"] == prev_year ]
print(f"\nTemperature Before {max_year}")
print(before_highest_cutting_year)

# Year with Lowest Tree Cuuting & Thier Temp Difference Last Year
index_lowest_cutting_yr = climate_change['umd_tree_cover_loss__ha'].idxmin()
min_year = climate_change.loc[index_lowest_cutting_yr, "Year"]
lowest_cutting_year = climate_change.loc[climate_change["Year"] == min_year ]
print(f"\nYear With Lowest Tree Cutting : {min_year}")
print(lowest_cutting_year)

prev_year = min_year - 1
before_lowest_cutting_year = climate_change.loc[climate_change["Year"] == prev_year ]
print(f"\nTemperature Before {min_year}")
print(before_lowest_cutting_year)


avg_temp = climate_change.groupby("Year")["Temperature - (Celsius)"].mean()
fig, ax1 = plt.subplots(figsize=(10,5))
ax1.set_xlabel("Year")
ax1.set_ylabel("Avg Temperature (°C)", color="blue")
ax1.plot(avg_temp.index, avg_temp, marker='o', color="blue")
ax2 = ax1.twinx()  
ax2.set_ylabel("Tree Loss (ha)", color="green")
ax2.plot(trees_data["Year"], trees_data["umd_tree_cover_loss__ha"], marker='s', color="green")
plt.title("Temperature vs Tree Loss Trend (Dual Axis)")
plt.grid(True)
plt.show()

for month in climate_change["Month"].unique():
    temp_month = climate_change[climate_change["Month"] == month]
    plt.plot(temp_month["Year"], temp_month["Temperature - (Celsius)"], label=month)

plt.legend()
plt.title("Temperature Trend (Month-wise)")
plt.grid(True)
plt.show()



# Making New CSV Data File With Updated Data
climate_change.to_csv("python/data_anlysis_visualization/temperature_with_tree_loss_2001-2015.csv",index=False)

print("\n----- Machine Learning Model (Predict Temperature) -----")

# Convert months to numeric
month_map = {
    "January": 1,
    "February": 2,
    "June": 6,
    "July": 7,
    "November": 11,
    "December": 12
}

climate_change["Month_Num"] = climate_change["Month"].map(month_map)

# Feature matrix (X) and Target (y)
X = climate_change[[
    "umd_tree_cover_loss__ha",
    "gfw_gross_emissions_co2e_all_gases__Mg",
    "Month_Num",
    "Year"
]]

y = climate_change["Temperature - (Celsius)"]

# Train-Test Split
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

# Train Model
temp_model = LinearRegression()
temp_model.fit(X_train, y_train)

# Predictions
y_pred_temp = temp_model.predict(X_test)

plt.figure(figsize=(8,5))
plt.scatter(y_test, y_pred_temp)
plt.xlabel("Actual Temperature (°C)")
plt.ylabel("Predicted Temperature (°C)")
plt.title("Actual vs Predicted Temperature (ML Model)")
plt.grid(True)
plt.show()

sample = np.array([[10000, 500000, 7, 2012]])
temp_prediction = temp_model.predict(sample)
print(f"Predicted Temperature for sample: {temp_prediction[0]:.2f} °C")


print("\n----- Predict Temperature Based on User Input -----")

# User Input
tree_loss = float(input("Enter Tree Cover Loss (ha): "))
co2 = float(input("Enter CO2 Emissions (Mg): "))
month = int(input("Enter Month Number (1–12): "))
year = int(input("Enter Year: "))

user_sample = np.array([[tree_loss, co2, month, year]])

# Predict
prediction = temp_model.predict(user_sample)

print(f"\nPredicted Temperature = {prediction[0]:.2f} °C")

with open("temperature_model.pkl", "wb") as f:
    pickle.dump(temp_model, f)

print("\nModel saved successfully")
