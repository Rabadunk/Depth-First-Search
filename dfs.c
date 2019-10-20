#include <stdio.h>
#include <stdlib.h>
#include "map.h"

int prev_added_direction = start;

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

void add_to_path(int direction)
{

    switch (direction)
    {
    case start:
        path[pathIndex] = 'f';
        pathIndex++;
        break;
    case up:
        if (prev_added_direction == down)
        {
            path[pathIndex] = 'u';
            pathIndex++;
        }
        else if (prev_added_direction == left)
        {
            path[pathIndex] = 'r';
            pathIndex++;
        }
        else if (prev_added_direction == right)
        {
            path[pathIndex] = 'l';
            pathIndex++;
        }
        else if (prev_added_direction == up)
        {
            path[pathIndex] = 's';
            pathIndex++;
        }

        prev_added_direction = up;

        break;
    case down:
        if (prev_added_direction == up)
        {
            path[pathIndex] = 'u';
            pathIndex++;
        }
        else if (prev_added_direction == left)
        {
            path[pathIndex] = 'l';
            pathIndex++;
        }
        else if (prev_added_direction == right)
        {
            path[pathIndex] = 'r';
            pathIndex++;
        }
        else if (prev_added_direction == down)
        {
            path[pathIndex] = 's';
            pathIndex++;
        }

        prev_added_direction = down;
        break;
    case left:
        if (prev_added_direction == right)
        {
            path[pathIndex] = 'u';
            pathIndex++;
        }
        else if (prev_added_direction == down)
        {
            path[pathIndex] = 'r';
            pathIndex++;
        }
        else if (prev_added_direction == up)
        {
            path[pathIndex] = 'l';
            pathIndex++;
        }
        else if (prev_added_direction == left)
        {
            path[pathIndex] = 's';
            pathIndex++;
        }

        prev_added_direction = left;
        break;

    case right:
        if (prev_added_direction == left)
        {
            path[pathIndex] = 'u';
            pathIndex++;
        }
        else if (prev_added_direction == down)
        {
            path[pathIndex] = 'l';
            pathIndex++;
        }
        else if (prev_added_direction == up)
        {
            path[pathIndex] = 'r';
            pathIndex++;
        }
        else if (prev_added_direction == right)
        {
            path[pathIndex] = 's';
            pathIndex++;
        }

        prev_added_direction = right;
        break;
    };
}

void print_map()
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d", map[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}

void print_path()
{
    printf("path: ");
    for (int i = 0; i < pathIndex; i++)
    {
        printf("%c", path[i]);
    }

    printf("\n");
}

int dfs(int row, int col, int prevRow, int prevCol, int direction, int prev_direction)
{
    int *current = &map[row][col];

    if (*current == empty || *current == intersection)
    {

        if (*current == empty)
        {
            *current = crumb;
        }
        else if (*current == intersection)
        {
            *current = crumbed_intersection;
        }

        if (*current == crumbed_intersection)
        {
            add_to_path(direction);
        }

        int sum = 0;

        //printf("row: %d, column: %d, direction: %d\n", row, col, direction);
        dfs(row, col - 1, row, col, left, opp_direction(direction));
        dfs(row + 1, col, row, col, down, opp_direction(direction));
        dfs(row, col + 1, row, col, right, opp_direction(direction));
        dfs(row - 1, col, row, col, up, opp_direction(direction));

        if (*current == crumbed_intersection)
        {
            add_to_path(prev_direction);
        }

        //printf("prev row: %d, prev column: %d, prev direction: %d \n", prevRow, prevCol, prev_direction);
    }

    return 0;
}

void alloc_path()
{
    *path = malloc(200 * sizeof(char *));
}

int main()
{

    dfs(start_row, start_col, 0, 0, down, start);
    print_path();

    return 0;
}
