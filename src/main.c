#include "rogue.h"
#include "utils.h"
#include "main_menu.h"

void menu_loop() {
	int choice;
	char * choices[] = {"Start Game", "End Game"};

	Game game;
	game.current_level = 0;

	while (true) {
		choice = main_menu(2, choices);
		switch (choice) {
			case START_GAME:
				game_loop(&game);
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
