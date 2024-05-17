#include "../hpp/Stulist.hpp"
#include "../hpp/Manlist.hpp"
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>

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
    int userTypev;
    cout << "请输入您的身份(1:教师 2:管理员):" << endl;
    cin >> userTypev;
    cout << "请输入账号:" << endl;
    cin >> usernamev;
    cout << "请输入密码:" << endl;
    cin >> passwordv;

    Manager *checkstatus = findManagerByUsername(usernamev);
    if (userTypev == 2 && checkstatus->getUserType() != 2) {
        cout << "很抱歉,您不是管理员!" << endl;
        return nullptr;
    }
    if (checkstatus != nullptr && checkstatus->getStatus() == 2) {
        cout << "您的账号已被锁定!请联系管理员." << endl;
        return nullptr;
    }
    int wrongtime = 0;
    Manager *target = nullptr;

    while (wrongtime < 5) {
        target = checkIfLogin(usernamev, passwordv);
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
    write();
    return nullptr;
}

void Manlist::addTeacherByManager() {
    string usernamev, passwordv, classmanagev;
    cout << "请输入您要添加教师账号的用户名:" << endl;
    cin >> usernamev;
    cout << "请输入您要添加教师账号的密码:" << endl;
    cin >> passwordv;
    cout << "请输入您要添加教师账号的权限:" << endl;
    cin >> classmanagev;
    Manager *man = checkIfExist(usernamev);
    if (man != nullptr) {
        cout << "您添加的教师账号已经存在!" << endl;
        return;
    }
    Manager *p = new Manager(usernamev, passwordv, 1, 1, classmanagev);
    p->next = head->next;
    head->next = p;
    size++;
    write();
    cout << "添加成功!" << endl;
}

Manager *Manlist::checkIfLogin(string usernamev, string passwordv) {
    Manager *p = head->next;
    while (p) {
        if (p->getUsername() == usernamev && p->getPassword() == passwordv)
            return p;
        p = p->next;
    }
    return nullptr;
}

Manager *Manlist::checkIfExist(string usernamev) {
    Manager *p = head->next;
    while (p) {
        if (p->getUsername() == usernamev)
            return p;
        p = p->next;
    }
    return nullptr;
}

