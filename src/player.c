#include <echo.h>

#define MAX_RADIUS 12

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
move_player(SDL_Event e, Tile** m)
{
	SDL_Point new_pos = player->pos;

	bool shift_down = SDL_GetModState() & KMOD_SHIFT;

	if (e.key.keysym.sym == SDLK_w) {
		if (shift_down) new_pos.x -= 1;
 		new_pos.y -= 1;
	}
	else if (e.key.keysym.sym == SDLK_s) {
		if (shift_down) new_pos.x += 1;
		new_pos.y += 1;
	}
	else if (e.key.keysym.sym == SDLK_a) {
		if (shift_down) new_pos.y += 1;
		new_pos.x -= 1;
	}
	else if (e.key.keysym.sym == SDLK_d) {
		if (shift_down) new_pos.y -= 1;
		new_pos.x += 1;
	}

	//TO_DO: Add collision checking on the new_pos
	if (in_map(new_pos.x, new_pos.y) && m[new_pos.y][new_pos.x].walkable) {
		player->pos = new_pos;
	}
	update_player_fov(m);
	
}

void
draw_player(Player* p)
{
	p->dest.x = p->pos.x * MAP_TILE_W;
	p->dest.y = p->pos.y * MAP_TILE_H;

	SDL_RenderCopy(renderer, tilesheet, &p->source, &p->dest);
}


//TO_DO: CHANGE ALL LINES MODIFYING MAP INTO MAP FUNCTIONS
void
update_player_fov(Tile** m)
{
	int dist_sq, min_x, min_y, max_x, max_y, px = player->pos.x, py = player->pos.y, y, x;
	int radius_sq = MAX_RADIUS * MAX_RADIUS;

	//clear FOV
	for (y = 0; y < MAP_H; y++) {
		for (x = 0; x < MAP_W; x++) {
			m[y][x].visible = false;
		}
	}

	min_x = (px - MAX_RADIUS) < 0 ? 0 : px - MAX_RADIUS;
	max_x = (px + MAX_RADIUS) >= MAP_W ? MAP_W - 1 : px + MAX_RADIUS;
	min_y = (py - MAX_RADIUS) < 0 ? 0 : py - MAX_RADIUS;
	max_y = (py + MAX_RADIUS) >= MAP_H ? MAP_H - 1 : py + MAX_RADIUS;

	m[py][px].visible = true;

	for (y = min_y; y <= max_y; y++) {
		for (x = min_x; x <= max_x; x++) {
			dist_sq = get_distance_sq(px, py, x, y);
			if (dist_sq <= radius_sq) {
				if (has_los(m, px, py, x, y)) {
					m[y][x].visible = true;
					m[y][x].seen = true;
				}
			}
		}
	}
}

bool
has_los(Tile** m, int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int x = x1;
	int y = y1;

	int sx = x1 < x2 ? 1 : -1;
	int sy = y1 < y2 ? 1 : -1;
	int err = dx - dy;

	while (x != x2 || y != y2) {
		if (x != x2 || y != y2) {
			if (x < 0 || x >= MAP_W || y < 0 || y >= MAP_H) return false;
			if (m[y][x].blocks_light) return false;
		}

		int e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x += sx;
		}
		if (e2 < dx) {
			err += dx;
			y += sy;
		}
	}
	return true;
}


void
kill_player(Player* p)
{
	free(p);
	p = NULL;
	printf("Player free'd...\n");
}
