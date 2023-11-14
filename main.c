#include <stdio.h>
#include <malloc.h>

#define BOARD_SIZE 10

char** initializeBoard()
{
    char** board = (char**) malloc(sizeof(char*) * BOARD_SIZE);
    for (int x = 0; x < BOARD_SIZE; ++x)
    {
        board[x] = (char *) malloc(sizeof (char) * BOARD_SIZE);
        for (int y = 0; y < BOARD_SIZE; ++y)
        {
            board[x][y] = '.';
        }
    }
    return board;
}

int main()
{


    printf("Hello, World!\n");
    return 0;
}
