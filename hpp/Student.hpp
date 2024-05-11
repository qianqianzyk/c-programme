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

    string getName() const { return name; }

    string getGender() const { return gender; }

    string getId() const { return id; }

    string getClassName() const { return className; }

    const int *getScores() const { return scores; }

    int getTotalScore() const { return totalScore; }

    double getAverageScore() const { return averageScore; }

    void setName(const string &namev) { name = namev; }

    void setGender(const string &genderv) { gender = genderv; }

    void setId(const string &idv) { id = idv; }

    void setClassName(const string &classNamev) { className = classNamev; }

    void setScores(const int (&scoresv)[4]) { memcpy(scores, scoresv, sizeof(scores)); }

    // 计算总分
    void calculateTotalScore();

    // 计算个人平均分
    void calculateAverageScore();

    // 初始化学生成绩
    void readScores(int (&scores)[4]);
};


#endif
