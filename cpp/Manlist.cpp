#include "../hpp/Stulist.hpp"
#include "../hpp/Manlist.hpp"
#include <fstream>

using namespace std;

void Manlist::addManager(string &usernamev, string &passwordv, int &userTypev, int &statusv, string &classmanagev) {
    Manager *p = new Manager(usernamev, passwordv, userTypev, statusv, classmanagev);
    p->next = head->next;
    head->next = p;
    size++;
}

Manager *Manlist::login() {
    system("cls");
    string usernamev, passwordv;
    cout << "请输入账号:" << endl;
    cin >> usernamev;
    cout << "请输入密码:" << endl;
    cin >> passwordv;

    Manager *checkstatus = findManagerByUsername(usernamev);
    if (checkstatus != nullptr && checkstatus->getstatus() == 2) {
        cout << "您的账号已被锁定!请联系管理员." << endl;
        return nullptr;
    }
    int wrongtime = 0;
    Manager *target = nullptr;

    while (wrongtime < 5) {
        target = checkifexist(usernamev, passwordv);
        if (target != nullptr) {
            return target;
        } else {
            wrongtime++;
            cout << "账号或密码错误! 请注意,您还有" << 5 - wrongtime << "次机会!" << endl;
            if (wrongtime == 5) {
                if (lockAccount(usernamev)) {
                    cout << "您已达到最大尝试次数,帐号已被锁定.请联系管理员!" << endl;
                } else {
                    cout << "账号不存在!请联系管理员,并进行注册." << endl;
                }
                return nullptr;
            }
            cout << "请输入账号:" << endl;
            cin >> usernamev;
            cout << "请输入密码:" << endl;
            cin >> passwordv;
        }
    }
    return nullptr;
}

Manager *Manlist::checkifexist(string usernamev, string passwordv) {
    Manager *p = head->next;
    while (p) {
        if (p->getusername() == usernamev && p->getpassword() == passwordv)
            return p;
        p = p->next;
    }
    return nullptr;
}

Manager *Manlist::findManagerByUsername(const string &usernamev) {
    Manager *current = head->next;
    while (current != nullptr) {
        if (current->getusername() == usernamev) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void Manlist::addStudentByManager(Stulist stulistv) {
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
    Student *stu = stulistv.checkifexist(idv);
    if (stu != nullptr) {
        cout << "您添加的学生已经存在!" << endl;
        return;
    }
    stulistv.addStudent(namev, genderv, idv, classNamev, scoresv);
    cout << "添加成功!" << endl;
}

bool Manlist::delmanager(string usernamev) {
    Manager *p = head->next, *pre = head;
    while (p) {
        if (p->getusername() == usernamev) {
            pre->next = p->next;
            delete p;
            size--;
            return true;
        }
        pre = p;
        p = p->next;
    }
    return false;
}

void Manlist::write() {
    ofstream out("../txt/Manager.txt");
    Manager *p = head->next;
    while (p) {
        out << p->getusername() << ' ';
        out << p->getpassword() << ' ';
        out << p->getuserType() << ' ';
        out << p->getstatus() << ' ';
        out << p->getclassmanage() << ' ' << endl;
        p = p->next;
    }
    out.close();
}

bool Manlist::lockAccount(const string &usernamev) {
    Manager *target = findManagerByUsername(usernamev);
    if (target != nullptr) {
        target->setstatus(2);
        write();
        return true;
    }
    return false;
}

void Manlist::showAllManagers() {
    Manager *current = head->next;
    while (current != nullptr) {
        cout << "Username: " << current->getusername() << endl;
        cout << "Password: " << current->getpassword() << endl;
        cout << "User Type: " << current->getuserType() << endl;
        cout << "Status: " << current->getstatus() << endl;
        cout << "ClassManage" << current->getclassmanage() << endl;
        cout << "------------------------" << endl;

        current = current->next;
    }
}
