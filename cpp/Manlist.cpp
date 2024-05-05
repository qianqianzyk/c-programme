#include "../hpp/Stulist.hpp"
#include "../hpp/Manlist.hpp"
#include <vector>
#include <algorithm>
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

void Manlist::managerFindStudentByID(Stulist stulistv) {
    string idv;
    cout << "请输入您要查找学生的学号:" << endl;
    cin >> idv;
    Student *stu = stulistv.checkifexist(idv);
    if (stu == nullptr) {
        cout << "很抱歉,并未找到该学生!" << endl;
        return;
    }
    cout << "----------------------------------" << endl;
    cout << "查询成功!学生信息为:" << endl;
    cout << "姓名:" << stu->getname() << endl;
    cout << "性别:" << stu->getgender() << endl;
    cout << "学号:" << stu->getid() << endl;
    cout << "班级:" << stu->getclassName() << endl;
    cout << "成绩(高数,程C,离散,大物):";
    const int *scores = stu->getscores();
    for (int i = 0; i < 4; ++i) {
        cout << scores[i] << ' ';
    }
    cout << endl;
    cout << "总分:" << stu->gettotalScore() << endl;
    cout << "平均分:" << stu->getaverageScore() << endl;
    cout << "----------------------------------" << endl;
}

void Manlist::managerFindStudentsByName(Stulist stulistv) {
    string namev;
    cout << "请输入您要查找学生的姓名(支持模糊查找):" << endl;
    cin >> namev;

    bool found = false;
    Student *p = stulistv.getHead()->next;
    while (p) {
        if (p->getname().find(namev) != string::npos) {
            found = true;
            cout << "姓名:" << p->getname() << endl;
            cout << "性别:" << p->getgender() << endl;
            cout << "学号:" << p->getid() << endl;
            cout << "班级:" << p->getclassName() << endl;
            cout << "成绩(高数,程C,离散,大物):";
            const int *scores = p->getscores();
            for (int i = 0; i < 4; ++i) {
                cout << scores[i] << ' ';
            }
            cout << endl;
            cout << "总分:" << p->gettotalScore() << endl;
            cout << "平均分:" << p->getaverageScore() << endl;
            cout << "----------------------------------" << endl;
        }
        p = p->next;
    }
    if (!found) {
        cout << "未找到符合条件的学生." << endl;
        return;
    } else {
        cout << "查询成功!找到以上学生." << endl;
        return;
    }
}

void Manlist::managerFindStudentsByClass(Stulist stulistv) {
    string classv;
    cout << "请输入您要查找学生的班级(支持模糊查找):" << endl;
    cin >> classv;

    vector<string> matchClasses;

    Student *p = stulistv.getHead()->next;
    while (p) {
        if (p->getclassName().find(classv) != string::npos) {
            matchClasses.push_back(p->getclassName());
        }
        p = p->next;
    }

    sort(matchClasses.begin(), matchClasses.end());
    matchClasses.erase(unique(matchClasses.begin(), matchClasses.end()), matchClasses.end());

    if (matchClasses.empty()) {
        cout << "未找到符合条件的班级." << endl;
        return;
    }
    cout << "查询成功!找到以下班级：" << endl;
    cout << "如果想要获取学生的详细信息,请使用学号或姓名查询!" << endl;
    cout << "-----------------------------" << endl;
    for (const string &className: matchClasses) {
        cout << "班级: " << className << endl;
        cout << "姓名          学号" << endl;
        p = stulistv.getHead()->next;
        while (p) {
            if (p->getclassName() == className) {
                cout << p->getname() << "         " << p->getid() << endl;
            }
            p = p->next;
        }
        cout << "-----------------------------" << endl;
    }
}

void Manlist::managerSortStudentsByID(Stulist stulistv) {

    Student *students = stulistv.getHead()->next;

    // 插入排序对链表中的学生按学号升序排序
    Student *sortedList = nullptr;
    while (students) {
        // 从未排序链表中移除一个节点
        Student *current = students;
        students = students->next;
        // 将节点插入到已排序链表中的正确位置
        if (!sortedList || current->getid() < sortedList->getid()) {
            // 将节点插入到已排序链表的开头
            current->next = sortedList;
            sortedList = current;
        } else {
            // 在已排序链表中找到插入位置
            Student *temp = sortedList;
            while (temp->next && temp->next->getid() < current->getid()) {
                temp = temp->next;
            }
            // 将节点插入到已排序链表的中间
            current->next = temp->next;
            temp->next = current;
        }
    }

    cout << "排序成功!(按学号升序排序)" << endl;
    cout << "(名次||姓名||性别||学号||成绩.高数||成绩.程C||成绩.离散||成绩.大物||总分||平均分)" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    while (sortedList) {
        cout << number++ << " " << sortedList->getname() << " " << sortedList->getgender() << " " << sortedList->getid()
             << " ";
        const int *scores = sortedList->getscores();
        for (int i = 0; i < 4; ++i) {
            cout << scores[i] << ' ';
        }
        cout << sortedList->gettotalScore() << " " << sortedList->getaverageScore() << endl;
        // 移动到下一个节点并释放当前节点的内存
        Student *temp = sortedList;
        sortedList = sortedList->next;
        delete temp;
    }
    cout << "----------------------------------------------------------------------------------" << endl;
}

