#include <stdio.h>
#include <malloc.h>

#define BOARD_SIZE 10

struct vector2D
{
    int x;
    int y;
} start_position = {0, 0};

enum direction
{
    north = 'n',
    east = 'e',
    south = 's',
    west = 'w'
};

char** board;


void printBoard()
{
    for (int x = 0; x < BOARD_SIZE; ++x)
    {
        for (int y = 0; y < BOARD_SIZE; ++y)
        {
            printf("%c", board[y][x]);
        }
        printf("\n");
    }
}

char** initializeBoard()
{
    board = (char**) malloc(sizeof(char**) * BOARD_SIZE);

    for (int x = 0; x < BOARD_SIZE; ++x)
    {
        board[x] = (char*) malloc(sizeof(char*) * BOARD_SIZE);
        for (int y = 0; y < BOARD_SIZE; ++y)
        {
            board[x][y] = '.';
        }
    }

    board[0][0] = 'A';

    return board;
}

void freeBoard()
{
    for (int x = 0; x < BOARD_SIZE; ++x)
    {
        free(board[x]);
    }
    free(board);
}

char getPathLetter(int pathIndex)
{
    return (char) (65 + pathIndex);
}

int updateRobotPosition(struct vector2D* position, struct vector2D direction)
{
    struct vector2D newPosition = {(*position).x + direction.x, (*position).y - direction.y};

    if (newPosition.x < 0 || newPosition.x > BOARD_SIZE - 1 || newPosition.y < 0 || newPosition.y > BOARD_SIZE - 1)
    {
        return 0;
    }

    if (board[newPosition.x][newPosition.y] != '.')
    {
        return 0;
    }

    *position = newPosition;
    return 1;
}

int move(enum direction dir, struct vector2D* position)
{
    switch (dir)
    {
        case north:
            return updateRobotPosition(position, (struct vector2D) {0, 1});
        case east:
            return updateRobotPosition(position, (struct vector2D) {1, 0});
        case south:
            return updateRobotPosition(position, (struct vector2D) {0, -1});
        case west:
            return updateRobotPosition(position, (struct vector2D) {-1, 0});
    }

    return 0;
}

void updateBoard(struct vector2D position, int pathIndex)
{
    board[position.x][position.y] = getPathLetter(pathIndex);
}


int main()
{
    int pathIndex = 1;
    char input;
    struct vector2D pos = start_position;
    board = initializeBoard();

        printBoard();
    enum direction dir;
    while (1)
    {
        //board[1][0] = '*';
        printf("walk to:\n");
        scanf(" %c", &input);
        if (input == 'x')
        {
            break;
        }

        dir = input;

        if (!move(dir, &pos))
        {
            printf("not possible\n");
            continue;
        }

        updateBoard(pos, pathIndex);
        pathIndex = pathIndex > 24 ? 0 : pathIndex + 1;
        printBoard();
    }

    freeBoard();
    return 0;
}
