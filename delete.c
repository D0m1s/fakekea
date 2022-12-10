#include <stdio.h>
#include <stdlib.h>
#include "sqlite\sqlite3.h"
#include "functions.h"

void delete()
{
	sqlite3 *db;
	sqlite3_open("data/db.db", &db);
	
	
	sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "select count(*) from product", -1, &stmt, NULL);
    rc = sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);



	int index = 0;
	for(;;) {
		printf("Enter number of product which you want to delete: ");
		if(scanf("%d",&index)==1&&getchar()=='\n') {
			break;
		} else {
			printf("Invalid input.\n");
			while(getchar()!='\n')
				;
		}
	}
	char *query = malloc(1000);
	sprintf(query, "delete from product where rowid = (select rowid from product limit 1 offset %d)", index+1);
	if(sqlite3_exec(db, query, NULL, NULL, NULL)){ 
		printf("Error\n");
	} else{
		printf("Success\n");
	}

	free(query);
	sqlite3_close(db);

}
