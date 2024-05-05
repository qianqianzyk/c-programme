#include <iostream>
#include <fstream>
#include "./hpp/Menu.hpp"
#include "./hpp/Manlist.hpp"
#include "./hpp/Stulist.hpp"

using namespace std;

int main() {
    Stulist stulist;
    Manlist manlist;

    ifstream inStudent("../txt/Student.txt");
    ifstream inManager("../txt/Manager.txt");

    // 读取学生信息
    string name, gender, id, className;
    int scores[4];
    while (inStudent >> name >> gender >> id >> className) {
        for (int i = 0; i < 4; ++i) inStudent >> scores[i];
        stulist.addStudent(name, gender, id, className, scores);
    }
    inStudent.close();

    // 读取管理员信息
    string username, password, classmanage;
    int userType, status;
    while (inManager >> username >> password >> userType >> status >> classmanage) {
        manlist.addManager(username, password, userType, status, classmanage);
    }
    inManager.close();

    int choice_1, choice_2, choice_3, choice_4;

    process1:
    Menu::welcome();
    while (cin >> choice_1) {
        switch (choice_1) {
            case 1: {
                Manager *target = manlist.login();
                if (target == nullptr) goto process1;
                process2:
                Menu::teacherMenu();
                cin >> choice_2;
                switch (choice_2) {
                    case 1: {//添加学生信息
                        stulist.addStudentByTeacher(target->getclassmanage());
                        goto process2;
                        break;
                    }
                    case 2: {//查询学生信息
                        Menu::howfind();
                        cin >> choice_3;
                        switch (choice_3) {
                            case 1: {//根据学号
                                stulist.findStudentByID(target->getclassmanage());
                                goto process2;
                                break;
                            }
                            case 2: {//根据姓名
                                stulist.findStudentsByName(target->getclassmanage());
                                goto process2;
                                break;
                            }
                            case 3: {//根据班级
                                stulist.findStudentsByClass(target->getclassmanage());
                                goto process2;
                                break;
                            }
                            case 4: {
                                goto process2;
                                break;
                            }
                            default: {
                                cout << "请输入有效值!" << endl;
                                goto process2;
                                break;
                            }

                        }
                    }
                    case 3: {//排序
                        Menu::howsort();
                        cin >> choice_4;
                        switch (choice_4) {
                            case 1: {//根据学号
                                stulist.sortStudentsByID(target->getclassmanage());
                                goto process2;
                                break;
                            }
                            case 2: {//根据单科成绩
                                stulist.sortStudentsBySubjectScore(target->getclassmanage());
                                goto process2;
                                break;
                            }
                            case 3: {//根据平均分
                                stulist.sortStudentsByAverageScore(target->getclassmanage());
                                goto process2;
                                break;
                            }
                            case 4: {//根据总分
                                stulist.sortStudentsByTotalScore(target->getclassmanage());
                                goto process2;
                                break;
                            }
                            case 5: {
                                goto process2;
                                break;
                            }
                            default: {
                                cout << "请输入有效值!" << endl;
                                goto process2;
                                break;
                            }
                        }
                    }
                    case 4: {//统计学生成绩
                        stulist.countStudentsScore(target->getclassmanage());
                        goto process2;
                        break;
                    }
                    case 7: {
                        goto process1;
                        break;
                    }
                    default: {
                        cout << "请输入有效值!" << endl;
                        goto process2;
                        break;
                    }
                }
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                Menu::bye();
                stulist.write();
                manlist.write();
                return 0;
                break;
            }
            default: {
                cout << "请输入有效值!" << endl;
                goto process1;
                break;
            }
        }
    }
    return 0;
}