#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

void print_menu();

int main() {
    system("cls");
    print_menu();
    char action;
    for (;;) {
        if (kbhit()) {
            action = getch();
            switch (action) {
                case '1':
                    system("cls");
                    insert();
                    print_menu();
                    break;
                case '2':
                    system("cls");
                    delete ();
                    print_menu();
                    break;
                case '3':
                    system("cls");
                    modify();
                    print_menu();
                    break;
                case '4':
                    system("cls");
                    update();
                    print_menu();
                    break;
                case '5':
                    print();
                    print_menu();
                    break;
                case '6':
                    system("start web/index.html");
                    system("cls");
                    print_menu();
                    break;
                case '7':
                    system("start http://fakekea.ml");
                    system("cls");
                    print_menu();
                    break;
                case '0':
                    return 0;
            }
        }
    }
}

void print_menu() {
    printf("Welcome to the FakeKea admin menu! (Very secret!) What would you like to do?\n");
    printf(
        "1 - Create new item\n"
        "2 - Delete an item\n"
        "3 - Modify an item\n"
        "4 - Update website\n"
        "5 - Print items\n"
        "6 - Open the local website\n"
        "7 - Open fakekea.ml\n"
        "0 - Exit program\n");
}