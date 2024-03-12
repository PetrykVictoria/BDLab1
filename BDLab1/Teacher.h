#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector> 
#include <string>
#include <map>
#include <regex>
#include "Master.h"
#include "Slave.h"


using namespace std;

void GetInfoTeacher(Teacher& teacher) {

    cout << "Enter teacher's first name: ";
    cin >> teacher.firstName;
    cout << "Enter teacher's last name: ";
    cin >> teacher.lastName;
    cout << "Enter teacher's middle Name: ";
    cin >> teacher.middleName;
    cout << "Enter subject: ";
    cin >> teacher.subject;
}

void InsertTeacher(Teacher& teacher) {
    ifstream fileIn("Master.txt");
    int prevId = 0;
    Teacher lastTeacher;
    vector<Teacher> teachers;

    if (fileIn.is_open()) {
        while (fileIn >> lastTeacher.Id >> lastTeacher.firstName >> lastTeacher.lastName >> lastTeacher.middleName >> lastTeacher.subject) {
            teachers.push_back(lastTeacher);
            if (lastTeacher.Id != 0) {
                prevId = lastTeacher.Id;
            }
        }
        fileIn.close();
    }
    else {
        cerr << "Could not open file for reading." << endl;
        return;
    }

    bool replaced = false;
    for (auto& teacherItem : teachers) {
        if (teacherItem.Id == 0) {
            teacher.Id = prevId + 1;
            teacherItem = teacher;
            replaced = true;
            break;
        }
        prevId = teacherItem.Id;
    }


    if (!replaced) {
        teacher.Id = prevId + 1;
        teachers.push_back(teacher);
    }

    ofstream fileOut("Master.txt");
    if (!fileOut.is_open()) {
        cerr << "Could not open file for writing." << endl;
        return;
    }

    for (auto& teacherItem : teachers) {
        fileOut << teacherItem.Id << " "
            << teacherItem.firstName << " "
            << teacherItem.lastName << " "
            << teacherItem.middleName << " "
            << teacherItem.subject << '\n';
    }

    fileOut.close();

    cout << "Data successfully added" << endl;
}

void FindTeacherById(int teacherId) {
    ifstream file("Master.txt");
    if (!file.is_open()) {
        cerr << "Could not open file for reading." << endl;
        return;
    }

    Teacher teacher;
    bool found = false;

    while (file >> teacher.Id >> teacher.firstName >> teacher.lastName >> teacher.middleName >> teacher.subject) {
        if (teacher.Id == teacherId) {
            found = true;

            cout << "Teacher found:" << endl;
            cout << "Id: " << teacher.Id << endl;
            cout << "First Name: " << teacher.firstName << endl;
            cout << "Last Name: " << teacher.lastName << endl;
            cout << "Middle Name: " << teacher.middleName << endl;
            cout << "Subject: " << teacher.subject << endl;
            break;
        }
    }

    if (!found) {
        cout << "Teacher with id " << teacherId << " not found." << endl;
    }

    file.close();
}
void GetAllTeachers() {
    ifstream file("Master.txt");
    if (!file.is_open()) {
        cerr << "Could not open file for reading." << endl;
        return;
    }

    Teacher teacher;
    bool found = false;

    cout << "List of all teachers:" << endl;
    while (file >> teacher.Id >> teacher.firstName >> teacher.lastName >> teacher.middleName >> teacher.subject) {
        if (teacher.Id == 0) {
            continue;
        }
        found = true;

        cout << "Id: " << teacher.Id << endl;
        cout << "First Name: " << teacher.firstName << endl;
        cout << "Last Name: " << teacher.lastName << endl;
        cout << "Middle Name: " << teacher.middleName << endl;
        cout << "Subject: " << teacher.subject << endl;
        cout << "-------------------------" << endl;
    }

    if (!found) {
        cout << "No teachers found." << endl;
    }

    file.close();
}


int CountRecords() {
    std::ifstream file("Master.txt");
    if (!file.is_open()) {
        std::cerr << "Could not open file for reading." << std::endl;
        return -1;
    }
        int count = 0;
    Teacher teacher;
    while (file >> teacher.Id >> teacher.firstName >> teacher.lastName >> teacher.middleName >> teacher.subject) {
        if (teacher.Id != 0) {
            ++count;
        }
    }

    file.close();

    return count;
}