void Manlist::managerSortStudentsBySubjectScore(Stulist stulistv) {

    Student *students = stulistv.getHead()->next;

    int index;
    cout << "请输入您要根据哪门成绩进行排序(1:高数 2:程C 3:离散 4:大物 )" << endl;
    cin >> index;
    // 插入排序按指定科目成绩降序排序
    Student *sortedList = nullptr;
    while (students) {
        // 从未排序链表中移除一个节点
        Student *current = students;
        students = students->next;
        // 将节点插入到已排序链表中的正确位置
        if (!sortedList || current->getscores()[index - 1] > sortedList->getscores()[index - 1]) {
            // 将节点插入到已排序链表的开头
            current->next = sortedList;
            sortedList = current;
        } else {
            // 在已排序链表中找到插入位置
            Student *temp = sortedList;
            while (temp->next && temp->next->getscores()[index - 1] > current->getscores()[index - 1]) {
                temp = temp->next;
            }
            // 将节点插入到已排序链表的中间
            current->next = temp->next;
            temp->next = current;
        }
    }

    cout << "排序成功!(按单科成绩降序排序)" << endl;
    cout << "(名次||姓名||性别||学号||成绩.高数||成绩.程C||成绩.离散||成绩.大物||总分||平均分)" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    while (sortedList) {
        cout << number++ << " " << sortedList->getname() << " " << sortedList->getgender() << " " << sortedList->getid()
             << " ";
        const int *scores = sortedList->getscores();
        for (int i = 0; i < 4; ++i) {
            cout << scores[i] << ' ';
        }
        cout << sortedList->gettotalScore() << " " << sortedList->getaverageScore() << endl;
        // 移动到下一个节点并释放当前节点的内存
        Student *temp = sortedList;
        sortedList = sortedList->next;
        delete temp;
    }
    cout << "----------------------------------------------------------------------------------" << endl;
}

void Manlist::managerSortStudentsByTotalScore(Stulist stulistv) {

    Student *students = stulistv.getHead()->next;

    // 插入排序按总分降序排序
    Student *sortedList = nullptr;
    while (students) {
        // 从未排序链表中移除一个节点
        Student *current = students;
        students = students->next;
        // 将节点插入到已排序链表中的正确位置
        if (!sortedList || current->gettotalScore() > sortedList->gettotalScore()) {
            // 将节点插入到已排序链表的开头
            current->next = sortedList;
            sortedList = current;
        } else {
            // 在已排序链表中找到插入位置
            Student *temp = sortedList;
            while (temp->next && temp->next->gettotalScore() > current->gettotalScore()) {
                temp = temp->next;
            }
            // 将节点插入到已排序链表的中间
            current->next = temp->next;
            temp->next = current;
        }
    }

    cout << "排序成功!(按总分降序排序)" << endl;
    cout << "(名次||姓名||性别||学号||成绩.高数||成绩.程C||成绩.离散||成绩.大物||总分||平均分)" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    while (sortedList) {
        cout << number++ << " " << sortedList->getname() << " " << sortedList->getgender() << " " << sortedList->getid()
             << " ";
        const int *scores = sortedList->getscores();
        for (int i = 0; i < 4; ++i) {
            cout << scores[i] << ' ';
        }
        cout << sortedList->gettotalScore() << " " << sortedList->getaverageScore() << endl;
        // 移动到下一个节点并释放当前节点的内存
        Student *temp = sortedList;
        sortedList = sortedList->next;
        delete temp;
    }
    cout << "----------------------------------------------------------------------------------" << endl;
}

void Manlist::managerSortStudentsByAverageScore(Stulist stulistv) {

    Student *students = stulistv.getHead()->next;

    // 插入排序按平均分降序排序
    Student *sortedList = nullptr;
    while (students) {
        // 从未排序链表中移除一个节点
        Student *current = students;
        students = students->next;
        // 将节点插入到已排序链表中的正确位置
        if (!sortedList || current->getaverageScore() > sortedList->getaverageScore()) {
            // 将节点插入到已排序链表的开头
            current->next = sortedList;
            sortedList = current;
        } else {
            // 在已排序链表中找到插入位置
            Student *temp = sortedList;
            while (temp->next && temp->next->getaverageScore() > current->getaverageScore()) {
                temp = temp->next;
            }
            // 将节点插入到已排序链表的中间
            current->next = temp->next;
            temp->next = current;
        }
    }

    cout << "排序成功!(按平均分降序排序)" << endl;
    cout << "(名次||姓名||性别||学号||成绩.高数||成绩.程C||成绩.离散||成绩.大物||总分||平均分)" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    while (sortedList) {
        cout << number++ << " " << sortedList->getname() << " " << sortedList->getgender() << " " << sortedList->getid()
             << " ";
        const int *scores = sortedList->getscores();;
        for (int i = 0; i < 4; ++i) {
            cout << scores[i] << ' ';
        }
        cout << sortedList->gettotalScore() << " " << sortedList->getaverageScore() << endl;
        // 移动到下一个节点并释放当前节点的内存
        Student *temp = sortedList;
        sortedList = sortedList->next;
        delete temp;
    }
    cout << "----------------------------------------------------------------------------------" << endl;
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
