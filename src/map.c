#include <echo.h>

void
init_tiles(Tile arr[])
{
	int i;
	printf("%d max ground tiles\n", MAX_TILES);
	for (i = 0; i < MAX_TILES; i++) {
		if (i == T_T_GROUND) {
			arr[i] = (Tile) {
				.t_type = T_T_GROUND,
				.walkable = true,
				.source = (SDL_Rect) {
					.x = 16,
					.y = 0,
					.w = TILE_W,
					.h = TILE_H
				}
			}; 
		} else if (i == T_T_GRASS) {
			arr[i] = (Tile) {
				.t_type = T_T_GRASS,
				.walkable = true,
				.source = (SDL_Rect) {
					.x = 32,
					.y = 0,
					.w = TILE_W,
					.h = TILE_H
				}
			}; 
		}
	}
}


Tile**
generate_map(void)
{
	int y, x;
	Tile** m = calloc(MAP_H, sizeof(Tile*));
	if (m == NULL) {
		printf("Map could not be initialised\n");
		return m;
	}

	for (y = 0; y < MAP_H; y++) {
		m[y] = calloc(MAP_W, sizeof(Tile));
		if (m[y] == NULL) {
			printf("Map could not be initialised\n");
			return m;
		}
		for (x = 0; x < MAP_W; x++) {
			Tile t = *(get_rand_tile());
			m[y][x] = t;
		}
	}

	return m; 
}

Tile*
get_rand_tile(void)
{
	int r;
	Tile* t;

	r = rand() % 10;

	if (r < 8) {
		t = &tile_list[T_T_GROUND];
	} else {
		t = &tile_list[T_T_GRASS];
	}
	return t;
}

void
draw_map(Tile** m)
{
	int y, x;
	SDL_Rect dest;
	for (y = 0; y < MAP_H; y++) {
		dest.y = y * MAP_TILE_H;
		dest.w = MAP_TILE_W;
		dest.h = MAP_TILE_H;
		for (x = 0; x < MAP_W; x++) {
			dest.x = x * MAP_TILE_W;
			SDL_RenderCopy(renderer, tilesheet, &m[y][x].source, &dest);
		}
	}
}

void
kill_map(Tile** m)
{
	int y;
	for (y = 0; y < MAP_H; y++) {
		free(m[y]);
		m[y] = NULL;
	}
	free(m);
	m = NULL;
	printf("Map free'd...\n");
}

