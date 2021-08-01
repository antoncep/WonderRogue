#ifndef _WINDOW_NCURSES_H_
#define _WINDOW_NCURSES_H_
/*******************************************************************************
*  
*  window_ncurses.h
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

typedef struct Window window_t;

bool window_create(window_t**);
bool window_delete(window_t**);

bool ncurses_render(bool(*)(void*), void*);
bool ncurses_input(bool(*)(void*,int16_t), void*);
bool ncurses_draw(int16_t, int, int);
bool ncurses_string(int, int, char*, int);

/*******************************************************************************
*  
*  END window_ncurses.h
*  
*******************************************************************************/
#endif // _WINDOW_NCURSES_H_
