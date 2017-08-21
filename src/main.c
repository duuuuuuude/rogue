#include "rogue.h"

int main () {
    Player* user;
    user = player_setup();

    screen_setup();

    map_setup();

    int kek = 0;
    // game loop
    int ch;
    while((ch = getch()) != 'q') {
        kek++;
        handle_input(ch, user);
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

Room** map_setup() {
    Room** rooms;
    // TODO Room* rooms = (Room*)malloc(sizeof(Room)*6);
    rooms = (Room**)malloc(sizeof(Room*) * 6); // Array of 6 pointers?

    rooms[0] = create_room(13, 13, 6, 8);
    draw_room(rooms[0]);
    
    rooms[1] = create_room(40, 2, 6, 8);
    draw_room(rooms[1]);

    rooms[2] = create_room(40, 10, 6, 12);
    draw_room(rooms[2]);
    
    connect_doors(rooms[0]->doors[3], rooms[2]->doors[1]);
    connect_doors(rooms[1]->doors[2], rooms[0]->doors[0]);

    return rooms;
}

