#include <iostream>
#include <fstream>
#include "../hpp/Stulist.hpp"
#include "../hpp/Manlist.hpp"

using namespace std;

void Stulist::addStudent(string &namev, string &genderv, string &idv, string &classNamev, int (&scoresv)[4]) {
    Student *p = new Student(namev, genderv, idv, classNamev);
    p->readscores(scoresv);
    p->next = head->next;
    head->next = p;
    size++;
}

void Stulist::addStudentByTeacher(string classmanagev) {
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
    if (classNamev == classmanagev) {
        Student *stu = checkifexist(idv);
        if (stu != nullptr) {
            cout << "您添加的学生已经存在!" << endl;
            return;
        }
        Student *p = new Student(namev, genderv, idv, classNamev);
        p->readscores(scoresv);
        p->next = head->next;
        head->next = p;
        size++;
        cout << "添加成功!" << endl;
    } else {
        cout << "很抱歉,您无权操作!请联系管理员." << endl;
    }
}

Student *Stulist::checkifexist(string idv) {
    Student *p = head->next;
    while (p) {
        if (p->getid() == idv)
            return p;
        p = p->next;
    }
    return nullptr;
}

void Stulist::write() {
    ofstream out("../txt/Student.txt");
    Student *p = head->next;
    while (p) {
        out << p->getname() << ' ';
        out << p->getgender() << ' ';
        out << p->getid() << ' ';
        out << p->getclassName() << ' ' << endl;
        const int *scores = p->getscores();
        for (int i = 0; i < 4; ++i) {
            out << scores[i] << ' ';
        }
        out << endl;
        p = p->next;
    }
    out.close();
}

void Stulist::findStudentByID(string classmanagev) {
    string idv;
    cout << "请输入您要查找学生的学号:" << endl;
    cin >> idv;
    Student *stu = checkifexist(idv);
    if (stu == nullptr) {
        cout << "很抱歉,并未找到该学生!" << endl;
        return;
    } else {
        if (stu->getclassName() == classmanagev) {
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
        } else {
            cout << "很抱歉,您无权操作!请联系管理员." << endl;
        }
    }
}

