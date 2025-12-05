# Srms
Student Record Management System (SRMS) is a simple console-based C++ project that allows Admin, Staff, Students, and Guests to access and manage student information. It uses file handling (students.txt) to store and update student records including attendance, semester results, and personal details.
# 📚 Student Record Management System (SRMS)

A simple yet functional **Student Record Management System** built in **C++**, using file handling for persistent storage.  
This system supports multiple user roles — **Admin, Staff, Student, and Guest**, each with different access levels.

---

## 🚀 Features

### 🔐 User Roles
#### **1. Admin**
- Add new student records  
- View all students  
- Edit complete student details  

#### **2. Staff**
- Update attendance of any student  
- View all student records  

#### **3. Student**
- Login using student ID and password  
- View full personal information  
- View attendance & semester results  

#### **4. Guest**
- View basic student details using ID  
- No login required (guest credentials available)

---

## 📁 Data Storage Format

Student records are saved in a file named `students.txt` in the following format:

## 🔑 Default Credentials

| Role      | Username/ID | Password   |
|-----------|-------------|------------|
| **Admin** | admin       | admin123   |
| **Staff** | staff       | staff123   |
| **Guest** | guest       | guest123   |
| **Student** | (Saved ID) | (Saved Pass) |
