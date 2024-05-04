#include <iostream>
#include <fstream>
#include "../hpp/Stulist.hpp"
#include "../hpp/Manlist.hpp"

using namespace std;

void Stulist::addStudent(string &namev, string &genderv, string &idv, string &classNamev, int (&scoresv)[4]) {
    Student *p = new Student(namev, genderv, idv, classNamev);
    p->readscores(scoresv);
    p->next = head->next;
    head->next = p;
    size++;
}

void Stulist::addStudentByTeacher(string classmanagev) {
    string namev, genderv, idv, classNamev;
    int scoresv[4];
    cout << "请输入您要添加学生的姓名:" << endl;
    cin >> namev;
    cout << "请输入您要添加学生的性别:" << endl;
    cin >> genderv;
    cout << "请输入您要添加学生的学号:" << endl;
    cin >> idv;
    cout << "请输入您要添加学生的班级:" << endl;
    cin >> classNamev;
    cout << "请输入您要添加学生的成绩(四门分别是高数,程C,离散,大物.请按顺序填写!):" << endl;
    for (int i = 0; i < 4; ++i) cin >> scoresv[i];
    if (classNamev == classmanagev) {
        Student *stu = checkifexist(idv);
        if (stu != nullptr) {
            cout << "您添加的学生已经存在!" << endl;
            return;
        }
        Student *p = new Student(namev, genderv, idv, classNamev);
        p->readscores(scoresv);
        p->next = head->next;
        head->next = p;
        size++;
        cout << "添加成功!" << endl;
    } else {
        cout << "很抱歉,您无权操作!请联系管理员." << endl;
    }
}

Student *Stulist::checkifexist(string idv) {
    Student *p = head->next;
    while (p) {
        if (p->getid() == idv)
            return p;
        p = p->next;
    }
    return nullptr;
}

void Stulist::write() {
    ofstream out("../txt/Student.txt");
    Student *p = head->next;
    while (p) {
        out << p->getname() << ' ';
        out << p->getgender() << ' ';
        out << p->getid() << ' ';
        out << p->getclassName() << ' ' << endl;
        const int *scores = p->getscores();
        for (int i = 0; i < 4; ++i) {
            out << scores[i] << ' ';
        }
        out << endl;
        p = p->next;
    }
    out.close();
}

void Stulist::findStudentByID(string classmanagev) {
    string idv;
    cout << "请输入您要查找学生的学号:" << endl;
    cin >> idv;
    Student *stu = checkifexist(idv);
    if (stu == nullptr) {
        cout << "很抱歉,并未找到该学生!" << endl;
        return;
    } else {
        if (stu->getclassName() == classmanagev) {
            cout << "----------------------------------" << endl;
            cout << "查询成功!学生信息为:" << endl;
            cout << "姓名:" << stu->getname() << endl;
            cout << "性别:" << stu->getgender() << endl;
            cout << "学号:" << stu->getid() << endl;
            cout << "班级:" << stu->getclassName() << endl;
            cout << "成绩(高数,程C,离散,大物):";
            const int *scores = stu->getscores();
            for (int i = 0; i < 4; ++i) {
                cout << scores[i] << ' ';
            }
            cout << endl;
            cout << "总分:" << stu->gettotalScore() << endl;
            cout << "平均分:" << stu->getaverageScore() << endl;
            cout << "----------------------------------" << endl;
        } else {
            cout << "很抱歉,您无权操作!请联系管理员." << endl;
        }
    }
}

void Stulist::findStudentsByName(string classmanagev) {
    string namev;
    cout << "请输入您要查找学生的姓名(支持模糊查找):" << endl;
    cin >> namev;

    bool found = false;
    Student *p = head->next;
    while (p) {
        if (p->getname().find(namev) != string::npos && p->getclassName() == classmanagev) {
            found = true;
            cout << "姓名:" << p->getname() << endl;
            cout << "性别:" << p->getgender() << endl;
            cout << "学号:" << p->getid() << endl;
            cout << "班级:" << p->getclassName() << endl;
            cout << "成绩(高数,程C,离散,大物):";
            const int *scores = p->getscores();
            for (int i = 0; i < 4; ++i) {
                cout << scores[i] << ' ';
            }
            cout << endl;
            cout << "总分:" << p->gettotalScore() << endl;
            cout << "平均分:" << p->getaverageScore() << endl;
            cout << "----------------------------------" << endl;
        }
        p = p->next;
    }
    if (!found) {
        cout << "未找到符合条件的学生.请确认是否是您班级里的学生!" << endl;
        return;
    } else {
        cout << "查询成功!找到以上学生." << endl;
        return;
    }
}

void Stulist::findStudentsByClass(string classmanagev) {
    cout << "请注意,查询到的为您班级上的学生.如果未查到指定的学生,可能是因为该学生为其他班级上的或者该学生的信息并未填写提交!"
         << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << "查询成功!找到以下学生." << endl;
    cout << "如果想要获取学生的详细信息,请使用学号或姓名查询!" << endl;

    Student *p = head->next;
    while (p) {
        if (p->getclassName() == classmanagev) {
            cout << "姓名          学号" << endl;
            cout << p->getname() << "         " << p->getid() << endl;
        }
        p = p->next;
    }
    cout << "---------------------------------------------------------------------------------------------" << endl;
}

void Stulist::showAllStudents() {
    Student *current = head->next;
    while (current != nullptr) {
        cout << "Name: " << current->getname() << endl;
        cout << "Gender: " << current->getgender() << endl;
        cout << "ID: " << current->getid() << endl;
        cout << "Class: " << current->getclassName() << endl;
        cout << "Scores:";
        const int *scores = current->getscores();
        for (int i = 0; i < 4; ++i) {
            cout << scores[i] << ' ';
        }
        cout << endl;
        cout << "Total Score:" << current->gettotalScore() << endl;
        cout << "Average Score:" << current->getaverageScore() << endl;
        cout << "-----------------------------------------" << endl;

        current = current->next;
    }
}

