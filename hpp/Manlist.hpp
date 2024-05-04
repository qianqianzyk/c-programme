#ifndef C_PROGRAMME_MANLIST_H
#define C_PROGRAMME_MANLIST_H

#include "../hpp/Manager.hpp"

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

    // 添加老师账号
    void addManager(string &usernamev, string &passwordv, int &userTypev, int &statusv, string &classmanagev);

    // 登录
    Manager *login();

    // 检查账号是否存在
    Manager *checkifexist(string usernamev, string passwordv);

    // 查找账号是否存在
    Manager *findManagerByUsername(const string &username);

    // 删除账号
    bool delmanager(string usernamev);

    // 写入文件
    void write();

    // 锁定账号
    bool lockAccount(const string &username);

    // 获取所有账号
    void showAllManagers();
};


#endif //C_PROGRAMME_MANLIST_H
