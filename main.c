#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_TITLE_LENGTH 31
#define VALID_MENU_ACTIONS "nbrlsx"

//####################################################//
//# ICH HABE DEN TEST NICHT GANZ NACH ANGABE GEMACHT #//
//####################################################//

enum genre_type
{
    HORROR,
    ADVENTURE,
    ROMANCE,
    NON_FICTION
} typedef genre_type;

struct node
{
    void* item;
    struct node* next;
} typedef node;

struct book
{
    char* title;
    genre_type genre;
    int year;
    int amount;
} typedef book;

struct borrowedBook
{
    book* book;
    char* borrower;
} typedef borrowedBook;

struct userInputParams
{
    char* inputType;
    char* message;

    int memSize;
    void* validationData;
} typedef userInputParams;

int validateGenericTypeAsChar(const void* type, const void* types)
{
    return strchr((char*) types, *((char*) type)) != NULL;
}

int validateIntegerIsAboveLowerBoundExcl(const void* number, const void* lowerBound)
{
    return *((int*) number) > *((int*) lowerBound);
}

int validateIntegerBoundsIncl(const void* number, const void* bounds)
{
    return *((int*) number) >= ((int*) bounds)[0] && *((int*) number) <= ((int*) bounds)[1];
}

int validateStringLength(const void* string, const void* length)
{
    for (int i = 0; i < *((int*) length) + 1; ++i)
    {
        if (((char*) string)[i] == '\0')
        {
            return 1;
        }
    }
    return 0;
}

void* getUserInputWithValidation(const userInputParams params, int validate(const void*, const void*))
{
    void* memory = malloc(params.memSize);
    while (1)
    {
        printf("%s", params.message);
        scanf(params.inputType, memory);

        if (validate(memory, params.validationData))
        {
            return memory;
        }

        printf("\nUngueltige Eingabe");
    }
}

void printList(node* list, void printItem(const void*))
{
    int i = 1;
    for (node* iterator = list; iterator != NULL; ++i, iterator = iterator->next)
    {
        printf("\n%d: ", i);
        printItem(iterator->item);
    }

    printf("\n");
}

void printBook(const void* item)
{
    printf("%s, %s (%d)",
           ((book*) item)->title,
           (char* []) {"Horror", "Abenteuer", "Romantik", "Sachbuch"}[((book*) item)->genre - 1],
            ((book*) item)->year
    );
}

void printBorrowedBook(const void* item)
{
    borrowedBook* borrowedBook = ((struct borrowedBook*) item);

    printf("%s geliehen von %s", borrowedBook->book->title, borrowedBook->borrower);
}

int getListSize(node* list)
{
    int size = 0;
    for (node* iterator = list; iterator != NULL; iterator = iterator->next, size++);

    return size;
}

int listContainsItem(void* item, node* list)
{
    for (node* iterator = list; iterator != NULL; iterator = iterator->next)
    {
        if (item == iterator)
        {
            return 1;
        }
    }
    return 0;
}

node* createNode(void* item)
{
    node* newNode = (node*) malloc(sizeof(node));
    newNode->item = item;
    newNode->next = NULL;

    return newNode;
}

void freeNode(node* node, void freeItem(void*))
{
    freeItem(node->item);
    free(node);
}

void freeBook(void* book)
{
    free(((struct book*) book)->title);
    free(book);
}

void freeBorrowedBook(void* borrowedBook)
{
    free(((struct borrowedBook*) borrowedBook)->borrower);
    free(borrowedBook);
}

void freeList(node* list, void freeItem(void*))
{
    if (list == NULL)
    {
        return;
    }

    freeList(list->next, freeItem);
    freeNode(list, freeItem);
}

node* addItemToList(void* item, node* list)
{
    node* newNode = createNode(item);

    if (list == NULL)
    {
        return newNode;
    }
    newNode->next = list;
    return newNode;
}

node* getNodeWithIndex(int index, node* list)
{
    for (node* iterator = list; iterator != NULL; iterator = iterator->next)
    {
        if (!(--index))
        {
            return iterator;
        }
    }

    return NULL;
}

node* removeItemFromListAtIndex(int index, node* list, void freeItem(void*))
{
    if (index == 0)
    {
        node* next = list->next;
        freeNode(list, freeItem);

        return next;
    }

    node* previous = getNodeWithIndex(index - 1, list);
    node* node = previous->next;

    previous->next = node->next;
    freeNode(node, freeItem);

    return list;
}

book* createBook()
{
    book* newBook = (book*) malloc(sizeof(book));

    newBook->title = (char*) getUserInputWithValidation(
            (userInputParams) {
                    "%s",
                    "\nGeben Sie den Titel ein: ",
                    MAX_TITLE_LENGTH + 1,
                    (int[]) {MAX_TITLE_LENGTH}
            },
            validateStringLength
    );

    int* genre = getUserInputWithValidation(
            (userInputParams) {
                    "%d",
                    "\nGeben Sie das Genre ein. Horror (1), Abenteuer (2), Romantik (3), Sachbuch (4): ",
                    sizeof(int),
                    (int[]) {1, 4}
            },
            validateIntegerBoundsIncl
    );
    newBook->genre = *genre;
    free(genre);

    int* year = getUserInputWithValidation(
            (userInputParams) {
                    "%d",
                    "\nGeben Sie das Erscheinungsjahr ein: ",
                    sizeof(int),
                    (int[]) {0}
            },
            validateIntegerIsAboveLowerBoundExcl
    );
    newBook->year = *year;
    free(year);

    int* amount = getUserInputWithValidation(
            (userInputParams) {
                    "%d",
                    "\nGeben Sie ein wieviele Exemplare vorhanden sind: ",
                    sizeof(int),
                    (int[]) {0}
            },
            validateIntegerIsAboveLowerBoundExcl
    );
    newBook->amount = *amount;
    free(amount);

    return newBook;
}

