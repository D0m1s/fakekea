#include <stdio.h>
#include <stdlib.h>
#include "sqlite\sqlite3.h"
#include <conio.h>

void print_list();
void finish_read();
void change_url();
void change_title();
void change_tag();
void change_description();
void change_price();

int main()
{
	sqlite3 *db;
	sqlite3_open("data/db.db", &db);
	int index = 1;

	sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "select count(*) from product", -1, &stmt, NULL);
    rc = sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);

	for(;;) {
		printf("Welcome to the product modifier! Enter the index of the product you'd like to modify:\n");
		if(scanf("%d", &index)==1&&getchar()=='\n') {
			if(index>=count) {
				printf("You've entered a number higher than the product count! Try again.\n");
			} else if(index<0) {
				printf("You can't modify a product that doesn't exist!\n");
			} else {
				break;
			}
		} else {
			printf("Invalid input.\n");
			while(getchar()!='\n')
				;
		}
	}

	printf("Product chosen!\n");
	print_list();
	char command;
	for(;;) {
		if(kbhit()) {
			command = getch();
			switch(command) {
				case '1':
					change_url();
					print_list();
					break;
				case '2':
					change_title();
					print_list();
					break;
				case '3':
					change_tag();
					print_list();
					break;
				case '4':
					change_description();
					print_list();
					break;
				case '5':
					change_price();
					print_list();
					break;
				case '0':
					return 0;
			}
		}

	}
	
	char *query = malloc(1000);
	char *test = "abcd";
	// pakeicia pirmos prekes title, vietoj title galima rasyti kitus is create.c ir atitinkamai ta pakeis
	
	sprintf(query, "update product set title = '%s' where rowid = %d", test, index);
	if(sqlite3_exec(db, query, NULL, NULL, NULL)){ 
		printf("Error\n");
	} else{
		printf("Success\n");
	}

	free(query);
	sqlite3_close(db);

}

void print_list() {
	printf("What would you like to modify?\n");
	printf("1 - Image Url\n"
		   "2 - Title\n"
		   "3 - Tag\n"
		   "4 - Description\n"
		   "5 - Price\n"
		   "0 - Exit Program\n");
}

void change_url() {
    printf("Enter new image URL: ");
    char img[100];
    scanf("%100[^\n]", img);
    finish_read();
}

void finish_read() {
    if (getchar() != '\n')
    {
        while (getchar() != '\n')
            ;
    }
}

void change_title() {
	printf("Enter new title: ");
    char title[100];
    scanf("%100[^\n]", title);
    finish_read();
}

void change_tag() {
	printf("Enter new tag: ");
    char tag[100];
    scanf("%100[^\n]", tag);
    finish_read();
}

void change_description() {
	printf("Enter new description: ");
    char description[100];
    scanf("%100[^\n]", description);
    finish_read();
}

void change_price() {
    double price;
    for(;;) {
        printf("Enter price: ");
        if(scanf("%lf", &price)==1&&getchar()=='\n') {
            break;
        } else {
            printf("Invalid input.\n");
            while(getchar()!='\n')
                ;
        }
    }
}