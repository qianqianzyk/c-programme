#ifndef C_PROGRAMME_MANAGER_H
#define C_PROGRAMME_MANAGER_H

#include <iostream>
#include <cstring>

using namespace std;

class Manager {
public:
    Manager *next;

    Manager(string usernamev = "", string passwordv = "", int userTypev = 1, int statusv = 1) : username(usernamev),
                                                                                                password(passwordv),
                                                                                                userType(userTypev),
                                                                                                status(statusv) {};//构造函数
    bool manageridentity();//管理员身份认证

    string getusername() { return username; }//获取账号

    string getpassword() { return password; }//获取密码

    int getuserType() { return userType; }//获取用户类型

    int getstatus() { return status; }//获取账号状态

    void setstatus(int s) { status = s; }//修改账号状态
private:
    string username;//账号
    string password;//密码
    int userType; //用户类型(0:初始化1:老师;2:管理员)
    int status; //账号状态(1:活跃;2:锁定)
};

#endif
