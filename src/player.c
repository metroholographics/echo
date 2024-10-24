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
draw_player(Player* p)
{
	p->dest.x = p->pos.x * MAP_TILE_W;
	p->dest.y = p->pos.y * MAP_TILE_H;

	SDL_RenderCopy(renderer, tilesheet, &p->source, &p->dest);
}


void
kill_player(Player* p)
{
	free(p);
	p = NULL;
	printf("Player free'd...\n");
}
