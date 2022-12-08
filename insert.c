#include <stdio.h>
#include <stdlib.h>
#include "sqlite\sqlite3.h"

int main()
{
	sqlite3 *db;
	sqlite3_open("data/db.db", &db);

	char *img = "https://cdn.shopify.com/s/files/1/0056/0912/8000/products/SofalovaNORAS8_700x700.jpg?v=1613816385";
	char *title = "sofaa";
	char *tag = "Sofos";
	char *description = "gera sofa";
	char *price = "255";
	char *tableCount = "2"; 
	char *tableLeft[10] = {"test1", "test2", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
	char *tableRight[10] = {"vienas", "du", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

	char *query = malloc(10000);

	sprintf(query, "insert into product values('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')", 
	img, title, tag, description, price, tableCount, tableLeft[0], tableRight[0], tableLeft[1], tableRight[1], 
	tableLeft[2], tableRight[2], tableLeft[3], tableRight[3], tableLeft[4], tableRight[4], tableLeft[5], tableRight[5], 
	tableLeft[6], tableRight[6], tableLeft[7], tableRight[7], tableLeft[8], tableRight[8], tableLeft[9], tableRight[9]);

	if(sqlite3_exec(db, query, NULL, NULL, NULL)){ 
		printf("Error\n");
	} else{
		printf("Success\n");
	}
	free(query);
	sqlite3_close(db);

}
