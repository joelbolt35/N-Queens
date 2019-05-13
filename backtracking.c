/*
* NQueens problem.
* Find a solution to the N queens problem on an NxN board size if possible

* Conditions:
* 1. Two queens must not be on the same row
* 2. Two queens must not be on the same column
* 3. Two queens must not be diagonal of one another

*/

#include <stdio.h>
#include <stdlib.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


int  findPositions(int** board, int row, int const size);
void print(int** board, int const size);
int  collisionCheck(int** board, int row, int col, int const size); 

int main()
{
    // NxN matrix board
    int size = 0;
    printf("Board Size: "); scanf("%d", &size); 
    int** board = malloc(sizeof(int*) * size);
    for(int i = 0; i < size; i++)
        board[i] = malloc(sizeof(int) * size);
    // Initialize board to 0's
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            board[i][j] = 0;

    int solveable = 0;
    // locate queen's positions
    solveable = findPositions(board, 0, size);

    if(solveable == 1)
        print(board, size);
    else
        printf(ANSI_COLOR_RED "No Solution!\n"ANSI_COLOR_RESET);


    return EXIT_SUCCESS;
}

int findPositions(int** board, int row, int const size)
{
    // if all rows have queens, problem solved
    if(row == size) return 1;

    // else cycle through the columns
    for(int i = 0; i < size; i++) 
    {
        board[row][i] = 1;
        // checking for collision
        if(collisionCheck(board, row, i, size) == 0) 
        {
            if(findPositions(board, row + 1, size) == 1) //recurse to next row. Returns 1 if the queen was placed successfully
            {
                return 1;
            }

        }
        board[row][i] = 0;
    }
    
}

void print(int** board, int const size)
{
    for(int i = 0; i < size; i++)
    {
        printf("\n ");
        for(int j = 0; j < size; j++)
        {
            if(board[i][j] == 1)
                printf(ANSI_COLOR_RED" %d " ANSI_COLOR_RESET "|" ANSI_COLOR_RESET, board[i][j]);
            else
                printf( " %d |" , board[i][j]);
        }
        printf("\n");
        for(int j = 0; j < size; j++)
        {
            printf(" ---");
        }
    }
    printf("\n");
}

int collisionCheck(int** board, int row, int col, int const size)
{
    //row and col is the position that we just placed a queen. We need to make sure that is valid
    if(row == 0)
        return 0;
    //1 - check if queen is on the same column as another queen
    for(int i = 0; i < row; i++)
        if(board[i][col] == 1)
            return 1;
    //2 - check it's upper diagonals
    int tempCol = col;
    int tempRow = row;
    while(tempCol != 0 && tempRow != 0)
        if(board[--tempRow][--tempCol] == 1)
            return 1;
    tempCol = col;
    tempRow = row;
    while(tempCol != size-1 && tempRow != 0)
        if(board[--tempRow][++tempCol] == 1)
            return 1;
    return 0;
}   
