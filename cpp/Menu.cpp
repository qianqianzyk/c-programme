#include "../hpp/Menu.hpp"

using namespace std;

void Menu::welcome() {
    clearScreen();
    cout << "=========Menu==========" << endl;
    cout << "|欢迎进入学生成绩管理系统！  |" << endl;
    cout << "|1.教师登录              |" << endl;
    cout << "|2.管理员登陆            |" << endl;
    cout << "|3.退出系统              |" << endl;
    cout << "========================" << endl;
    cout << "请输入:";
}

void Menu::teacherMenu() {
    clearScreen();
    cout << "======教师功能菜单=======" << endl;
    cout << "|1. 添加学生信息         |" << endl;
    cout << "|2. 查询学生信息         |" << endl;
    cout << "|3. 排序学生成绩         |" << endl;
    cout << "|4. 统计学生成绩         |" << endl;
    cout << "|5. 修改学生信息         |" << endl;
    cout << "|6. 删除学生信息         |" << endl;
    cout << "|7. 返回上级菜单         |" << endl;
    cout << "=======================" << endl;
    cout << "请输入:";
}

void Menu::managerMenu() {
    clearScreen();
    cout << "=====管理员功能菜单=====" << endl;
    cout << "|1.  添加学生信息        |" << endl;
    cout << "|2.  查询学生信息        |" << endl;
    cout << "|3.  排序学生成绩        |" << endl;
    cout << "|4.  统计学生成绩        |" << endl;
    cout << "|5.  修改学生信息        |" << endl;
    cout << "|6.  删除学生信息        |" << endl;
    cout << "|7.  添加教师账号        |" << endl;
    cout << "|8.  删除教师账号        |" << endl;
    cout << "|9.  重置账号密码        |" << endl;
    cout << "|10. 修改账号状态        |" << endl;
    cout << "|11. 返回上级菜单        |" << endl;
    cout << "=======================" << endl;
    cout << "请输入:";
}

void Menu::bye() {
    clearScreen();
    cout << "=======================" << endl;
    cout << "|感谢您使用学生成绩管理系统~ |" << endl;
    cout << "========================" << endl;
}

void Menu::howFind() {
    clearScreen();
    cout << "=======================" << endl;
    cout << "|1. 根据学生学号         |" << endl;
    cout << "|2. 根据学生姓名         |" << endl;
    cout << "|3. 根据学生班级         |" << endl;
    cout << "|4. 返回上级菜单         |" << endl;
    cout << "=======================" << endl;
    cout << "请输入:";
}

void Menu::howSort() {
    clearScreen();
    cout << "======================" << endl;
    cout << "|1. 根据学生学号         |" << endl;
    cout << "|2. 根据单科成绩         |" << endl;
    cout << "|3. 根据平均成绩         |" << endl;
    cout << "|4. 根据学生总分         |" << endl;
    cout << "|5. 返回上级菜单         |" << endl;
    cout << "=======================" << endl;
    cout << "请输入:";
}