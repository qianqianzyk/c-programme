#ifndef C_PROGRAMME_MANLIST_H
#define C_PROGRAMME_MANLIST_H

#include "../hpp/Manager.hpp"
#include "../hpp/Stulist.hpp"

using namespace std;

class Manlist {
private:
    Manager *head;
    int size;
public:
    Manlist() {
        head = new Manager;
        head->next = nullptr;
        size = 0;
    }

    // 添加账号
    void addManager(string &usernamev, string &passwordv, int &userTypev, int &statusv, string &classmanagev);

    // 登录
    Manager *login();

    // 管理员添加教师账号
    void addTeacherByManager();

    // 检查登录
    Manager *checkIfLogin(string usernamev, string passwordv);

    // 检查账号是否存在
    Manager *checkIfExist(string usernamev);

    // 查找账号是否存在
    Manager *findManagerByUsername(const string &username);

    // 管理员添加学生
    void addStudentByManager(Stulist &stulistv);

    // 管理员根据学号查询学生
    void managerFindStudentByID(Stulist &stulistv);

    // 管理员根据姓名查询学生
    void managerFindStudentsByName(Stulist &stulistv);

    // 管理员根据班级查询学生
    void managerFindStudentsByClass(Stulist &stulistv);

    // 管理员根据学号升序排序学生
    void managerSortStudentsByID(Stulist &stulistv);

    // 管理员根据单科成绩降序排序学生
    void managerSortStudentsBySubjectScore(Stulist &stulistv);

    // 管理员根据总分降序排序学生
    void managerSortStudentsByTotalScore(Stulist &stulistv);

    // 管理员根据个人平均分降序排序学生
    void managerSortStudentsByAverageScore(Stulist &stulistv);

    // 管理员根据班级统计学生成绩
    void managerCountStudentsScore(Stulist &stulistv);

    // 管理员修改学生信息
    void managerUpdateStudentByID(Stulist &stulistv);

    // 管理员删除学生信息
    void managerDeleteStudentByID(Stulist &stulistv);

    // 删除账号
    void delManager();

    // 重置账号密码
    void resetPassword();

    // 写入文件
    void write();

    // 锁定账号
    bool lockAccount(const string &username);

    // 修改账号状态
    void setAccount();

    // 获取所有账号
    void showAllManagers();
};


#endif //C_PROGRAMME_MANLIST_H
