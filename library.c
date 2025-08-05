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
// Helper: Find user index by ID
int findUserById(int id) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == id) return i;
    }
    return -1;
}

// Helper: Find book index by ID
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

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    users[uIndex].borrowDate.day = tm.tm_mday;
    users[uIndex].borrowDate.month = tm.tm_mon + 1;
    users[uIndex].borrowDate.year = tm.tm_year + 1900;

    printf("Book borrowed successfully on %02d-%02d-%d.\n",
        users[uIndex].borrowDate.day,
        users[uIndex].borrowDate.month,
        users[uIndex].borrowDate.year);
}

// Return book
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

    printf("Book ID %d returned successfully.\n", users[uIndex].borrowedBookId);
    users[uIndex].borrowedBookId = -1;
}
// Search books by title or subject keyword
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

// View all books
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

// Main menu loop
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
    mainMenu();
    return 0;
}
// Save books array to file
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

// Load books array from file
void loadBooksFromFile() {
    FILE *fp = fopen("books.dat", "rb");
    if (!fp) {
        // File might not exist on first run - not an error
        return;
    }
    fread(&bookCount, sizeof(int), 1, fp);
    fread(books, sizeof(Book), bookCount, fp);
    fclose(fp);
}

// Save users array to file
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

// Load users array from file
void loadUsersFromFile() {
    FILE *fp = fopen("users.dat", "rb");
    if (!fp) {
        // File might not exist on first run - not an error
        return;
    }
    fread(&userCount, sizeof(int), 1, fp);
    fread(users, sizeof(User), userCount, fp);
    fclose(fp);
}
