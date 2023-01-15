#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
                case '8':
                    system("cls");
                    updateWebsite();
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
        "4 - Update local website\n"
        "5 - Print items\n"
        "6 - Open the local website\n"
        "7 - Open fakekea.ml\n"
        "8 - Update fakekea.ml\n"
        "0 - Exit program\n");
}

void updateWebsite() {
    printf("Enter password: ");
    char password[100];
    scanf("%100[^\n]", password);
    finish_read();
    char text[1000];
    sprintf(text, "@echo off\necho open ftpupload.net> temp.txt\necho ezyro_32945929>> temp.txt\necho %s>> temp.txt\necho cd fakekea.ml>> temp.txt\necho cd htdocs>> temp.txt\necho send web/index.html>> temp.txt\necho quit>> temp.txt\nftp -s:temp.txt\ndel temp.txt", password);
    FILE *fp = fopen("update.bat", "w");
    fprintf(fp, "%s", text);
    fclose(fp);
    system("update.bat>validate.txt");

    FILE *fp2 = fopen("validate.txt", "r");
    char *text2 = malloc((returnFileSize(fp2) + 1));

    fread(text2, returnFileSize(fp2), 1, fp2);
    if (strstr(text2, "Login authentication failed") != NULL) {
        printf("Invalid password entered.\n\n");
    } else {
        printf("Website updated successfully.\n\n");
    }

    fclose(fp2);
    remove("update.bat");
    remove("validate.txt");
    free(text2);

    return;
}