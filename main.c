// TODO: GET TO KNOW HOW NCURSES COORDS WORK
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

typedef struct Position {
    int x;
    int y;
    // TILE_TYPE
} Position;

typedef struct Room {
    Position position;
    int height;
    int width;

    Position** doors;
    
    // Each r. stores info of how many monsters/items it has
    // Monster** monsters
    // Item** items
} Room;

typedef struct Player {
    Position position;
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
int connect_doors(Position* door_one, Position* door_two);

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

    rooms[2] = create_room(40, 10, 6, 8);
    draw_room(rooms[2]);
    
    connect_doors(rooms[0]->doors[3], rooms[2]->doors[1]);

    return rooms;
}

int draw_room(Room* room) {
    int x;
    int y;
    for (x = room->position.x; x < room->position.x + room->width; x++) {
        // top and bottom
        mvprintw(room->position.y, x, "-");
        mvprintw(room->position.y + room->height - 1, x, "-");
    }
    for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++) {
        // walls 
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");
        // floors 
        for(x = room->position.x + 1; x < room->position.x + room->width - 1; x++) {
            mvprintw(y, x, ".");
        }
    }

    mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
    mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
    mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
    mvprintw(room->doors[3]->y, room->doors[3]->x, "+");
}

Room* create_room(int x, int y, int height, int width) {
    Room* new_room;
    new_room = (Room*)malloc(sizeof(Room));

    new_room->position.x = x;
    new_room->position.y = y;
    new_room->height = height;
    new_room->width = width;
    
    new_room->doors = (Position**)malloc(sizeof(Position*) * 4);

    // top door
    new_room->doors[0] = (Position*)malloc(sizeof(Position));
    new_room->doors[0]->x = rand() % (width - 2) + new_room->position.x + 1;
    new_room->doors[0]->y = new_room->position.y;

    // bottom door
    new_room->doors[1] = (Position*)malloc(sizeof(Position));
    new_room->doors[1]->x = rand() % (width - 2) + new_room->position.x + 1;
    new_room->doors[1]->y = new_room->position.y + height - 1;

    // left door
    new_room->doors[2] = (Position*)malloc(sizeof(Position));
    new_room->doors[2]->y = rand() % (height - 2) + new_room->position.y + 1;
    new_room->doors[2]->x = new_room->position.x;

    // right door
    new_room->doors[3] = (Position*)malloc(sizeof(Position));
    new_room->doors[3]->y = rand() % (height - 2) + new_room->position.y + 1;
    new_room->doors[3]->x = new_room->position.x + width - 1;

    return new_room;
}

int connect_doors(Position* door_one, Position* door_two) {
    Position temp;

    temp.x = door_one->x;
    temp.y = door_one->y;

    // path finding

    while(1) {
        // step left
        if (abs((temp.x - 1) - door_two->x) < abs(temp.x - door_two->x) && (mvinch(temp.y, temp.x - 1) == ' ')) {
            mvprintw(temp.y, temp.x - 1, "#");
            temp.x = temp.x - 1;
        }
        // step right
        else if (abs((temp.x + 1) - door_two->x) < abs(temp.x - door_two->x) && (mvinch(temp.y, temp.x + 1) == ' ')) {
            mvprintw(temp.y, temp.x + 1, "#");
            temp.x = temp.x + 1;
        }
        // step up
        else if (abs((temp.y - 1) - door_two->y) < abs(temp.y - door_two->y) && (mvinch(temp.y - 1, temp.x) == ' ')) {
            mvprintw(temp.y - 1, temp.x, "#");
            temp.y = temp.y - 1;
        }
        // step down
        else if (abs((temp.y + 1) - door_two->y) < abs(temp.y - door_two->y) && (mvinch(temp.y + 1, temp.x) == ' ')) {
            mvprintw(temp.y + 1, temp.x, "#");
            temp.y = temp.y + 1;
        } 
        else {
            return 0;
        }
    }
    return 1;
}

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
 

