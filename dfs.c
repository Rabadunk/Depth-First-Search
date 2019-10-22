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

    printf("printing coordinates array, size: %d\n", coordsIndex);

    for (int i = 0; i < coordsIndex; i++)
    {
        printf("%d %d,", rowcoords[i], colcoords[i]);
    }

    printf("\n");
}

void print_maze()
{
    printf("\n");

    printf("maze\n");

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf(" %d ", map[i][j]);
        }

        printf("\n");
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

        printf("%d %d,\n", row, col);
        add_coords(row, col);

        if (dfs(row, col - 1, row, col, left, opp_direction(direction)))
        {
            *current = me;
            printf("%d %d,\n", row, col - 1);
            add_coords(row, col - 1);
            return 1;
        }

        if (dfs(row + 1, col, row, col, down, opp_direction(direction)))
        {
            *current = me;
            printf("%d %d,\n", row + 1, col);
            add_coords(row + 1, col);
            return 1;
        }

        if (dfs(row, col + 1, row, col, right, opp_direction(direction)))
        {
            printf("%d %d,\n", row, col + 1);
            add_coords(row, col + 1);
            *current = me;
            return 1;
        }

        if (dfs(row - 1, col, row, col, up, opp_direction(direction)))
        {
            printf("%d %d, \n", row - 1, col);
            add_coords(row - 1, col);
            *current = me;
            return 1;
        }

        //printf("prev row: %d, prev column: %d, prev direction: %d \n", prevRow, prevCol, prev_direction);

        if (*current == crumb || *current == crumbed_intersection)
        {
            printf("%d %d \n,", prevRow, prevCol);
            add_coords(prevRow, prevCol);
        }
    }

    return 0;
}
#define REMOVED_VALUE 256

int CheckIntersection(int gridY, int gridX) {
	if (map[gridY][gridX] == 4) {
		return 1;
	}
	else {
		return 0;
	}
	/*
	GetOpenNeighbours(gridY, gridX);
	int count = 0;
	for (int i = 0; i < 9; i++) {
		if (neighbours[i][0] != REMOVED_VALUE && neighbours[i][1] != REMOVED_VALUE) {
			count++;
		}
	}
	if (count > 2) {
		return 1;
	}
	if (count == 2) {
		int nodeX = -1;
		int nodeY = -1;
		for (int i = 0; i < 9; i++) {
			if (neighbours[i][0] != REMOVED_VALUE && neighbours[i][1] != REMOVED_VALUE) {
				if (nodeX == -1 && nodeY == -1) {
					nodeY = neighbours[i][0];
					nodeX = neighbours[i][1];
				}
				else {
					if (nodeY != neighbours[i][0] && nodeX != neighbours[i][1]) {
						return 1;
					}
				}
			}
		}
	}
	return 0;
	*/
}


//LOOK HERE BOIS --!!!!!!!!!!!!!!!!!!!!
enum instructions directions[64];

int finalDirectionY = 1;
int finalDirectionX = 0;

const char* getDirectionName(enum instruction direction)
{
	switch (direction)
	{
	case Straight: return "Straight";
	case Left: return "Left";
	case Right: return "Right";
	case Stop: return "Stop";
	case UTurn: return "UTurn";
	}
}
//Pass in an array of node and it will convert to directions
void ConvertPathToDirection() {
	int i = 0;
	int j = 0;
	int prevDeltaX = finalDirectionX;
	int prevDeltaY = finalDirectionY;
	int deltaY;
	int deltaX;
	int prevIntersectY = 0;
	int prevIntersectX = 0;
	while (i != coordsIndex) {
		deltaY = rowcoords[i + 1] - rowcoords[i];
		deltaX = colcoords[i + 1] - colcoords[i];

		if (CheckIntersection(rowcoords[i], colcoords[i]) == 0) {
			i++;
			continue;
		}

		if (prevIntersectY == rowcoords[i] && prevIntersectX == colcoords[i]) {
			int prevCordX = colcoords[i - 1];
			int prevCordY = rowcoords[i - 1];

			directions[j] = UTurn;
			printf("%s \n", getDirectionName(directions[j]));
			j++;
			prevDeltaY = rowcoords[i] - prevCordY;
			prevDeltaX = colcoords[i] - prevCordX;
		}

		prevIntersectY = rowcoords[i];
		prevIntersectX = colcoords[i];

		if (i + 1 == coordsIndex) {
			i++;
			continue;
		}
		if (deltaY == -prevDeltaY && deltaY != 0) {
			directions[j] = UTurn;
			prevDeltaX = deltaX;
			prevDeltaY = deltaY;
			printf("%s \n", getDirectionName(directions[j]));
			i++;
			j++;
			continue;
		}
		else if (deltaX == -prevDeltaX && deltaX != 0) {
			directions[j] = UTurn;
			prevDeltaX = deltaX;
			prevDeltaY = deltaY;
			printf("%s \n", getDirectionName(directions[j]));
			i++;
			j++;
			continue;
		}
		if (deltaY == 1 && prevDeltaX == 1) {
			directions[j] = Right;
		}
		else if (deltaY == 1 && prevDeltaX == -1) {
			directions[j] = Left;
		}
		else if (deltaY == -1 && prevDeltaX == -1) {
			directions[j] = Right; //CHANGE THIS LOGIC PLS
		}
		else if (deltaY == -1 && prevDeltaX == 1) {
			directions[j] = Left;
		}
		else if (deltaX == 1 && prevDeltaY == -1) {
			directions[j] = Right;
		}
		else if (deltaX == -1 && prevDeltaY == 1) {
			directions[j] = Right;
		}
		else if (deltaX == -1 && prevDeltaY == -1) {
			directions[j] = Left;
		}
		else if (deltaX == 1 && prevDeltaY == 1) {
			directions[j] = Left;
		}
		else {
			directions[j] = Straight;
		}
		printf("%s \n", getDirectionName(directions[j]));
		prevDeltaX = deltaX;
		prevDeltaY = deltaY;
		i++;
		j++;
	}
	i -= 2;
	finalDirectionY = rowcoords[i + 1] - rowcoords[i];
	finalDirectionX = colcoords[i + 1] - colcoords[i];
}

int main()
{
    print_maze();
    dfs(start_row, start_col, 0, 0, down, start);
	ConvertPathToDirection();
    print_coords();
    print_maze();

    return 0;
}
