#include <iostream>
#include "Master.h"
#include "Slave.h"
#include "Teacher.h"
#include "Student.h"

using namespace std;

int main()
{
    int choice;
    do {
        cout << "Choose an option: \n1.Add teacher\n2.Get teacher\n3.Update teacher\n4.Delete teacher\n5.Get list of all teachers\n6.Calculate teachers\n7.Add student\n8.Get student\n9.Update student\n10.Delete student\n11.Get list of all students\n12.Calculate students\n13.Exit\n" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << " " << endl;

        int numRecords;
        int numStudents;
        int teacherId;
        int studentId;

        switch (choice) {
        case 1:
        {
            Teacher teacher;
            GetInfoTeacher(teacher);
            InsertTeacher(teacher);
            break;
        }
        case 2:
            cout << "Enter teacher's id to search: ";
            cin >> teacherId;
            FindTeacherById(teacherId);
            break;
        case 3:
            cout << "Enter teacher's id to update: ";
            cin >> teacherId;
            UpdateTeacher(teacherId);
            break;
        case 4:
            cout << "Enter teacher's id to delete: ";
            cin >> teacherId;
            DeleteTeacher(teacherId);
            break;
        case 5:
            GetAllTeachers();
            break;
        case 6:
        {
            numRecords = CountRecords();
            if (numRecords == -1) {
                cout << "An error occurred while trying to count the records." << endl;
            }
            else {
                cout << "Number of teachers: " << numRecords << endl;
            }
            CountStudentsForAllTeachers();
            break;
        }
        case 7:
        {
            Student student;
            GetInfoStudent(student, teacherId);
            InsertStudent(student, teacherId);
            break;
        }
        case 8:
            cout << "Enter student's id to search: ";
            cin >> studentId;
            FindStudentById(studentId);
            break;
        case 9:
            cout << "Enter teacher's id to update: ";
            cin >> studentId;
            UpdateStudent(studentId);
            break;
        case 10:
            cout << "Enter student's id to delete: ";
            cin >> studentId;
            DeleteStudent(studentId);
            break;
        case 11:
            GetAllStudents();
            break;
        case 12:
        {
            numStudents = CountStudents();
            if (numStudents == -1) {
                cout << "An error occurred while trying to count the students." << endl;
            }
            else {
                cout << "Number of students: " << numStudents << endl;
            }
            break;
        }

        case 13:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please choose a valid option." << endl;
            break;
        }
    } while (choice != 13); 

    return 0;
}
