#include "rogue.h"

void screen_setup() { 
	MAX_HEIGHT = 25;
	MAX_WIDTH = 100;
    srand(time(NULL));
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    refresh();
}
int print_gamehub(Level* level) {
    mvprintw(25, 0, "   LeveL: %d", level->level);
    printw("    Gold: %d", level->user->gold);
    printw("    Hp: %d(%d)", level->user->health, level->user->max_health);
    printw("    Attack: %d", level->user->attack);
    printw("    Exp:: %d", level->user->experience);
    printw("      ");

    return 1;
}
