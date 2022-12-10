#include <stdio.h>
#include <stdlib.h>
#include "sqlite\sqlite3.h"

void delete() {
    sqlite3 *db;
    sqlite3_open("data/db.db", &db);

    int index = -1;
    for (;;) {
        printf("Enter number of product which you want to delete: ");
        if (scanf("%d", &index) == 1 && getchar() == '\n') {
            break;
        } else {
            printf("Invalid input.\n");
            while (getchar() != '\n')
                ;
        }
    }
    char *query = calloc(1000, 1);
    sprintf(query, "delete from product where rowid = (select rowid from product limit 1 offset %d)", index);
    if (sqlite3_exec(db, query, NULL, NULL, NULL)) {
        printf("Error\n");
    } else {
        printf("Success\n");
    }
    free(query);
    sqlite3_close(db);
    return;
}
