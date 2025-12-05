#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Student {
    string id, name, department, email, password, club, semResult;
    int attCoding = 0, attCPP = 0, attDAA = 0;
};

Student deserialize(const string &line) {
    Student s; string token; stringstream ss(line);
    getline(ss, s.id, '|'); getline(ss, s.name, '|');
    getline(ss, s.department, '|'); getline(ss, s.email, '|');
    getline(ss, s.password, '|'); getline(ss, s.club, '|');
    getline(ss, s.semResult, '|');

    if (getline(ss, token, '|') && !token.empty()) s.attCoding = stoi(token);
    if (getline(ss, token, '|') && !token.empty()) s.attCPP = stoi(token);
    if (getline(ss, token, '|') && !token.empty()) s.attDAA = stoi(token);
    return s;
}

string serialize(const Student &s) {
    stringstream ss;
    ss << s.id << "|" << s.name << "|" << s.department << "|" << s.email << "|"
       << s.password << "|" << s.club << "|" << s.semResult << "|"
       << s.attCoding << "|" << s.attCPP << "|" << s.attDAA;
    return ss.str();
}

bool fetchStudent(const string &id, Student &out) {
    ifstream file("students.txt"); string line;
    if (!file) return false;
    while (getline(file, line)) {
        Student s = deserialize(line);
        if (s.id == id) { out = s; file.close(); return true; }
    }
    file.close();
    return false;
}

void updateStudent(const Student &s) {
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    string line;

    if (!temp) { cout << "Unable to open temp file for writing.\n"; return; }

    while (getline(file, line)) {
        Student st = deserialize(line);
        temp << (st.id == s.id ? serialize(s) : line) << "\n";
    }
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
}

void showBasic(const Student &s) {
    cout << "ID: " << s.id << "\nName: " << s.name
         << "\nDept: " << s.department << "\nEmail: " << s.email << endl;
}

void showFull(const Student &s) {
    showBasic(s);
    cout << "Club: " << s.club << "\nSem Result: " << s.semResult
         << "\nCoding: " << s.attCoding << "%"
         << "\nC++: " << s.attCPP << "%"
         << "\nDAA: " << s.attDAA << "%\n";
}

void addStudent() {
    Student s;
    cout << "\nEnter Student ID: "; cin >> s.id;
    cin.ignore();
    cout << "Name: "; getline(cin, s.name);
    cout << "Department: "; getline(cin, s.department);
    cout << "Email: "; getline(cin, s.email);
    cout << "Password: "; cin >> s.password;
    cin.ignore();
    cout << "Club: "; getline(cin, s.club);
    cout << "Semester Result: "; cin >> s.semResult;
    cout << "Attendance Coding/C++/DAA: ";
    cin >> s.attCoding >> s.attCPP >> s.attDAA;

    ofstream out("students.txt", ios::app);
    if (!out) { cout << "Unable to open students.txt for appending.\n"; return; }
    out << serialize(s) << "\n";
    out.close();
    cout << "Added Successfully!\n";
}

void viewAllStudents() {
    ifstream file("students.txt"); string line;
    if (!file) { cout << "No students found.\n"; return; }
    cout << "\n--- All Students ---\n";
    while (getline(file, line)) {
        Student s = deserialize(line);
        cout << s.id << " | " << s.name << " | " << s.department << endl;
    }
    file.close();
}

void editStudent() {
    string id; cout << "Enter ID to edit: "; cin >> id;
    Student s;
    if (!fetchStudent(id, s)) { cout << "Not Found!\n"; return; }

    cin.ignore();
    cout << "New Name (" << s.name << "): "; getline(cin, s.name);
    cout << "New Dept (" << s.department << "): "; getline(cin, s.department);
    cout << "New Email (" << s.email << "): "; getline(cin, s.email);
    cout << "New Club (" << s.club << "): "; getline(cin, s.club);
    cout << "New Sem Result: "; cin >> s.semResult;
    cout << "New Attendance Coding/C++/DAA: ";
    cin >> s.attCoding >> s.attCPP >> s.attDAA;
    cout << "New Password: "; cin >> s.password;

    updateStudent(s);
    cout << "Updated!\n";
}

void staffEditAttendance() {
    string id; cout << "Enter ID: "; cin >> id;
    Student s;
    if (!fetchStudent(id, s)) { cout << "Not Found!\n"; return; }

    showBasic(s);
    cout << "\nUpdate Attendance Coding/C++/DAA: ";
    cin >> s.attCoding >> s.attCPP >> s.attDAA;

    updateStudent(s);
    cout << "Attendance Updated!\n";
}



void guestMode() {

    string id; cout << "Enter Student ID: "; cin >> id;
    Student s;
    if (!fetchStudent(id, s)) { cout << "Not Found!\n"; return; }
    showBasic(s);
}

void studentLogin() {
    string id, pass;
    cout << "ID: "; cin >> id;
    cout << "Password: "; cin >> pass;

    Student s;
    if (!fetchStudent(id, s) || s.password != pass) {
        cout << "Invalid Login!\n";
        return;
    }

    cout << "\n--- Your Details ---\n";
    showFull(s);
}

void adminMenu() {
    int c;
    while (true) {
        cout << "\nAdmin: 1.Add 2.ViewAll 3.Edit 4.Exit\nChoice: ";
        cin >> c;
        if (c == 1) addStudent();
        else if (c == 2) viewAllStudents();
        else if (c == 3) editStudent();
        else if (c == 4) return;
        else cout << "Invalid Choice!\n";
    }
}

void staffMenu() {
    int c;
    while (true) {
        cout << "\nStaff: 1.EditAttendance 2.ViewAll 3.Exit\nChoice: ";
        cin >> c;
        if (c == 1) staffEditAttendance();
        else if (c == 2) viewAllStudents();
        else if (c == 3) return;
        else cout << "Invalid Choice!\n";
    }
}

void adminLogin() {
    string u, p;
    cout << "Username: "; cin >> u;
    cout << "Password: "; cin >> p;
    if (u == "admin" && p == "admin123") adminMenu();
    else cout << "Invalid!\n";
}

void staffLogin() {
    string u, p;
    cout << "Username: "; cin >> u;
    cout << "Password: "; cin >> p;
    if (u == "staff" && p == "staff123") staffMenu();
    else cout << "Invalid!\n";
}
void guestLogin() {
    string id, pass;
    cout << "\n===== Guest Login =====\n";
    cout << "Enter Guest ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> pass;

    if (id == "guest" && pass == "guest123") {
        guestMode();
       
    } else {
        cout << "\nInvalid Guest ID or Password!\n";
       
    }
}

int main() {
    int c;
    while (true) {
        cout << "\n1.Admin 2.Staff 3.Student 4.Guest 5.Exit\nChoice: ";
        cin >> c;
        if (c == 1) adminLogin();
        else if (c == 2) staffLogin();
        else if (c == 3) studentLogin();
        else if (c== 4)  guestLogin();


        else if (c == 5) break;
        else cout << "Invalid choice!\n";
    }
    return 0;
}

