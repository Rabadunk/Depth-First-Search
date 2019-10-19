#include <stdio.h>
#include <stdlib.h>

int **visited[15][19] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int rows = 15;
int cols = 19;
int start_row = 1;
int start_col = 1;

enum terrain
{
    empty,
    wall,
    goal,
    crumb
};

void print_visited()
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d", visited[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}

int dfs(int row, int col)
{
    int *current = &visited[row][col];

    if (*current == empty)
    {
        *current = crumb;

        if (dfs(row, col - 1))
        {
            *current = crumb;
            return 1;
        }

        if (dfs(row + 1, col))
        {
            *current = crumb;
            return 1;
        }

        if (dfs(row, col + 1))
        {
            *current = crumb;
            return 1;
        }

        if (dfs(row - 1, col))
        {
            *current = crumb;
            return 1;
        }
    }

    return 0;
}

int main()
{

    // print_visited();
    dfs(start_row, start_col);
    // print_visited();

    return 0;
}
