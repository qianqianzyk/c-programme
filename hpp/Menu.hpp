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

    static void howFind();

    static void howCount();

    static void howSort();

    static void countScore();

private:
    static void clearScreen() {
        system("cls");
    }
};

#endif
