#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
struct temp {
    char id[100];
    char name[100];
    char author[100];
    char search[100];
};

void addBook(struct temp *obj);
void showAll(struct temp *obj);
void extractBook(struct temp *obj);
int isAlphaString(const char *str);

int main() {
	char choice;
    struct temp obj;
	int opt;
printf("ENTER THE CODE :\t");
char c1,c2,c3,c4;
c1=getch();
printf("*");
c2=getch();
printf("*");
c3=getch();
printf("*");
c4=getch();
printf("*");
if(c1=='B' && c2=='O' && c3=='O' && c4=='K')
{
    while (1) {
        printf("----------------------------------\n");
        printf("1 - ALL BOOKS DETAIL\n");
        printf("2 - BORROW BOOK\n");
        printf("3 - ADD BOOKS\n");
        printf("4 - EXIT\n");
        printf("----------------------------------\n");
        printf("Enter Your Choice :\n");
        scanf(" %c", &choice);
        getchar(); 

        switch (choice) {
            case '1':
                showAll(&obj);
                break;
            case '2':
                extractBook(&obj);
                break;
            case '3':
                addBook(&obj);
                break;
            case '4':
                return 0;
            default:
                printf("-----Invalid Choice-----\n");
        }
    }
}
else{
	printf("\nSorry Invalid Code!!!");
}
    return 0;
}

void addBook(struct temp *obj) {
    FILE *file;

    printf("\nEnter The Book ID :\t ");
    fgets(obj->id, sizeof(obj->id), stdin);
    obj->id[strcspn(obj->id, "\n")] = '\0'; 

do {
        printf("Enter The Book Name  :\t");
        fgets(obj->name, sizeof(obj->name), stdin);
        obj->name[strcspn(obj->name, "\n")] = '\0'; 
        if (!isAlphaString(obj->name)) {
            printf("Invalid input. Please enter alphabets only!!!\n");
        }
    } while (!isAlphaString(obj->name));

    do {
        printf("Enter The Book's Author name :\t");
        fgets(obj->author, sizeof(obj->author), stdin);
        obj->author[strcspn(obj->author, "\n")] = '\0'; 
        if (!isAlphaString(obj->author)) {
            printf("Invalid input. Please enter alphabets only!!!\n");
        }
    } while (!isAlphaString(obj->author));

  
    file = fopen("bookData.txt", "a");
    if (file == NULL) {
        printf("Error opening file!!!\n");
        return;
    }

    fprintf(file, "%s*%s*%s\n", obj->id, obj->name, obj->author);
    fclose(file);
}

void showAll(struct temp *obj) {
    FILE *file;

    file = fopen("bookData.txt", "r");
    if (file == NULL) {
        printf("Error opening file!!!\n");
        return;
    }

    printf("\n\n");
    printf("\t\t Book Id \t\t\t Book Name \t\t\t Author's Name\n");

    while (fscanf(file, "%[^*]*%[^*]*%[^\n]\n", obj->id, obj->name, obj->author) != EOF) {
        printf("\t\t %s \t\t\t\t %s \t\t\t %s\n", obj->id, obj->name, obj->author);
    }

    fclose(file);
}

void extractBook(struct temp *obj) {
    FILE *file;
    int found = 0;

    showAll(obj);

    printf("Enter The Book Id :\t");
    fgets(obj->search, sizeof(obj->search), stdin);
    obj->search[strcspn(obj->search, "\n")] = '\0'; 

    file = fopen("bookData.txt", "r");
    if (file == NULL) {
        printf("Error opening file!!!\n");
        return;
    }

    printf("\n\n");
    printf("\t\t Book Id \t\t\t Book Name \t\t\t Author's Name\n");

    while (fscanf(file, "%[^*]*%[^*]*%[^\n]\n", obj->id, obj->name, obj->author) != EOF) {
        if (strcmp(obj->search, obj->id) == 0) {
            printf("\t\t %s \t\t\t %s \t\t\t %s\n", obj->id, obj->name, obj->author);
            printf("Book Borrowed Successfully!!!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("BOOK NOT FOUND!!!\n");
    }

    fclose(file);
}

int isAlphaString(const char *str) {
    while (*str) {
        if (!isalpha(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

