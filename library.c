#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constants
#define MAX_BOOKS 100
#define MAX_USERS 100
#define MAX_STRING 100
#define BORROW_DAYS 7
#define PENALTY_PER_DAY 5

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
    int penalty;
} User;

// Global arrays
Book books[MAX_BOOKS];
User users[MAX_USERS];
int bookCount = 0, userCount = 0;

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

// Book Management Functions
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Book storage full!\n");
        return;
    }

    Book *b = &books[bookCount];
    b->id = bookCount + 1;

    printf("Enter book title: ");
    getchar(); // flush newline
    fgets(b->title, MAX_STRING, stdin);
    b->title[strcspn(b->title, "\n")] = '\0';

    printf("Enter author: ");
    fgets(b->author, MAX_STRING, stdin);
    b->author[strcspn(b->author, "\n")] = '\0';

    printf("Enter subject: ");
    fgets(b->subject, MAX_STRING, stdin);
    b->subject[strcspn(b->subject, "\n")] = '\0';

    b->available = 1;
    bookCount++;
    printf("Book added with ID: %d\n", b->id);
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

void viewBooks() {
    if (bookCount == 0) {
        printf("No books available.\n");
        return;
    }
    printf("All Books:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("ID: %d | Title: %s | Author: %s | Subject: %s | Available: %s\n",
            books[i].id, books[i].title, books[i].author, books[i].subject,
            books[i].available ? "Yes" : "No");
    }
}

void searchBooks() {
    char keyword[MAX_STRING];
    printf("Enter keyword to search (title or subject): ");
    getchar(); // clear buffer
    fgets(keyword, MAX_STRING, stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    int found = 0;
    printf("Search Results:\n");
    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, keyword) != NULL || strstr(books[i].subject, keyword) != NULL) {
            printf("ID: %d | Title: %s | Author: %s | Subject: %s | Available: %s\n",
                books[i].id, books[i].title, books[i].author, books[i].subject,
                books[i].available ? "Yes" : "No");
            found = 1;
        }
    }
    if (!found) {
        printf("No books found with keyword '%s'.\n", keyword);
    }
}

// User Management
void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached!\n");
        return;
    }

    User *u = &users[userCount];
    u->id = userCount + 1;

    printf("Enter user name: ");
    getchar();
    fgets(u->name, MAX_STRING, stdin);
    u->name[strcspn(u->name, "\n")] = '\0';

    printf("Enter password: ");
    fgets(u->password, MAX_STRING, stdin);
    u->password[strcspn(u->password, "\n")] = '\0';

    u->borrowedBookId = -1;
    u->penalty = 0;
    userCount++;
    printf("User registered with ID: %d\n", u->id);
}

int findUserById(int id) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == id) return i;
    }
    return -1;
}

int findBookById(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) return i;
    }
    return -1;
}

// Borrow book
void borrowBook() {
    int userId, bookId;
    printf("Enter your user ID: ");
    scanf("%d", &userId);
    int uIndex = findUserById(userId);
    if (uIndex == -1) {
        printf("User not found.\n");
        return;
    }
    if (users[uIndex].borrowedBookId != -1) {
        printf("You already borrowed a book (ID: %d).\n", users[uIndex].borrowedBookId);
        return;
    }

    printf("Enter Book ID to borrow: ");
    scanf("%d", &bookId);
    int bIndex = findBookById(bookId);
    if (bIndex == -1) {
        printf("Book not found.\n");
        return;
    }
    if (!books[bIndex].available) {
        printf("Book is not available.\n");
        return;
    }

    books[bIndex].available = 0;
    users[uIndex].borrowedBookId = bookId;
    users[uIndex].borrowDate = getTodayDate();
    users[uIndex].penalty = 0;

    printf("Book borrowed successfully on %02d-%02d-%d.\n",
        users[uIndex].borrowDate.day,
        users[uIndex].borrowDate.month,
        users[uIndex].borrowDate.year);
}

// Return book with penalty calculation
void returnBook() {
    int userId;
    printf("Enter your user ID: ");
    scanf("%d", &userId);
    int uIndex = findUserById(userId);
    if (uIndex == -1) {
        printf("User not found.\n");
        return;
    }
    if (users[uIndex].borrowedBookId == -1) {
        printf("You have no book to return.\n");
        return;
    }

    int bIndex = findBookById(users[uIndex].borrowedBookId);
    if (bIndex != -1) {
        books[bIndex].available = 1;
    }

    Date today = getTodayDate();
    int daysBorrowed = dateDiff(users[uIndex].borrowDate, today);

    if (daysBorrowed > BORROW_DAYS) {
        users[uIndex].penalty = (daysBorrowed - BORROW_DAYS) * PENALTY_PER_DAY;
    } else {
        users[uIndex].penalty = 0;
    }

    printf("Book ID %d returned successfully.\n", users[uIndex].borrowedBookId);
    printf("Days borrowed: %d\n", daysBorrowed);
    if (users[uIndex].penalty > 0) {
        printf("Late return penalty: %d\n", users[uIndex].penalty);
    } else {
        printf("No penalty.\n");
    }

    users[uIndex].borrowedBookId = -1;
}

// File operations
void saveBooksToFile() {
    FILE *fp = fopen("books.dat", "wb");
    if (!fp) {
        printf("Failed to save books.\n");
        return;
    }
    fwrite(&bookCount, sizeof(int), 1, fp);
    fwrite(books, sizeof(Book), bookCount, fp);
    fclose(fp);
}

void loadBooksFromFile() {
    FILE *fp = fopen("books.dat", "rb");
    if (!fp) return;  // First run: file may not exist

    fread(&bookCount, sizeof(int), 1, fp);
    fread(books, sizeof(Book), bookCount, fp);
    fclose(fp);
}

void saveUsersToFile() {
    FILE *fp = fopen("users.dat", "wb");
    if (!fp) {
        printf("Failed to save users.\n");
        return;
    }
    fwrite(&userCount, sizeof(int), 1, fp);
    fwrite(users, sizeof(User), userCount, fp);
    fclose(fp);
}

void loadUsersFromFile() {
    FILE *fp = fopen("users.dat", "rb");
    if (!fp) return;

    fread(&userCount, sizeof(int), 1, fp);
    fread(users, sizeof(User), userCount, fp);
    fclose(fp);
}

// Main menu
void mainMenu() {
    int choice;
    while (1) {
        printf("\n=== Library Management System ===\n");
        printf("1. Register User\n");
        printf("2. Add Book\n");
        printf("3. View All Books\n");
        printf("4. Search Books\n");
        printf("5. Borrow Book\n");
        printf("6. Return Book\n");
        printf("7. Update Book\n");
        printf("8. Delete Book\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: registerUser(); break;
            case 2: addBook(); break;
            case 3: viewBooks(); break;
            case 4: searchBooks(); break;
            case 5: borrowBook(); break;
            case 6: returnBook(); break;
            case 7: updateBook(); break;
            case 8: deleteBook(); break;
            case 9:
                printf("Exiting program. Goodbye!\n");
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

int main() {
    loadBooksFromFile();
    loadUsersFromFile();

    printf("Welcome to the Library Management System!\n");
    mainMenu();

    saveBooksToFile();
    saveUsersToFile();

    printf("Thank you for using the system. Goodbye!\n");
    return 0;
}
// End of library.c