#include <stdio.h>
#include <malloc.h>

#define BOARD_SIZE 10

struct vector2D
{
    int x;
    int y;
} typedef vector2D;

struct transform
{
    vector2D position;
    vector2D rotation;
} typedef transform;

char** initializeBoard()
{
    char** board = (char**) malloc(sizeof(char**) * BOARD_SIZE);

    for (int x = 0; x < BOARD_SIZE; ++x)
    {
        board[x] = (char*) malloc(sizeof(char*) * BOARD_SIZE);
        for (int y = 0; y < BOARD_SIZE; ++y)
        {
            board[x][y] = '.';
        }
    }

    return board;
}

int isOnBoard(vector2D position) {
    if (position.x < 0 || position.x > BOARD_SIZE - 1 || position.y < 0 || position.y > BOARD_SIZE - 1) {
        return 0;
    }

    return 1;
}

int updateBoard(transform* ant, char** board)
{
    switch (board[ant->position.x][ant->position.y])
    {
        case '.':
            board[ant->position.x][ant->position.y] = '#';
            //Turns right (is inverted??)
            ant->rotation = (vector2D) {-ant->rotation.y, ant->rotation.x};
            break;
        case '#':
            board[ant->position.x][ant->position.y] = '.';
            //Turns right (is inverted??)
            ant->rotation = (vector2D) {ant->rotation.y, -ant->rotation.x};
            break;
    }

    ant->position = (vector2D) {ant->position.x + ant->rotation.x, ant->position.y + ant->rotation.y};

    return isOnBoard(ant->position);
}

void printBoard(vector2D position, char** board) {
    for (int y = 0; y < BOARD_SIZE; ++y)
    {
        for (int x = 0; x < BOARD_SIZE; ++x)
        {
            if(isOnBoard(position) && position.x == x && position.y == y) {
                printf("%c", board[x][y] == '.' ? 'a' : 'A');
                continue;
            }

            printf("%c", board[x][y]);
        }
        printf("\n");
    }
}

void freeBoard(char** board)
{
    for (int x = 0; x < BOARD_SIZE; ++x)
    {
        free(board[x]);
    }
    free(board);
}

int main()
{
    char** board = initializeBoard();
    transform ant;
    ant.rotation = (vector2D) {-1, 0};
    int numberOfTurns = 0;

    printf("Number of turns: ");
    scanf(" %d", &numberOfTurns);
    printf("Start position: ");
    scanf(" %d %d", &ant.position.x, &ant.position.y);

    for (int i = 0; i < numberOfTurns; ++i)
    {
        if(!updateBoard(&ant, board)) {
            break;
        }
    }

    printBoard(ant.position, board);
    freeBoard(board);

    return 0;
}
