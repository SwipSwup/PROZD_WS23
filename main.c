#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_TITLE_LENGTH 31
#define VALID_MENU_ACTIONS "nbrlsx"

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
    book* book;
    char* name;
    struct borrowNode* next;
} typedef borrowerNode;

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
                    "\nGeben Sie den Titel ein:",
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

    for (bookNode* n = inventory; n != NULL; n = n->next)
    {
        if (n->next == NULL)
        {
            n->next = newBookNode;
            n = n->next;
        }
    }

    return inventory;
}

void freeBook(book* book)
{
    free(book->title);
    free(book);
}

void freeInventory(bookNode* inventory) {
    if(inventory == NULL) {
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
    PRINT_LIST  = 'l',
    PRINT_LIST_IN_ORDER = 's',
    EXIT_PROGRAM = 'x'
} typedef menuAction;

void programMenu(bookNode* inventory)
{
    void* mem = NULL;

    while (1)
    {
        //Frag den User nach Input
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
                inventory = addBookToInventory(createBook(), inventory);
                break;
            case BORROW_BOOK:
                break;
            case RETURN_BOOK:
                break;
            case PRINT_LIST:
                break;
            case PRINT_LIST_IN_ORDER:
                break;
            case EXIT_PROGRAM:
                freeInventory(inventory);
                free(mem);
                return;
        }
    }
}

int main()
{
    bookNode* inventory = NULL;
    programMenu(inventory);

    return 0;
}

