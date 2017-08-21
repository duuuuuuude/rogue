#ifndef ROGUE_H
#define ROGUE_H

// TODO: GET TO KNOW HOW NCURSES COORDS WORK
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

typedef struct Level {
    char** tiles;
    int level;
    int num_of_rooms;
    struct Room** rooms;
    //struct Monster** monsters;
    //int num_of_monsters;
} Level;

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

// level/map functions
Room** rooms_setup();
char** save_lvl_positions();
Level* create_level(int);

// player functions
Player* player_setup();

Position* handle_input(int, Player*);
int check_pos(Position*, Player*, char**); 
int player_move(Position*, Player*, char**);

// room functions
int draw_room(Room*);
Room* create_room(int x, int y, int height, int width); 
int connect_doors(Position* door_one, Position* door_two);

#endif
