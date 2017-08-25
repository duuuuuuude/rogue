#include "rogue.h"
#include "utils.h"

Level* create_level(int level) {
    Level* new_level;
    new_level = malloc(sizeof(Level));

    new_level->level = level;
    new_level->num_of_rooms = 6;
    new_level->rooms = rooms_setup();
    connect_doors(new_level);
    new_level->tiles = save_lvl_positions();

    new_level->user = player_setup();
    place_player(new_level->rooms, new_level->user);

    add_monsters(new_level);

    return new_level;
}

void draw_level(Level* level) {
    char** positions;

    // printing tiles
    for (int y = 0; y < MAX_HEIGHT; y++) {
        for (int x = 0; x < MAX_WIDTH; x++) {
        	mvaddch(y, x, level->tiles[y][x]);
        }
    }
    // printing monsters
    for (int i = 0; i < level->num_of_monsters; i++) {
    	draw_monster(level->monsters[i]);
    }

    draw_player(level->user);
}

Room** rooms_setup() {
    Room** rooms;

    rooms = (Room**)malloc(sizeof(Room*) * 6); // Array of 6 pointers?

    for (int x = 0; x < 6; x++) {
        rooms[x] = create_room(x, 4);
        draw_room(rooms[x]);

    }

    return rooms;
}

void connect_doors(Level* level) {
	int random_room, random_door;
	int count;
	// for every room
	for (int i = 0; i < level->num_of_rooms; i++) {
		// for every door
		for (int j = 0; j < level->rooms[i]->num_of_doors; j++) {
			// if picked door is already connected, go to next door
			if (level->rooms[i]->doors[j]->connected == 1) {
				continue;
			}

			count = 0;

			while (count < 2) {
				// pick random door from random room
				random_room = rand() % level->num_of_rooms;
				random_door = rand() % level->rooms[random_room]->num_of_doors;
				// if randomly picked door already connected or we picked a room we're currently in..
				if (level->rooms[random_room]->doors[random_door]->connected == 1 || random_room == i) {
					count++;
					continue;
				}
				// connect this door with randomly picked one
				pathfind(&level->rooms[random_room]->doors[random_door]->position,
						&level->rooms[i]->doors[j]->position);
				// mark this room and randomly picked one as connected
				level->rooms[random_room]->doors[random_door]->connected = 1;
				level->rooms[i]->doors[j]->connected = 1;
				// if we've successfully connected, we need to brakes
				break;
			}
		}
	}
}

char** save_lvl_positions() {
    char** positions;
    positions = (char**)malloc(sizeof(char*) * 25);

    for (int y = 0; y < MAX_HEIGHT; y++) {
        positions[y] = (char*)malloc(sizeof(char) * 100);
        for (int x = 0; x < MAX_WIDTH; x++) {
            positions[y][x] = mvinch(y, x);
        }
    }
    return positions;
}
