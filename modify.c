#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "sqlite\sqlite3.h"

void modify() {
    sqlite3 *db;
    sqlite3_open("data/db.db", &db);

    int index;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "select count(*) from product;", -1, &stmt, NULL);
    sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    if (count == 0) {
        printf("There are no item listings! Can't modify anything!\n\n");
        sqlite3_close(db);
        return;
    }

    char *query = malloc(1000);

    for (;;) {
        printf("Welcome to the product modifier! Enter the index of the product you'd like to modify (enter -1 if you'd like to go back): ");
        if (scanf("%d", &index) == 1 && getchar() == '\n') {
            if (index == -1) {
                printf("Cancelling modification.\n\n");
                sqlite3_close(db);
                return;
            }
            if (index > count) {
                printf("You've entered a number higher than the product count! Try again.\n");
            } else if (index <= 0) {
                printf("You can't modify a product that doesn't exist!\n");
            } else {
                break;
            }
        } else {
            printf("Invalid input.\n");
            while (getchar() != '\n')
                ;
        }
    }

    printf("Product chosen!\n");
    print_list();
    char command;
    for (;;) {
        if (kbhit()) {
            command = getch();
            switch (command) {
                case '1':
                    change_url(db, index);
                    print_list();
                    break;
                case '2':
                    change_title(db, index);
                    print_list();
                    break;
                case '3':
                    change_tag(db, index);
                    print_list();
                    break;
                case '4':
                    change_description(db, index);
                    print_list();
                    break;
                case '5':
                    change_price(db, index);
                    print_list();
                    break;
                case '6':
                    change_table(db, index);
                    print_list();
                    break;
                case '0':
                    sqlite3_close(db);
                    system("cls");
                    return;
            }
        }
    }
}

void print_list() {
    printf("What would you like to modify?\n");
    printf(
        "1 - Image Url\n"
        "2 - Title\n"
        "3 - Tag\n"
        "4 - Description\n"
        "5 - Price\n"
        "6 - Table\n"
        "0 - Go back\n");
}

void change_url(sqlite3 *db, int index) {
    char *query = malloc(1000);
    printf("Enter new image URL: ");
    char img[100];
    scanf("%100[^\n]", img);
    sprintf(query, "update product set img = '%s' where rowid = %d;", img, index);
    if (sqlite3_exec(db, query, NULL, NULL, NULL)) {
        printf("Error\n");
    } else {
        printf("Success\n");
    }
    finish_read();
    free(query);
}

void change_title(sqlite3 *db, int index) {
    char *query = malloc(1000);
    printf("Enter new title: ");
    char title[100];
    scanf("%100[^\n]", title);
    sprintf(query, "update product set title = '%s' where rowid = %d;", title, index);
    if (sqlite3_exec(db, query, NULL, NULL, NULL)) {
        printf("Error\n");
    } else {
        printf("Success\n");
    }
    finish_read();
    free(query);
}

void change_tag(sqlite3 *db, int index) {
    char *query = malloc(1000);
    printf("Enter new tag: ");
    char tag[100];
    scanf("%100[^\n]", tag);
    sprintf(query, "update product set tag = '%s' where rowid = %d;", tag, index);
    if (sqlite3_exec(db, query, NULL, NULL, NULL)) {
        printf("Error\n");
    } else {
        printf("Success\n");
    }
    finish_read();
    free(query);
}

void change_description(sqlite3 *db, int index) {
    char *query = malloc(10000);
    printf("Enter new description: ");
    char *description = calloc(1025, 1);
    scanf("%1024[^\n]", description);
    sprintf(query, "update product set description = '%s' where rowid = %d;", description, index);
    if (sqlite3_exec(db, query, NULL, NULL, NULL)) {
        printf("Error\n");
    } else {
        printf("Success\n");
    }
    finish_read();
    free(description);
    free(query);
}

void change_price(sqlite3 *db, int index) {
    char *query = malloc(1000);
    double price;
    for (;;) {
        printf("Enter price: ");
        if (scanf("%lf", &price) == 1 && getchar() == '\n') {
            sprintf(query, "update product set price = '%lf' where rowid = %d;", price, index);
            if (sqlite3_exec(db, query, NULL, NULL, NULL)) {
                printf("Error\n");
            } else {
                printf("Success\n");
            }
            free(query);
            break;
        } else {
            printf("Invalid input.\n");
            while (getchar() != '\n')
                ;
        }
    }
}

