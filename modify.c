#include <stdio.h>
#include <stdlib.h>
#include "sqlite\sqlite3.h"

int main()
{
	sqlite3 *db;
	sqlite3_open("data/db.db", &db);
	
	
	char *query = malloc(1000);
	char *test = "abcd";
	// pakeicia pirmos prekes title, vietoj title galima rasyti kitus is create.c ir atitinkamai ta pakeis
	int index = 1;
	sprintf(query, "update product set title = '%s' where rowid = %d", test, index);
	if(sqlite3_exec(db, query, NULL, NULL, NULL)){ 
		printf("Error\n");
	} else{
		printf("Success\n");
	}

	free(query);
	sqlite3_close(db);

}
