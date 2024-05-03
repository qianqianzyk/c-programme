#ifndef C_PROGRAMME_STUDENT_H
#define C_PROGRAMME_STUDENT_H

#include <iostream>
#include <cstring>

using namespace std;

class Student {
private:
    string name;
    string gender;
    string id;
    string className;
    int scores[4];
    int totalScore;
    double averageScore;
public:
    Student *next;

    // 构造函数
    Student(string namev = "", string genderv = "", string idv = "", string classNamev = "")
            : name(namev), gender(genderv), id(idv), className(classNamev), totalScore(0), averageScore(0.0) {
        for (int i = 0; i < 4; ++i) {
            scores[i] = 0;
        }
    }

    string getname() const { return name; }

    string getgender() const { return gender; }

    string getid() const { return id; }

    string getclassName() const { return className; }

    const int *getscores() const { return scores; }

    int gettotalScore() const { return totalScore; }

    int getaverageScore() const { return averageScore; }

    // 计算总分
    void calculateTotalScore();

    // 计算个人平均分
    void calculateAverageScore();

    // 初始化学生成绩
    void readscores(int (&scores)[4]);
};


#endif
