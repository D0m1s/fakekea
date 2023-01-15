#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "sqlite\sqlite3.h"

void insert() {
    sqlite3 *db;
    sqlite3_open("data/db.db", &db);

    printf("Enter image URL (or enter -1 if you want to go back): ");
    char *img = calloc(101, 1);
    scanf("%100[^\n]", img);
    char validate[3] = "-1";
    finish_read();
    if (strcmp(img, validate) == 0) {
        printf("Cancelling insertion.\n\n");
        sqlite3_close(db);
        return;
    }

    printf("Enter title: ");
    char *title = calloc(101, 1);
    scanf("%100[^\n]", title);
    finish_read();

    printf("Enter tag: ");
    char *tag = calloc(101, 1);
    scanf("%100[^\n]", tag);
    finish_read();

    printf("Enter description: ");
    char *description = calloc(1025, 1);
    scanf("%1024[^\n]", description);
    finish_read();

    double price;
    for (;;) {
        printf("Enter price: ");
        if (scanf("%lf", &price) == 1 && getchar() == '\n') {
            if (price < 0) {
                printf("Can't have a negative price!\n");
            } else {
                price = roundf(price * 100) / 100;
                break;
            }
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
        printf("Enter value for the left side of the %d row: ", i+1);
        tableLeft[i] = calloc(101, 1);
        scanf("%100[^\n]", tableLeft[i]);
        finish_read();

        printf("Enter value for the right side of the %d row: ", i+1);
        tableRight[i] = calloc(101, 1);
        scanf("%100[^\n]", tableRight[i]);
        finish_read();
    }

    char *query;
    query = malloc(100000);
    sprintf(query, "insert into product values('%s', '%s', '%s', '%s', '%.2lf', %d, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');",
            img, title, tag, description, price, tableCount, tableLeft[0], tableRight[0], tableLeft[1], tableRight[1],
            tableLeft[2], tableRight[2], tableLeft[3], tableRight[3], tableLeft[4], tableRight[4], tableLeft[5], tableRight[5],
            tableLeft[6], tableRight[6], tableLeft[7], tableRight[7], tableLeft[8], tableRight[8], tableLeft[9], tableRight[9]);

    if (sqlite3_exec(db, query, NULL, NULL, NULL)) {
        printf("Error\n");
    } else {
        printf("Success\n");
    }

    free(img);
    free(title);
    free(tag);
    free(description);
    for (int i = 0; i < tableCount; ++i) {
        free(tableLeft[i]);
        free(tableRight[i]);
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