# : Mini Project → Data Analyzer
# Write a Python program that:
# Reads a text file or CSV.
# Counts word frequency.
# Finds most common word.

# Writes results to a new file.
frequency = {}
with open('python/core-problems/data.txt', 'r') as file:
    words = file.read().lower().split()
    for word in words:
        if word in frequency:
            frequency[word] += 1
        else:
            frequency[word] = 1
maximum = max(frequency.values())
print("--------------------- Frequency Of Words ---------------------")
for word,count in frequency.items():
    print(f"{word.title()} : {count}")
    if count == maximum:
        name = word.title()

print(f"Most Common Word : {name}, Occured {maximum} Times")

with open ("python/core-problems/analysed_data.txt", "w")  as outputfile:
    outputfile.write("--------------------- Frequency Of Words ---------------------\n")
    for word,count in frequency.items():
     outputfile.write(f"{word.title()} : {count}\n")
    
    outputfile.write(f"Most Common Word : {name}, Occured {maximum} Times\n")

