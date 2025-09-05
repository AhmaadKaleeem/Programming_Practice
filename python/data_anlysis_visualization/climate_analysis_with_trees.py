import pandas as pd

temperature_data = pd.read_csv("python/Excel-Automation/tempreture_1901_2016_pakistan.csv")
trees_data = pd.read_csv("python/Excel-Automation/treecover_loss__ha.csv")

# Data Inspection
print("origional Data")
print(temperature_data.head())
print(temperature_data.tail())
print(trees_data.head())
print(trees_data)

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

# Merging Into New Dataset For Analysis
climate_chnage = pd.merge(temperature_data,trees_data, on="Year", how="inner")
print("\nNew Combined Data")
print(climate_chnage)

# Tree Loss Trends 2001-2008
print("\n2001-2008 Tree Loss Trend")
first_eight_years = climate_chnage[(climate_chnage["Year"] >=2001) & (climate_chnage["Year"] <=2008) ]
first_eight_years = first_eight_years.sort_values(by='umd_tree_cover_loss__ha', ascending=False)
print(first_eight_years)

# Last 8 Year Data Sorted From Maximum To Minimum Trees Loss 
print("\n2008-2015 Tree Loss Trend")
last_eight_years = climate_chnage[(climate_chnage["Year"] >=2008) & (climate_chnage["Year"] <=2015) ]
last_eight_years = last_eight_years.sort_values(by='umd_tree_cover_loss__ha', ascending=False)
print(last_eight_years)

# 2003 - 2006 Trend and temperature comparision  Month Wise
three_year_temp =  climate_chnage[(climate_chnage["Year"] >=2003) & (climate_chnage["Year"] <=2006) ]
three_year_temp = three_year_temp.sort_values(by='Temperature - (Celsius)', ascending=False)
for month in ['January','February','June','July','November','December']:
 selected = three_year_temp[three_year_temp["Month"] == month]
 print(f"\n{month} Climate From 2003-2006")
 print(selected)

# Year with Highest and Their Temp Differ From Last Year
index_highest_cutting_year = climate_chnage['umd_tree_cover_loss__ha'].idxmax()
max_year = climate_chnage.loc[index_highest_cutting_year, "Year"]
highest_cutting_year = climate_chnage.loc[climate_chnage["Year"] == max_year ]
print(f"\nYear With Highest Tree Cutting : {max_year}")
print(highest_cutting_year)

prev_year = max_year - 1
before_highest_cutting_year = climate_chnage.loc[climate_chnage["Year"] == prev_year ]
print(f"\nTemperature Before {max_year}")
print(before_highest_cutting_year)

# Year with Lowest Tree Cuuting & Thier Temp Difference Last Year
index_lowest_cutting_yr = climate_chnage['umd_tree_cover_loss__ha'].idxmin()
min_year = climate_chnage.loc[index_lowest_cutting_yr, "Year"]
lowest_cutting_year = climate_chnage.loc[climate_chnage["Year"] == min_year ]
print(f"\nYear With Lowest Tree Cutting : {min_year}")
print(lowest_cutting_year)

prev_year = min_year - 1
before_lowest_cutting_year = climate_chnage.loc[climate_chnage["Year"] == prev_year ]
print(f"\nTemperature Before {min_year}")
print(before_lowest_cutting_year)

# Making New CSV Data File With Updated Data
climate_chnage.to_csv("python/Excel-Automation/temperature_with_tree_loss_2001-2015.csv",index=False)