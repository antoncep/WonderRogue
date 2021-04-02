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

static void render_screen(engine_struct *);
static char handle_input(engine_struct *);
static void new_game(engine_struct *);

/*******************************************************************************
*  
*  initialize engine and return pointer to engine_struct
*  
*******************************************************************************/
engine_struct *init_engine(void)
{
	engine_struct *engine = NULL;
	
	engine = (engine_struct *)malloc(sizeof(engine_struct));
	if (!engine)
		return NULL;
	
	engine->dungeon = NULL;
	
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
*  receive pointer to engine_struct and free memory for member and self
*  
*******************************************************************************/
int stop_engine(engine_struct *engine)
{
	if (!engine) return -1;
	
	endwin();
	
	if (engine->dungeon)
		delete_dungeon(engine->dungeon);
	
	free(engine);
	
	return 0;
}

/*******************************************************************************
*  
*  render chars to ncurses screen
*  
*******************************************************************************/
static void render_screen(engine_struct *engine)
{
	if (!engine) return;
	if (!engine->dungeon) return;
	
	clear();
	
	for (uint32_t map_y = 0; map_y < LINES; map_y++) {
		move(map_y, 0);
		for (uint32_t map_x = 0; map_x < COLS; map_x++) {
			addch((*engine->dungeon->zlevels[0]).tiles[(map_y * COLS) + map_x].symbol);
		}
	}
	
	refresh();
	
	return;
}

/*******************************************************************************
*  
*  wait for key input and decide how to handle input
*  
*******************************************************************************/
static char handle_input(engine_struct *engine)
{
	if (!engine) return '\0';
	
	char out = (char)getch();
	
	return out;
}

/*******************************************************************************
*  
*  initialize new dungeon for gameplay
*  
*******************************************************************************/
static void new_game(engine_struct *engine)
{
	if (!engine) return;
	
	if (engine->dungeon)
		delete_dungeon(engine->dungeon);
	
	engine->dungeon = create_dungeon(1, 350, 350);
	if (!engine->dungeon)
		stop_engine(engine);
	
	return;
}

/*******************************************************************************
*  
*  END engine.c
*  
*******************************************************************************/
