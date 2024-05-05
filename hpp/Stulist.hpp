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

    // 根据学号升序排序
    void sortStudentsByID(string classmanagev);

    // 根据单科成绩降序排序
    void sortStudentsBySubjectScore(string classmanagev);

    // 根据总分降序排序
    void sortStudentsByTotalScore(string classmanagev);

    // 根据平均分降序排序
    void sortStudentsByAverageScore(string classmanagev);

    // 查找同一个班的学生
    Student *findTheSameClassStudents(std::string classmanagev);

    // 展示所有学生
    void showAllStudents();

};

#endif