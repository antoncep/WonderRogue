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

typedef char* str_t;

typedef struct EngineParams engine_params_t;
struct EngineParams {
	
	int window_width;
	int window_height;
};

typedef struct Engine engine_t;

engine_t* ngn(bool(*)(engine_t**));
bool engine_create(engine_t**);
bool engine_delete(engine_t**);

bool engine_params_set(engine_t*, engine_params_t*);
bool engine_run_state_cycle(engine_t*);

/*******************************************************************************
*  
*  END engine.h
*  
*******************************************************************************/
#endif // _ENGINE_H_
