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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ncurses.h>

typedef struct EngineParams engine_params_t;
struct EngineParams {
	
	uint16_t window_width;
	uint16_t window_height;
	uint16_t refresh_rate;
	uint16_t padding;
};

typedef struct EngineMetrics engine_metrics_t;
struct EngineMetrics {
	
	uint64_t ticks_per_second;
	uint64_t ticks_per_frame;
	uint64_t ticks_since_second;
	uint64_t ticks_since_frame;
	uint64_t total_seconds;
	uint64_t total_frames;
	uint64_t frames_per_second;
};

typedef struct Engine engine_t;

typedef struct EngineState engine_state_t;
struct EngineState {
	
	bool (*process_faster_pipeline)(engine_t*);
	bool (*process_stable_pipeline)(engine_t*);
};

bool engine_create(engine_t**);
bool engine_delete(engine_t**);

bool engine_params_set(engine_t*, engine_params_t*);
bool engine_state_loop(engine_t*);

/*******************************************************************************
*  
*  END engine.h
*  
*******************************************************************************/
#endif // _ENGINE_H_
