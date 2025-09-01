from fpdf import FPDF

username = input("Name: ")

pdf = FPDF(orientation="portrait", unit="mm", format="A4")
pdf.add_page()

# Title
pdf.set_font("Times", style="B", size=18)
pdf.cell(0, 10, "CS50 Shirtificate", ln=True, align="C")

# Shirt image
pdf.image("shirtificate.png", x=30, y=40, w=150)

# User text on the shirt
pdf.set_font("Arial", "B", 20)
pdf.set_text_color(255, 255, 255)
pdf.set_y(120)
pdf.cell(0, 10, f"{username} took CS50", align="C")

# Save the file with correct name
pdf.output("shirtificate.pdf")
