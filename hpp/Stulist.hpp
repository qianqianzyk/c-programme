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

    // 根据学号查找学生
    void findStudentByID(string classmanagev);

    // 根据姓名查找学生(模糊查找)
    void findStudentsByName(string classmanagev);

    // 根据班级查找学生
    void findStudentsByClass(string classmanagev);

    // 展示所有学生
    void showAllStudents();

};


#endif
