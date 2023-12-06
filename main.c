#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 31
#define VALID_MENU_ACTIONS "nbrlsx"

//####################################################//
//# ICH HABE DEN TEST NICHT GANZ NACH ANGABE GEMACHT #//
//####################################################//

/// An enum holding all available genres.
enum genre_type
{
    // The way I handelt genres makes this enum obsolete.
    HORROR,
    ADVENTURE,
    ROMANCE,
    NON_FICTION
} typedef genre_type;

/// A generic node that can hold on type of data pointer and points to the next node.
struct node
{
    void* item;
    struct node* next;
} typedef node;

/// A struct to hold all the books data.
struct book
{
    char* title;
    genre_type genre;
    int year;
    int amount;
} typedef book;

/// A struct to hold all the borrowed books data.
/// Points to the book that's being borrowed instead of only saving the title for easy access later.
struct borrowedBook
{
    book* book;
    char* borrower;
} typedef borrowedBook;

/// A struct holding all the data that is needed to get input for the user.
struct userInputParams
{
    char* inputType;
    char* message;

    int memSize;
    void* validationData;
} typedef userInputParams;

/// This function validates if the given type is in the valid types.
/// \param type The type to be checked of type char*.
/// \param types The valid types of type char*.
/// \return True if the type is in types otherwise false.
int validateGenericTypeAsChar(const void* type, const void* types)
{
    return strchr((char*) types, *((char*) type)) != NULL;
}

/// This function validates if the give number is bigger than the lower boundary.
/// \param number The number to be checked of type int*.
/// \param lowerBound The lower boundary of type int*.
/// \return True if the number is bigger than the boundary otherwise false.
int validateIntegerIsAboveLowerBoundExcl(const void* number, const void* lowerBound)
{
    return *((int*) number) > *((int*) lowerBound);
}

/// This function validates if the given number in between the boundaries.
/// \param number The number to be checked of type int*.
/// \param bounds The boundaries of type int**. int[0] being the lower boundary and int[1] the upper boundary.
/// \return True if the number is in between inclusive the boundaries otherwise false.
int validateIntegerBoundsIncl(const void* number, const void* bounds)
{
    return *((int*) number) >= ((int*) bounds)[0] && *((int*) number) <= ((int*) bounds)[1];
}

/// This function validates if the length of the given string is under or equals the maxLength.
/// \param string The string to be check of type char*.
/// \param maxLength The maximum length of type int*.
/// \return True if the given string in under or equals the maxLength otherwise false.
int validateMaxStringLength(const void* string, const void* maxLength)
{
    for (int i = 0; i < *((int*) maxLength) + 1; ++i)
    {
        if (((char*) string)[i] == '\0')
        {
            return 1;
        }
    }
    return 0;
}

/// This function gets the user input and validates it until the user has given a valid input. Creates memory on the heap.
/// \param params The input parameters.
/// \param validate The validation function for the input.
/// \return The validated user input.
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

        printf("\nUngueltige Eingabe!");
    }
}

/// This function get the size of a list.
/// \param list The address of the first node of the list.
/// \return The size of the list.
int getListSize(node* list)
{
    int size = 0;
    for (node* iterator = list; iterator != NULL; iterator = iterator->next, size++);

    return size;
}

/// This function converts a list into an array of the list nodes.
/// \param list The address of the first node of the list.
/// \return An array with the list nodes of the size of the list.
node** listToArray(node* list)
{
    node** arr = malloc(sizeof(node*) * getListSize(list));

    int index = 0;
    for (node* iterator = list; iterator != NULL; iterator = iterator->next, index++)
    {
        arr[index] = iterator;
    }

    return arr;
}

/// This function creates a list node.
/// \param item The address of the list item.
/// \return The address of the list node on the heap.
node* createNode(void* item)
{
    node* newNode = (node*) malloc(sizeof(node));
    newNode->item = item;
    newNode->next = NULL;

    return newNode;
}

