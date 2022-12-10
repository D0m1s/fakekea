#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite\sqlite3.h"
#include "functions.h"

void update()
{
	sqlite3 *db;
	sqlite3_open("data/db.db", &db);
	sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "select img, title, tag, description, price, tableCount, left1, right1, left2, right2, left3, right3, left4, right4, left5, right5, left6, right6, left7, right7, left8, right8, left9, right9, left10, right10 from product", -1, &stmt, NULL);

	sqlite3_stmt *stmt2;
	int rc2 = sqlite3_prepare_v2(db, "select count(*) from product", -1, &stmt2, NULL);
	rc2 = sqlite3_step(stmt2);
	int count = sqlite3_column_int(stmt2, 0);
	
	int offset = 915;

	FILE *file; 
	file = fopen("data/templateListing", "r");
	int templateSize = returnFileSize(file);
	char *template = calloc(templateSize+1, 1);
	fread(template, templateSize, 1, file);
	fclose(file);

	file = fopen("data/templateHTML", "r");
	int htmlSize = returnFileSize(file);
	char *templateHTML = calloc(htmlSize+1, 1);
	fread(templateHTML, htmlSize, 1, file);
	fclose(file);

	int offsets[6] = {92,198,278,345,455,572};
	for(int i = 0; i < count; ++i){
		sqlite3_step(stmt);
		int addedSize = 0;
		char *productHTML = calloc(templateSize+1, 1);
		strcpy(productHTML, template);
		char id[15];
		sprintf(id, "%d", i);
		expand(&productHTML, strlen(productHTML)+1, strlen(id), offsets[0]+addedSize, id);
		addedSize = strlen(id);
		expand(&productHTML, strlen(productHTML)+1, strlen(sqlite3_column_text(stmt, 0)), offsets[1]+addedSize, (char *)sqlite3_column_text(stmt, 0));
		addedSize += strlen(sqlite3_column_text(stmt, 0));
		expand(&productHTML, strlen(productHTML)+1, strlen(sqlite3_column_text(stmt, 1)), offsets[2]+addedSize, (char *)sqlite3_column_text(stmt, 1));
		addedSize += strlen(sqlite3_column_text(stmt, 1));
		expand(&productHTML, strlen(productHTML)+1, strlen(sqlite3_column_text(stmt, 2)), offsets[3]+addedSize, (char *)sqlite3_column_text(stmt, 2));
		addedSize += strlen(sqlite3_column_text(stmt, 2));
		expand(&productHTML, strlen(productHTML)+1, strlen(sqlite3_column_text(stmt, 3)), offsets[4]+addedSize, (char *)sqlite3_column_text(stmt, 3));
		addedSize += strlen(sqlite3_column_text(stmt, 3));
		expand(&productHTML, strlen(productHTML)+1, strlen(sqlite3_column_text(stmt, 4)), offsets[5]+addedSize, (char *)sqlite3_column_text(stmt, 4));
		expand(&templateHTML, strlen(templateHTML)+1, strlen(productHTML), offset, productHTML);
		offset += strlen(productHTML);

		free(productHTML);
	}
	free(template);
	file = fopen("data/templatePopup", "r");
	templateSize = returnFileSize(file);
	template = calloc(templateSize+1, 1);
	fread(template, templateSize, 1, file);
	fclose(file);
	offset += 53;
	int offsets2[5] = {40, 102, 120, 139, 184};

	rc = sqlite3_prepare_v2(db, "select img, title, tag, description, price, tableCount, left1, right1, left2, right2, left3, right3, left4, right4, left5, right5, left6, right6, left7, right7, left8, right8, left9, right9, left10, right10 from product", -1, &stmt, NULL);
	for(int i = 0; i < count; ++i){
		sqlite3_step(stmt);
		int addedSize = 0;
		char *productHTML =  calloc(templateSize+1, 1);
		strcpy(productHTML, template);
		char id[15];
		sprintf(id, "%d", i);
		expand(&productHTML, strlen(productHTML)+1, strlen(id), offsets2[0]+addedSize, id);
		addedSize = strlen(id);
		expand(&productHTML, strlen(productHTML)+1, strlen(sqlite3_column_text(stmt, 0)), offsets2[1]+addedSize, (char *)sqlite3_column_text(stmt, 0));
		addedSize += strlen(sqlite3_column_text(stmt, 0));
		expand(&productHTML, strlen(productHTML)+1, strlen(sqlite3_column_text(stmt, 1)), offsets2[2]+addedSize, (char *)sqlite3_column_text(stmt, 1));
		addedSize += strlen(sqlite3_column_text(stmt, 1));
		expand(&productHTML, strlen(productHTML)+1, strlen(sqlite3_column_text(stmt, 3)), offsets2[3]+addedSize, (char *)sqlite3_column_text(stmt, 3));
		addedSize += strlen(sqlite3_column_text(stmt, 3));
		if(sqlite3_column_int(stmt, 5) != 0){
			char tableBegin[8] = "<table>";
			expand(&productHTML, strlen(productHTML)+1, 7, offsets2[3]+addedSize+5, tableBegin);
			addedSize += 7;
			for(int j = 0; j < sqlite3_column_int(stmt, 5); ++j){
				char table[5] = "<tr>";
				char table1[5] = "<td>";
				char table2[6] = "</td>";
				char table3[6] = "</tr>";
				expand(&productHTML, strlen(productHTML)+1, 4, offsets2[3]+addedSize+5, table);
				addedSize += 4;
				expand(&productHTML, strlen(productHTML)+1, 4, offsets2[3]+addedSize+5, table1);
				addedSize += 4;
				expand(&productHTML, strlen(productHTML)+1, strlen(sqlite3_column_text(stmt, 6+j*2)), offsets2[3]+addedSize+5, (char *)sqlite3_column_text(stmt, 6+j*2));
				addedSize += strlen(sqlite3_column_text(stmt, 6+j*2));
				expand(&productHTML, strlen(productHTML)+1, 5, offsets2[3]+addedSize+5, table2);
				addedSize += 5;
				expand(&productHTML, strlen(productHTML)+1, 4, offsets2[3]+addedSize+5, table1);
				addedSize += 4;
				expand(&productHTML, strlen(productHTML)+1, strlen(sqlite3_column_text(stmt, 7+j*2)), offsets2[3]+addedSize+5, (char *)sqlite3_column_text(stmt, 7+j*2));
				addedSize += strlen(sqlite3_column_text(stmt, 7+j*2));
				expand(&productHTML, strlen(productHTML)+1, 5, offsets2[3]+addedSize+5, table2);
				addedSize += 5;
				expand(&productHTML, strlen(productHTML)+1, 5, offsets2[3]+addedSize+5, table3);
				addedSize += 5;
			}
			char tableEnd[9] = "</table>";
			expand(&productHTML, strlen(productHTML)+1, 8, offsets2[3]+addedSize+5, tableEnd);
			addedSize += 8;
		}
		expand(&productHTML, strlen(productHTML)+1, strlen(sqlite3_column_text(stmt, 4)), offsets2[4]+addedSize, (char *)sqlite3_column_text(stmt, 4));
		expand(&templateHTML, strlen(templateHTML)+1, strlen(productHTML), offset, productHTML);
		offset += strlen(productHTML);
		free(productHTML);
	}
	
	file = fopen("web/index.html", "w");
	fprintf(file, "%s", templateHTML);
	free(templateHTML);
	fclose(file);
	sqlite3_close(db);

}

int returnFileSize(FILE *file){
  fseek(file, 0, SEEK_END);
  int fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);
  return fileSize;
}

void expand(char **html, int size, int length, int offset, char *toAdd){
	char *newString = calloc(size+length, 1);
	strncpy(newString, *html, offset);
	*(newString+offset) = '\0';
	strcat(newString, toAdd);
	strcat(newString, *html+offset);
	free(*html);
	*html = newString;
}