void change_table(sqlite3 *db, int index) {
    printf(
        "What do you want to modify about the table?\n"
        "1 - Amount of rows\n"
        "2 - Information in rows\n"
        "0 - Go back\n");
    char command;
    for (;;) {
        if (kbhit()) {
            command = getch();
            switch (command) {
                case '1':
                    change_tables(db, index);
                    printf(
                        "What do you want to modify about the table?\n"
                        "1 - Amount of rows\n"
                        "2 - Information in rows\n"
                        "0 - Go back\n");
                    break;
                case '2':
                    change_row(db, index);
                    printf(
                        "What do you want to modify about the table?\n"
                        "1 - Amount of rows\n"
                        "2 - Information in a row\n"
                        "0 - Go back\n");
                    break;
                case '0':
                    return;
            }
        }
    }
}

void change_tables(sqlite3 *db, int index) {
    sqlite3_stmt *stmt;
    char *query = malloc(1000);
    sprintf(query, "select tableCount from product where rowid = %d;", index);
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_step(stmt);
    int table_count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    // printf("%d\n", sqlite3_column_int(stmt, 0));
    int new_amount;
    for (;;) {
        printf("Enter new amount of rows:\n");
        if (scanf("%d", &new_amount) == 1 && getchar() == '\n') {
            if (new_amount < 0) {
                printf("Can't have less than 0 rows!\n");
            } else if (new_amount > 10) {
                printf("Can't have more than 10 rows!\n");
            } else {
                break;
            }
        } else {
            printf("Invalid input!\n");
            while (getchar() != '\n')
                ;
        }
    }

    if (new_amount < table_count) {
        sprintf(query, "update product set tableCount = '%d' where rowid = %d;", new_amount, index);
        if (sqlite3_exec(db, query, NULL, NULL, NULL)) {
            printf("Error\n");
        } else {
            printf("Success\n");
        }
    } else {
        sprintf(query, "update product set tableCount = '%d' where rowid = %d;", new_amount, index);
        if (sqlite3_exec(db, query, NULL, NULL, NULL)) {
            printf("Error\n");
        } else {
            printf("Success\n");
        }
        char *tableLeft[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
        char *tableRight[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

        /*This loop reads new row values from console*/

        for (int i = table_count; i < new_amount; i++) {
            printf("Enter value for tableLeft[%d]: ", i);
            char value1[100];
            scanf("%100[^\n]", value1);
            finish_read();
            tableLeft[i] = value1;

            printf("Enter value for tableRight[%d]: ", i);
            char value2[100];
            scanf("%100[^\n]", value2);
            finish_read();
            tableRight[i] = value2;
        }

        /*This loop updates the database with the new row values*/
        for (int i = table_count; i < new_amount; i++) {
            sprintf(query, "update product set left%d = '%s' where rowid = %d;", i + 1, tableLeft[i], index);
            sqlite3_exec(db, query, NULL, NULL, NULL);
            sprintf(query, "update product set right%d = '%s' where rowid = %d;", i + 1, tableRight[i], index);
            sqlite3_exec(db, query, NULL, NULL, NULL);
        }
    }
    free(query);
    return;
}

void change_row(sqlite3 *db, int index) {
    sqlite3_stmt *stmt;
    char *query = malloc(1000);
    sprintf(query, "select tableCount from product where rowid = %d;", index);
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_step(stmt);
    int table_count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    int modify_row;

    for (;;) {
        printf("Enter which row to modify: ");
        if (scanf("%d", &modify_row) == 1 && getchar() == '\n') {
            if (modify_row <= 0 || modify_row >= table_count) {
                printf("Invalid row chosen.\n");
            } else {
                printf("Enter value for the left side of the %d row: ", modify_row);
                char value1[100];
                scanf("%100[^\n]", value1);
                finish_read();

                printf("Enter value for the right side of the %d row: : ", modify_row);
                char value2[100];
                scanf("%100[^\n]", value2);
                finish_read();

                sprintf(query, "update product set left%d = '%s' where rowid = %d;", modify_row, value1, index);
                sqlite3_exec(db, query, NULL, NULL, NULL);
                sprintf(query, "update product set right%d = '%s' where rowid = %d;", modify_row, value2, index);
                sqlite3_exec(db, query, NULL, NULL, NULL);

                break;
            }
        } else {
            printf("Invalid input.\n");
            while (getchar() != '\n')
                ;
        }
    }
    printf("Success.\n");
    free(query);
    return;
}