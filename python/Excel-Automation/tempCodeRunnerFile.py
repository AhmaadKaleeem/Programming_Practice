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