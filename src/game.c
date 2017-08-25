#include "rogue.h"

void render(Game* game) {
	clear();
	print_gamehub(game->levels[game->current_level - 1]);
	draw_level(game->levels[game->current_level - 1]);
}

int game_loop(Game* game) {
	int ch = '\0';
	Position* new_position;
	Level* level;

	if (game->current_level == 0) {
		game->levels[game->current_level] = create_level(1);
		game->current_level++;
	}
	level = game->levels[game->current_level - 1];

	print_gamehub(level);

	while (ch != 'q') {
		print_gamehub(level);
		new_position = handle_input(ch, level->user);
		check_pos(new_position, level);
		move_monsters(level);
		render(game);

		clear();
		print_gamehub(level);
		draw_level(level);

		move(level->user->position->y, level->user->position->x);

		if (level->user->health <= 0) {
			game->current_level = 0;
			return -1;
		}
		ch = getch();
	}
}

