#ifndef C_PROGRAMME_MENU_H
#define C_PROGRAMME_MENU_H

#include <iostream>

using namespace std;

class Menu {
public:
    static void welcome();

    static void teacherMenu();

    static void managerMenu();

    static void bye();

    static void howfind();

    static void howcount();

    static void howsort();

    static void countscore();

private:
    static void clearScreen() {
        system("cls");
    }
};

#endif
