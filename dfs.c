#include <stdio.h>
#include <stdlib.h>

int visited[15][19] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 2, 1, 2, 0, 2, 1, 0, 0, 2, 1, 0, 1},
    {1, 0, 1, 0, 1, 2, 0, 2, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 2, 0, 2, 0, 2, 1, 2, 0, 2, 1, 0, 1, 2, 0, 0, 0, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 2, 0, 2, 0, 2, 0, 2, 1, 2, 1, 0, 1, 0, 1, 2, 0, 2, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1},
    {1, 2, 0, 2, 1, 0, 1, 2, 0, 2, 1, 2, 0, 2, 1, 0, 0, 2, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 2, 0, 0, 0, 2, 0, 2, 1, 2, 0, 2, 0, 2, 1, 2, 0, 2, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1},
    {1, 2, 0, 0, 0, 0, 0, 2, 1, 2, 0, 0, 0, 0, 0, 2, 0, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

char *path[200];

int rows = 15;
int cols = 19;
int start_row = 1;
int start_col = 1;
int pathIndex = 0;

enum terrain
{
    empty,
    wall,
    intersection,
    crumb,
    crumbed_intersection
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

int prev_added_direction = down;

enum commands
{
    turn_right,
    turn_left,
    u_turn
};

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

void add_to_path(int direction)
{

    switch (direction)
    {
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
    int *current = &visited[row][col];

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

        print_path();

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

    // print_visited();
    dfs(start_row, start_col, 0, 0, down, start);
    // print_visited();

    return 0;
}
