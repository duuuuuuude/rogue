#include "rogue.h"

int main () {
    screen_setup();

    Level* level = create_level(1);

    // game loop
    int ch;
    while((ch = getch()) != 'q') {
        Position* new_position = handle_input(ch, level->user);
        check_pos(new_position, level->user, level->tiles);
        move_monsters(level);
        //move(level->user->position->y, level->user->position->x);
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

