#ifndef functions
#define functions

#include "sqlite\sqlite3.h"

void print();
int returnFileSize(FILE *file);
void expand(char **html, int size, int length, int offset, char *toAdd);
void update();
void print_list();
void finish_read();
void change_url(sqlite3 *db, int index);
void change_title(sqlite3 *db, int index);
void change_tag(sqlite3 *db, int index);
void change_description(sqlite3 *db, int index);
void change_price(sqlite3 *db, int index);
void change_table(sqlite3 *db, int index);
void change_row(sqlite3 *db, int index);
void insert_row(sqlite3 *db, int index);
void delete_row(sqlite3 *db, int index);
void modify();
void delete();
void finish_read();
void insert();

#endif