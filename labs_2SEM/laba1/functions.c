#include "header.h"



void showBooksTable(struct Book *books, int count)
{
    if (count == 0)
    {
        printf("\nКниги не найдены.\n");
        return;
    }

    // Вывод строк с данными
    for (int i = 0; i < count; i++)
    {
        printf("%-*d %-*s %-*s %d\n",
               NUM_WIDTH, i + 1, // Номер книги остаётся слева
               AUTHOR_WIDTH, (books + i)->author,
               TITLE_WIDTH, (books + i)->title,
               (books + i)->year);
    }
}



void findBooks(struct Book *books, int count, int searchType)
{
    struct Book *foundBooks = (struct Book *)malloc(count * sizeof(struct Book));
    if (foundBooks == NULL)
    {
        printf("Ошибка выделения памяти для поиска книг!\n");
        exit(1);
    }
    int foundCount = 0;

    while (1)
    {
        if (searchType == 0 || searchType == 2)
        {
            char *searchStr = NULL;
            if (searchType == 0)
                printf("\nВведите фамилию автора для поиска: ");
            else
                printf("\nВведите название книги для поиска: ");
            getValidString(&searchStr);

            for (int i = 0; i < count; i++)
            {
                if ((searchType == 0 && isSameString((books + i)->author, searchStr)) ||
                    (searchType == 2 && isSameString((books + i)->title, searchStr)))
                {
                    *(foundBooks + foundCount) = *(books + i);
                    foundCount++;
                }
            }

            if (foundCount == 0)
            {
                printf("\nНет совпадений для \"%s\". Попробуйте снова.\n", searchStr);
                free(searchStr);
                continue;
            }
            else
            {
                if (searchType == 0)
                    printf("\nНайденные книги автора \"%s\":\n", searchStr);
                else
                    printf("\nНайденные книги с названием \"%s\":\n", searchStr);
            }
            free(searchStr);
            break;
        }
        else if (searchType == 1)
        {
            int searchYear;
            printf("\nВведите год издания для поиска: ");
            searchYear = getValidInt(MIN_YEAR, MAX_YEAR);

            for (int i = 0; i < count; i++)
            {
                if ((books + i)->year == searchYear)
                {
                    *(foundBooks + foundCount) = *(books + i);
                    foundCount++;
                }
            }

            if (foundCount == 0)
            {
                printf("\nКниги из года %d не найдены. Попробуйте снова.\n", searchYear);
                continue;
            }
            else
            {
                printf("\nНайденные книги из года %d:\n", searchYear);
            }
            break;
        }
        else if (searchType == 3)
        {
            int restartChoice;
            printf("\nХотите перезапустить программу? (1 для Да, любое другое число для возврата в главное меню): ");
            restartChoice = getValidInt(1, INT_MAX);
            free(foundBooks);
            return;
        }
    }

    showBooksTable(foundBooks, foundCount);

    if (foundCount > 1)
    {
        int choice;
        printf("\nВведите номер книги, которую хотите выбрать (от 1 до %d): ", foundCount);
        choice = getValidInt(1, foundCount);
        printf("\nВы выбрали книгу %d:\n", choice);
        showBooksTable(foundBooks + choice - 1, 1);
    }

    free(foundBooks);
}


void sortBooksByYear(struct Book *books, int count, int descending)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if ((descending && (books + i)->year < (books + j)->year) ||
                (!descending && (books + i)->year > (books + j)->year))
            {
                struct Book temp = *(books + i);
                *(books + i) = *(books + j);
                *(books + j) = temp;
            }
        }
    }
}


void freeBooksMem(struct Book *books, int count)
{
    if (books != NULL)
    {
        for (int i = 0; i < count; i++)
        {
            free((books + i)->author);
            free((books + i)->title);
        }
        free(books);
    }
}

void printMenu(const char *message, const char *option1, const char *option2, const char *option3, const char *option4)
{
    printf("\n%s\n", message);
    printf("1. %s\n", option1);
    printf("2. %s\n", option2);
    printf("3. %s\n", option3);
    printf("4. %s\n", option4);
}

void inputBooksData(struct Book *books, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("\nВведите данные для книги %d:\n", i + 1);
        printf("Введите фамилию автора: ");
        getValidString(&((books + i)->author));
        printf("Введите название книги: ");
        getValidString(&((books + i)->title));
        printf("Введите год издания (%d-%d): ", MIN_YEAR, MAX_YEAR);
        (books + i)->year = getValidInt(MIN_YEAR, MAX_YEAR);
    }
}


struct Book* memBooks(struct Book *books, int count, int newCount)
{
    struct Book *tempBooks = (struct Book *)realloc(books, (count + newCount) * sizeof(struct Book));
    if (tempBooks == NULL)
    {
        printf("Ошибка выделения памяти!\n");
        freeBooksMem(books, count);
        exit(1);
    }
    return tempBooks;
}

void handleUserChoices(struct Book *books, int count)
{
    int choice;
    while (1)
    {
        printMenu("Поиск книг по:", "Фамилии автора", "Году издания", "Названию", "Выход");
        choice = getValidInt(1, 4);
    
        findBooks(books, count, choice - 1);
    
        printf("\nВведите 1 для повторного поиска, любое другое число для возврата в меню выхода: ");
        choice = getValidInt(1, INT_MAX);
        if (choice != 1)
            break;
        showBooksTable(books, count);
    }
}


void SortSelection(struct Book *books, int count)
{
    int choice;
    printf("\nХотите отсортировать книги по году издания?\n1. По возрастанию\n2. По убыванию\n3. Ничего не сортировать\n");
    choice = getValidInt(1, 3);

    if (choice == 1)
    {
        sortBooksByYear(books, count, 0);
        printf("\nКниги отсортированы по году издания (по возрастанию).\n");
    }
    else if (choice == 2)
    {
        sortBooksByYear(books, count, 1);
        printf("\nКниги отсортированы по году издания (по убыванию).\n");
    }
    else if (choice == 3)
    {

    }
    // Если выбран пункт 3, сортировка не производится
}


struct Book* moveBooksAfterN(struct Book *books, int *count, int *newCount)
{
    int newBookCount = 0;
    for (int i = 0; i < *count; i++)
    {
        if ((books + i)->year > N)
        {
            newBookCount++;
        }
    }


    if (newBookCount == 0)
    {
        return NULL;
    }


    struct Book *newBooks = (struct Book *)malloc(newBookCount * sizeof(struct Book));
    if (newBooks == NULL)
    {
        printf("Ошибка выделения памяти для книг после %d года!\n", N);
        exit(1);
    }

    int j = 0; 
    for (int i = 0; i < *count; i++)
    {
        if ((books + i)->year > N)
        {
            *(newBooks + j) = *(books + i);
            j++;
        }
    }

    *newCount = newBookCount;

    struct Book *tempBooks = (struct Book *)realloc(books, (*count - newBookCount) * sizeof(struct Book));
    if (tempBooks == NULL && *count - newBookCount > 0)
    {
        printf("Ошибка перераспределения памяти!\n");
        free(newBooks);
        exit(1);
    }


    books = tempBooks;
    *count -= newBookCount;

    return newBooks;
}
