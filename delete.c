#include <stdio.h>
#include <stdlib.h>
#include "sqlite\sqlite3.h"

void delete() {
    sqlite3 *db;
    sqlite3_open("data/db.db", &db);
    
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "select count(*) from product;", -1, &stmt, NULL);
    sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    int index = -1;
    for (;;) {
        printf("Enter number of product which you want to delete: ");
        if (scanf("%d", &index) == 1 && getchar() == '\n') {
            if (index > count) {
                printf("You've entered a number higher than the product count! Try again.\n");
            } else if (index <= 0) {
                printf("You can't delete a product that doesn't exist!\n");
            } else {
                break;
            }
        } else {
            printf("Invalid input.\n");
            while (getchar() != '\n')
                ;
        }
    }
    char *query = calloc(1000, 1);
    sprintf(query, "delete from product where rowid = %d; vacuum", index);
    if (sqlite3_exec(db, query, NULL, NULL, NULL)) {
        printf("Error\n");
    } else {
        printf("Success\n");
    }

    free(query);
    sqlite3_close(db);
    return;
}
