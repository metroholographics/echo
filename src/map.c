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
		} else if (i == T_T_DIRT) {
			arr[i] = (Tile) {
				.t_type = T_T_DIRT,
				.walkable = true,
				.source = (SDL_Rect) {
					.x = 32,
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
					.x = 48,
					.y = 0,
					.w = TILE_W,
					.h = TILE_H
				}
			}; 
		} else if (i == T_T_TREE) {
			arr[i] = (Tile) {
				.t_type = T_T_TREE,
				.walkable = false,
				.source = (SDL_Rect) {
					.x = 64,
					.y = 0,
					.w = TILE_W,
					.h = TILE_H
				}
			}; 
		} else if (i == T_T_WATER) {
			arr[i] = (Tile) {
				.t_type = T_T_TREE,
				.walkable = false,
				.source = (SDL_Rect) {
					.x = 80,
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
			m[y][x] = *(get_rand_tile());//tile_list[T_T_GROUND];
		}
	}
	
	gen_forest(m); 
	return m; 
}

void
gen_forest(Tile** m)
{

	int c_x, c_y, chance, i, num_trees, rand_x, rand_y, y, x; 

	num_trees = (rand() % 10) + 10;

	for (i = 0; i < num_trees; i++) {
		rand_y = rand() % MAP_H;
		rand_x = rand() % MAP_W;
		m[rand_y][rand_x] = tile_list[T_T_TREE];
	} /*TODO: Store these positions in an array to jump to them below?*/

	/* TODO: loop to the exact point of the trees placed and generate 'forest', instead of looping*/
	for (y = 0; y < MAP_H; y++) {
		for (x = 0; x < MAP_W; x++) {
			if (m[y][x].t_type == T_T_TREE) {
				for (c_y = -1; c_y < 2; c_y++) {
					for (c_x = -1; c_x < 2; c_x++) {
						chance = rand() % 100;
						if (y + c_y > 0 && y + c_y < MAP_H && x + c_x > 0 && x + c_x < MAP_W) {
							if (chance <= 40) m[y + c_y][x + c_x] = tile_list[T_T_TREE];
							else m[y + c_y][x + c_x] = tile_list[T_T_GRASS];
						}
					}
				}
			} 
		}
	}
}

Tile*
get_rand_tile(void)
{
	int r;
	Tile* t;

	r = rand() % 100;
	if (r < 15) {
		t = &tile_list[T_T_DIRT];
	}
	else t = &tile_list[T_T_GROUND];

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

