#include "header.h"

int main()
{
    struct Book *books = NULL;
    int count = 0;
    int choice;
    int bookCount;

    while (1)
    {
        printf("\nВведите количество книг: ");
        bookCount = getValidInt(1, INT_MAX);
        books = memBooks(books, count, bookCount);
        inputBooksData(books + count, bookCount);
        count += bookCount;

        printf("\nВсе книги:\n");
        showBooksTable(books, count);

        SortSelection(books, count);

        printf("\nКниги после сортировки:\n");
        showBooksTable(books, count);

        handleUserChoices(books, count);
        printf("\nВведите 1 для перезапуска программы или любое другое число для выхода: ");
        choice = getValidInt(1, INT_MAX);

        if (choice != 1)
        {
            freeBooksMem(books, count);
            break;
        }
        else
        {
            freeBooksMem(books, count);
            count = 0;
            books = NULL;

            printf("\nПерезапуск программы...\n");
        }
    }
    return 0;
}
