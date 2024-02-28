#pragma once
#include <stdio.h>
#include "Slave.h"
#include "Master.h"
#include <iostream>
using namespace std;


void GetInfoStudent(Student& student, int& teacherId) {
    cout << "Enter teacher's id: ";
    cin >> teacherId;
    cout << "Enter student's first name: ";
    cin >> student.firstName;
    cout << "Enter student's last name: ";
    cin >> student.lastName;
    string date;
    cout << "Enter date of Birth ('YYYY-MM-DD'): ";
    cin >> date;
    cout << "Enter gender (m or f): ";
    cin >> student.gender;
    cout << "Enter student's number of class: ";
    cin >> student.Class;
}

void InsertStudent(Student& student, int teacherId) {
    ifstream teacherFile("Master.txt");
    Teacher teacher;
    bool teacherExists = false;
    while (teacherFile >> teacher.Id >> teacher.firstName >> teacher.lastName >> teacher.middleName >> teacher.dateBirth >> teacher.subject) {
        if (teacher.Id == teacherId) {
            teacherExists = true;
            break;
        }
    }
    teacherFile.close();

    if (!teacherExists) {
        cerr << "Teacher with id " << teacherId << " does not exist." << endl;
        return;
    }

    ifstream fileIn("Slave.txt");
    int lastId = 0;
    Student lastStudent;
    vector<pair<Student, int>> students;

    if (fileIn.is_open()) {
        while (fileIn >> lastStudent.Id >> lastStudent.firstName >> lastStudent.lastName >> lastStudent.dateBirth >> lastStudent.gender >> lastStudent.Class >> lastStudent.teacherId) {
            if (fileIn.fail()) {
                cerr << "Error reading file." << endl;
                return;
            }
            students.push_back(make_pair(lastStudent, lastStudent.teacherId));
            if (lastStudent.Id != 0) {
                lastId = lastStudent.Id;
            }
        }
        fileIn.close();
    }
    else {
        cerr << "Could not open file for reading." << endl;
        return;
    }


    bool replaced = false;
    for (auto& pair : students) {
        if (pair.first.Id == 0) {
            student.Id = pair.second; 
            pair.first = student;
            pair.second = teacherId;
            replaced = true;
            break;
        }
    }

    if (!replaced) {
        student.Id = lastId + 1;
        students.push_back(make_pair(student, teacherId));
    }

    ofstream fileOut("Slave.txt");
    if (!fileOut.is_open()) {
        cerr << "Could not open file for writing." << endl;
        return;
    }

    for (auto& pair : students) {
        fileOut << pair.first.Id << " "
            << pair.first.firstName << " "
            << pair.first.lastName << " "
            << pair.first.dateBirth << " "
            << pair.first.gender << " "
            << pair.first.Class << " "
            << pair.second << '\n';
    }

    fileOut.close();

    cout << "Data successfully added" << endl;
}


void FindStudentById(int studentId) {
    ifstream file("Slave.txt");
    if (!file.is_open()) {
        cerr << "Could not open file for reading." << endl;
        return;
    }

    Student student;
    int teacherId;
    bool found = false;

    while (file >> student.Id >> student.firstName >> student.lastName >> student.dateBirth >> student.gender >> student.Class >> teacherId) {
        if (student.Id == studentId) {
            found = true;

            cout << "Student found:" << endl;
            cout << "Id: " << student.Id << endl;
            cout << "Teacher Id: " << teacherId << endl;
            cout << "First Name: " << student.firstName << endl;
            cout << "Last Name: " << student.lastName << endl;
            cout << "Date of Birth: " << student.dateBirth << endl;
            cout << "Gender: " << student.gender << endl;
            cout << "Class: " << student.Class << endl;

            break;
        }
    }

    if (!found) {
        cout << "Student with id " << studentId << " not found." << endl;
    }

    file.close();
}

void GetAllStudents() {
    ifstream file("Slave.txt");
    if (!file.is_open()) {
        cerr << "Could not open file for reading." << endl;
        return;
    }

    Student student;
    int teacherId;
    bool found = false;

    cout << "List of all students:" << endl;
    while (file >> student.Id >> student.firstName >> student.lastName >> student.dateBirth >> student.gender >> student.Class >> teacherId) {
        found = true;

        cout << "Id: " << student.Id << endl;
        cout << "Teacher Id: " << teacherId << endl;
        cout << "First Name: " << student.firstName << endl;
        cout << "Last Name: " << student.lastName << endl;
        cout << "Date of Birth: " << student.dateBirth << endl;
        cout << "Gender: " << student.gender << endl;
        cout << "Class: " << student.Class << endl;
        cout << "-------------------------" << endl;
    }

    if (!found) {
        cout << "No students found." << endl;
    }

    file.close();
}

int CountStudents() {
    std::ifstream file("Slave.txt");
    if (!file.is_open()) {
        std::cerr << "Could not open file for reading." << std::endl;
        return -1;
    }

    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        ++count;
    }

    file.close();

    return count;
}

void UpdateStudent(int studentId) {
    ifstream file("Slave.txt");
    if (!file.is_open()) {
        cerr << "Could not open file for reading." << endl;
        return;
    }

    Student student;
    int teacherId;
    bool found = false;
    vector<pair<Student, int>> students;

    while (file >> student.Id >> student.firstName >> student.lastName >> student.dateBirth >> student.gender >> student.Class >> teacherId) {
        if (student.Id == studentId) {
            found = true;
            cout << "Student found. Please enter new information:" << endl;
            GetInfoStudent(student, teacherId);
            student.Id = studentId;
        }
        students.push_back(make_pair(student, teacherId));
    }

    file.close();

    if (!found) {
        cout << "Student with id " << studentId << " not found." << endl;
        return;
    }

    ofstream fileOut("Slave.txt");
    if (!fileOut.is_open()) {
        cerr << "Could not open file for writing." << endl;
        return;
    }

    for (auto& pair : students) {
        fileOut << pair.first.Id << " "
            << pair.first.firstName << " "
            << pair.first.lastName << " "
            << pair.first.dateBirth << " "
            << pair.first.gender << " "
            << pair.first.Class << " "
            << pair.second << '\n';
    }

    fileOut.close();

    cout << "Student successfully updated." << endl;
}
void DeleteStudent(int studentId) {
    ifstream fileIn("Slave.txt");
    if (!fileIn.is_open()) {
        cerr << "Could not open file for reading." << endl;
        return;
    }

    vector<pair<Student, int>> students;
    Student student;
    int teacherId;

    bool found = false;

    while (fileIn >> student.Id >> student.firstName >> student.lastName >> student.dateBirth >> student.gender >> student.Class >> teacherId) {
        if (student.Id == studentId) {
            found = true;
            cout << "Student found. Deleting..." << endl;
            teacherId = student.Id;
            student.Id = 0;
        }
        students.push_back(make_pair(student, teacherId));
    }

    fileIn.close();

    if (!found) {
        cout << "Student with id " << studentId << " not found." << endl;
        return;
    }

    ofstream fileOut("Slave.txt");
    if (!fileOut.is_open()) {
        cerr << "Could not open file for writing." << endl;
        return;
    }

    for (auto& pair : students) {
        fileOut << pair.first.Id << " "
            << pair.first.firstName << " "
            << pair.first.lastName << " "
            << pair.first.dateBirth << " "
            << pair.first.gender << " "
            << pair.first.Class << " "
            << pair.second << '\n';
    }

    fileOut.close();

    cout << "Student successfully deleted." << endl;
}
