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


int  findPositions(int** board, int row, int const size, int* solutionNum);
void print(int** board, int const size, int* solutionNum);
int  collisionCheck(int** board, int row, int col, int const size); 

int** initializeBoard(int** board, int const size);
void freeMem(int** board, int const size);

int main()
{
    // NxN matrix board
    int size = 0;
    while(1)
    {
        int solutionNum = 0;
        printf("Board Size (-1 to EXIT): "); scanf("%d", &size);
        if(size == -1)
            break; 
        int** board = malloc(sizeof(int*) * size);;
        initializeBoard(board, size);

        // locate queen's positions
        findPositions(board, 0, size, &solutionNum);

        freeMem(board, size);
    }
    return EXIT_SUCCESS;
}

int findPositions(int** board, int row, int const size, int* solutionNum)
{
    //No Solution Cases
    if(size == 2 || size == 3)
    {
        printf(ANSI_COLOR_RED "No Solution!\n"ANSI_COLOR_RESET);
        return 0;
    }

    // Base Case -> if all rows have queens, problem solved
    if(row == size)
    {
        print(board, size, solutionNum);
        (*solutionNum)++;
        return 1;
    }

    // else cycle through the columns
    for(int i = 0; i < size; i++) 
    {
        board[row][i] = 1;
        // checking for collision
        if(collisionCheck(board, row, i, size) == 0) // If no collision
            findPositions(board, row + 1, size, solutionNum); //recurse to next row. Returns 1 if the queen was placed successfully
        board[row][i] = 0;
    }
    return 1;
}

void print(int** board, int const size, int* solutionNum)
{
    printf(ANSI_COLOR_GREEN "Solution # %d:\n" ANSI_COLOR_RESET, (*solutionNum)+1);
    for(int i = 0; i < size; i++)
    {
        printf("\n ");
        for(int j = 0; j < size; j++)
        {
            if(board[i][j] == 1)
                printf(ANSI_COLOR_RED" %d " ANSI_COLOR_RESET "|", board[i][j]);
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

int** initializeBoard(int** board, int const size)
{
    for(int i = 0; i < size; i++)
        board[i] = malloc(sizeof(int) * size);
    // Initialize board to 0's
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            board[i][j] = 0;
}

void freeMem(int** board, int const size)
{
    for(int i = 0; i < size; i++)
    {
        free(board[i]);
        board[i] = NULL;
    }
    free(board);
    board = NULL;
}