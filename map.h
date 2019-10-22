int map[15][19] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 1, 2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 2, 1, 2, 0, 2, 1, 2, 0, 2, 1, 0, 1},
    {1, 0, 1, 0, 1, 2, 0, 2, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 2, 0, 2, 0, 2, 1, 2, 0, 2, 1, 0, 1, 2, 0, 0, 0, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 2, 0, 2, 0, 2, 0, 2, 1, 2, 1, 0, 1, 0, 1, 2, 0, 2, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1},
    {1, 2, 0, 2, 1, 0, 1, 2, 0, 2, 1, 2, 0, 2, 1, 2, 0, 2, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 2, 0, 0, 0, 2, 0, 2, 1, 2, 0, 2, 0, 2, 1, 2, 0, 2, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1},
    {1, 2, 0, 0, 0, 0, 0, 2, 1, 2, 0, 0, 0, 0, 0, 2, 0, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int food_list[6][2] = {
    {4, 5},
    {7, 1},
    {11, 5},
    {10, 11},
    {5, 8},
    {17, 2}};

int rows = 15;
int cols = 19;

int prev_added_row = 1;
int prev_added_col = 1;

int start_row = 1;
int start_col = 1;

int *path[350];
int *rowcoords[350];
int *colcoords[350];
int *commands[300];

int pathIndex = 0;
int commandIndex = 0;
int coordsIndex = 0;

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
    straight
};

int *sum = 0;
