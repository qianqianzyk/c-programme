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

    int choice_1, choice_2, choice_3, choice_4, choice_5, choice_6;

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
                        stulist.addStudentByTeacher(target->getClassManage());
                        goto process2;
                        break;
                    }
                    case 2: {//查询学生信息
                        Menu::howFind();
                        cin >> choice_3;
                        switch (choice_3) {
                            case 1: {//根据学号
                                stulist.findStudentByID(target->getClassManage());
                                goto process2;
                                break;
                            }
                            case 2: {//根据姓名
                                stulist.findStudentsByName(target->getClassManage());
                                goto process2;
                                break;
                            }
                            case 3: {//根据班级
                                stulist.findStudentsByClass(target->getClassManage());
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
                        Menu::howSort();
                        cin >> choice_4;
                        switch (choice_4) {
                            case 1: {//根据学号
                                stulist.sortStudentsByID(target->getClassManage());
                                goto process2;
                                break;
                            }
                            case 2: {//根据单科成绩
                                stulist.sortStudentsBySubjectScore(target->getClassManage());
                                goto process2;
                                break;
                            }
                            case 3: {//根据平均分
                                stulist.sortStudentsByAverageScore(target->getClassManage());
                                goto process2;
                                break;
                            }
                            case 4: {//根据总分
                                stulist.sortStudentsByTotalScore(target->getClassManage());
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
                        stulist.countStudentsScore(target->getClassManage());
                        goto process2;
                        break;
                    }
                    case 5: {//修改学生信息
                        stulist.updateStudentByID(target->getClassManage());
                        goto process2;
                        break;
                    }
                    case 6: {//删除学生信息
                        stulist.deleteStudentByID(target->getClassManage());
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
                Manager *target = manlist.login();
                if (target == nullptr) goto process1;
                process3:
                Menu::managerMenu();
                cin >> choice_5;
                switch (choice_5) {
                    case 1: {//管理员添加学生信息
                        manlist.addStudentByManager(stulist);
                        goto process3;
                        break;
                    }
                    case 2: {//查询学生信息
                        Menu::howFind();
                        cin >> choice_5;
                        switch (choice_5) {
                            case 1: {//根据学号
                                manlist.managerFindStudentByID(stulist);
                                goto process3;
                                break;
                            }
                            case 2: {//根据姓名
                                manlist.managerFindStudentsByName(stulist);
                                goto process3;
                                break;
                            }
                            case 3: {//根据班级
                                manlist.managerFindStudentsByClass(stulist);
                                goto process3;
                                break;
                            }
                            case 4: {
                                goto process3;
                                break;
                            }
                            default: {
                                cout << "请输入有效值!" << endl;
                                goto process3;
                                break;
                            }
                        }
                    }
                    case 3: {//排序
                        Menu::howSort();
                        cin >> choice_6;
                        switch (choice_6) {
                            case 1: {//根据学号
                                manlist.managerSortStudentsByID(stulist);
                                goto process3;
                                break;
                            }
                            case 2: {//根据单科成绩
                                manlist.managerSortStudentsBySubjectScore(stulist);
                                goto process3;
                                break;
                            }
                            case 3: {//根据平均分
                                manlist.managerSortStudentsByAverageScore(stulist);
                                goto process3;
                                break;
                            }
                            case 4: {//根据总分
                                manlist.managerSortStudentsByTotalScore(stulist);
                                goto process3;
                                break;
                            }
                            case 5: {
                                goto process3;
                                break;
                            }
                            default: {
                                cout << "请输入有效值!" << endl;
                                goto process3;
                                break;
                            }
                        }
                    }
                    case 4: {//统计
                        manlist.managerCountStudentsScore(stulist);
                        goto process3;
                        break;
                    }
                    case 5: {//修改学生信息
                        manlist.managerUpdateStudentByID(stulist);
                        goto process3;
                        break;
                    }
                    case 6: {//删除学生信息
                        manlist.managerDeleteStudentByID(stulist);
                        goto process3;
                        break;
                    }
                    case 7: {//添加教师账号
                        manlist.addTeacherByManager();
                        goto process3;
                        break;
                    }
                    case 8: {//删除教师账号
                        manlist.delManager();
                        goto process3;
                        break;
                    }
                    case 9: {//重置账号密码
                        manlist.resetPassword();
                        goto process3;
                        break;
                    }
                    case 10: {//接触账号锁定
                        manlist.setAccount();
                        goto process3;
                        break;
                    }
                    case 11: {
                        goto process1;
                        break;
                    }
                    default: {
                        cout << "请输入有效值!" << endl;
                        goto process3;
                        break;
                    }
                }
                break;
            }
            case 3: {
                Menu::bye();
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