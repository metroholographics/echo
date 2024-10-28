#include <echo.h>

Player*
init_player(void)
{
	Player* p = calloc(1, sizeof(Player));

	if (p == NULL) {
		printf("Player could not be initialised\n");
		return p;
	}
	p->source.x = 0;
	p->source.y = 0;
	p->source.w = TILE_W;
	p->source.h = TILE_H;
	p->pos.x = MAP_W / 2;
	p->pos.y = MAP_H / 2;
	p->dest.x = 0;
	p->dest.y = 0;
	p->dest.w = MAP_TILE_W;
	p->dest.h = MAP_TILE_H;

	return p;
}

void
move_player(SDL_Event e)
{
	SDL_Point new_pos = player->pos;

	if (e.key.keysym.sym == SDLK_w) new_pos.y -= 1;
	else if (e.key.keysym.sym == SDLK_s) new_pos.y += 1;
	else if (e.key.keysym.sym == SDLK_a) new_pos.x -= 1;
	else if (e.key.keysym.sym == SDLK_d) new_pos.x += 1;
	//TO_DO: Add collision checking on the new_pos
	player->pos = new_pos;
	
}

void
draw_player(Player* p)
{
	clear_player_fov();
	p->dest.x = p->pos.x * MAP_TILE_W;
	p->dest.y = p->pos.y * MAP_TILE_H;

	SDL_RenderCopy(renderer, tilesheet, &p->source, &p->dest);
}

void
update_player_fov(void)
{
	int i;

	get_matrix_three();
	for (i = 0; i < 9; i++) {
		if (player->matrix[i].y >= 0 && player->matrix[i].y < MAP_H && player->matrix[i].x >= 0 && player->matrix[i].x < MAP_W) {
			map[player->matrix[i].y][player->matrix[i].x].visible = true;
			map[player->matrix[i].y][player->matrix[i].x].seen = true;
		}
	}
}

void
clear_player_fov(void)
{
	int i;

	for (i = 0; i < 9; i++) {
		if (player->matrix[i].y >= 0 && player->matrix[i].y < MAP_H && player->matrix[i].x >= 0 && player->matrix[i].x < MAP_W) {
			map[player->matrix[i].y][player->matrix[i].x].visible = false;
		}
	}
}

void
get_matrix_three(void)
{
	player->matrix[0] = (SDL_Point) {.y = player->pos.y - 1, .x = player->pos.x - 1};
	player->matrix[1] = (SDL_Point) {.y = player->pos.y - 1, .x = player->pos.x};
	player->matrix[2] = (SDL_Point) {.y = player->pos.y - 1, .x = player->pos.x + 1};
	player->matrix[3] = (SDL_Point) {.y = player->pos.y, .x = player->pos.x - 1};
	player->matrix[4] = (SDL_Point) {.y = player->pos.y, .x = player->pos.x};
	player->matrix[5] = (SDL_Point) {.y = player->pos.y, .x = player->pos.x + 1};
	player->matrix[6] = (SDL_Point) {.y = player->pos.y + 1, .x = player->pos.x - 1};
	player->matrix[7] = (SDL_Point) {.y = player->pos.y + 1, .x = player->pos.x};
	player->matrix[8] = (SDL_Point) {.y = player->pos.y + 1, .x = player->pos.x + 1};
}

void
kill_player(Player* p)
{
	free(p);
	p = NULL;
	printf("Player free'd...\n");
}
