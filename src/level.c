#include "rogue.h"

Level* create_level(int level) {
    Level* new_level;
    new_level = malloc(sizeof(Level));

    new_level->rooms = rooms_setup();
    new_level->tiles = save_lvl_positions();
    new_level->level = level;
    new_level->num_of_rooms = 3;
    new_level->user = player_setup();
    add_monsters(new_level);
    return new_level;
}

Room** rooms_setup() {
    Room** rooms;
    // TODO Room* rooms = (Room*)malloc(sizeof(Room)*6);
    rooms = (Room**)malloc(sizeof(Room*) * 6); // Array of 6 pointers?

    rooms[0] = create_room(13, 13, 6, 8);
    draw_room(rooms[0]);
    
    rooms[1] = create_room(40, 2, 6, 8);
    draw_room(rooms[1]);

    rooms[2] = create_room(40, 10, 6, 12);
    draw_room(rooms[2]);
    
    connect_doors(rooms[0]->doors[3], rooms[2]->doors[1]);
    connect_doors(rooms[1]->doors[2], rooms[0]->doors[0]);

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
