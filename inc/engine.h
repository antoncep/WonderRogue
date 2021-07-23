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

typedef struct Engine engine_t;
typedef struct EngineParams engine_params_t;
struct EngineParams {
	
	int window_width;
	int window_height;
};

typedef void* engine_command_data_t;
typedef bool (*engine_command_f)(engine_t*, engine_command_data_t);

bool engine(engine_command_f, engine_command_data_t);
bool engine_set_parameters(engine_t*, engine_command_data_t);
bool engine_run_loop(engine_t*, engine_command_data_t);

/*******************************************************************************
*  
*  END engine.h
*  
*******************************************************************************/
#endif // _ENGINE_H_
