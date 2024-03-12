#include <iostream>
#include "Teacher.h"
#include "Student.h"

using namespace std;

int main()
{
    int choice;
    do {
        cout << "\nChoose an option: \n1.Add teacher\n2.Get teacher\n3.Update teacher\n4.Delete teacher\n5.Get list of all teachers\n6.Calculate teachers\n7.Add student\n8.Get student\n9.Update student\n10.Delete student\n11.Get list of all students\n12.Calculate students\n13.Exit\n" << endl;
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
            do {
                cout << "Enter teacher's id to search: ";
                cin >> teacherId;
                if (teacherId == 0) {
                    cout << "Invalid Id. Please enter a non-zero Id." << endl;
                }
            } while (teacherId == 0);
            FindTeacherById(teacherId);
            break;
        case 3:
            do {
                cout << "Enter teacher's id to update: ";
                cin >> teacherId;
                if (teacherId == 0) {
                    cout << "Invalid Id. Please enter a non-zero Id." << endl;
                }
            } while (teacherId == 0);
            UpdateTeacher(teacherId);
            break;
        case 4:
            do {
                cout << "Enter teacher's id to delete: ";
                cin >> teacherId;
                if (teacherId == 0) {
                    cout << "Invalid Id. Please enter a non-zero Id." << endl;
                }
            } while (teacherId == 0);
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
            do {
                cout << "Enter student's id to search: ";
                cin >> studentId;
                if (studentId == 0) {
                    cout << "Invalid Id. Please enter a non-zero Id." << endl;
                }
            } while (studentId == 0);
            FindStudentById(studentId);
            break;
        case 9:
            do {
                cout << "Enter student's id to update: ";
                cin >> studentId;
                if (studentId == 0) {
                    cout << "Invalid Id. Please enter a non-zero Id." << endl;
                }
            } while (studentId == 0);
            UpdateStudent(studentId);
            break;
        case 10:
            do {
                cout << "Enter student's id to delete: ";
                cin >> studentId;
                if (studentId == 0) {
                    cout << "Invalid Id. Please enter a non-zero Id." << endl;
                }
            } while (studentId == 0);
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