Manager *Manlist::findManagerByUsername(const string &usernamev) {
    Manager *current = head->next;
    while (current != nullptr) {
        if (current->getUsername() == usernamev) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void Manlist::addStudentByManager(Stulist &stulistv) {
    string namev, genderv, idv, classNamev;
    int scoresv[4];
    cout << "请输入您要添加学生的姓名:" << endl;
    cin >> namev;
    cout << "请输入您要添加学生的性别:" << endl;
    cin >> genderv;
    if (!(genderv == "男" || genderv == "女")){
        cout << "性别输入无效!" << endl;
        return;
    }
    cout << "请输入您要添加学生的学号:" << endl;
    cin >> idv;
    if (!(idv.length() == 12 && all_of(idv.begin(), idv.end(), ::isdigit))){
        cout << "学号输入无效!请重新输入(12位数字)." << endl;
        return;
    }
    cout << "请输入您要添加学生的班级:" << endl;
    cin >> classNamev;
    cout << "请输入您要添加学生的成绩(四门分别是高数,程C,离散,大物.请按顺序填写!):" << endl;
    for (int i = 0; i < 4; ++i) cin >> scoresv[i];
    Student *stu = stulistv.checkIfExist(idv);
    if (stu != nullptr) {
        cout << "您添加的学生已经存在!" << endl;
        return;
    }
    stulistv.addStudent(namev, genderv, idv, classNamev, scoresv);
    stulistv.write();
    cout << "添加成功!" << endl;
    cout << "姓名:" << namev << endl;
    cout << "性别:" << genderv << endl;
    cout << "学号:" << idv << endl;
    cout << "班级:" << classNamev << endl;
    cout << "成绩(高数,程C,离散,大物):";
    for (int i = 0; i < 4; ++i) {
        cout << scoresv[i] << ' ';
    }
    cout << endl;
    cout << "----------------------------------" << endl;
}

void Manlist::managerFindStudentByID(Stulist &stulistv) {
    string idv;
    cout << "请输入您要查找学生的学号:" << endl;
    cin >> idv;
    Student *stu = stulistv.checkIfExist(idv);
    if (stu == nullptr) {
        cout << "很抱歉,并未找到该学生!" << endl;
        return;
    }
    cout << "----------------------------------" << endl;
    cout << "查询成功!学生信息为:" << endl;
    cout << "姓名:" << stu->getName() << endl;
    cout << "性别:" << stu->getGender() << endl;
    cout << "学号:" << stu->getId() << endl;
    cout << "班级:" << stu->getClassName() << endl;
    cout << "成绩(高数,程C,离散,大物):";
    const int *scores = stu->getScores();
    for (int i = 0; i < 4; ++i) {
        cout << scores[i] << ' ';
    }
    cout << endl;
    cout << "总分:" << stu->getTotalScore() << endl;
    cout << "平均分:" << stu->getAverageScore() << endl;
    cout << "----------------------------------" << endl;
}

void Manlist::managerFindStudentsByName(Stulist &stulistv) {
    string namev;
    cout << "请输入您要查找学生的姓名(支持模糊查找):" << endl;
    cin >> namev;

    bool found = false;
    Student *p = stulistv.getHead()->next;
    while (p) {
        if (p->getName().find(namev) != string::npos) {
            found = true;
            cout << "姓名:" << p->getName() << endl;
            cout << "性别:" << p->getGender() << endl;
            cout << "学号:" << p->getId() << endl;
            cout << "班级:" << p->getClassName() << endl;
            cout << "成绩(高数,程C,离散,大物):";
            const int *scores = p->getScores();
            for (int i = 0; i < 4; ++i) {
                cout << scores[i] << ' ';
            }
            cout << endl;
            cout << "总分:" << p->getTotalScore() << endl;
            cout << "平均分:" << p->getAverageScore() << endl;
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

void Manlist::managerFindStudentsByClass(Stulist &stulistv) {
    string classv;
    cout << "请输入您要查找学生的班级(支持模糊查找):" << endl;
    cin >> classv;

    vector<string> matchClasses;

    Student *p = stulistv.getHead()->next;
    while (p) {
        if (p->getClassName().find(classv) != string::npos) {
            matchClasses.push_back(p->getClassName());
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
            if (p->getClassName() == className) {
                cout << p->getName() << "         " << p->getId() << endl;
            }
            p = p->next;
        }
        cout << "-----------------------------" << endl;
    }
}

void Manlist::managerSortStudentsByID(Stulist &stulistv) {
    Stulist *s = new Stulist(stulistv);
    Student *students = s->getHead()->next;
    // 插入排序对链表中的学生按学号升序排序
    Student *sortedList = nullptr;
    while (students) {
        // 从未排序链表中移除一个节点
        Student *current = students;
        students = students->next;
        // 将节点插入到已排序链表中的正确位置
        if (!sortedList || current->getId() < sortedList->getId()) {
            // 将节点插入到已排序链表的开头
            current->next = sortedList;
            sortedList = current;
        } else {
            // 在已排序链表中找到插入位置
            Student *temp = sortedList;
            while (temp->next && temp->next->getId() < current->getId()) {
                temp = temp->next;
            }
            // 将节点插入到已排序链表的中间
            current->next = temp->next;
            temp->next = current;
        }
    }

    cout << "排序成功!(按学号升序排序)" << endl;
    cout << "(名次||姓名||性别||学号||班级||成绩.高数||成绩.程C||成绩.离散||成绩.大物||总分||平均分)" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    while (sortedList) {
        cout << number++ << " " << sortedList->getName() << " " << sortedList->getGender() << " " << sortedList->getId()
             << " " << sortedList->getClassName() << " ";
        const int *scores = sortedList->getScores();
        for (int i = 0; i < 4; ++i) {
            cout << scores[i] << ' ';
        }
        cout << sortedList->getTotalScore() << " " << sortedList->getAverageScore() << endl;
        // 移动到下一个节点并释放当前节点的内存
        Student *temp = sortedList;
        sortedList = sortedList->next;
        delete temp;
    }
    cout << "----------------------------------------------------------------------------------" << endl;
}

void Manlist::managerSortStudentsBySubjectScore(Stulist &stulistv) {
    Stulist *s = new Stulist(stulistv);
    Student *students = s->getHead()->next;
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
        if (!sortedList || current->getScores()[index - 1] > sortedList->getScores()[index - 1]) {
            // 将节点插入到已排序链表的开头
            current->next = sortedList;
            sortedList = current;
        } else {
            // 在已排序链表中找到插入位置
            Student *temp = sortedList;
            while (temp->next && temp->next->getScores()[index - 1] > current->getScores()[index - 1]) {
                temp = temp->next;
            }
            // 将节点插入到已排序链表的中间
            current->next = temp->next;
            temp->next = current;
        }
    }

    cout << "排序成功!(按单科成绩降序排序)" << endl;
    cout << "(名次||姓名||性别||学号||班级||成绩.高数||成绩.程C||成绩.离散||成绩.大物||总分||平均分)" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    while (sortedList) {
        cout << number++ << " " << sortedList->getName() << " " << sortedList->getGender() << " " << sortedList->getId()
             << " " << sortedList->getClassName() << " ";
        const int *scores = sortedList->getScores();
        for (int i = 0; i < 4; ++i) {
            cout << scores[i] << ' ';
        }
        cout << sortedList->getTotalScore() << " " << sortedList->getAverageScore() << endl;
        // 移动到下一个节点并释放当前节点的内存
        Student *temp = sortedList;
        sortedList = sortedList->next;
        delete temp;
    }
    cout << "----------------------------------------------------------------------------------" << endl;
}

void Manlist::managerSortStudentsByTotalScore(Stulist &stulistv) {
    Stulist *s = new Stulist(stulistv);
    Student *students = s->getHead()->next;
    // 插入排序按总分降序排序
    Student *sortedList = nullptr;
    while (students) {
        // 从未排序链表中移除一个节点
        Student *current = students;
        students = students->next;
        // 将节点插入到已排序链表中的正确位置
        if (!sortedList || current->getTotalScore() > sortedList->getTotalScore()) {
            // 将节点插入到已排序链表的开头
            current->next = sortedList;
            sortedList = current;
        } else {
            // 在已排序链表中找到插入位置
            Student *temp = sortedList;
            while (temp->next && temp->next->getTotalScore() > current->getTotalScore()) {
                temp = temp->next;
            }
            // 将节点插入到已排序链表的中间
            current->next = temp->next;
            temp->next = current;
        }
    }

    cout << "排序成功!(按总分降序排序)" << endl;
    cout << "(名次||姓名||性别||学号||班级||成绩.高数||成绩.程C||成绩.离散||成绩.大物||总分||平均分)" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    while (sortedList) {
        cout << number++ << " " << sortedList->getName() << " " << sortedList->getGender() << " " << sortedList->getId()
             << " " << sortedList->getClassName() << " ";
        const int *scores = sortedList->getScores();
        for (int i = 0; i < 4; ++i) {
            cout << scores[i] << ' ';
        }
        cout << sortedList->getTotalScore() << " " << sortedList->getAverageScore() << endl;
        // 移动到下一个节点并释放当前节点的内存
        Student *temp = sortedList;
        sortedList = sortedList->next;
        delete temp;
    }
    cout << "----------------------------------------------------------------------------------" << endl;
}

void Manlist::managerSortStudentsByAverageScore(Stulist &stulistv) {
    Stulist *s = new Stulist(stulistv);
    Student *students = s->getHead()->next;
    // 插入排序按平均分降序排序
    Student *sortedList = nullptr;
    while (students) {
        // 从未排序链表中移除一个节点
        Student *current = students;
        students = students->next;
        // 将节点插入到已排序链表中的正确位置
        if (!sortedList || current->getAverageScore() > sortedList->getAverageScore()) {
            // 将节点插入到已排序链表的开头
            current->next = sortedList;
            sortedList = current;
        } else {
            // 在已排序链表中找到插入位置
            Student *temp = sortedList;
            while (temp->next && temp->next->getAverageScore() > current->getAverageScore()) {
                temp = temp->next;
            }
            // 将节点插入到已排序链表的中间
            current->next = temp->next;
            temp->next = current;
        }
    }

    cout << "排序成功!(按平均分降序排序)" << endl;
    cout << "(名次||姓名||性别||学号||班级||成绩.高数||成绩.程C||成绩.离散||成绩.大物||总分||平均分)" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    while (sortedList) {
        cout << number++ << " " << sortedList->getName() << " " << sortedList->getGender() << " " << sortedList->getId()
             << " " << sortedList->getClassName() << " ";
        const int *scores = sortedList->getScores();;
        for (int i = 0; i < 4; ++i) {
            cout << scores[i] << ' ';
        }
        cout << sortedList->getTotalScore() << " " << sortedList->getAverageScore() << endl;
        // 移动到下一个节点并释放当前节点的内存
        Student *temp = sortedList;
        sortedList = sortedList->next;
        delete temp;
    }
    cout << "----------------------------------------------------------------------------------" << endl;
}

void Manlist::managerCountStudentsScore(Stulist &stulistv) {
    Stulist *s = new Stulist(stulistv);
    Student *students = s->getHead()->next;

    map<string, vector<Student *>> classStudentsMap;
    while (students) {
        string className = students->getClassName();
        classStudentsMap[className].push_back(students);
        students = students->next;
    }

    cout << "统计成功!" << endl;
    cout << "-----------------------------" << endl;

    vector<pair<string, double>> classAverages;
    for (auto &pair: classStudentsMap) {
        string className = pair.first;
        vector<Student *> &classStudents = pair.second;

        double totalAverage = 0.0;
        int number = classStudents.size();

        for (Student *student: classStudents) {
            totalAverage += student->getTotalScore();
        }
        totalAverage /= number;

        classAverages.push_back(make_pair(className, totalAverage));
    }

    sort(classAverages.begin(), classAverages.end(), [](const pair<string, double> &a, const pair<string, double> &b) {
        return a.second > b.second;
    });

    int rank = 1;
    for (const auto &classAverage: classAverages) {
        cout << "班级排名: " << rank++ << ". " << classAverage.first << "  平均分: " << classAverage.second << endl;
    }

    cout << "-----------------------------" << endl;

    for (auto &pair: classStudentsMap) {
        string className = pair.first;
        vector<Student *> &classStudents = pair.second;

        Student *sortedList = nullptr;
        for (Student *current: classStudents) {
            if (!sortedList || current->getTotalScore() > sortedList->getTotalScore()) {
                current->next = sortedList;
                sortedList = current;
            } else {
                Student *temp = sortedList;
                while (temp->next && temp->next->getTotalScore() > current->getTotalScore()) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
        }

        cout << className << "班学生成绩:" << endl;
        int number = 0;
        double totalAverage = 0.0;
        int numAbove60[4] = {0};
        double totalSubjectScores[4] = {0};

        while (sortedList) {
            const int *scores = sortedList->getScores();
            for (int i = 0; i < 4; ++i) {
                totalSubjectScores[i] += scores[i];
                if (scores[i] > 60) {
                    numAbove60[i]++;
                }
            }
            totalAverage += sortedList->getTotalScore();

            Student *temp = sortedList;
            sortedList = sortedList->next;
            delete temp;
            number++;
        }
        cout << "班级总人数:" << number << endl << endl;
        cout << "各科成绩平均分:" << endl;
        const char *subjectNames[4] = {"高数", "程C", "离散", "大物"};
        for (int i = 0; i < 4; ++i) {
            cout << subjectNames[i] << ": " << totalSubjectScores[i] / (number * 1.0) << endl;
        }
        cout << endl;
        cout << "各科及格的人数:" << endl;
        for (int i = 0; i < 4; ++i) {
            cout << subjectNames[i] << ": " << numAbove60[i] << endl;
        }
        cout << endl;
        cout << "班级平均分:" << totalAverage / (number * 1.0) << endl;
        cout << "-----------------------------" << endl;
    }
}

void Manlist::managerUpdateStudentByID(Stulist &stulistv) {
    string idv;
    cout << "请输入您要修改学生信息的学号:" << endl;
    cin >> idv;
    Student *stu = stulistv.checkIfExist(idv);
    if (stu == nullptr) {
        cout << "很抱歉，并未找到该学生!" << endl;
        return;
    }
    cout << "----------------------------------" << endl;
    cout << "当前学生信息为:" << endl;
    cout << "姓名:" << stu->getName() << endl;
    cout << "性别:" << stu->getGender() << endl;
    cout << "学号:" << stu->getId() << endl;
    cout << "班级:" << stu->getClassName() << endl;
    cout << "成绩(高数,程C,离散,大物):";
    const int *scores = stu->getScores();
    for (int i = 0; i < 4; ++i) {
        cout << scores[i] << ' ';
    }
    cout << endl;
    cout << "总分:" << stu->getTotalScore() << endl;
    cout << "平均分:" << stu->getAverageScore() << endl;
    cout << "----------------------------------" << endl;

    cout << "请输入修改后的信息(注意:如果信息不变请输入原来的!):" << endl;
    string namev, genderv, classNamev;
    int scoresv[4];
    cout << "姓名:" << endl;
    cin >> namev;
    cout << "性别:" << endl;
    cin >> genderv;
    if (!(genderv == "男" || genderv == "女")){
        cout << "性别输入无效!" << endl;
        return;
    }
    cout << "班级:" << endl;
    cin >> classNamev;
    cout << "成绩(高数,程C,离散,大物):" << endl;
    for (int i = 0; i < 4; ++i) cin >> scoresv[i];

    stu->setName(namev);
    stu->setGender(genderv);
    stu->setClassName(classNamev);
    stu->readScores(scoresv);

    stulistv.write();
    cout << "学生信息修改成功!" << endl;
    cout << "姓名:" << stu->getName() << endl;
    cout << "性别:" << stu->getGender() << endl;
    cout << "学号:" << stu->getId() << endl;
    cout << "班级:" << stu->getClassName() << endl;
    cout << "成绩(高数,程C,离散,大物):";
    for (int i = 0; i < 4; ++i) {
        cout << scores[i] << ' ';
    }
    cout << endl;
    cout << "----------------------------------" << endl;
}

void Manlist::managerDeleteStudentByID(Stulist &stulistv) {
    string idv;
    cout << "请输入您要删除学生信息的学号:" << endl;
    cin >> idv;

    Student *current = stulistv.getHead()->next;
    Student *pre = nullptr;
    while (current != nullptr) {
        if (current->getId() == idv) {
            if (pre == nullptr) {
                stulistv.getHead()->next = current->next;
            } else {
                pre->next = current->next;
            }
            delete current;
            stulistv.write();
            cout << "成功删除学生信息!" << endl;
            return;
        }
        pre = current;
        current = current->next;
    }
    cout << "很抱歉，并未找到该学生!" << endl;
}


void Manlist::delManager() {
    string usernamev;
    cout << "请输入您要删除教师账号的用户名:" << endl;
    cin >> usernamev;
    Manager *p = head->next, *pre = head;
    while (p) {
        if (p->getUsername() == usernamev) {
            pre->next = p->next;
            delete p;
            size--;
            write();
            cout << "删除成功!" << endl;
            return;
        }
        pre = p;
        p = p->next;
    }
    cout << "未找到该教师账号!" << endl;
}

void Manlist::resetPassword() {
    string usernamev;
    cout << "请输入您要重置教师账号的用户名:" << endl;
    cin >> usernamev;
    Manager *man = checkIfExist(usernamev);
    if (man == nullptr) {
        cout << "未找到该教师账号!" << endl;
        return;
    }
    string passwordv1, passwordv2;
    cout << "请输入新密码:" << endl;
    cin >> passwordv1;
    cout << "请再次输入密码:" << endl;
    cin >> passwordv2;
    if (passwordv1 != passwordv2) {
        cout << "请输入相同的密码!" << endl;
        return;
    }
    man->setPassword(passwordv1);
    write();
    cout << "重置成功!" << endl;
}

void Manlist::write() {
    ofstream out("../txt/Manager.txt");
    Manager *p = head->next;
    while (p) {
        out << p->getUsername() << ' ';
        out << p->getPassword() << ' ';
        out << p->getUserType() << ' ';
        out << p->getStatus() << ' ';
        out << p->getClassManage() << ' ' << endl;
        p = p->next;
    }
    out.close();
}

bool Manlist::lockAccount(const string &usernamev) {
    Manager *target = findManagerByUsername(usernamev);
    if (target != nullptr) {
        target->setStatus(2);
        write();
        return true;
    }
    return false;
}

void Manlist::setAccount() {
    string usernamev;
    cout << "请输入您要修改教师账号状态的用户名:" << endl;
    cin >> usernamev;
    Manager *man = checkIfExist(usernamev);
    if (man == nullptr) {
        cout << "未找到该教师账号!" << endl;
        return;
    }
    int statusv;
    cout << "请输入您要修改的状态(1:活跃 2:锁定):";
    cin >> statusv;
    man->setStatus(statusv);
    write();
    cout << "修改成功!" << endl;
}

void Manlist::showAllManagers() {
    Manager *current = head->next;
    while (current != nullptr) {
        cout << "Username: " << current->getUsername() << endl;
        cout << "Password: " << current->getPassword() << endl;
        cout << "User Type: " << current->getUserType() << endl;
        cout << "Status: " << current->getStatus() << endl;
        cout << "ClassManage" << current->getClassManage() << endl;
        cout << "------------------------" << endl;

        current = current->next;
    }
}
