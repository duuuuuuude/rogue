#include "rogue.h"
#include "utils.h"
#include "main_menu.h"

int game_loop() {
	int ch;
	Position* new_position;
	Level* level;

	level = create_level(1);
	print_gamehub(level);

	while ((ch = getch()) != 'q') {
		print_gamehub(level);
		new_position = handle_input(ch, level->user);
		check_pos(new_position, level);
		move_monsters(level);
		move(level->user->position->y, level->user->position->x);

		if (level->user->health <= 0) {
			return -1;
		}
	}
}

void menu_loop() {
	int choice;
	char * choices[] = {"Start Game", "End Game"};

	while (true) {
		choice = main_menu(2, choices);

		switch (choice) {
			case START_GAME:
				game_loop();
				clear();
				break;
			case QUIT_GAME:
				return;
				break;
		}
	}
}

int main() {
	screen_setup();
	menu_loop();
	endwin();
	return 0;
}
