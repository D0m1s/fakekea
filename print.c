#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "sqlite\sqlite3.h"

void print() {
    sqlite3 *db;
    sqlite3_open("data/db.db", &db);

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "select img, title, tag, description, price, tableCount, left1, right1, left2, right2, left3, right3, left4, right4, left5, right5, left6, right6, left7, right7, left8, right8, left9, right9, left10, right10 from product", -1, &stmt, NULL);
    int i = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        printf("%d. %s\n", i + 1, sqlite3_column_text(stmt, 1));
        ++i;
    }

    sqlite3_close(db);
    return;
}
