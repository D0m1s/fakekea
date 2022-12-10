#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "sqlite\sqlite3.h"

void insert() {
    sqlite3 *db;
    sqlite3_open("data/db.db", &db);

    printf("Enter image URL: ");
    char img[100];
    scanf("%100[^\n]", img);
    finish_read();

    printf("Enter title: ");
    char title[100];
    scanf("%100[^\n]", title);
    finish_read();

    printf("Enter tag: ");
    char tag[100];
    scanf("%100[^\n]", tag);
    finish_read();

    printf("Enter description: ");
    char description[100];
    scanf("%100[^\n]", description);
    finish_read();

    double price;
    for (;;) {
        printf("Enter price: ");
        if (scanf("%lf", &price) == 1 && getchar() == '\n') {
            break;
        } else {
            printf("Invalid input.\n");
            while (getchar() != '\n')
                ;
        }
    }

    int tableCount;
    for (;;) {
        printf("Enter table count: ");
        if (scanf("%d", &tableCount) == 1 && getchar() == '\n') {
            if (tableCount > 10) {
                printf("Table count can be no more than 10!\n");
            } else {
                break;
            }
        } else {
            printf("Invalid input.\n");
            while (getchar() != '\n')
                ;
        }
    }

    char *tableLeft[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    char *tableRight[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    for (int i = 0; i < tableCount; i++) {
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

    char *query;
    query = malloc(10000);
    sprintf(query, "insert into product values('%s', '%s', '%s', '%s', '%lf', %d, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
            img, title, tag, description, price, tableCount, tableLeft[0], tableRight[0], tableLeft[1], tableRight[1],
            tableLeft[2], tableRight[2], tableLeft[3], tableRight[3], tableLeft[4], tableRight[4], tableLeft[5], tableRight[5],
            tableLeft[6], tableRight[6], tableLeft[7], tableRight[7], tableLeft[8], tableRight[8], tableLeft[9], tableRight[9]);

    if (sqlite3_exec(db, query, NULL, NULL, NULL)) {
        printf("Error\n");
    } else {
        printf("Success\n");
    }

    free(query);
    sqlite3_close(db);
    return;
}

void finish_read() {
    if (getchar() != '\n') {
        while (getchar() != '\n')
            ;
    }
}