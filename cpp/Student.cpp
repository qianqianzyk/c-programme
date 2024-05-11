#include "../hpp/Student.hpp"

using namespace std;

void Student::calculateTotalScore() {
    totalScore = 0;
    for (int i = 0; i < 4; ++i) {
        totalScore += scores[i];
    }
}

void Student::calculateAverageScore() {
    averageScore = totalScore / 4.0;
}

void Student::readScores(int (&scoresv)[4]) {
    for (int i = 0; i < 4; ++i) {
        this->scores[i] = scoresv[i];
    }
    calculateTotalScore();
    calculateAverageScore();
}