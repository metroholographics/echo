#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <echo.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* tilesheet = NULL;
Player* player = NULL;
Tile tile_list[MAX_TILES];
Tile** map = NULL;

int
main(int argc, char* argv[])
{
	srand(time(NULL));
	bool running;
	SDL_Event e;

	if (init_context() != 0) return 1;
	if (load_tilesheet() != 0) return 1;

	player = init_player();

	init_tiles(tile_list);
	for (int i = 0; i < MAX_TILES; i++) {
		printf("tile %d loaded\n", tile_list[i].t_type);
	}

	map = generate_map();
	if (map != NULL) printf("Map gen successful\n");
	else return 1;

	running = true;
    while (running)
    {
    	SDL_SetRenderDrawColor(renderer, 21, 19, 19, 255);
    	SDL_RenderClear(renderer);

        while (SDL_PollEvent(&e) != 0)
        {
        	switch (e.type) {
        		case SDL_QUIT:
        			running = false;
        			break;
        		case SDL_KEYDOWN:
        			if (e.key.keysym.sym == SDLK_w) player->pos.y -= 1;
        			else if (e.key.keysym.sym == SDLK_s) player->pos.y += 1;
        			else if (e.key.keysym.sym == SDLK_a) player->pos.x -= 1;
        			else if (e.key.keysym.sym == SDLK_d) player->pos.x += 1;
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
    SDL_RenderSetIntegerScale(renderer, true);
    return 0;
}

int
load_tilesheet(void) {
	tilesheet = IMG_LoadTexture(renderer, "./assets/tilesheet.png");
	if (tilesheet == NULL) {
		printf("error loading tilesheet: %s\n", SDL_GetError());
		quit_game();
		return 1;
	}
	return 0;
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


