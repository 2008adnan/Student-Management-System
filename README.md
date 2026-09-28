# 🎓 Student Management System in C

A simple, menu-driven **console application written in C** to manage student records. Data is saved to a binary file, so records are still there after you close and reopen the program.

Built as a hands-on project after learning the fundamentals of C programming.

---

## ✨ Features

| # | Option | What it does |
|---|--------|--------------|
| 1 | **Add** | Adds a new student (roll number, name, marks). Duplicate roll numbers are rejected. |
| 2 | **Display** | Shows all students in a neat table with a total count. |
| 3 | **Search** | Finds a student by roll number and shows their details. |
| 4 | **Rusticate** | Removes a student's record from the file, after asking for confirmation. |
| 5 | **Exit** | Closes the program. |

Extra touches:
- Input validation: typing letters where a number is expected won't crash the program.
- Names with spaces (e.g. `Asha Verma`) are supported.
- Confirmation prompt (`y/n`) before rusticating, since it can't be undone.
- Friendly messages when the file is empty or a student isn't found.

---

## 🧠 C Concepts Used

- **`do-while` loop**: keeps the menu running until the user chooses Exit
- **`switch` statement**: runs the right function for each menu choice
- **File handling**: `fopen`, `fclose`, `fread`, `fwrite`, `rewind`, `remove`, `rename`
- **Binary files**: records stored with `fwrite` / `fread` in `students.dat`
- **Structures (`struct`)**: groups roll, name and marks into one record
- **Functions**: each feature is its own function, keeping `main()` clean
- **Input handling**: `scanf` return-value checks, `fgets`, and a custom `clearBuffer()`
- **Strings**: `strcspn` to strip the newline that `fgets` leaves behind

---

## 📁 Project Structure

```
student-management-system/
├── student_management.c   # complete source code
├── README.md              # you are here
└── students.dat           # created automatically when you add the first student
```

---

## 🚀 How to Run

### Requirements
- A C compiler such as **GCC** (MinGW on Windows, or the built-in one on Linux/macOS)

### Compile
```bash
gcc student_management.c -o student
```

### Run
```bash
./student          # Linux / macOS
student.exe        # Windows
```

---

## 🖥️ Sample Output

```
==============================
  STUDENT MANAGEMENT SYSTEM
==============================
1. Add
2. Display
3. Search
4. Rusticate
5. Exit
Enter your choice: 2

--- All Students ---
Roll No    Name                      Marks
---------------------------------------------
101        Asha Verma                88.50
102        Rohan Singh               76.00
---------------------------------------------
Total students: 2
```

---

## ⚙️ How It Works

### Data structure
```c
struct Student {
    int   roll;
    char  name[50];
    float marks;
};
```

### Saving and loading
- **Add** opens `students.dat` in append-binary mode (`"ab"`) and writes one record with `fwrite`.
- **Display / Search** open the file in read-binary mode (`"rb"`) and read records one by one with `fread`.

### Rusticating a student
A record can't be deleted from the middle of a file directly, so the program:
1. Finds the student and shows their details.
2. Asks for `y/n` confirmation.
3. Copies every student **except** that one into `temp.dat`.
4. Deletes the old file and renames `temp.dat` to `students.dat`.

```
Old file:  [101] [102] [103]     ← rusticate 102
             ↓     ✗     ↓
New file:  [101]       [103]
```

---

## ⚠️ Limitations

- Records are searched one by one (fine for small data, slow for very large files).
- Rusticating rewrites the whole file each time.
- The binary file may not be portable between different systems or compilers.
- Only the roll number can be used for searching.

---

## 📚 What I Learned

- How to structure a C program using functions instead of one big `main()`
- How file handling works, and the difference between text and binary modes
- Why input buffers cause problems with `scanf` + `fgets`, and how to fix them
- How to delete a record from a file using a temporary file
- Defensive programming: checking `NULL` after `fopen` and validating user input

---

## 👤 Author

**Adnan Ahmad**
[LinkedIn](https://www.linkedin.com/in/2008adnanahmad/) · [GitHub - 2008adnan](https://github.com/2008adnan)

⭐ If you found this helpful, consider giving the repo a star!
