#include <stdio.h>
#include <stdlib.h>
#include "sqlite\sqlite3.h"

int main()
{
	sqlite3 *db;
	sqlite3_open("data/db.db", &db);

	if(sqlite3_exec(db, "create table product (img, title, tag, description, price, tableCount, left1, right1, left2, right2, left3, right3, left4, right4, left5, right5, left6, right6, left7, right7, left8, right8, left9, right9, left10, right10)", NULL, NULL, NULL)){ 
		printf("Error\n");
	} else{
		printf("Success\n");
	}

	sqlite3_close(db);

}