void Stulist::findStudentsByName(string classmanagev) {
    string namev;
    cout << "请输入您要查找学生的姓名(支持模糊查找):" << endl;
    cin >> namev;

    bool found = false;
    Student *p = head->next;
    while (p) {
        if (p->getname().find(namev) != string::npos && p->getclassName() == classmanagev) {
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
        cout << "未找到符合条件的学生.请确认是否是您班级里的学生!" << endl;
        return;
    } else {
        cout << "查询成功!找到以上学生." << endl;
        return;
    }
}

void Stulist::findStudentsByClass(string classmanagev) {
    cout << "请注意,查询到的为您班级上的学生.如果未查到指定的学生,可能是因为该学生为其他班级上的或者该学生的信息并未填写提交!"
         << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << "查询成功!找到以下学生." << endl;
    cout << "如果想要获取学生的详细信息,请使用学号或姓名查询!" << endl;

    Student *p = head->next;
    while (p) {
        if (p->getclassName() == classmanagev) {
            cout << "姓名          学号" << endl;
            cout << p->getname() << "         " << p->getid() << endl;
        }
        p = p->next;
    }
    cout << "---------------------------------------------------------------------------------------------" << endl;
}

void Stulist::sortStudentsByID(string classmanagev) {

    Student *classStudents = findTheSameClassStudents(classmanagev);

    // 插入排序对链表中的学生按学号升序排序
    Student *sortedList = nullptr;
    while (classStudents) {
        // 从未排序链表中移除一个节点
        Student *current = classStudents;
        classStudents = classStudents->next;
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

    cout << "排序成功!(按学号升序排序)" << endl << classmanagev << "班学生列表:" << endl;
    cout << "(名次||姓名||性别||学号||成绩.高数||成绩.程C||成绩.离散||成绩.大物||总分||平均分)" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    while (sortedList) {
        cout << number++ << sortedList->getname() << " " << sortedList->getgender() << " " << sortedList->getid()
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

void Stulist::sortStudentsBySubjectScore(string classmanagev) {

    Student *classStudents = findTheSameClassStudents(classmanagev);

    int index;
    cout << "请输入您要根据哪门成绩进行排序(1:高数 2:程C 3:离散 4:大物 )" << endl;
    cin >> index;
    // 插入排序按指定科目成绩降序排序
    Student *sortedList = nullptr;
    while (classStudents) {
        // 从未排序链表中移除一个节点
        Student *current = classStudents;
        classStudents = classStudents->next;
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

    cout << "排序成功!(按单科成绩降序排序)" << endl << classmanagev << "班学生列表:" << endl;
    cout << "(名次||姓名||性别||学号||成绩.高数||成绩.程C||成绩.离散||成绩.大物||总分||平均分)" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    while (sortedList) {
        cout << number++ << sortedList->getname() << " " << sortedList->getgender() << " " << sortedList->getid()
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

void Stulist::sortStudentsByTotalScore(string classmanagev) {

    Student *classStudents = findTheSameClassStudents(classmanagev);
    // 插入排序按总分降序排序
    Student *sortedList = nullptr;
    while (classStudents) {
        // 从未排序链表中移除一个节点
        Student *current = classStudents;
        classStudents = classStudents->next;
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

    cout << "排序成功!(按总分降序排序)" << endl << classmanagev << "班学生列表:" << endl;
    cout << "(名次||姓名||性别||学号||成绩.高数||成绩.程C||成绩.离散||成绩.大物||总分||平均分)" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    while (sortedList) {
        cout << number++ << sortedList->getname() << " " << sortedList->getgender() << " " << sortedList->getid()
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

void Stulist::sortStudentsByAverageScore(string classmanagev) {

    Student *classStudents = findTheSameClassStudents(classmanagev);

    // 插入排序按平均分降序排序
    Student *sortedList = nullptr;
    while (classStudents) {
        // 从未排序链表中移除一个节点
        Student *current = classStudents;
        classStudents = classStudents->next;
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

    cout << "排序成功!(按平均分降序排序)" << endl << classmanagev << "班学生列表:" << endl;
    cout << "(名次||姓名||性别||学号||成绩.高数||成绩.程C||成绩.离散||成绩.大物||总分||平均分)" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    while (sortedList) {
        cout << number++ << sortedList->getname() << " " << sortedList->getgender() << " " << sortedList->getid()
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

void Stulist::countStudentsScore(string classmanagev) {

    Student *classStudents = findTheSameClassStudents(classmanagev);

    // 插入排序按总分降序排序
    Student *sortedList = nullptr;
    while (classStudents) {
        // 从未排序链表中移除一个节点
        Student *current = classStudents;
        classStudents = classStudents->next;
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

    cout << "统计成功!" << endl << classmanagev << "班学生成绩:" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    double totalAverage = 0.0;
    int numAbove60[4] = {0};
    double totalSubjectScores[4] = {0};
    while (sortedList) {
        const int *scores = sortedList->getscores();
        for (int i = 0; i < 4; ++i) {
            totalSubjectScores[i] += scores[i];
            if (scores[i] > 60) {
                numAbove60[i]++;
            }
        }
        totalAverage += sortedList->gettotalScore();

        Student *temp = sortedList;
        sortedList = sortedList->next;
        delete temp;
        number++;
    }
    // 输出班级总人数
    cout << "班级总人数:" << number - 1 << endl;
    cout << endl;
    // 输出各科成绩平均分
    cout << "各科成绩平均分:" << endl;
    const char *subjectNames[4] = {"高数", "程C", "离散", "大物"};
    for (int i = 0; i < 4; ++i) {
        cout << subjectNames[i] << ": " << totalSubjectScores[i] / ((number - 1) * 1.0) << endl;
    }
    cout << endl;
    // 输出各科成绩超过60分的人数
    cout << "各科及格的人数:" << endl;
    for (int i = 0; i < 4; ++i) {
        cout << subjectNames[i] << ": " << numAbove60[i] << endl;
    }
    cout << endl;
    // 输出总分的平均分
    cout << "班级平均分:" << totalAverage / ((number - 1) * 1.0) << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

Student *Stulist::findTheSameClassStudents(std::string classmanagev) {
    // 创建一个新的链表来存储给定班级的学生
    Student *classStudents = nullptr;
    // 遍历链表，将给定班级的学生添加到新链表中
    Student *p = head->next;
    while (p) {
        if (p->getclassName() == classmanagev) {
            Student *newStudent = new Student(*p);
            newStudent->next = classStudents;
            classStudents = newStudent;
        }
        p = p->next;
    }
    return classStudents;
}

void Stulist::showAllStudents() {
    Student *current = head->next;
    while (current != nullptr) {
        cout << "Name: " << current->getname() << endl;
        cout << "Gender: " << current->getgender() << endl;
        cout << "ID: " << current->getid() << endl;
        cout << "Class: " << current->getclassName() << endl;
        cout << "Scores:";
        const int *scores = current->getscores();
        for (int i = 0; i < 4; ++i) {
            cout << scores[i] << ' ';
        }
        cout << endl;
        cout << "Total Score:" << current->gettotalScore() << endl;
        cout << "Average Score:" << current->getaverageScore() << endl;
        cout << "-----------------------------------------" << endl;

        current = current->next;
    }
}

