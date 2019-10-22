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

void add_coords(int x, int y)
{
    rowcoords[coordsIndex] = x;
    colcoords[coordsIndex] = y;
    coordsIndex++;
}

void print_coords()
{
    printf("\n");

    printf("printing coordinates array\n");

    for (int i = 0; i < coordsIndex; i++)
    {
        printf("%d %d,", rowcoords[i], colcoords[i]);
    }

    printf("\n");
}

int dfs(int row, int col, int prevRow, int prevCol, int direction, int prev_direction)
{
    int *current = &map[row][col];

    if (*current == empty || *current == intersection)
    {

        int me = 0;

        if (*current == empty)
        {
            me = crumb;
            *current = crumb;
        }
        else if (*current == intersection)
        {
            me = crumbed_intersection;
            *current = crumbed_intersection;
        }

        printf("%d %d,", row, col);
        add_coords(row, col);

        if (dfs(row, col - 1, row, col, left, opp_direction(direction)))
        {
            *current = me;
            printf("%d %d,", row, col - 1);
            add_coords(row, col - 1);
            return 1;
        }

        if (dfs(row + 1, col, row, col, down, opp_direction(direction)))
        {
            *current = me;
            printf("%d %d,", row + 1, col);
            add_coords(row + 1, col);
            return 1;
        }

        if (dfs(row, col + 1, row, col, right, opp_direction(direction)))
        {
            printf("%d %d,", row, col + 1);
            add_coords(row, col + 1);
            *current = me;
            return 1;
        }

        if (dfs(row - 1, col, row, col, up, opp_direction(direction)))
        {
            printf("%d %d,", row - 1, col);
            add_coords(row - 1, col);
            *current = me;
            return 1;
        }

        //printf("prev row: %d, prev column: %d, prev direction: %d \n", prevRow, prevCol, prev_direction);

        if (*current == crumb || *current == crumbed_intersection)
        {
            printf("%d %d,", prevRow, prevCol);
            add_coords(prevRow, prevCol);
        }
    }

    return 0;
}

void alloc_path()
{
    *path = malloc(350 * sizeof(int *));
    *commands = malloc(350 * sizeof(int *));
}

int main()
{
    alloc_path();
    dfs(start_row, start_col, 0, 0, down, start);
    print_coords();

    return 0;
}
