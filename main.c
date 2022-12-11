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
                    system("cls");
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
                case '0':
                    return 0;
            }
        }
    }
}

void print_menu() {
    printf("Welcome to the FakeKea admin menu! (Very secret!) What would you like to do?\n");
    printf("1 - Create new item\n");
    printf("2 - Delete an item\n");
    printf("3 - Modify an item\n");
    printf("4 - Update website\n");
    printf("5 - Print items\n");
    printf("0 - Exit program\n");
}