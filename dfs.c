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

int *path[200];

int rows = 15;
int cols = 19;
int start_row = 1;
int start_col = 1;
int pathIndex = 0;

enum terrain
{
    empty,
    wall,
    goal,
    crumb
};

enum directions
{
    up,
    down,
    left,
    right,
    start
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

int dfs(int row, int col, int direction)
{
    int *current = &visited[row][col];

    if (*current == empty)
    {
        *current = crumb;
        //path[pathIndex] = direction;
        //pathIndex++;

        //printf("row: %d, column: %d \n", row, col);

        if (dfs(row, col - 1, left))
        {
            *current = crumb;
            return 1;
        }

        if (dfs(row + 1, col, down))
        {
            *current = crumb;
            return 1;
        }

        if (dfs(row, col + 1, right))
        {
            *current = crumb;
            return 1;
        }

        if (dfs(row - 1, col, up))
        {
            *current = crumb;
            return 1;
        }
    }

    return 0;
}

void print_path()
{
    for (int i = 0; i < 200; i++)
    {
        printf("Direction: %d \n", path[i]);
    }
}

void alloc_path()
{
    *path = malloc(200 * sizeof(int *));
}

int main()
{

    // print_visited();
    dfs(start_row, start_col, start);
    // print_visited();
    // print_path();

    return 0;
}
