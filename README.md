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