void CountStudentsForAllTeachers() {
    ifstream teacherFile("Master.txt");
    ifstream studentFile("Slave.txt");

    if (!teacherFile.is_open() || !studentFile.is_open()) {
        cerr << "Could not open file for reading." << endl;
        return;
    }

    Teacher teacher;
    Student student;
    map<int, int> teacherStudentCount;

    while (teacherFile >> teacher.Id >> teacher.firstName >> teacher.lastName >> teacher.middleName >> teacher.subject) {
        if (teacher.Id != 0) {
            teacherStudentCount[teacher.Id] = 0;
        }
    }

    int currentTeacherId;
    while (studentFile >> student.Id >> student.firstName >> student.lastName >> student.gender >> student.Class >> currentTeacherId) {
        if (student.Id == 0) {
            continue; // Skip students with ID 0
        }
        if (teacherStudentCount.count(currentTeacherId) > 0) {
            ++teacherStudentCount[currentTeacherId];
        }
    }

    teacherFile.close();
    studentFile.close();

    for (const auto& pair : teacherStudentCount) {
        if (pair.first != 0) { // Skip teachers with ID 0
            cout << "Teacher with id " << pair.first << " has " << pair.second << " students." << endl;
        }
    }
}


void UpdateTeacher(int teacherId) {
    ifstream file("Master.txt");
    if (!file.is_open()) {
        cerr << "Could not open file for reading." << endl;
        return;
    }

    Teacher teacher;
    bool found = false;
    vector<Teacher> teachers;

    while (file >> teacher.Id >> teacher.firstName >> teacher.lastName >> teacher.middleName >> teacher.subject) {
        if (teacher.Id == teacherId) {
            found = true;
            cout << "Teacher found. Please enter new information:" << endl;
            GetInfoTeacher(teacher);
            teacher.Id = teacherId;
        }
        teachers.push_back(teacher);
    }

    file.close();

    if (!found) {
        cout << "Teacher with id " << teacherId << " not found." << endl;
        return;
    }

    ofstream fileOut("Master.txt");
    if (!fileOut.is_open()) {
        cerr << "Could not open file for writing." << endl;
        return;
    }

    for (Teacher& teacher : teachers) {
        fileOut << teacher.Id << " "
            << teacher.firstName << " "
            << teacher.lastName << " "
            << teacher.middleName << " "
            << teacher.subject << '\n';
    }

    fileOut.close();

    cout << "Teacher successfully updated." << endl;
}

void DeleteTeacher(int teacherId) {
    ifstream fileIn("Master.txt");
    if (!fileIn.is_open()) {
        cerr << "Could not open file for reading." << endl;
        return;
    }

    vector<Teacher> teachers;
    Teacher teacher;

    bool found = false;

    // Read all teachers from the file and find the one to delete
    while (fileIn >> teacher.Id >> teacher.firstName >> teacher.lastName >> teacher.middleName >> teacher.subject) {
        if (teacher.Id == teacherId) {
            found = true;
            cout << "Teacher found. Deleting..." << endl;
            // Replace the teacher's ID with 0 to mark it as deleted
            teacher.Id = 0;
        }
        teachers.push_back(teacher);
    }

    fileIn.close();

    if (!found) {
        cout << "Teacher with id " << teacherId << " not found." << endl;
        return;
    }

    ofstream fileOut("Master.txt");
    if (!fileOut.is_open()) {
        cerr << "Could not open file for writing." << endl;
        return;
    }

    for (Teacher& teacher : teachers) {
        fileOut << teacher.Id << " "
            << teacher.firstName << " "
            << teacher.lastName << " "
            << teacher.middleName << " "
            << teacher.subject << '\n';
    }

    fileOut.close();

    cout << "Teacher successfully deleted." << endl;

        // Now delete all students of the deleted teacher
        ifstream studentFileIn("Slave.txt");
    if (!studentFileIn.is_open()) {
        cerr << "Could not open file for reading." << endl;
        return;
    }

    vector<Student> students;
    Student student;

    // Read all students from the file and find the ones to delete
    while (studentFileIn >> student.Id >> student.firstName >> student.lastName >> student.gender >> student.Class >> student.teacherId) {
        if (student.teacherId == teacherId) {
            // Replace the student's ID with 0 to mark it as deleted
            student.Id = 0;
        }
        students.push_back(student);
    }

    studentFileIn.close();

    ofstream studentFileOut("Slave.txt");
    if (!studentFileOut.is_open()) {
        cerr << "Could not open file for writing." << endl;
        return;
    }

    for (Student& student : students) {
        studentFileOut << student.Id << " "
            << student.firstName << " "
            << student.lastName << " "
            << student.gender << " "
            << student.Class << " "
            << student.teacherId << '\n';
    }

    studentFileOut.close();

    cout << "Students of the deleted teacher successfully deleted." << endl;
}







