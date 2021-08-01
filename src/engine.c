/*******************************************************************************
*  
*  engine.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "stopwatch.h"
#include "window_ncurses.h"
#include "scene.h"
#include "engine.h"

struct Engine {
	
	stopwatch_t* stopwatch;
	window_t* window;
	scene_t* root_scene;
	engine_params_t params;
	engine_state_t state;
	engine_metrics_t metrics;
};

static bool process_faster_pipeline(engine_t*);
static bool process_stable_pipeline(engine_t*);

static bool engine_input_system(void*, int16_t);
static bool engine_event_system(void*);
static bool engine_physics_system(void*);
static bool engine_render_system(void*);

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool engine_create(engine_t** engine)
{
	if (*engine) {
		
		fprintf(stderr, "invalid handle!\n");
		return false;
	}
	
	*engine = malloc(sizeof **engine);
	if (!*engine) {
		
		fprintf(stderr, "could not allocate memory for engine!\n");
		return false;
	}
	
	if (!memset(*engine, 0, sizeof **engine)) {
		
		fprintf(stderr, "could not initialise memory for engine!\n");
		return false;
	}
	
	if (!stopwatch_create(&(*engine)->stopwatch)) {
		
		fprintf(stderr, "could not create stopwatch!\n");
		return false;
	}
	
	if (!window_create(&(*engine)->window)) {
		
		fprintf(stderr, "could not create window!\n");
		return false;
	}
	
	if (!scene_create(&(*engine)->root_scene)) {
		
		fprintf(stderr, "could not create scene!\n");
		return false;
	}
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool engine_delete(engine_t** engine)
{
	if (!*engine) {
		
		fprintf(stderr, "invalid handle!\n");
		return false;
	}
	
	if ((*engine)->root_scene && !scene_delete(&(*engine)->root_scene)) {
		
		fprintf(stderr, "could not delete scene!\n");
		return false;
	}
	
	if ((*engine)->window && !window_delete(&(*engine)->window)) {
		
		fprintf(stderr, "could not delete window!\n");
		return false;
	}
	
	if ((*engine)->stopwatch && !stopwatch_delete(&(*engine)->stopwatch)) {
		
		fprintf(stderr, "could not delete stopwatch!\n");
		return false;
	}
	
	free(*engine);
	*engine = 0;
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool engine_params_set(engine_t* engine, engine_params_t* engine_params)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	memcpy(&engine->params, engine_params, sizeof engine->params);
	
	fprintf(stderr, "window: %dx%d\n",
		engine->params.window_width,
		engine->params.window_height);
	
	if (!scene_init(engine->root_scene)) {
		
		fprintf(stderr, "could not initialise scene!\n");
		return false;
	}
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool engine_state_loop(engine_t* engine)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	engine->metrics.ticks_per_second = NANOSECS_PER_SECOND;
	engine->metrics.ticks_per_frame = engine->metrics.ticks_per_second / engine->params.refresh_rate;
	
	stopwatch_start(engine->stopwatch);
	while (stopwatch_stamp(engine->stopwatch)) {
		
		if (!process_faster_pipeline(engine)) {
			
			fprintf(stderr, "faster pipeline break!\n");
			break;
		}
		
		engine->metrics.ticks_since_frame += stopwatch_delta(engine->stopwatch);
		if (engine->metrics.ticks_since_frame >= engine->metrics.ticks_per_frame) {
			
			engine->metrics.total_frames += 1;
			engine->metrics.ticks_since_frame = engine->metrics.ticks_since_frame % engine->metrics.ticks_per_frame;
			
			if (!process_stable_pipeline(engine)) {
				
				fprintf(stderr, "stable pipeline break!\n");
				break;
			}
		}
		
		engine->metrics.ticks_since_second += stopwatch_delta(engine->stopwatch);
		if (engine->metrics.ticks_since_second >= engine->metrics.ticks_per_second) {
			
			engine->metrics.total_seconds += engine->metrics.ticks_since_second / engine->metrics.ticks_per_second;
			engine->metrics.ticks_since_second = engine->metrics.ticks_since_second % engine->metrics.ticks_per_second;
			
			engine->metrics.frames_per_second = engine->metrics.total_frames;
			engine->metrics.total_frames = 0;
		}
	}
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
static bool process_faster_pipeline(engine_t* engine)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	if (!ncurses_input(engine_input_system, engine)) {
		
		fprintf(stderr, "error occured in input system\n");
		return false;
	}
	
	if (!engine_event_system(engine)) {
		
		fprintf(stderr, "error occured in event system\n");
		return false;
	}
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
static bool process_stable_pipeline(engine_t* engine)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	if (!engine_physics_system(engine)) {
		
		fprintf(stderr, "error occured in physics system\n");
		return false;
	}
	
	if (!ncurses_render(engine_render_system, engine)) {
		
		fprintf(stderr, "error occured in render system\n");
		return false;
	}
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
static bool engine_input_system(void* engine, int16_t ch)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	if (ch == -1) {
		
		return true;
	}
	
	if ((char)ch == 'q') {
		
		return false;
	}
	
	if (!scene_input(((engine_t*)engine)->root_scene, ch)) {
		
		fprintf(stderr, "scene input error!\n");
		return false;
	}
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
static bool engine_event_system(void* engine)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
static bool engine_physics_system(void* engine)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
static bool engine_render_system(void* engine)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	if (!scene_render(((engine_t*)engine)->root_scene, ncurses_draw)) {
		
		fprintf(stderr, "could not render scene!\n");
		return false;
	}
	
	char str[50];
	
	sprintf(str, "metrics.ticks_since_frame: %ld\n", ((engine_t*)engine)->metrics.ticks_since_frame);
	ncurses_string(0, 0, str, 50);
	sprintf(str, "metrics.total_seconds: %ld\n", ((engine_t*)engine)->metrics.total_seconds);
	ncurses_string(0, 1, str, 50);
	sprintf(str, "metrics.total_frames: %ld\n", ((engine_t*)engine)->metrics.total_frames);
	ncurses_string(0, 2, str, 50);
	sprintf(str, "metrics.frames_per_second: %ld\n", ((engine_t*)engine)->metrics.frames_per_second);
	ncurses_string(0, 3, str, 50);
	
	return true;
}

/*******************************************************************************
*  
*  END engine.c
*  
*******************************************************************************/
