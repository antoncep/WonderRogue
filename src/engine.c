/*******************************************************************************
*  
*  engine.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <malloc.h>
#include <ncurses.h>
#include "engine.h"

static bool render_screen(engine_struct *);
static char handle_input(engine_struct *);
static bool new_game(engine_struct *, char *, char *);

/*******************************************************************************
*  
*  initialize engine and return engine_struct *
*  
*******************************************************************************/
engine_struct *init_engine(void)
{
	engine_struct *engine = NULL;
	
	engine = (engine_struct *)malloc(sizeof(engine_struct));
	if (!engine) {
		
		printf("could not allocate memory for engine!\n");
		return NULL;
	}
	
	engine->dungeon = NULL;
	engine->player  = NULL;
	
	engine->render_screen = render_screen;
	engine->handle_input  = handle_input;
	engine->new_game      = new_game;
	
	initscr();
	cbreak();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	
	return engine;
}

/*******************************************************************************
*  
*  take engine_struct * and free memory for members and self
*  
*******************************************************************************/
bool stop_engine(engine_struct *engine)
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
*  take engine_struct * and render chars to ncurses screen
*  
*******************************************************************************/
static bool render_screen(engine_struct *engine)
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
*  take engine_struct * and wait for key input and decide how to handle input
*  
*******************************************************************************/
static char handle_input(engine_struct *engine)
{
	if (!engine) {
		
		printf("invalid engine!\n");
		return '\0';
	}
	
	return (char)getch();
}

/*******************************************************************************
*  
*  take engine_struct * and initialize new dungeon for gameplay
*  
*******************************************************************************/
static bool new_game(engine_struct *engine, char *dungeon_name, char *player_name)
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
	engine->player = create_player(player_name, (vector2d_struct){ 0.0, 0.0 });
	if (!engine->player) {
		
		printf("could not create player!\n");
		return false;
	}
	
	return true;
}

/*******************************************************************************
*  
*  END engine.c
*  
*******************************************************************************/
