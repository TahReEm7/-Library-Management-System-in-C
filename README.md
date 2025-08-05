# Library Management System (C)

This is a simple terminal-based Library Management System implemented in C. It manages book cataloging, user registration, borrowing, returning, and penalty calculation for late returns.

## Features
- Add, update, delete books
- Register users
- Search books by title or subject
- Borrow and return books with date tracking
- Late return penalty calculation
- Persistent data storage using binary files

## Usage
- Compile with `gcc library.c -o library`
- Run with `./library`
- Follow on-screen menu prompts

## File storage
- `books.dat` stores book data
- `users.dat` stores user data

## Limitations
- Supports up to 100 books and 100 users
- Single book per user borrowing limit

## Author
Tahreem Hossain

