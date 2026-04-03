#include <iostream>
using namespace std;

// Size of the grid
const int N = 9;

// Function to print the 9x9 Sudoku grid
void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to find an empty cell (represented by 0)
bool findEmptyLocation(int grid[N][N], int &row, int &col)
{
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            if (grid[row][col] == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Function to check if it's safe to place 'num' at grid[row][col]
bool isSafe(int grid[N][N], int row, int col, int num)
{
    // 1. Check the row
    for (int x = 0; x < N; x++)
    {
        if (grid[row][x] == num)
        {
            return false;
        }
    }

    // 2. Check the column
    for (int x = 0; x < N; x++)
    {
        if (grid[x][col] == num)
        {
            return false;
        }
    }

    // 3. Check the 3x3 subgrid
    int startRow = row - (row % 3);
    int startCol = col - (col % 3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i + startRow][j + startCol] == num)
            {
                return false;
            }
        }
    }

    return true;
}

// Main backtracking function to solve the Sudoku
bool solveSudoku(int grid[N][N])
{
    int row, col;

    if (!findEmptyLocation(grid, row, col))
    {
        return true;
    }

    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;

            if (solveSudoku(grid))
            {
                return true;
            }

            grid[row][col] = 0;
        }
    }

    return false;
}

int main()
{
    int grid[N][N];

    cout << "Enter the 9x9 Sudoku grid row by row." << endl;
    cout << "Use 0 for empty cells, and separate numbers with spaces or newlines:" << endl;

    // Read the user input into the grid
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> grid[i][j];
        }
    }

    cout << "\nSolving your puzzle...\n"
         << endl;

    if (solveSudoku(grid))
    {
        cout << "Sudoku successfully solved:" << endl;
        cout << "-------------------------" << endl;
        printGrid(grid);
    }
    else
    {
        cout << "No solution exists for the provided board." << endl;
    }

    return 0;
}