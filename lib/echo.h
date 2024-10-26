#ifndef ECHO_H
#define ECHO_H

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

#define SCREEN_W 1024 //960
#define SCREEN_H 576 //540

#define TILE_W 16
#define TILE_H 24

#define MAP_W 80
#define MAP_H 26
#define MAP_TILE_W SCREEN_W / MAP_W
#define MAP_TILE_H SCREEN_H / MAP_H

typedef enum {
	T_T_GROUND = 0,
	T_T_DIRT,
	T_T_GRASS,
	T_T_TREE,
	T_T_WATER,
	MAX_TILES
} Tile_Type;

typedef struct {
	Tile_Type t_type;
	bool walkable;
	SDL_Rect source;
	bool visible;
	bool seen;
} Tile;

typedef struct {
	SDL_Rect source;
	SDL_Point pos;
	SDL_Rect dest;
} Player;

extern	SDL_Window* window;
extern	SDL_Renderer* renderer;
extern	SDL_Texture* tilesheet;
extern	Player* player;
extern	Tile tile_list[MAX_TILES];
extern	Tile** map;

//main functions
int		init_context(void);
int		load_tilesheet(void);
void	quit_game(void);

//player.c functions
Player*	init_player(void);
void	draw_player(Player* p);
void	kill_player(Player* p);

//map.c functions
void	init_tiles(Tile arr[]);
Tile**	generate_map(void);
Tile*	get_rand_tile(void);
void	gen_forest(Tile** m);
void	draw_map(Tile** m);
void	kill_map(Tile** m);


#endif
