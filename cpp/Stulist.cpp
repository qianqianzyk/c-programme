#include <iostream>
#include <cstring>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "../hpp/Stulist.hpp"
#include "../hpp/Manlist.hpp"

using namespace std;

void Stulist::addStudent(string &namev, string &genderv, string &idv, string &classNamev, int (&scoresv)[4]) {
    Student *p = new Student(namev, genderv, idv, classNamev);
    p->readScores(scoresv);
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
    if (classNamev == classmanagev) {
        Student *stu = checkIfExist(idv);
        if (stu != nullptr) {
            cout << "您添加的学生已经存在!" << endl;
            return;
        }
        Student *p = new Student(namev, genderv, idv, classNamev);
        p->readScores(scoresv);
        p->next = head->next;
        head->next = p;
        size++;
        write();
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
    } else {
        cout << "很抱歉,您无权操作!请联系管理员." << endl;
    }
}

Student *Stulist::checkIfExist(string idv) {
    Student *p = head->next;
    while (p) {
        if (p->getId() == idv)
            return p;
        p = p->next;
    }
    return nullptr;
}

void Stulist::write() {
    ofstream out("../txt/Student.txt");
    Student *p = head->next;
    while (p) {
        out << p->getName() << ' ';
        out << p->getGender() << ' ';
        out << p->getId() << ' ';
        out << p->getClassName() << ' ' << endl;
        const int *scores = p->getScores();
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
    Student *stu = checkIfExist(idv);
    if (stu == nullptr) {
        cout << "很抱歉,并未找到该学生!" << endl;
        return;
    } else {
        if (stu->getClassName() == classmanagev) {
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
        if (p->getName().find(namev) != string::npos && p->getClassName() == classmanagev) {
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
        if (p->getClassName() == classmanagev) {
            cout << "姓名          学号" << endl;
            cout << p->getName() << "         " << p->getId() << endl;
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

    cout << "排序成功!(按学号升序排序)" << endl << classmanagev << "班学生列表:" << endl;
    cout << "(名次||姓名||性别||学号||成绩.高数||成绩.程C||成绩.离散||成绩.大物||总分||平均分)" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    while (sortedList) {
        cout << number++ << " " << sortedList->getName() << " " << sortedList->getGender() << " " << sortedList->getId()
             << " ";
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

    cout << "排序成功!(按单科成绩降序排序)" << endl << classmanagev << "班学生列表:" << endl;
    cout << "(名次||姓名||性别||学号||成绩.高数||成绩.程C||成绩.离散||成绩.大物||总分||平均分)" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    while (sortedList) {
        cout << number++ << " " << sortedList->getName() << " " << sortedList->getGender() << " " << sortedList->getId()
             << " ";
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

void Stulist::sortStudentsByTotalScore(string classmanagev) {

    Student *classStudents = findTheSameClassStudents(classmanagev);
    // 插入排序按总分降序排序
    Student *sortedList = nullptr;
    while (classStudents) {
        // 从未排序链表中移除一个节点
        Student *current = classStudents;
        classStudents = classStudents->next;
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

    cout << "排序成功!(按总分降序排序)" << endl << classmanagev << "班学生列表:" << endl;
    cout << "(名次||姓名||性别||学号||成绩.高数||成绩.程C||成绩.离散||成绩.大物||总分||平均分)" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    while (sortedList) {
        cout << number++ << " " << sortedList->getName() << " " << sortedList->getGender() << " " << sortedList->getId()
             << " ";
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

void Stulist::sortStudentsByAverageScore(string classmanagev) {

    Student *classStudents = findTheSameClassStudents(classmanagev);

    // 插入排序按平均分降序排序
    Student *sortedList = nullptr;
    while (classStudents) {
        // 从未排序链表中移除一个节点
        Student *current = classStudents;
        classStudents = classStudents->next;
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

    cout << "排序成功!(按平均分降序排序)" << endl << classmanagev << "班学生列表:" << endl;
    cout << "(名次||姓名||性别||学号||成绩.高数||成绩.程C||成绩.离散||成绩.大物||总分||平均分)" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
    while (sortedList) {
        cout << number++ << " " << sortedList->getName() << " " << sortedList->getGender() << " " << sortedList->getId()
             << " ";
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

void Stulist::countStudentsScore(string classmanagev) {

    Student *classStudents = findTheSameClassStudents(classmanagev);

    // 插入排序按总分降序排序
    Student *sortedList = nullptr;
    while (classStudents) {
        // 从未排序链表中移除一个节点
        Student *current = classStudents;
        classStudents = classStudents->next;
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

    cout << "统计成功!" << endl << classmanagev << "班学生成绩:" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    int number = 1;
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

Student *Stulist::findTheSameClassStudents(string classmanagev) {
    // 创建一个新的链表来存储给定班级的学生
    Student *classStudents = nullptr;
    // 遍历链表，将给定班级的学生添加到新链表中
    Student *p = head->next;
    while (p) {
        if (p->getClassName() == classmanagev) {
            Student *newStudent = new Student(*p);
            newStudent->next = classStudents;
            classStudents = newStudent;
        }
        p = p->next;
    }
    return classStudents;
}

void Stulist::updateStudentByID(string classmanagev) {
    string idv;
    cout << "请输入您要修改学生信息的学号:" << endl;
    cin >> idv;
    Student *stu = checkIfExist(idv);
    if (stu == nullptr) {
        cout << "很抱歉，并未找到该学生!" << endl;
        return;
    } else {
        if (stu->getClassName() == classmanagev) {
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
            string namev, genderv;
            int scoresv[4];
            cout << "姓名:" << endl;
            cin >> namev;
            cout << "性别:" << endl;
            cin >> genderv;
            if (!(genderv == "男" || genderv == "女")){
                cout << "性别输入无效!" << endl;
                return;
            }
            cout << "成绩(高数,程C,离散,大物):" << endl;
            for (int i = 0; i < 4; ++i) cin >> scoresv[i];

            stu->setName(namev);
            stu->setGender(genderv);
            stu->readScores(scoresv);

            write();
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
        } else {
            cout << "很抱歉,您无权操作!请联系管理员." << endl;
        }
    }
}

void Stulist::deleteStudentByID(string classmanagev) {
    string idv;
    cout << "请输入您要删除学生信息的学号:" << endl;
    cin >> idv;

    Student *current = head->next;
    Student *pre = nullptr;
    while (current != nullptr) {
        if (current->getId() == idv && classmanagev != current->getClassName()) {
            cout << "很抱歉,您无权操作!请联系管理员." << endl;
            return;
        }
        if (current->getId() == idv && classmanagev == current->getClassName()) {
            if (pre == nullptr) {
                head->next = current->next;
            } else {
                pre->next = current->next;
            }
            delete current;
            write();
            cout << "成功删除学生信息!" << endl;
            return;
        }
        pre = current;
        current = current->next;
    }

    cout << "很抱歉，并未找到该学生!" << endl;
}

void Stulist::showAllStudents() {
    Student *current = head->next;
    while (current != nullptr) {
        cout << "Name: " << current->getName() << endl;
        cout << "Gender: " << current->getGender() << endl;
        cout << "ID: " << current->getId() << endl;
        cout << "Class: " << current->getClassName() << endl;
        cout << "Scores:";
        const int *scores = current->getScores();
        for (int i = 0; i < 4; ++i) {
            cout << scores[i] << ' ';
        }
        cout << endl;
        cout << "Total Score:" << current->getTotalScore() << endl;
        cout << "Average Score:" << current->getAverageScore() << endl;
        cout << "-----------------------------------------" << endl;

        current = current->next;
    }
}

