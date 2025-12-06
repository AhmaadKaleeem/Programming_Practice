# CodeGuardX

**An AI-Powered Security Scanner for Python & JavaScript Code**

> Making code security simple and educational for everyone

---

##  Introduction

CodeGuardX is a security tool that scans your Python and JavaScript code to find vulnerabilities **before** you deploy.  It's designed for students and developers who want to learn about security while building safer applications.

**The best part?** It doesn't just tell you what's wrong—it explains **why** it's dangerous and **how** to fix it using AI. 

---

##  Why CodeGuardX?

**The Problem:**
- 80% of data breaches happen because of insecure code
- Common issues like SQL injection and hardcoded passwords still cause major problems
- Existing security tools are too complex for beginners

**Our Solution:**
- ✅ Automatically scan Python and JavaScript files
- ✅ Detect OWASP Top 10 security vulnerabilities
- ✅ Get AI-powered explanations in plain English
- ✅ Learn while you code

---

## ✨ Key Features

- 🔍 **Smart Scanning** - Uses Abstract Syntax Trees (AST) to deeply understand your code
- 🛡️ **OWASP Top 10** - Detects the most common security vulnerabilities
- 🤖 **AI Explanations** - Powered by OpenAI to explain issues in simple terms
- 📊 **Multiple Reports** - Terminal, HTML, and JSON formats
- 📚 **Educational** - Learn security while fixing bugs

---

##  What Does It Detect?

CodeGuardX finds common security issues like:

- 🔑 Hardcoded passwords and API keys
- 💉 SQL Injection vulnerabilities
- 🔐 Weak encryption (MD5, SHA1)
- ⚠️ Dangerous functions (`eval`, `exec`, `pickle`)
- 🌐 Cross-Site Scripting (XSS)
- And more...

---

## 🚀 Quick Start

### 1. Installation

```bash
# Clone the repository
git clone https://github.com/AhmaadKaleeem/codeguardx. git
cd codeguardx

# Install dependencies
pip install -r requirements. txt
```

### 2.  Set Up OpenAI API Key

```bash
export OPENAI_API_KEY='your-api-key-here'
```

### 3. Run Your First Scan

```bash
# Scan a single file
python codeguardx.py scan myfile.py

# Scan a folder
python codeguardx.py scan ./my-project
```

---

## 📖 Usage Examples

### Basic Scan
```bash
python codeguardx.py scan app.py
```

### Scan with HTML Report
```bash
python codeguardx.py scan ./src --report html
```

### Scan with AI Explanations
```bash
python codeguardx.py scan app.py --ai-explain
```

---

## 📊 Example Output

```
╔════════════════════════════════════════════════╗
║         CodeGuardX Security Report             ║
╚════════════════════════════════════════════════╝

📁 File: login.py
⚠️  Line 15: Hardcoded Password Found
    Severity: HIGH
    Code: password = "admin123"
    
🤖 AI Says:
   Never store passwords directly in your code!
   Anyone with access to your code can see them.
   
✅ Better Approach:
   Use environment variables:
   password = os.getenv("DB_PASSWORD")
```

---

## 🛠️ Project Status

🚧 **This project is under active development!**

### ✅ Completed
- Project planning and research
- README documentation

### 🔨 In Progress
- Core scanning engine
- AST parser for Python & JavaScript
- Vulnerability detection rules

### 📋 Upcoming
- OpenAI API integration
- Report generation (HTML/JSON)
- CI/CD integration
- Web dashboard

---

## 🤝 Contributing

This is a student project and contributions are welcome! Whether you're:
- 🐛 Reporting bugs
- 💡 Suggesting features
- 📝 Improving documentation
- 💻 Adding code

Feel free to open an issue or submit a pull request! 

---

## 📚 Learn More

- [OWASP Top 10](https://owasp.org/www-project-top-ten/)
- [Python AST Module](https://docs.python.org/3/library/ast.html)
- [OpenAI API Documentation](https://platform.openai. com/docs)

---

## 📄 License

MIT License - Feel free to use this project for learning! 

---

## 👨‍💻 Author

**AhmaadKaleeem**

- GitHub: [@AhmaadKaleeem](https://github. com/AhmaadKaleeem)

---

## 🌟 Show Your Support

If you find this project helpful, please give it a ⭐️! 

---

**Made with ❤️ for developers who care about security**
