#include "rogue.h"

int main () {
    Player* user = player_setup();

    // Position* new_position;

    screen_setup();
    //rooms_setup();
    Level* level = create_level(1);
    //char** level = save_lvl_positions();
    // game loop
    int ch;
    while((ch = getch()) != 'q') {
        Position* new_position = handle_input(ch, user);
        check_pos(new_position, user, level->tiles);
    }

    endwin(); 

    return 0;
}

void screen_setup() { 
    srand(time(NULL));
    initscr();
    printw("Hello world!");
    noecho();
    refresh();
}