void insertBook(node** inventory)
{
    *inventory = addItemToList(createBook(), *inventory);
}

borrowedBook* createBorrowedBook(book* book, char* name)
{
    borrowedBook* newBorrowedBook = (borrowedBook*) malloc(sizeof(borrowedBook));
    newBorrowedBook->book = book;
    newBorrowedBook->borrower = name;
    return newBorrowedBook;
}

//TODO clean up
int isBorrower(char* name, book* book, node* borrowedBooks)
{
    for (node* iterator = borrowedBooks; iterator != NULL; iterator = iterator->next)
    {
        if (((borrowedBook*) iterator->item)->book == book && !strcmp(((borrowedBook*) iterator->item)->borrower, name))
        {
            return 1;
        }
    }
    return 0;
}


//borrowedBook* getBorrowedBookByBook(book* book, node* borrowedBooks) {
//    for (node* iterator = borrowedBooks; iterator != NULL; iterator = iterator->next)
//    {
//        if (((borrowedBook*) iterator->item)->book == book)
//        {
//            return ((borrowedBook*) iterator->item);
//        }
//    }
//    return NULL;
//}

/*int tryGetBorrowedBookByBook(book* book, node* borrowedBooks, borrowedBook** outBorrowedBook)
{
    for (node* iterator = borrowedBooks; iterator != NULL; iterator = iterator->next)
    {
        if (((borrowedBook*) iterator->item)->book == book)
        {
            *outBorrowedBook = ((borrowedBook*) iterator->item);
            return 1;
        }
    }
    return 0;
}*/

void borrowBook(node* inventory, node** borrowedBooks)
{
    if (inventory == NULL)
    {
        printf("\nEs sind keine Buecher im Inventar vorhanden.");
        return;
    }

    printList(inventory, printBook);

    char preparedString[100];
    sprintf(preparedString, "\nWelchen Titel moechten Sie leihen? (1-%d): ", getListSize(inventory));

    void* mem = getUserInputWithValidation(
            (userInputParams)
                    {
                            "%d",
                            preparedString,
                            sizeof(int),
                            (int[]) {1, getListSize(inventory)}
                    },
            validateIntegerBoundsIncl
    );

    book* book = (struct book*) getNodeWithIndex(*((int*) mem), inventory)->item;
    free(mem);

    char* name = (char*) getUserInputWithValidation(
            (userInputParams) {
                    "%s",
                    "\nGeben Sie Ihren Namen ein: ",
                    MAX_TITLE_LENGTH + 1,
                    (int[]) {MAX_TITLE_LENGTH}
            },
            validateStringLength
    );

    if (isBorrower(name, book, *borrowedBooks))
    {
        printf("\nSie haben diesen Titel bereits ausgeliehen!");
        return;
    }

    if (!book->amount)
    {
        printf("\nBereits alle Exemplare ausgeliehen!");
        return;
    }

    *borrowedBooks = addItemToList(createBorrowedBook(book, name), *borrowedBooks);
    book->amount--;
}

void returnBook(node* inventory, node** borrowedBooks)
{
    if (*borrowedBooks == NULL)
    {
        printf("\nEs sind keine Titel ausgeliehen!");
    }

    printList(*borrowedBooks, printBorrowedBook);

    char preparedString[100];
    sprintf(preparedString, "Welchen Titel moechten Sie retournieren? (1-%d): ", getListSize(*borrowedBooks));
    int* index = (int*) getUserInputWithValidation(
            (userInputParams) {
                    "%d",
                    preparedString,
                    sizeof(int),
                    (int[]) {1, getListSize(*borrowedBooks)}
            },
            validateIntegerBoundsIncl
    );

    ((book*)getNodeWithIndex(*index, *borrowedBooks)->item)->amount++;
    *borrowedBooks = removeItemFromListAtIndex(*index, *borrowedBooks, freeBorrowedBook);

    free(index);
}

enum menuAction
{
    INSERT_BOOK = 'n',
    BORROW_BOOK = 'b',
    RETURN_BOOK = 'r',
    PRINT_LIST = 'l',
    PRINT_LIST_IN_ORDER = 's',
    EXIT_PROGRAM = 'x'
} typedef menuAction;

void programMenu(node* inventory, node* borrowedBooks)
{
    void* mem = NULL;

    while (1)
    {
        mem = getUserInputWithValidation(
                (userInputParams) {
                        " %c",
                        "\nNeues Buch eingeben (n), Buch ausleihen (b), Buch zurueckgeben (r), Buecher auflisten (l), Buecher sortieren (s), Programm beenden (x)\nAuswahl: ",
                        sizeof(char),
                        VALID_MENU_ACTIONS
                },
                validateGenericTypeAsChar
        );

        switch ((menuAction) *((char*) mem))
        {
            case INSERT_BOOK:
                insertBook(&inventory);
                break;
            case BORROW_BOOK:
                borrowBook(inventory, &borrowedBooks);
                break;
            case RETURN_BOOK:
                returnBook(inventory, &borrowedBooks);
                break;
            case PRINT_LIST:
                //printf("\nsize: %d", getListSize(inventory));
                printList(inventory, printBook);
                break;
            case PRINT_LIST_IN_ORDER:
                break;
            case EXIT_PROGRAM:
                freeList(inventory, freeBook);
                freeList(borrowedBooks, freeBorrowedBook);
                free(mem);
                return;
        }
        free(mem);
    }
}

int main()
{
    node* inventory = NULL;
    node* borrowedBooks = NULL;
    programMenu(inventory, borrowedBooks);

    return 0;
}

