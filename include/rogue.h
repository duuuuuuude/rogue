#ifndef ROGUE_H
#define ROGUE_H

// TODO: GET TO KNOW HOW NCURSES COORDS WORK
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

typedef struct Position {
    int x;
    int y;
    // TILE_TYPE
} Position;

typedef struct Room {
    Position position;
    int height;
    int width;

    Position** doors;
    
    // Each r. stores info of how many monsters/items it has
    // Monster** monsters
    // Item** items
} Room;

typedef struct Player {
    Position position;
    int health;
} Player;

void screen_setup();
Room** map_setup();
Player* player_setup();
int handle_input(int, Player*);
int player_move(int, int, Player*);
int check_pos(int, int, Player*); 
int draw_room(Room*);
Room* create_room(int x, int y, int height, int width); 
int connect_doors(Position* door_one, Position* door_two);


#endif