/// This functions frees a node and it's item from the heap.
/// \param node The address of the list node.
/// \param freeItem The function to free the node item.
void freeNode(node* node, void freeItem(void*))
{
    freeItem(node->item);
    free(node);
}

/// This function frees a book from the heap.
/// \param book The address of the book.
void freeBook(void* book)
{
    free(((struct book*) book)->title);
    free(book);
}

/// This function frees a borrowed book for the heap.
/// \param borrowedBook The address of the borrowed book.
void freeBorrowedBook(void* borrowedBook)
{
    free(((struct borrowedBook*) borrowedBook)->borrower);
    free(borrowedBook);
}

/// This function frees an entire list and its items.
/// \param list The address of the first list node.
/// \param freeItem The function to free the node item.
void freeList(node* list, void freeItem(void*))
{
    if (list == NULL)
    {
        return;
    }

    freeList(list->next, freeItem);
    freeNode(list, freeItem);
}

/// This function adds an item to a list.
/// \param item The address of the item.
/// \param list The address of the first node of the list
/// \return The address of the first node of the list.
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

/// This function returns the node at the given index.
/// \param index The index of the node.
/// \param list The address of the first node of the list.
/// \return The the address of the node at the index otherwise NULL.
node* getNodeWithIndex(int index, node* list)
{
    for (node* iterator = list; iterator != NULL; iterator = iterator->next, index--)
    {
        if (!index)
        {
            return iterator;
        }
    }

    return NULL;
}

/// This function removes a node at the index and frees it from the heap.
/// \param index The index of the node.
/// \param list The address of the first node of the list.
/// \param freeItem The function to free the item.
/// \return The address of the first node of the list.
node* removeNodeFromListAtIndex(int index, node* list, void freeItem(void*))
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

/// This function prints the list and its items.
/// \param list The address of the first node of the list.
/// \param printItem The function to print the list item.
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

/// This function compares the year of two books.
/// \param a The first book of type node**.
/// \param b The second book of type node**.
/// \return 1 if the year of the first book is bigger, -1 if the year of the second book is bigger and 0 if both years a equal.
int bookYearComparator(const void* a, const void* b)
{
    return ((book*) ((*(node**) a)->item))->year - ((book*) ((*(node**) b)->item))->year;
}

/// This function prints a list sorted.
/// \param list The address of the first node of the list.
/// \param comparator The function to compare two list items.
/// \param printItem The function to print the list item.
void printListInOrder(node* list, int comparator(const void*, const void*), void printItem(const void*))
{
    node** listAsArray = listToArray(list);
    qsort(listAsArray, getListSize(list), sizeof(node*), comparator);

    for (int i = 0; i < getListSize(list); i++)
    {
        printf("\n%d: ", i + 1);
        printItem((book*) listAsArray[i]->item);
    }

    printf("\n");
    free(listAsArray);
}

/// This function prints the data of a book.
/// \param item The book of type book*.
void printBook(const void* item)
{
    printf("%s, %s (%d)",
           ((book*) item)->title,
           (char* []) {"Horror", "Abenteuer", "Romantik", "Sachbuch"}[((book*) item)->genre],
            ((book*) item)->year
    );
}

/// This function prints the data of a borrowed book.
/// \param item The borrowed book of type borrowedBook*.
void printBorrowedBook(const void* item)
{
    printf("%s geliehen von %s",
           ((borrowedBook*) item)->book->title,
           ((borrowedBook*) item)->borrower
    );
}

/// This function creates a book and fills it with data.
/// \return The address of the book on the heap.
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
            validateMaxStringLength
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
    newBook->genre = *genre - 1;
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

/// This function inserts a new Book into the inventory
/// \param inventory The address of the address of the first node of the inventory.
void insertBook(node** inventory)
{
    *inventory = addItemToList(createBook(), *inventory);
}

/// This function creates a borrowed book on the heap.
/// \param book The address of the book.
/// \param name The name of the borrower.
/// \return The address of the borrowed book on the heap.
borrowedBook* createBorrowedBook(book* book, char* name)
{
    borrowedBook* newBorrowedBook = (borrowedBook*) malloc(sizeof(borrowedBook));
    newBorrowedBook->book = book;
    newBorrowedBook->borrower = name;
    return newBorrowedBook;
}

