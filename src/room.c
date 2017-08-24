#include "rogue.h"

int draw_room(Room* room) {
    int x;
    int y;
    for (x = room->position.x; x < room->position.x + room->width; x++) {
        // top and bottom
        mvprintw(room->position.y, x, "-");
        mvprintw(room->position.y + room->height - 1, x, "-");
    }
    for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++) {
        // walls 
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");
        // floors 
        for(x = room->position.x + 1; x < room->position.x + room->width - 1; x++) {
            mvprintw(y, x, ".");
        }
    }

    mvprintw(room->doors[0]->position.y, room->doors[0]->position.x, "+");
    mvprintw(room->doors[1]->position.y, room->doors[1]->position.x, "+");
    mvprintw(room->doors[2]->position.y, room->doors[2]->position.x, "+");
    mvprintw(room->doors[3]->position.y, room->doors[3]->position.x, "+");
}

Room* create_room(int grid, int num_of_doors) {
    Room* new_room;
    new_room = (Room*)malloc(sizeof(Room));
    new_room->num_of_doors = num_of_doors;

    switch(grid) {
        case 0:
            new_room->position.x = 0;
            new_room->position.y = 0;
            break;

        case 1:
            new_room->position.x = 33;
            new_room->position.y = 0;
            break;

        case 2:
            new_room->position.x = 66;
            new_room->position.y = 0;
            break;

        case 3:
            new_room->position.x = 0;
            new_room->position.y = 14;
            break;

        case 4:
            new_room->position.x = 33;
            new_room->position.y = 14;
            break;

        case 5:
            new_room->position.x = 66;
            new_room->position.y = 14;
            break;
    }
    new_room->height = rand() % 6 + 4;
    new_room->width = rand() % 14 + 4;
    
    // offset
    new_room->position.x += rand() % (30 - new_room->width) + 1;
    new_room->position.y += rand() % (10 - new_room->height) + 1;

    // Allocate memory for doors
    new_room->doors = (Door**)malloc(sizeof(Door*) * num_of_doors);
    for (int i = 0; i < num_of_doors; i++) {
    	new_room->doors[i] = (Door*)malloc(sizeof(Door));
    	new_room->doors[i]->connected = 0;

    }

    // top door
    new_room->doors[0]->position.x = rand() % (new_room->width - 2) + new_room->position.x + 1;
    new_room->doors[0]->position.y = new_room->position.y;

    // left door
    new_room->doors[1]->position.y = rand() % (new_room->height - 2) + new_room->position.y + 1;
    new_room->doors[1]->position.x = new_room->position.x;

    // bottom door
    new_room->doors[2]->position.x = rand() % (new_room->width - 2) + new_room->position.x + 1;
    new_room->doors[2]->position.y = new_room->position.y + new_room->height - 1;

    // right door
    new_room->doors[3]->position.y = rand() % (new_room->height - 2) + new_room->position.y + 1;
    new_room->doors[3]->position.x = new_room->position.x + new_room->width - 1;

    return new_room;
}

