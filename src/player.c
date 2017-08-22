#include "rogue.h"

Player* player_setup() {
    Player* new_player;
    new_player = (Player*)malloc(sizeof(Player));
    new_player->position = malloc(sizeof(Position));
    new_player->position->x = 14;
    new_player->position->y = 14;
    new_player->health = 20;
    new_player->attack = 1;
    mvprintw(new_player->position->y, new_player->position->x, "@");
    move(new_player->position->y, new_player->position->x); // move cursor

    return new_player;
}

Position* handle_input(int ch, Player* user) {
    Position* new_position;
    new_position = (Position*)malloc(sizeof(Position));

    switch(ch) {
        // move up
        case 'w':
            // NOTE: user's struct coords aren't actually being changed 
            new_position->x = user->position->x;
            new_position->y = user->position->y - 1;
            break;

        // move down
        case 's':
            new_position->x = user->position->x;
            new_position->y = user->position->y + 1;
            break;

        // move left
        case 'a':
            new_position->x = user->position->x - 1;
            new_position->y = user->position->y;
            break;

        // move right
        case 'd':
            new_position->x = user->position->x + 1;
            new_position->y = user->position->y;
            break;

        default:
            break;
    }
    return new_position;
}

/* check what is at next position */
int check_pos(Position* next_pos, Level* level) {
    Player* user;
    user = level->user;
    int space;
   
    switch(mvinch(next_pos->y, next_pos->x)) {
        case '.':
        case '+':
        case '#':
            player_move(next_pos, user, level->tiles);
            break;

        case 'X':
        case 'G':
        case 'T':
            combat(user, get_monster_at(next_pos, level->monsters), 1);
            break;

        default:
            move(user->position->y, user->position->x);
            break;
    }
}

/* change player's coords */
int player_move(Position* new_position, Player* user, char** level) {
    char buffer[8];

    sprintf(buffer, "%c", level[user->position->y][user->position->x]);

    mvprintw(user->position->y, user->position->x, buffer);
    
    user->position->y = new_position->y;
    user->position->x = new_position->x;

    mvprintw(user->position->y, user->position->x, "@");
    move(user->position->y, user->position->x);
}
