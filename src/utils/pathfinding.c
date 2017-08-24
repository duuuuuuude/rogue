#include "rogue.h"
#include "utils.h"

void add_to_frontier(int** frontier, int frontier_count, int y, int x) {
	frontier[frontier_count][0] = y;
	frontier[frontier_count][1] = x;
}

int check_position(int y, int x) {
	char temp = mvinch(y, x);

	if (temp == '.' || temp == '|' || temp == '-') {
		return 0;
	} else {
		return 1;
	}
}

// Add neighbor cells of (x, y) to queue(aka frontier) and set (aka CameFrom array)
int add_neighbour_cells(int** frontier, int frontier_count, int*** came_from, int y, int x) {
    // add coord to north
    if (y > 0 && came_from[y - 1][x][0] < 0 && check_position(y - 1, x)) {
        // add to queue
    	add_to_frontier(frontier, frontier_count, y - 1, x);
        frontier_count++;
        // add to came_from
        came_from[y - 1][x][0] = y;
        came_from[y - 1][x][1] = x;
    }

    // add to queue coord to south
    if (y < (MAX_HEIGHT - 1) && came_from[y + 1][x][0] < 0 && check_position(y + 1, x)) {
        add_to_frontier(frontier, frontier_count, y + 1, x);
        frontier_count++;
        came_from[y + 1][x][0] = y;
        came_from[y + 1][x][1] = x;
    }

    // add to queue coord to east
    if (x < (MAX_WIDTH - 1) && came_from[y][x + 1][0] < 0 && check_position(y, x + 1)) {
        add_to_frontier(frontier, frontier_count, y, x + 1);
        frontier_count++;
        came_from[y][x + 1][0] = y;
        came_from[y][x + 1][1] = x;
    }

    // add to queue coord to west
    if (x > 0 && came_from[y][x - 1][0] < 0 && check_position(y, x - 1)) {
        add_to_frontier(frontier, frontier_count, y, x - 1);
        frontier_count++;
        came_from[y][x - 1][0] = y;
        came_from[y][x - 1][1] = x;
    }

    return frontier_count;
}

void pathfind(Position* start, Position* end) {

	int x;	// coord x
	int y;	// coord y

	// Frontier. Stores array of (x, y). [count]([0] - x OR [1] - y)
	// [count][0 or 1] = x or y coords
	int** frontier = malloc(sizeof(int*) * MAX_HEIGHT * MAX_WIDTH);

	// CameFrom array. Stores two pairs of (x, y). First pair - came to, 2nd - came from
	// First 2 indexes of CameFrom - coords popped from frontier queue (on 1st step of alg.) or
	int*** came_from = malloc(sizeof(int**) * MAX_HEIGHT);

	int frontier_index = 0;
	int frontier_count = 0;

	// Allocate memory for frontier array
	for (int i = 0; i < MAX_HEIGHT * MAX_WIDTH; i++) {
		frontier[i] = malloc(sizeof(int) * 2);
	}

	// Allocate memory for came_from array
	for (int i = 0; i < MAX_HEIGHT; i++) {
		came_from[i] = malloc(sizeof(int*) * MAX_WIDTH);
		for (int j = 0; j < MAX_WIDTH; j++) {
			came_from[i][j] = malloc(sizeof(int) * 2);
			came_from[i][j][0] = -1;
			came_from[i][j][1] = -1;
		}
	}

	// (came_from[1][1]: (-9, -9) -> came_from[1][1][0] = -9; came_from[1][1][1] = -9;)
	came_from[start->y][start->x][0] = -9;
	came_from[start->y][start->x][1] = -9;

	// add start position to frontier 'queue'
	add_to_frontier(frontier, frontier_count, start->y, start->x);
	frontier_count++;

	while (frontier_index < frontier_count) {
		// pop an element from frontier 'queue'
		y = frontier[frontier_index][0];
		x = frontier[frontier_index][1];

		frontier_index++;

		// if popped el equals end
		if (y == end->y && x == end->x) {
			break;
		}
		// add neighbors of this cell to queue and set
		frontier_count = add_neighbour_cells(frontier, frontier_count, came_from, y, x);
	}

	y = end->y;
	x = end->x;

	while (y != start->y || x != start->x) {
		int temp_y = y;
		y = came_from[temp_y][x][0];
		x = came_from[temp_y][x][1];
		mvprintw(y, x, "+");
		getch();
	}
}


