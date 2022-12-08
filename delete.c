#include <stdio.h>
#include <stdlib.h>
#include "sqlite\sqlite3.h"

int main()
{
	sqlite3 *db;
	sqlite3_open("data/db.db", &db);

	int index = 0;
	char *query = malloc(1000);
	sprintf(query, "delete from product where rowid = (select rowid from product limit 1 offset %d)", index);
	if(sqlite3_exec(db, query, NULL, NULL, NULL)){ 
		printf("Error\n");
	} else{
		printf("Success\n");
	}

	free(query);
	sqlite3_close(db);

}
