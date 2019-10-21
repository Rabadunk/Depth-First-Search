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

void add_to_path(int this_row, int this_col)
{
    if (this_row > prev_added_row)
    {
        path[pathIndex] = down;
        pathIndex++;
        prev_added_row = this_row;
    }
    else if (this_row < prev_added_row)
    {
        path[pathIndex] = up;
        pathIndex++;
        prev_added_row = this_row;
    }
    else if (this_col > prev_added_col)
    {
        path[pathIndex] = right;
        pathIndex++;
        prev_added_col = this_col;
    }
    else if (this_col < prev_added_col)
    {
        path[pathIndex] = left;
        pathIndex++;
        prev_added_col = this_col;
    }
}

void print_path()
{
    for (int i = 0; i < pathIndex; i++)
    {
        printf("%d: %d \n", i, path[i]);
    }

    printf("\n");
}

void print_command()
{
    printf("commands size: %d \n", commandIndex);
    for (int i = 0; i < commandIndex; i++)
    {
        printf("%d: %d \n", i, commands[i]);
    }

    printf("\n");
}

int dfs(int row, int col, int prevRow, int prevCol, int direction, int prev_direction)
{
    int *current = &map[row][col];

    if (*current == empty || *current == intersection)
    {

        int me = 0;

        add_to_path(row, col);

        if (*current == empty)
        {
            me = crumb;
            *current = crumb;
        }
        else if (*current == intersection)
        {
            me = crumbed_intersection;
            *current = crumbed_intersection;
            path[pathIndex] = straight;
            pathIndex++;
        }

        printf("%d %d,", row, col);

        if (dfs(row, col - 1, row, col, left, opp_direction(direction)))
        {
            *current = me;
            return 1;
        };

        if (dfs(row + 1, col, row, col, down, opp_direction(direction)))
        {
            *current = me;
            return 1;
        };

        if (dfs(row, col + 1, row, col, right, opp_direction(direction)))
        {
            *current = me;
            return 1;
        };

        if (dfs(row - 1, col, row, col, up, opp_direction(direction)))
        {
            *current = me;
            return 1;
        };

        printf("%d %d,", row, col);

        add_to_path(row, col);

        //printf("prev row: %d, prev column: %d, prev direction: %d \n", prevRow, prevCol, prev_direction);
    }

    return 0;
}

void alloc_path()
{
    *path = malloc(350 * sizeof(int *));
    *commands = malloc(350 * sizeof(int *));
}

void make_commands()
{

    for (int i = 1; i < pathIndex - 1; i++)
    {

        int prev = path[i - 1];
        int next = path[i + 1];
        int current = path[i];

        if (current == straight && prev != next)
        {
            commands[commandIndex] = next;
            commandIndex++;
        }
        else if (current == straight && prev == next)
        {
            commands[commandIndex] = straight;
            commandIndex++;
        }
        else if (current != next && next != straight)
        {
            commands[commandIndex] = next;
            commandIndex++;
        }
    }
}

int main()
{
    alloc_path();
    dfs(start_row, start_col, 0, 0, down, start);
    print_path();
    make_commands();
    print_command();

    return 0;
}
