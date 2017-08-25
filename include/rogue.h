#ifndef ROGUE_H
#define ROGUE_H

// TODO: GET TO KNOW HOW NCURSES COORDS WORK
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

typedef struct Game {
	struct Level* levels[10];
	int current_level;
} Game;


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

    struct Door** doors;
    int num_of_doors;
    // Each r. stores info of how many monsters/items it has
    // Monster** monsters
    // Item** items
} Room;

typedef struct Door {
	Position position;
	int connected; // 0 - false; 1 - true
} Door;

typedef struct Player {
    Position* position;
    int health;
    int attack;
    int gold;
    int max_health;
    int experience;

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
    int alive;
    Position* position;
} Monster;

int MAX_HEIGHT;
int MAX_WIDTH;


// screen functions
void screen_setup();
int print_gamehub(Level*); 

// level/map functions
Room** rooms_setup();
char** save_lvl_positions();
Level* create_level(int);

// player functions
Player* player_setup();
Position* handle_input(int, Player*);
int check_pos(Position*, Level*); 
int player_move(Position*, Player*, char**);
int place_player(Room** rooms, Player* user); 
void draw_player(Player*);

// room functions
int draw_room(Room*);
Room* create_room(int grid, int num_of_doors);
void connect_doors(Level*);

// monster functions 
int add_monsters(Level*);
Monster* select_monster(int level); 
Monster* create_monster(char symbol, int health, int attack, int speed, int defence, int pathfinding);
int set_starting_position(Monster* monster, Room* room);
int move_monsters(Level*);
int pathfinding_seek(Position*, Position*);
int pathfinding_random(Position*); 
void kill_monster(Monster*); 
Monster* get_monster_at(Position* position, Monster** monsters); 
int combat(Player* player, Monster* monster, int order); 

void draw_monster(Monster*);
int game_loop(Game*);
void draw_level(Level*);

#endif
