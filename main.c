#include <stdio.h>
#include <conio.h>

void print_menu();

int main() {
    print_menu();
    char action;
    for(;;) {
        if(kbhit()) {
            action = getch();
            switch(action) {
                case '1':
                    break;
                case '2':
                    break;
                case '3':
                    break;
                case '4':
                    break;
                case '5':
                    return 0;
            }
        }
    }
}

void print_menu() {
        printf("Welcome to the FakeKea admin menu! (Very secret!) What would you like to do?\n");
        printf("1 - Create new item\n");
        printf("2 - Delete an item\n");
        printf("3 - Create database\n");
        printf("4 - Update website\n");
        printf("5 - Exit program\n");
}