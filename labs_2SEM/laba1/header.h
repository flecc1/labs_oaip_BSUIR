#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN_YEAR 1  
#define MAX_YEAR 2025
#define N 2020


#define NUM_WIDTH    5
#define AUTHOR_WIDTH 40
#define TITLE_WIDTH  60
#define YEAR_WIDTH   15

struct Book
{
    char *author;
    char *title;
    int year;
};


struct student
{
    char* secondName;
    int age;
    float bal;
};

int getValidInt(int min, int max);
void getValidString(char **str);
int isSameString(const char *s1, const char *s2);
void showBooksTable(struct Book *books, int count);
void findBooks(struct Book *books, int count, int searchType);
void sortBooksByYear(struct Book *books, int count, int descending);
void freeBooksMem(struct Book *books, int count);
void printMenu(const char *message, const char *option1, const char *option2, const char *option3, const char *option4);
void inputBooksData(struct Book *books, int count);
struct Book* memBooks(struct Book *books, int count, int newCount);
void handleUserChoices(struct Book *books, int count);
void SortSelection(struct Book *books, int count);
struct Book* moveBooksAfterN(struct Book *books, int *count, int *newCount);