/// This function checks if the given name has already borrowed the given book.
/// \param name The name of the borrower.
/// \param book The address of the book.
/// \param borrowedBooks The address of the first node of the borrowedBooks.
/// \return True if the name has already borrowed the book otherwise false.
int isBorrowerOfBook(char* name, book* book, node* borrowedBooks)
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

/// This function asks which book the user want's to borrow and updates the inventory and the borrowed book accordingly.
/// \param inventory The address of the first node of the inventory.
/// \param borrowedBooks The address of the address of the first node of the borrowedBooks.
void borrowBook(node* inventory, node** borrowedBooks)
{
    printList(inventory, printBook);
    if (inventory == NULL)
    {
        printf("\nEs sind keine Buecher im Inventar vorhanden.");
        return;
    }

    char preparedString[100];
    sprintf(preparedString, "\nWelchen Titel moechten Sie leihen? (1-%d): ", getListSize(inventory));

    int* index = getUserInputWithValidation(
            (userInputParams)
                    {
                            "%d",
                            preparedString,
                            sizeof(int),
                            (int[]) {1, getListSize(inventory)}
                    },
            validateIntegerBoundsIncl
    );

    book* book = (struct book*) getNodeWithIndex(*index - 1, inventory)->item;
    free(index);

    char* name = (char*) getUserInputWithValidation(
            (userInputParams) {
                    "%s",
                    "\nGeben Sie Ihren Namen ein: ",
                    MAX_TITLE_LENGTH + 1,
                    (int[]) {MAX_TITLE_LENGTH}
            },
            validateMaxStringLength
    );

    if (isBorrowerOfBook(name, book, *borrowedBooks))
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

/// This function asks which borrowed book the user wants to return.
/// \param borrowedBooks The address of the address of the first node of the borrowedBooks.
void returnBook(node** borrowedBooks)
{
    printList(*borrowedBooks, printBorrowedBook);
    if (*borrowedBooks == NULL)
    {
        printf("\nEs sind keine Titel ausgeliehen!");
        return;
    }

    char preparedString[100];
    sprintf(preparedString, "\nWelchen Titel moechten Sie retournieren? (1-%d): ", getListSize(*borrowedBooks));
    int* index = (int*) getUserInputWithValidation(
            (userInputParams) {
                    "%d",
                    preparedString,
                    sizeof(int),
                    (int[]) {1, getListSize(*borrowedBooks)}
            },
            validateIntegerBoundsIncl
    );

    ((borrowedBook*) getNodeWithIndex(*index - 1, *borrowedBooks)->item)->book->amount++;
    *borrowedBooks = removeNodeFromListAtIndex(*index - 1, *borrowedBooks, freeBorrowedBook);

    free(index);
}

/// An enum holding all the possible menu actions.
enum menuAction
{
    INSERT_BOOK = 'n',
    BORROW_BOOK = 'b',
    RETURN_BOOK = 'r',
    PRINT_LIST = 'l',
    PRINT_LIST_IN_ORDER = 's',
    EXIT_PROGRAM = 'x'
} typedef menuAction;

/// This function asks which menu action the user wants to perform and does so accordingly.
/// \param inventory The address of the first node of the inventory.
/// \param borrowedBooks The address of the first node of the borrowedBooks.
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
                returnBook(&borrowedBooks);
                break;
            case PRINT_LIST:
                //printf("\nsize: %d", getListSize(inventory));
                printList(inventory, printBook);
                break;
            case PRINT_LIST_IN_ORDER:
                printListInOrder(inventory, bookYearComparator, printBook);
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

/// The main function of the program. Sets the buffer of stdout to 0 for debugging purposes.
/// \return 0 if the the program exited without an error.
int main()
{
    setbuf(stdout, 0);

    node* inventory = NULL;
    node* borrowedBooks = NULL;
    programMenu(inventory, borrowedBooks);

    return 0;
}

