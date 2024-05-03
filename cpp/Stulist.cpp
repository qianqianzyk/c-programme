#include <iostream>
#include <fstream>
#include "../hpp/Stulist.hpp"
#include "../hpp/Manlist.hpp"

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
        if (stu != nullptr){
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
        cout << "很抱歉,您无权操作!请联系管理员."<<endl;
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