#include "rogue.h"

Player* player_setup() {
    Player* new_player;
    new_player = (Player*)malloc(sizeof(Player));

    new_player->position.x = 14;
    new_player->position.y = 14;
    new_player->health = 20;

    mvprintw(new_player->position.y, new_player->position.x, "@");
    move(new_player->position.y, new_player->position.x); // move cursor

    return new_player;
}

int handle_input(int ch, Player* user) {
    int new_x;
    int new_y;
    
    switch(ch) {
        // move up
        case 'w':
            // NOTE: user's struct coords aren't actually being changed 
            new_x = user->position.x;
            new_y = user->position.y - 1;
            break;

        // move down
        case 's':
            new_x = user->position.x;
            new_y = user->position.y + 1;
            break;

        // move left
        case 'a':
            new_x = user->position.x - 1;
            new_y = user->position.y;
            break;

        // move right
        case 'd':
            new_x = user->position.x + 1;
            new_y = user->position.y;
            break;

        default:
            break;
    }
    check_pos(new_x, new_y, user);
}

/* check what is at next position */
int check_pos(int new_x, int new_y, Player* user) {

    switch(mvinch(new_y, new_x)) {
        case '.':
        case '+':
        case '#':
            player_move(new_x, new_y, user);
            break;

        default:
            move(user->position.y, user->position.x);
            break;
    }
}

/* change player's coords */
int player_move(int x, int y, Player* user) {
    mvprintw(user->position.y, user->position.x, ".");
    
    user->position.x = x;
    user->position.y = y;

    mvprintw(user->position.y, user->position.x, "@");
    move(user->position.y, user->position.x);
}
