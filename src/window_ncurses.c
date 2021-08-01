/*******************************************************************************
*  
*  window_ncurses.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ncurses.h>
#include "window_ncurses.h"

struct Window {
	
	uint64_t id;
};

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool window_create(window_t** window)
{
	if (*window) {
		
		fprintf(stderr, "invalid handle!\n");
		return false;
	}
	
	*window = malloc(sizeof **window);
	if (!*window) {
		
		fprintf(stderr, "could not allocate memory for window!\n");
		return false;
	}
	
	if (!memset(*window, 0, sizeof **window)) {
		
		fprintf(stderr, "could not initialise memory for window!\n");
		return false;
	}
	
	initscr();
	cbreak();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	timeout(25);
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool window_delete(window_t** window)
{
	if (!*window) {
		
		fprintf(stderr, "invalid handle!\n");
		return false;
	}
	
	endwin();
	
	free(*window);
	*window = 0;
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool ncurses_render(bool(*engine_render)(void*), void* context)
{
	clear();
	engine_render(context);
	refresh();
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool ncurses_input(bool(*engine_input)(void*, int16_t), void* context)
{
	return engine_input(context, getch());
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool ncurses_draw(int16_t ch, int pox_x, int pos_y)
{
	move(pos_y, pox_x);
	addch(ch);
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool ncurses_string(int pox_x, int pos_y, char* string, int num_chars)
{
	mvaddnstr(pos_y, pox_x, string, num_chars);
	
	return true;
}

/*******************************************************************************
*  
*  END window_ncurses.c
*  
*******************************************************************************/
