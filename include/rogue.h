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
    struct Monster** monsters;
    int num_of_monsters;
    struct Player* user;
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
    Position* position;
    int health;
} Player;

typedef struct Monster {
    char string[2];
    // represent monster on the map
    char symbol;
    int health;
    int attack;
    int speed;
    int defence;
    int pathfinding;

    Position* position;
} Monster;

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

// monster functions 
int add_monsters(Level*);
Monster* select_monster(int level); 
Monster* create_monster(char symbol, int health, int attack, int speed, int defence, int pathfinding);
int set_starting_position(Monster* monster, Room* room);
int move_monsters(Level*);
int pathfinding_seek(Position*, Position*);
int pathfinding_random(Position*); 

#endif
