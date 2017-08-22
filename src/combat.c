#include "rogue.h"

int combat(Player* player, Monster* monster, int order) {
    if (order == 1) {
        // player attacking 
        monster->health -= player->attack;
        if (monster->health > 0) {
            player->health -= monster->attack;
        } else {
            kill_monster(monster);
        }
    } else {
        // monster attacking
        player->health -= monster->attack;
        if (player->health > 0) {
            monster->health -= player->attack;
        }
    }
    return 1;
}

