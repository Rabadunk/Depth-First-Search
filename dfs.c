#include <stdio.h>
#include <stdlib.h>

int visited[15][19] = {
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
    start,
    reverse
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

int dfs(int row, int col, int prevRow, int prevCol, int direction, int prev_direction)
{
    int *current = &visited[row][col];

    if (*current == empty)
    {
        *current = crumb;
        path[pathIndex] = direction;
        pathIndex++;

        int sum = 0;

        printf("row: %d, column: %d, direction: %d\n", row, col, direction);
        dfs(row, col - 1, row, col, left, opp_direction(direction));
        dfs(row + 1, col, row, col, down, opp_direction(direction));
        dfs(row, col + 1, row, col, right, opp_direction(direction));
        dfs(row - 1, col, row, col, up, opp_direction(direction));
        printf("prev row: %d, prev column: %d, prev direction: %d \n", prevRow, prevCol, prev_direction);
    }

    return 0;
}

int opp_direction(int direction)
{
    if (direction == up)
    {
        return down;
    }

    if (direction == down)
    {
        return up;
    }

    if (direction == right)
    {
        return left;
    }

    if (direction == left)
    {
        return right;
    }

    return up;
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
    dfs(start_row, start_col, 0, 0, start, start);
    // print_visited();
    // print_path();

    return 0;
}
