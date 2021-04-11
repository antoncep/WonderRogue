#ifndef _ENGINE_H_
#define _ENGINE_H_
/*******************************************************************************
*  
*  engine.h
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <ncurses.h>

#include "vector2d.h"
#include "utilities.h"

typedef char * str_t;

typedef struct Dungeon dungeon_t;
typedef struct Player player_t;

typedef struct Engine engine_t;
struct Engine {
	
	dungeon_t *dungeon;
	player_t *player;
	
	bool (*init_game)(engine_t *, str_t, str_t);
	bool (*render_screen)(engine_t *);
	char (*handle_input)(engine_t *);
	
};

engine_t *create_engine(void);
bool destruct_engine(engine_t *);

/*******************************************************************************
*  
*  END engine.h
*  
*******************************************************************************/
#endif // _ENGINE_H_
