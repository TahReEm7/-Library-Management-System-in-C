#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constants
#define MAX_BOOKS 100
#define MAX_USERS 100
#define MAX_STRING 100

// Structures
typedef struct {
    int day, month, year;
} Date;

typedef struct {
    int id;
    char title[MAX_STRING];
    char author[MAX_STRING];
    char subject[MAX_STRING];
    int available;
} Book;

typedef struct {
    int id;
    char name[MAX_STRING];
    char password[MAX_STRING];
    int borrowedBookId;
    Date borrowDate;
} User;

// Global arrays
Book books[MAX_BOOKS];
User users[MAX_USERS];
int bookCount = 0, userCount = 0;
// Book Management Functions

void addBook() {
    Book b;
    printf("Enter book ID: ");
    scanf("%d", &b.id);
    printf("Enter title: ");
    getchar(); // flush newline
    fgets(b.title, MAX_STRING, stdin);
    b.title[strcspn(b.title, "\n")] = '\0';
    printf("Enter author: ");
    fgets(b.author, MAX_STRING, stdin);
    b.author[strcspn(b.author, "\n")] = '\0';
    printf("Enter subject: ");
    fgets(b.subject, MAX_STRING, stdin);
    b.subject[strcspn(b.subject, "\n")] = '\0';
    b.available = 1;
    books[bookCount++] = b;
    printf("Book added successfully.\n");
}

void deleteBook() {
    int id;
    printf("Enter book ID to delete: ");
    scanf("%d", &id);
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            found = 1;
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            printf("Book deleted.\n");
            break;
        }
    }
    if (!found) printf("Book not found.\n");
}

void updateBook() {
    int id;
    printf("Enter book ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            printf("Enter new title: ");
            getchar();
            fgets(books[i].title, MAX_STRING, stdin);
            books[i].title[strcspn(books[i].title, "\n")] = '\0';
            printf("Enter new author: ");
            fgets(books[i].author, MAX_STRING, stdin);
            books[i].author[strcspn(books[i].author, "\n")] = '\0';
            printf("Enter new subject: ");
            fgets(books[i].subject, MAX_STRING, stdin);
            books[i].subject[strcspn(books[i].subject, "\n")] = '\0';
            printf("Book updated.\n");
            return;
        }
    }
    printf("Book not found.\n");
}
