/*******************************************************************************
*  
*  engine.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include "engine.h"
#include "dungeon.h"
#include "player.h"

static bool init_game(engine_t *, str_t, str_t);
static bool render_screen(engine_t *);
static char handle_input(engine_t *);

/*******************************************************************************
*  
*  initialize engine and return engine_t *
*  
*******************************************************************************/
engine_t *create_engine(void)
{
	engine_t *engine = NULL;
	
	engine = (engine_t *)malloc(sizeof(engine_t));
	if (!engine) {
		
		printf("could not allocate memory for engine!\n");
		return NULL;
	}
	
	engine->dungeon = NULL;
	engine->player  = NULL;
	
	engine->init_game     = init_game;
	engine->render_screen = render_screen;
	engine->handle_input  = handle_input;
	
	initscr();
	cbreak();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	
	return engine;
}

/*******************************************************************************
*  
*  take engine_t * and free memory for members and self
*  
*******************************************************************************/
bool destruct_engine(engine_t *engine)
{
	if (!engine) {
		
		printf("invalid engine!\n");
		return false;
	}
	
	endwin();
	
	if (engine->dungeon && !destruct_dungeon(engine->dungeon)) {
		
		printf("could not destruct dungeon!\n");
		return false;
	}
	engine->dungeon = NULL;
	
	if (engine->player && !destruct_player(engine->player)) {
		
		printf("could not destruct player!\n");
		return false;
	}
	engine->player = NULL;
	
	free(engine);
	engine = NULL;
	
	return true;
}

/*******************************************************************************
*  
*  take engine_t * and initialize new dungeon for gameplay
*  
*******************************************************************************/
static bool init_game(engine_t *engine, str_t dungeon_name, str_t player_name)
{
	if (!engine) {
		
		printf("invalid engine!\n");
		return false;
	}
	
	if (engine->dungeon && !destruct_dungeon(engine->dungeon)) {
		
		printf("could not destruct dungeon!\n");
		return false;
	}
	engine->dungeon = create_dungeon(dungeon_name, 1, 350, 350);
	if (!engine->dungeon) {
		
		printf("could not create dungeon!\n");
		return false;
	}
	
	if (engine->player && !destruct_player(engine->player)) {
		
		printf("could not destruct player!\n");
		return false;
	}
	engine->player = create_player(player_name, (vec2d_t){ 0.0, 0.0 });
	if (!engine->player) {
		
		printf("could not create player!\n");
		return false;
	}
	
	return true;
}

/*******************************************************************************
*  
*  take engine_t * and render chars to ncurses screen
*  
*******************************************************************************/
static bool render_screen(engine_t *engine)
{
	if (!engine) {
		
		printf("invalid engine!\n");
		return false;
	}
	if (!engine->dungeon) {
		
		printf("invalid dungeon!\n");
		return false;
	}
	if (!engine->player) {
		
		printf("invalid player!\n");
		return false;
	}
	
	clear();
	
	for (int32_t map_y = 0; map_y < LINES; map_y++) {
		move(map_y, 0);
		for (int32_t map_x = 0; map_x < COLS; map_x++) {
			addch((*engine->dungeon->zlevels[0]).tiles[(map_y * COLS) + map_x].symbol);
		}
	}
	
	move(engine->player->position.y, engine->player->position.x);
	addch(engine->player->symbol);
	
	refresh();
	
	return true;
}

/*******************************************************************************
*  
*  take engine_t * and wait for key input and decide how to handle input
*  
*******************************************************************************/
static char handle_input(engine_t *engine)
{
	if (!engine) {
		
		printf("invalid engine!\n");
		return '\0';
	}
	if (!engine->dungeon) {
		
		printf("invalid dungeon!\n");
		return '\0';
	}
	if (!engine->player) {
		
		printf("invalid player!\n");
		return '\0';
	}
	
	int16_t ch = getch();
	
	switch (ch) {
		
		case KEY_UP:
			engine->player->move_toward(engine->player, (vec2d_t){ 0.0, -1.0 });
			break;
		
		case KEY_DOWN:
			engine->player->move_toward(engine->player, (vec2d_t){ 0.0, 1.0 });
			break;
		
		case KEY_LEFT:
			engine->player->move_toward(engine->player, (vec2d_t){ -1.0, 0.0 });
			break;
		
		case KEY_RIGHT:
			engine->player->move_toward(engine->player, (vec2d_t){ 1.0, 0.0 });
			break;
		
		default:
			printf("unhandled input!\n");
	}
	
	return (char)ch;
}

/*******************************************************************************
*  
*  END engine.c
*  
*******************************************************************************/
