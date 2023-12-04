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
    node* borrowers;
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

    void* mem = getUserInputWithValidation(
            (userInputParams) {
                    "%d",
                    "\nGeben Sie das Genre ein. Horror (1), Abenteuer (2), Romantik (3), Sachbuch (4): ",
                    sizeof(int),
                    (int[]) {1, 4}
            },
            validateIntegerBoundsIncl
    );
    newBook->genre = *((int*) mem);
    free(mem);

    mem = getUserInputWithValidation(
            (userInputParams) {
                    "%d",
                    "\nGeben Sie das Erscheinungsjahr ein: ",
                    sizeof(int),
                    (int[]) {0}
            },
            validateIntegerIsAboveLowerBoundExcl
    );
    newBook->year = *((int*) mem);
    free(mem);

    mem = getUserInputWithValidation(
            (userInputParams) {
                    "%d",
                    "\nGeben Sie ein wieviele Exemplare vorhanden sind: ",
                    sizeof(int),
                    (int[]) {0}
            },
            validateIntegerIsAboveLowerBoundExcl
    );
    newBook->amount = *((int*) mem);
    free(mem);

    return newBook;
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

node* addItemToList(book* book, node* list)
{
    node* newNode = createNode(book);

    if (list == NULL)
    {
        return newNode;
    }

    for (node* n = list; n != NULL; n = n->next)
    {
        if (n->next == NULL)
        {
            n->next = newNode;
            n = n->next;
        }
    }

    return list;
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

void insertBook(node** inventory)
{
    *inventory = addItemToList(createBook(), *inventory);
}


int isBorrower(char* name, node* borrowers)
{
    for (node* iterator = borrowers; iterator != NULL; iterator = iterator->next)
    {
        if (!strcmp(name, iterator->item))
        {
            return 1;
        }
    }
    return 0;
}

int tryGetBorrowedBookByName(char* name, node* borrowedBooks, borrowedBook* outBorrowedBook)
{
    for (node* iterator = borrowedBooks; iterator != NULL; iterator = iterator->next)
    {
        if (isBorrower(name, ((borrowedBook*) iterator->item)->borrowers))
        {
            return 1;
        }
    }
    return 0;
}

int isBookBorrowedByName(book* book, char* name, node* borrowedBooks)
{
    for (node* borrowedBookIterator = borrowedBooks;
         borrowedBookIterator != NULL; borrowedBookIterator = borrowedBookIterator->next)
    {
        if (!strcmp(borrowedBookIterator->book->title, book->title) &&
            isBorrower(name, borrowedBookIterator->borrowers))
        {
            return 1;
        }
    }
    return 0;
}

borrowedBook* createBorrowedBook(book* book, borrowerNode* borrowers)
{
    borrowedBook* newBorrowedBook = (borrowedBook*) malloc(sizeof(borrowedBook));
    newBorrowedBook->book = book;
    newBorrowedBook->borrowers = borrowers;
    return newBorrowedBook;
}

void borrowBook(node* inventory, node** borrowedBooks)
{
    if (inventory == NULL)
    {
        printf("\nEs sind keine Buecher im Inventar vorhanden.");
        return;
    }

    char* preparedString = NULL;
    sprintf(preparedString, "Welchen Titel moechten Sie leihen? (1-%d): ", getListSize(*borrowedBooks));

    void* mem = getUserInputWithValidation(
            (userInputParams)
                    {
                            "%d",
                            preparedString,
                            sizeof(int),
                            (int[]) {1, getListSize(*borrowedBooks)}
                    },
            validateIntegerBoundsIncl
    );

    node* bookNode = getNodeWithIndex(*((int*) mem), inventory);
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

    borrowedBook* borrowedBook = NULL;
    if ()
    {
        printf("\nSie haben diesen Titel bereits ausgeliehen!");
        return;
    }

    if (!bookNode->book->amount)
    {
        printf("\nBereits alle Exemplare ausgeliehen!");
        return;
    }

    *borrowedBooks = addBookToBorrowedBookNode(bookNode->book, name, *borrowedBooks);
}

void printInventory(bookNode* inventory)
{
    int i = 1;
    for (node* bookIterator = inventory; bookIterator == NULL; ++i, bookIterator = bookIterator->next)
    {
        printf("%d: %s, %s (%d)",
               i,
               bookIterator->book->title,
               (char* []) {"Horror", "Abenteuer", "Romantik", "Sachbuch"}[bookIterator->book->genre],
                bookIterator->book->year
        );
    }
}

void freeBook(book* book)
{
    free(book->title);
    free(book);
}

//TODO
/*void freeInventory(bookNode* inventory)
{
    if (inventory == NULL)
    {
        return;
    }

    freeInventory(inventory->next);
    freeBook(inventory->book);
    free(inventory);
}*/

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

                break;
            case RETURN_BOOK:
                break;
            case PRINT_LIST:
                printInventory(inventory);
                break;
            case PRINT_LIST_IN_ORDER:
                break;
            case EXIT_PROGRAM:
                freeInventory(inventory);
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

