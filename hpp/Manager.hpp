#ifndef C_PROGRAMME_MANAGER_H
#define C_PROGRAMME_MANAGER_H

#include <iostream>
#include <cstring>

using namespace std;

class Manager {
public:
    Manager *next;

    Manager(string usernamev = "", string passwordv = "", int userTypev = 1, int statusv = 1, string classmanagev = "")
            : username(usernamev),
              password(passwordv),
              userType(userTypev),
              status(statusv), classmanage(classmanagev) {};//构造函数

    string getUsername() { return username; }//获取账号

    string getPassword() { return password; }//获取密码

    int getUserType() { return userType; }//获取用户类型

    int getStatus() { return status; }//获取账号状态

    string getClassManage() { return classmanage; }//获取权限

    void setStatus(int s) { status = s; }//修改账号状态

    void setPassword(string passwordv) { password = passwordv; }

private:
    string username;//账号
    string password;//密码
    int userType; //用户类型(0:初始化1:老师;2:管理员)
    int status; //账号状态(1:活跃;2:锁定)
    string classmanage; //管理的班级(管理员为0;老师为对应的班级)
};

#endif
