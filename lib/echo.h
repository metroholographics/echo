#ifndef ECHO_H
#define ECHO_H
#include <stdlib.h>
#include <SDL.h>

#define SCREEN_W 960
#define SCREEN_H 540

#define TILE_W 8
#define TILE_H 12

#define MAP_W 80
#define MAP_H 27
#define MAP_TILE_W SCREEN_W / MAP_W
#define MAP_TILE_H SCREEN_H / MAP_H

typedef struct {
	SDL_Rect source;
	SDL_Point pos;
	SDL_Rect dest;
} Player;

extern	SDL_Window* window;
extern	SDL_Renderer* renderer;
extern	SDL_Texture* tilesheet;
extern	Player* player;

//main functions
int		init_context(void);
int		load_tilesheet(void);
void	quit_game(void);

//player.c functions
Player*	init_player(void);
void	draw_player(Player* p);
void	kill_player(Player* p);



#endif
