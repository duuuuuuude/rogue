// TODO: GET TO KNOW HOW NCURSES COORDS WORK
#include <stdlib.h>
#include <ncurses.h>

typedef struct Room {
    int x_pos;
    int y_pos;
    int height;
    int width;
    // Each r. stores info of how many monsters/items it has
    // Monster** monsters
    // Item** items
} Room;

typedef struct Player {
    int x_pos;
    int y_pos;
    int health;
} Player;

void screen_setup();
Room** map_setup();
Player* player_setup();
int handle_input(int, Player*);
int player_move(int, int, Player*);
int check_pos(int, int, Player*); 
int draw_room(Room*);
Room* create_room(int x, int y, int height, int width); 

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

    rooms[2] = create_room(40, 10, 6, 8);
    draw_room(rooms[2]);

    return rooms;
}

int draw_room(Room* room) {
    int x;
    int y;
    for (x = room->x_pos; x < room->x_pos + room->width; x++) {
        // top and bottom
        mvprintw(room->y_pos, x, "-");
        mvprintw(room->y_pos + room->height - 1, x, "-");
    }
    for (y = room->y_pos + 1; y < room->y_pos + room->height - 1; y++) {
        // walls 
        mvprintw(y, room->x_pos, "|");
        mvprintw(y, room->x_pos + room->width - 1, "|");
        // floors 
        for(x = room->x_pos + 1; x < room->x_pos + room->width - 1; x++) {
            mvprintw(y, x, ".");
        }
    }
}

Room* create_room(int x, int y, int height, int width) {
    Room* new_room;
    new_room = (Room*)malloc(sizeof(Room));

    new_room->x_pos = x;
    new_room->y_pos = y;
    new_room->height = height;
    new_room->width = width;

    return new_room;
}

Player* player_setup() {
    Player* new_player;
    new_player = (Player*)malloc(sizeof(Player));

    new_player->x_pos = 14;
    new_player->y_pos = 14;
    new_player->health = 20;

    mvprintw(new_player->y_pos, new_player->x_pos, "@");
    move(new_player->y_pos, new_player->x_pos); // move cursor

    return new_player;
}

int handle_input(int ch, Player* user) {
    int new_x;
    int new_y;
    
    switch(ch) {
        // move up
        case 'w':
            // NOTE: user's struct coords aren't actually being changed 
            new_x = user->x_pos;
            new_y = user->y_pos - 1;
            break;

        // move down
        case 's':
            new_x = user->x_pos;
            new_y = user->y_pos + 1;
            break;

        // move left
        case 'a':
            new_x = user->x_pos - 1;
            new_y = user->y_pos;
            break;

        // move right
        case 'd':
            new_x = user->x_pos + 1;
            new_y = user->y_pos;
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
            player_move(new_x, new_y, user);
            break;

        default:
            move(user->y_pos, user->x_pos);
            break;
    }
}

/* change player's coords */
int player_move(int x, int y, Player* user) {
    mvprintw(user->y_pos, user->x_pos, ".");
    
    user->x_pos = x;
    user->y_pos = y;

    mvprintw(user->y_pos, user->x_pos, "@");
    move(user->y_pos, user->x_pos);
}
 
