#include "rogue.h"
#include "utils.h"

int main () {
    screen_setup();

    MAX_HEIGHT = 25;
    MAX_WIDTH = 100;

    Level* level = create_level(1);

    // game loop
    print_gamehub(level);
    
    int ch;
    while((ch = getch()) != 'q') {
        print_gamehub(level);
        Position* new_position = handle_input(ch, level->user);
        check_pos(new_position, level);
        move_monsters(level);
        move(level->user->position->y, level->user->position->x);
    }

    endwin(); 

    return 0;
}


