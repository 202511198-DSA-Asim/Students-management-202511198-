#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

void searchStudent() {
    string roll, name, age;
    string searchRoll;
    
    cout << "Enter Roll Number: ";
    cin >> searchRoll;
    
    ifstream file("students.txt");
    
    if (!file.is_open()) {
        cout << "Error: students.txt file not found!\n";
        return;
    }
    
    bool found = false;
    
    while (getline(file, roll, ',') &&
           getline(file, name, ',') &&
           getline(file, age)) {
        
        roll = trim(roll);
        name = trim(name);
        age = trim(age);
        
        if (roll == searchRoll) {
            cout << "\n====================================\n";
            cout << "STUDENT FOUND\n";
            cout << "====================================\n";
            cout << "Roll Number: " << roll << endl;
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "====================================\n";
            found = true;
            break;
        }
    }
    
    if (!found)
        cout << "Student with Roll Number '" << searchRoll << "' not found.\n";
    
    file.close();
}

void addStudent() {
    string roll, name, age;
    
    cout << "\n--- ADD NEW STUDENT ---\n";
    cout << "Enter Roll Number: ";
    cin >> roll;
    
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    
    cout << "Enter Age: ";
    cin >> age;
    
    ofstream file("students.txt", ios::app);
    
    if (!file.is_open()) {
        cout << "Error: Cannot open students.txt file!\n";
        return;
    }
    
    file << roll << "," << name << "," << age << endl;
    file.close();
    
    cout << "\nStudent Added Successfully!\n";
}

void updateStudent() {
    string searchRoll;
    cout << "Enter Roll Number to Update: ";
    cin >> searchRoll;
    
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    
    if (!file.is_open() || !temp.is_open()) {
        cout << "Error: File operation failed!\n";
        return;
    }
    
    string roll, name, age;
    bool found = false;
    
    while (getline(file, roll, ',') &&
           getline(file, name, ',') &&
           getline(file, age)) {
        
        roll = trim(roll);
        name = trim(name);
        age = trim(age);
        
        if (roll == searchRoll) {
            cout << "\nCurrent Name: " << name << endl;
            cout << "Current Age: " << age << endl;
            cout << "\nEnter New Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter New Age: ";
            cin >> age;
            found = true;
        }
        
        temp << roll << "," << name << "," << age << endl;
    }
    
    file.close();
    temp.close();
    
    remove("students.txt");
    rename("temp.txt", "students.txt");
    
    if (found)
        cout << "\nRecord Updated Successfully!\n";
    else
        cout << "\nStudent with Roll Number '" << searchRoll << "' not found.\n";
}

void deleteStudent() {
    string searchRoll;
    cout << "Enter Roll Number to Delete: ";
    cin >> searchRoll;
    
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    
    if (!file.is_open() || !temp.is_open()) {
        cout << "Error: File operation failed!\n";
        return;
    }
    
    string roll, name, age;
    bool found = false;
    string deletedName;
    
    while (getline(file, roll, ',') &&
           getline(file, name, ',') &&
           getline(file, age)) {
        
        roll = trim(roll);
        name = trim(name);
        age = trim(age);
        
        if (roll == searchRoll) {
            found = true;
            deletedName = name;
            continue;
        }
        
        temp << roll << "," << name << "," << age << endl;
    }
    
    file.close();
    temp.close();
    
    remove("students.txt");
    rename("temp.txt", "students.txt");
    
    if (found)
        cout << "\nRecord Deleted Successfully!\n   (Roll: " << searchRoll << ", Name: " << deletedName << ")\n";
    else
        cout << "\nStudent with Roll Number '" << searchRoll << "' not found.\n";
}

void viewAllStudents() {
    ifstream file("students.txt");
    
    if (!file.is_open()) {
        cout << "Error: students.txt file not found!\n";
        return;
    }
    
    string roll, name, age;
    int count = 0;
    
    cout << "\n====================================\n";
    cout << "ALL STUDENTS LIST\n";
    cout << "====================================\n";
    
    while (getline(file, roll, ',') &&
           getline(file, name, ',') &&
           getline(file, age)) {
        
        roll = trim(roll);
        name = trim(name);
        age = trim(age);
        
        cout << count + 1 << ". Roll: " << roll << " | Name: " << name << " | Age: " << age << endl;
        count++;
    }
    
    if (count == 0) {
        cout << "No students found in database.\n";
    } else {
        cout << "====================================\n";
        cout << "Total Students: " << count << "\n";
    }
    cout << "====================================\n";
    
    file.close();
}

int main() {
    int choice;
    
    cout << "\nWELCOME TO STUDENT MANAGEMENT SYSTEM\n";
    
    do {
        cout << "\n====================================\n";
        cout << "MAIN MENU\n";
        cout << "====================================\n";
        cout << "1. Search Student\n";
        cout << "2. Update Student\n";
        cout << "3. Add Student\n";
        cout << "4. Delete Student\n";
        cout << "5. View All Students\n";
        cout << "6. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                searchStudent();
                break;
            case 2:
                updateStudent();
                break;
            case 3:
                addStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                viewAllStudents();
                break;
            case 6:
                cout << "\nProgram Ended. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid Choice. Please try again.\n";
        }
        
    } while (choice != 6);
    
    return 0;
}
