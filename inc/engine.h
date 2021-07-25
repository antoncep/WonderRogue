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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <ncurses.h>

#include "vector2d.h"
#include "utilities.h"

typedef char* str_t;

typedef struct Engine engine_t;

typedef struct EngineParams engine_params_t;
struct EngineParams {
	
	uint16_t window_width;
	uint16_t window_height;
	uint16_t refresh_rate;
};

typedef struct EngineMetrics engine_metrics_t;
struct EngineMetrics {
	
	clock_t ticks_s;
	clock_t ticks_e;
	clock_t ticks_d;
	clock_t ticks_since_frame;
	float ticks_per_frame;
	uint16_t frames;
};

typedef struct EngineState engine_state_t;
struct EngineState {
	
	bool (*process_faster_pipeline)(engine_t*);
	bool (*process_stable_pipeline)(engine_t*);
};

engine_t* ngn(bool(*)(engine_t**));
bool engine_create(engine_t**);
bool engine_delete(engine_t**);

bool engine_params_set(engine_t*, engine_params_t*);
bool process_start(engine_t*);

/*******************************************************************************
*  
*  END engine.h
*  
*******************************************************************************/
#endif // _ENGINE_H_
