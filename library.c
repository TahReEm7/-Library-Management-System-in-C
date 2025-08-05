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
// Utility: Get today's date
Date getTodayDate() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    Date d = {tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900};
    return d;
}

// Utility: Compare two dates
int dateDiff(Date d1, Date d2) {
    struct tm tm1 = {0, 0, 0, d1.day, d1.month - 1, d1.year - 1900};
    struct tm tm2 = {0, 0, 0, d2.day, d2.month - 1, d2.year - 1900};
    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);
    double diff = difftime(t2, t1);
    return (int)(diff / (60 * 60 * 24));
}

// Add a book
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Book storage full!\n");
        return;
    }

    books[bookCount].id = bookCount + 1;
    printf("Enter book title: ");
    getchar(); // flush newline
    fgets(books[bookCount].title, MAX_STRING, stdin);
    strtok(books[bookCount].title, "\n");

    printf("Enter author: ");
    fgets(books[bookCount].author, MAX_STRING, stdin);
    strtok(books[bookCount].author, "\n");

    printf("Enter subject: ");
    fgets(books[bookCount].subject, MAX_STRING, stdin);
    strtok(books[bookCount].subject, "\n");

    books[bookCount].available = 1;
    printf("Book added with ID: %d\n", books[bookCount].id);
    bookCount++;
}

// Register user
void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached!\n");
        return;
    }

    users[userCount].id = userCount + 1;
    printf("Enter user name: ");
    getchar();
    fgets(users[userCount].name, MAX_STRING, stdin);
    strtok(users[userCount].name, "\n");

    printf("Enter password: ");
    fgets(users[userCount].password, MAX_STRING, stdin);
    strtok(users[userCount].password, "\n");

    users[userCount].borrowedBookId = -1;
    printf("User registered with ID: %d\n", users[userCount].id);
    userCount++;
}
