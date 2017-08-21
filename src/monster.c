#include "rogue.h"

int add_monsters(Level* level) {
    level->monsters = malloc(sizeof(Monster*) * 6);
    
    level->num_of_monsters = 0;

    for (int x = 0; x < level->num_of_rooms; x++) {
        if (rand() % 2 == 0) {
            level->monsters[level->num_of_monsters] = select_monster(level->level);
            set_starting_position(level->monsters[level->num_of_monsters], level->rooms[x]);
            level->num_of_monsters++;
        }
    }
}

Monster* select_monster(int level) {
    int monster;

    switch(level) {
        case 1:
        case 2:
        case 3:
            monster = (rand() % 2) + 1;
            break;
        case 4:
        case 5:
            monster = (rand() % 2) + 2;
            break;
        case 6:
            monster = 3;
            break;
    }

    switch(monster) {
        case 1:
            // spider
            return create_monster('X', 2, 1, 1, 1, 1);

        case 2:
            // goblin
            return create_monster('G', 5, 3, 1, 1, 2);

        case 3:
            // troll
            return create_monster('T', 15, 5, 1, 1, 1);
    }
}

Monster* create_monster(char symbol, int health, int attack, int speed, int defence, int pathfinding) {
   Monster* new_monster = (Monster*)malloc(sizeof(Monster));

   new_monster->symbol = symbol;
   new_monster->health = health;
   new_monster->attack = attack;
   new_monster->speed = speed;
   new_monster->defence = defence;
   new_monster->pathfinding = pathfinding;

   return new_monster;
}

int set_starting_position(Monster* monster, Room* room) {
    char buffer[8];

    monster->position.x = (rand() % (room->width - 2)) + room->position.x + 1;
    monster->position.y = (rand() % (room->height - 2)) + room->position.y + 1;

    sprintf(buffer, "%c", monster->symbol);

    mvprintw(monster->position.y, monster->position.x, buffer);

}

/*
 * Spider:
 *      symbol: X
 *      levels: 1-3
 *      health: 2
 *      attack: 1
 *      speed: 1
 *      defence: 1
 *      pathfinding: 1 (aka random)

 * Goblin:
 *      symbol: G
 *      levels: 1-5
 *      health: 2
 *      attack: 3
 *      speed: 1
 *      defence: 1
 *      pathfinding: 2 (aka seeking)

 * Troll:
 *      symbol: T
 *      levels: 4-6
 *      health: 15
 *      attack: 5
 *      speed: 1
 *      defence: 1
 *      pathfinding: 2 (aka random)
 * 
 * */


