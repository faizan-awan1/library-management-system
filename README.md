# 📚 Library Management System
 
A console-based Library Management System built in **C++** that demonstrates core programming concepts including structs, enums, pointers, references, dynamic memory management, function overloading, and recursion.
 
---
 
## 🚀 Features
 
- ➕ Add and delete books
- 👤 Register library members
- 📖 Issue and return books
- 🔍 Search books by ID or title
- 📋 View all books and members
- ✅ Tracks book availability in real time
---
 
## 🛠️ Concepts Used
 
| Concept | Where Used |
|---|---|
| **Arrays** | `books[]` and `members[]` to store data |
| **Structs** | `Book` and `Member` to group related data |
| **Enums** | `BookStatus` (Available/Issued/Reserved) and `Genre` |
| **Pointers** | `Book*`, `Member*` — dynamic object creation |
| **References** | `const Book& b` in display functions |
| **Memory Management** | `new` to allocate, `delete` to free heap memory |
| **Functions** | Every feature in its own function |
| **Function Overloading** | `enumToString(BookStatus)` and `enumToString(Genre)` |
| **Scope** | Global arrays, local variables per function |
| **Recursion** | `showMenu()` calls itself to keep the program running |
 
---
 
## 📁 Project Structure
 
```
library_manager.cpp   ← single file, all code here
README.md             ← this file
```
 
---
 
## ⚙️ How to Run
 
### Requirements
- C++ compiler (g++)
- Windows / Linux / Mac
### Steps
 
**1. Clone the repository**
```bash
git clone https://github.com/your-username/library-management-system.git
cd library-management-system
```
 
**2. Compile**
```bash
g++ library_manager.cpp -o library_manager
```
 
**3. Run**
```bash
# Windows
library_manager.exe
 
# Linux / Mac
./library_manager
```
 
---
 
## 🖥️ Program Menu
 
```
╔══════════════════════════════╗
║    LIBRARY MANAGEMENT SYS    ║
╠══════════════════════════════╣
║  1. Add Book                 ║
║  2. Add Member               ║
║  3. Issue Book               ║
║  4. Return Book              ║
║  5. Search Book              ║
║  6. View All Books           ║
║  7. View All Members         ║
║  8. Delete Book              ║
║  0. Exit                     ║
╚══════════════════════════════╝
```
 
---
 
## 💡 How It Works
 
- All data is stored **in RAM** (heap memory) while the program runs
- `new Book()` allocates memory dynamically for each book
- `delete` frees that memory when program exits — no memory leaks
- Menu keeps looping via **recursion** until user presses `0`
---
 
## 📌 Sample Usage
 
```
1. Add Book → Enter title, author, genre
2. Add Member → Enter member name
3. Issue Book → Enter Book ID + Member ID
4. Return Book → Enter Member ID
6. View All Books → See full book list with status
0. Exit → Program closes cleanly
```
 
---
 
## 👨‍💻 Author
 
**Akash**
BS Computer Science
 
---
 
## 📄 License
 
This project is open source and free to use for educational purposes.
