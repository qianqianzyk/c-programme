#include "../hpp/Student.hpp"

void Student::calculateTotalScore() {
    totalScore = 0;
    for (int i = 0; i < 4; ++i) {
        totalScore += scores[i];
    }
}

void Student::calculateAverageScore() {
    averageScore = static_cast<double>(totalScore) / 4.0;
}

void Student::readscores(int (&scoresv)[4]) {
    for (int i = 0; i < 4; ++i) {
        this->scores[i] = scoresv[i];
    }
    calculateAverageScore();
    calculateTotalScore();
}