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

    mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
    mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
    mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
    mvprintw(room->doors[3]->y, room->doors[3]->x, "+");
}

Room* create_room(int x, int y, int height, int width) {
    Room* new_room;
    new_room = (Room*)malloc(sizeof(Room));

    new_room->position.x = x;
    new_room->position.y = y;
    new_room->height = height;
    new_room->width = width;
    
    new_room->doors = (Position**)malloc(sizeof(Position*) * 4);

    // top door
    new_room->doors[0] = (Position*)malloc(sizeof(Position));
    new_room->doors[0]->x = rand() % (width - 2) + new_room->position.x + 1;
    new_room->doors[0]->y = new_room->position.y;

    // bottom door
    new_room->doors[1] = (Position*)malloc(sizeof(Position));
    new_room->doors[1]->x = rand() % (width - 2) + new_room->position.x + 1;
    new_room->doors[1]->y = new_room->position.y + height - 1;

    // left door
    new_room->doors[2] = (Position*)malloc(sizeof(Position));
    new_room->doors[2]->y = rand() % (height - 2) + new_room->position.y + 1;
    new_room->doors[2]->x = new_room->position.x;

    // right door
    new_room->doors[3] = (Position*)malloc(sizeof(Position));
    new_room->doors[3]->y = rand() % (height - 2) + new_room->position.y + 1;
    new_room->doors[3]->x = new_room->position.x + width - 1;

    return new_room;
}

int connect_doors(Position* door_one, Position* door_two) {
    Position temp;
    Position prev;

    temp.x = door_one->x;
    temp.y = door_one->y;
    
    prev = temp;
    // path finding
    int count = 0;
    while(1) {
        // step left
        if (abs((temp.x - 1) - door_two->x) < abs(temp.x - door_two->x) && (mvinch(temp.y, temp.x - 1) == ' ')) {
            prev.x = temp.x;
            temp.x = temp.x - 1;
        }
        // step right
        else if (abs((temp.x + 1) - door_two->x) < abs(temp.x - door_two->x) && (mvinch(temp.y, temp.x + 1) == ' ')) {
            prev.x = temp.x;
            temp.x = temp.x + 1;
        }
        // step up
        else if (abs((temp.y - 1) - door_two->y) < abs(temp.y - door_two->y) && (mvinch(temp.y - 1, temp.x) == ' ')) {
            prev.y = temp.y;
            temp.y = temp.y - 1;
        }
        // step down
        else if (abs((temp.y + 1) - door_two->y) < abs(temp.y - door_two->y) && (mvinch(temp.y + 1, temp.x) == ' ')) {
            prev.y = temp.y;
            temp.y = temp.y + 1;
        } 
        else {
            if (count == 0) {
                temp = prev;
                count++;
                continue;
            } 
            else {
                return 0;
           }
        }
        mvprintw(temp.y, temp.x, "#");
    }
    return 1;
} 

