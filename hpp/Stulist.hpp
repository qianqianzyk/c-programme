#ifndef C_PROGRAMME_STULIST_H
#define C_PROGRAMME_STULIST_H

#include <iostream>
#include "../hpp/Student.hpp"

using namespace std;

class Stulist {
private:
    Student *head;
    int size;
public:
    Stulist() {
        head = new Student;
        head->next = nullptr;
        size = 0;
    }

    // 添加学生
    void addStudent(string &namev, string &genderv, string &idv, string &classNamev, int (&scoresv)[4]);

    // 老师添加学生
    void addStudentByTeacher(string classmanagev);

    // 查看学生是否已经存在
    Student *checkifexist(string idv);

    // 写入文件
    void write();

//    // Function to display all students
//    void displayAllStudents() const {
//        Student *current = head;
//        while (current != nullptr) {
//            cout << "Name: " << current->name << ", Gender: " << current->gender << ", ID: " << current->id
//                 << ", Class: " << current->className;
//            cout << ", Scores: ";
//            for (int i = 0; i < 4; ++i) {
//                cout << current->scores[i] << " ";
//            }
//            cout << ", Total Score: " << current->totalScore << ", Average Score: " << current->averageScore << endl;
//            current = current->next;
//        }
//    }
};


#endif
