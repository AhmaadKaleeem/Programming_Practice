# In a file called extensions.py, implement a program that prompts the user for the name of a file and then outputs that file’s media type if the file’s name ends, case-insensitively, in any of these suffixes:
# .gif   image/gif
# .jpg   image/jpeg
# .jpeg   image/jpeg
# .png    image/png
# .pdf    application/pdf
# .txt    text/plain
# .zip    application/zip
# other > standard application/octet-stream

# Taking input form user
filename = input ("What is name of file? ").lower().strip()

# using conditionals and str function to check file name and gie output
if filename.endswith(".gif"):
    print("image/gif")
elif filename.endswith((".jpeg" , "jpg")):
    print("image/jpeg")
elif filename.endswith(".png"):
    print("image/png")
elif filename.endswith(".pdf"):
    print("application/pdf")
elif filename.endswith(".txt"):
    print("text/plain")
elif filename.endswith(".zip"):
    print("application/zip")
else :
    print("application/octet-stream")


