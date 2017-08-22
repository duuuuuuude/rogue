#include "rogue.h"

void screen_setup() { 
    srand(time(NULL));
    initscr();
    printw("Hello world!");
    noecho();
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
