#include "rogue.h"

Level* create_level(int level) {
    Level* new_level;
    new_level = malloc(sizeof(Level));

    new_level->rooms = rooms_setup();
    new_level->tiles = save_lvl_positions();
    new_level->level = level;
    new_level->num_of_rooms = 3;
    new_level->user = player_setup();

    place_player(new_level->rooms, new_level->user);
    add_monsters(new_level);
    return new_level;
}

Room** rooms_setup() {
    Room** rooms;

    rooms = (Room**)malloc(sizeof(Room*) * 6); // Array of 6 pointers?

    for (int x = 0; x < 6; x++) {
        rooms[x] = create_room(x);
        draw_room(rooms[x]);

    }
     
    //connect_doors(rooms[0]->doors[3], rooms[2]->doors[1]);
    //connect_doors(rooms[1]->doors[2], rooms[0]->doors[0]);

    return rooms;
}

char** save_lvl_positions() {
    char** positions;
    positions = (char**)malloc(sizeof(char*) * 25);

    for (int y = 0; y < 25; y++) {
        positions[y] = (char*)malloc(sizeof(char) * 100);
        for (int x = 0; x < 100; x++) {
            positions[y][x] = mvinch(y, x);
        }
    }
    return positions;
}
