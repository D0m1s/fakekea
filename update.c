#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite\sqlite3.h"

int returnFileSize(FILE *file);
int callback(void *NotUsed, int argc, char **argv, char **azColName);
void expand(char **html, int size, int length, int offset, char *toAdd);
void freeAll();

struct Product{
	char *id;
	char *img;
	char *title;
	char *tag;
	char *description;
	char *price;
	int tableCount;
	char *tableLeft[10];
	char *tableRight[10];
} product[100];

int productNum = 0;

int main()
{
	sqlite3 *db;
	sqlite3_open("data/db.db", &db);
	sqlite3_exec(db, "select * from product", callback, NULL, NULL);
	sqlite3_close(db);

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
	for(int i = 0; i < productNum; ++i){
		int addedSize = 0;
		char *productHTML = calloc(templateSize+1, 1);
		strcpy(productHTML, template);
		expand(&productHTML, strlen(productHTML)+1, strlen(product[i].id), offsets[0]+addedSize, product[i].id);
		addedSize = strlen(product[i].id);
		expand(&productHTML, strlen(productHTML)+1, strlen(product[i].img), offsets[1]+addedSize, product[i].img);
		addedSize += strlen(product[i].img);
		expand(&productHTML, strlen(productHTML)+1, strlen(product[i].title), offsets[2]+addedSize, product[i].title);
		addedSize += strlen(product[i].title);
		expand(&productHTML, strlen(productHTML)+1, strlen(product[i].tag), offsets[3]+addedSize, product[i].tag);
		addedSize += strlen(product[i].tag);
		expand(&productHTML, strlen(productHTML)+1, strlen(product[i].description), offsets[4]+addedSize, product[i].description);
		addedSize += strlen(product[i].description);
		expand(&productHTML, strlen(productHTML)+1, strlen(product[i].price), offsets[5]+addedSize, product[i].price);
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

	for(int i = 0; i < productNum; ++i){
		int addedSize = 0;
		char *productHTML =  calloc(templateSize+1, 1);
		strcpy(productHTML, template);
		expand(&productHTML, strlen(productHTML)+1, strlen(product[i].id), offsets2[0]+addedSize, product[i].id);
		addedSize = strlen(product[i].id);
		expand(&productHTML, strlen(productHTML)+1, strlen(product[i].img), offsets2[1]+addedSize, product[i].img);
		addedSize += strlen(product[i].img);
		expand(&productHTML, strlen(productHTML)+1, strlen(product[i].title), offsets2[2]+addedSize, product[i].title);
		addedSize += strlen(product[i].title);
		expand(&productHTML, strlen(productHTML)+1, strlen(product[i].description), offsets2[3]+addedSize, product[i].description);
		addedSize += strlen(product[i].description);
		if(product[i].tableCount != 0){
			char tableBegin[8] = "<table>";
			expand(&productHTML, strlen(productHTML)+1, 7, offsets2[3]+addedSize+5, tableBegin);
			addedSize += 7;
			for(int j = 0; j < product[i].tableCount; ++j){
				char table[5] = "<tr>";
				char table1[5] = "<td>";
				char table2[6] = "</td>";
				char table3[6] = "</tr>";
				expand(&productHTML, strlen(productHTML)+1, 4, offsets2[3]+addedSize+5, table);
				addedSize += 4;
				expand(&productHTML, strlen(productHTML)+1, 4, offsets2[3]+addedSize+5, table1);
				addedSize += 4;
				expand(&productHTML, strlen(productHTML)+1, strlen(product[i].tableLeft[j]), offsets2[3]+addedSize+5, product[i].tableLeft[j]);
				addedSize += strlen(product[i].tableLeft[j]);
				expand(&productHTML, strlen(productHTML)+1, 5, offsets2[3]+addedSize+5, table2);
				addedSize += 5;
				expand(&productHTML, strlen(productHTML)+1, 4, offsets2[3]+addedSize+5, table1);
				addedSize += 4;
				expand(&productHTML, strlen(productHTML)+1, strlen(product[i].tableRight[j]), offsets2[3]+addedSize+5, product[i].tableRight[j]);
				addedSize += strlen(product[i].tableRight[j]);
				expand(&productHTML, strlen(productHTML)+1, 5, offsets2[3]+addedSize+5, table2);
				addedSize += 5;
				expand(&productHTML, strlen(productHTML)+1, 5, offsets2[3]+addedSize+5, table3);
				addedSize += 5;
			}
			char tableEnd[9] = "</table>";
			expand(&productHTML, strlen(productHTML)+1, 8, offsets2[3]+addedSize+5, tableEnd);
			addedSize += 8;
		}
		expand(&productHTML, strlen(productHTML)+1, strlen(product[i].price), offsets2[4]+addedSize, product[i].price);
		expand(&templateHTML, strlen(templateHTML)+1, strlen(productHTML), offset, productHTML);
		offset += strlen(productHTML);
		free(productHTML);
	}
	
	file = fopen("web/index.html", "w");
	fprintf(file, "%s", templateHTML);
	free(templateHTML);
	freeAll();
	fclose(file);

	return 0;
}

int returnFileSize(FILE *file){
  fseek(file, 0, SEEK_END);
  int fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);
  return fileSize;
}
int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	NotUsed = 0;
	char id[15];
	sprintf(id, "%d", productNum);
	product[productNum].id = calloc(strlen(id)+1, 1);
	strcpy(product[productNum].id, id);
	
	product[productNum].img = calloc(strlen(argv[0])+1, 1);
	strcpy(product[productNum].img, argv[0]);
	product[productNum].title = calloc(strlen(argv[1])+1, 1);
	strcpy(product[productNum].title, argv[1]);
	product[productNum].tag = calloc(strlen(argv[2])+1, 1);
	strcpy(product[productNum].tag, argv[2]);
	product[productNum].description = calloc(strlen(argv[3])+1, 1);
	strcpy(product[productNum].description, argv[3]);
	product[productNum].price = calloc(strlen(argv[4])+1, 1);
	strcpy(product[productNum].price, argv[4]);
	
	sscanf(argv[5], "%d", &product[productNum].tableCount);

	for(int i = 0; i < product[productNum].tableCount; ++i){
		product[productNum].tableLeft[i] = calloc(strlen(argv[6+2*i])+1, 1);
		strcpy(product[productNum].tableLeft[i], argv[6+2*i]);
		product[productNum].tableRight[i] = calloc(strlen(argv[7+2*i])+1, 1);
		strcpy(product[productNum].tableRight[i], argv[7+2*i]);
	}

	++productNum;

	return 0;
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
void freeAll(){
	for(int i = 0; i < productNum; ++i){
		free(product[i].id);
		free(product[i].img);
		free(product[i].title);
		free(product[i].tag);
		free(product[i].description);
		free(product[i].price);
		for(int j = 0; j < product[i].tableCount; ++j){
			free(product[i].tableLeft[j]);
			free(product[i].tableRight[j]);
		}
	}
}