#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <echo.h>
#include <math.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* tilesheet = NULL;
Player* player = NULL;
Tile tile_list[MAX_TILES];
Tile** map = NULL;
char* sheet = "./assets/16x16.png";

int
main(int argc, char* argv[])
{
	srand(time(NULL));

	bool running = true;
	int i;
	SDL_Event e;

	if (init_context() != 0) return 1;
	if (load_tilesheet() != 0) return 1;

	player = init_player();

	init_tiles(tile_list);
	for (i = 0; i < MAX_TILES; i++) {
		printf("tile %d loaded\n", tile_list[i].t_type);
	}

	map = generate_map();
	if (map != NULL) printf("Map gen successful\n");
	else return 1;

	update_player_fov(map);

    while (running)
    {
    	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    	SDL_RenderClear(renderer);

        while (SDL_PollEvent(&e) != 0)
        {
        	switch (e.type) {
        		case SDL_QUIT:
        			running = false;
        			break;
        		case SDL_KEYDOWN:
        			move_player(e, map);
        			break;
        	}
        }

        draw_map(map);

		draw_player(player);

		SDL_RenderPresent(renderer);
     }

    quit_game();
}

int
init_context(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow(
    	"echo",
    	SDL_WINDOWPOS_CENTERED,
    	SDL_WINDOWPOS_CENTERED,
    	SCREEN_W, SCREEN_H, 0
    );

    if (!window)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
    	printf("error creating renderer: %s\n", SDL_GetError());
        quit_game();
        return 1;
    }

    return 0;
}

int
load_tilesheet(void) {
	tilesheet = IMG_LoadTexture(renderer, sheet);
	if (tilesheet == NULL) {
		printf("error loading tilesheet: %s\n", SDL_GetError());
		quit_game();
		return 1;
	}
	//SDL_SetTextureScaleMode(tilesheet, SDL_ScaleModeBest);
	return 0;
}

//TO_DO: MOVE THIS TO A TOOLS.C FILE
int
get_distance_sq(int x1, int y1, int x2, int y2)
{
	int dx, dy;

	dx = x2 - x1;
	dy = y2 - y1;

	return dx * dx + dy * dy;
}

void
quit_game(void)
{
	printf("---QUITTING---\n");
	kill_player(player);
	kill_map(map);
	SDL_DestroyTexture(tilesheet);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();
}


