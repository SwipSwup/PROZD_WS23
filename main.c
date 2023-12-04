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

struct book
{
    char* title;
    genre_type genre;
    int year;
    int amount;
} typedef book;

struct bookNode
{
    book* book;
    struct bookNode* next;
} typedef bookNode;

struct borrowerNode
{
    char* name;
    struct borrowerNode* next;
} typedef borrowerNode;

struct borrowedBook {
    book* book;
    borrowerNode* borrowers;
} typedef borrowedBook;

struct borrowedBookNode
{
    borrowedBook* borrowedBook;
    struct borrowedBookNode* next;
} typedef borrowedBookNode;

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

bookNode* createBookNode(book* book)
{
    bookNode* newBookNode = (bookNode*) malloc(sizeof(bookNode));
    newBookNode->book = book;
    newBookNode->next = NULL;

    return newBookNode;
}

bookNode* addBookToInventory(book* book, bookNode* inventory)
{
    bookNode* newBookNode = createBookNode(book);

    if (inventory == NULL)
    {
        return newBookNode;
    }

    for (bookNode* b = inventory; b != NULL; b = b->next)
    {
        if (b->next == NULL)
        {
            b->next = newBookNode;
            b = b->next;
        }
    }

    return inventory;
}

bookNode* getBookNodeWithIndex(int index, bookNode* inventory)
{
    for (bookNode* bookIterator = inventory; bookIterator != NULL; bookIterator = bookIterator->next)
    {
        if (!(--index))
        {
            return bookIterator;
        }
    }

    return NULL;
}

void insertBook(bookNode** inventory)
{
    *inventory = addBookToInventory(createBook(), *inventory);
}

int getBorrowedBooksSize(borrowedBookNode* borrowedBooks)
{
    int size = 0;

    for (borrowedBookNode* borrowedBookIterator = borrowedBooks;
         borrowedBookIterator != NULL; borrowedBookIterator = borrowedBookIterator->next, size++);

    return size;
}



int isBorrower(char* name, borrowerNode* borrowedBook)
{
    for (borrowerNode* borrowerIterator = borrowedBook;
         borrowerIterator != NULL; borrowerIterator = borrowedBook->next)
    {
        if (!strcmp(name, borrowerIterator->name))
        {
            return 1;
        }
    }
    return 0;
}

int isBookBorrowed(book* book, borrowedBookNode* borrowedBooks)
{
    for (borrowedBookNode* borrowedBookIterator = borrowedBooks;
         borrowedBookIterator != NULL; borrowedBookIterator = borrowedBookIterator->next)
    {
        if (!strcmp(borrowedBookIterator->book->title, book->title))
        {
            return 1;
        }
    }
    return 0;
}

int tryGetBorrowedBookByName(char* name, borrowedBookNode* borrowedBooks, borrowedBook* outBorrowedBook) {
    for (borrowedBookNode* borrowedBookIterator = borrowedBooks;
         borrowedBookIterator != NULL; borrowedBookIterator = borrowedBookIterator->next)
    {
        if (!strcmp(borrowedBookIterator->book->title, book->title))
        {
            return 1;
        }
    }
    return 0;
}

int isBookBorrowedByName(book* book, char* name, borrowedBookNode* borrowedBooks)
{
    for (borrowedBookNode* borrowedBookIterator = borrowedBooks;
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

borrowedBookNode* createBorrowedBookNode(book* book, borrowerNode* borrowers)
{
    borrowedBookNode* newBorrowedBookNode = (borrowedBookNode*) malloc(sizeof(borrowedBookNode));
    newBorrowedBookNode->book = book;
    newBorrowedBookNode->borrowers = borrowers;
    newBorrowedBookNode->next = NULL;
    return newBorrowedBookNode;
}

borrowedBookNode* addBookToBorrowedBookNode(book* book, char* name, borrowedBookNode* borrowedBooks)
{
    if (isBookBorrowed(book, borrowedBooks))
    {

    }
}

void borrowBook(bookNode* inventory, borrowedBookNode** borrowedBooks)
{
    if (inventory == NULL)
    {
        printf("\nEs sind keine Buecher im Inventar vorhanden.");
        return;
    }

    char* preparedString = NULL;
    sprintf(preparedString, "Welchen Titel moechten Sie leihen? (1-%d): ", getBorrowedBooksSize(*borrowedBooks));

    void* mem = getUserInputWithValidation(
            (userInputParams)
                    {
                            "%d",
                            preparedString,
                            sizeof(int),
                            (int[]) {1, getBorrowedBooksSize(*borrowedBooks)}
                    },
            validateIntegerBoundsIncl
    );

    bookNode* bookNode = getBookNodeWithIndex(*((int*) mem), inventory);
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

    if (isBookBorrowedByName(bookNode->book, name, *borrowedBooks))
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
    for (bookNode* bookIterator = inventory; bookIterator == NULL; ++i, bookIterator = bookIterator->next)
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

void freeInventory(bookNode* inventory)
{
    if (inventory == NULL)
    {
        return;
    }

    freeInventory(inventory->next);
    freeBook(inventory->book);
    free(inventory);
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

void programMenu(bookNode* inventory, borrowedBookNode* borrowedBooks)
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
    bookNode* inventory = NULL;
    borrowedBookNode* borrowedBooks = NULL;
    programMenu(inventory, borrowedBooks);

    return 0;
}

