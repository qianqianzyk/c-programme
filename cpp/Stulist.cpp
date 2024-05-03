#include "../hpp/Stulist.hpp"

void Stulist::addStudent(string &namev, string &genderv, string &idv, string &classNamev, int (&scoresv)[4]) {
    Student *p = new Student(namev, genderv, idv, classNamev);
    p->readscores(scoresv);
    p->next = head->next;
    head->next = p;
    size++;
}