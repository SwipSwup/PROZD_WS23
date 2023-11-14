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

int updateBoard(transform* ant, char** board)
{
    board[ant->position.x][ant->position.y] = board[ant->position.x][ant->position.y] ? '#' : '.', '#';

    switch (board[ant->position.x][ant->position.y])
    {
        case '#':
            board[ant->position.x][ant->position.y] = '.';
            ant->rotation = (vector2D) {-ant->rotation.y, ant->rotation.x};
            break;
        case '.':
            board[ant->position.x][ant->position.y] = '#';
            ant->rotation = (vector2D) {ant->rotation.y, -ant->rotation.x};
            break;
    }

    vector2D newPosition = (vector2D) {ant->position.x + ant->rotation.x, ant->position.y + ant->rotation.y};
    if (newPosition.x < 0 || newPosition.x > BOARD_SIZE - 1 || newPosition.y < 0 || newPosition.y > BOARD_SIZE - 1) {
        return 0;
    }

    ant->position = newPosition;
    return 1;
}

void printBoard(vector2D position, char** board) {
    for (int x = 0; x < BOARD_SIZE; ++x)
    {
        printf("\n");
        for (int y = 0; y < BOARD_SIZE; ++y)
        {
            if(position.x == x && position.y == y) {
                printf("%c", 'a');
                continue;
            }

            printf("%c", board[x][y]);
        }
    }
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

    return 0;
}
