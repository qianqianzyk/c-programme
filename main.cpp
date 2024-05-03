#include <iostream>
#include <fstream>
#include "./hpp/Menu.hpp"
#include "./hpp/Manlist.hpp"
#include "./hpp/Stulist.hpp"

using namespace std;

void processTeacherMenu(Stulist &stulist);

int main() {
    Stulist stulist;
    Manlist manlist;

    ifstream inStudent("../txt/Student.txt");
    ifstream inManager("../txt/Manager.txt");

    // 读取学生信息
    string name, gender, id, className;
    int scores[4];
    while (inStudent >> name >> gender >> id >> className) {
        for (int &score: scores) inStudent >> score;
        stulist.addStudent(name, gender, id, className, scores);
    }
    inStudent.close();

    // 读取管理员信息
    string username, password;
    int userType, status;
    while (inManager >> username >> password >> userType >> status) {
        manlist.addManager(username, password, userType, status);
    }
    inManager.close();

    int choice_1, choice_2;

    while (true) {
        Menu::welcome();

        cin >>
            choice_1;
        switch (choice_1) {
            case 1: {
                Manager *target = manlist.login();
                if (target != nullptr) {
                    processTeacherMenu(stulist);
                }
            }
                break;
            case 2:
// 管理员登录
// 根据管理员用户名和密码登录，并显示管理员功能菜单
                break;
            case 3:

                Menu::bye();

                return 0;
            default:
                cout << "请输入有效值!" <<
                     endl;
        }
    }
    return 0;
}

void processTeacherMenu(Stulist &stulist) {
    int choice;
    while (true) {
        Menu::teacherMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                // 添加学生信息
                // 从键盘读取学生信息并添加到学生列表中
                break;
            case 2:
                // 查询学生信息
                // 根据学号、姓名或班级等条件查询学生信息并显示
                break;
            case 3:
                // 排序学生成绩
                // 根据学号、姓名、成绩等条件对学生信息进行排序并显示
                break;
            case 4:
                // 统计学生成绩
                // 统计学生总分、平均分等信息并显示
                break;
            case 5:
                // 修改学生信息
                // 根据学号或姓名等条件修改学生信息
                break;
            case 6:
                // 删除学生信息
                // 根据学号或姓名等条件删除学生信息
                break;
            case 7:
                return; // 返回上级菜单
            default:
                cout << "请输入有效值!" << endl;
        }
    }
}
