/*******************************************************************************
*  
*  engine.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include "engine.h"
#include "scene.h"

struct Engine {
	
	engine_params_t params;
	engine_metrics_t metrics;
	engine_state_t state;
	scene_t scene;
};

static bool process_faster_pipeline(engine_t*);
static bool process_stable_pipeline(engine_t*);

static bool _render_system(engine_t*);
static bool _input_system(engine_t*);
static bool _event_system(engine_t*);
static bool _physics_system(engine_t*);

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
engine_t* ngn(bool(*action)(engine_t**))
{
	static engine_t* instance;
	
	if (action ? !action(&instance) : false) {
		
		fprintf(stderr, "engine action failed!\n");
	}
	
	return instance;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool engine_create(engine_t** instance)
{
	if (*instance) {
		
		fprintf(stderr, "engine instance already exists!\n");
		return false;
	}
	
	*instance = malloc(sizeof **instance);
	if (!*instance) {
		
		fprintf(stderr, "could not allocate memory for engine!\n");
		return false;
	}
	
	if (!memset(*instance, 0, sizeof **instance)) {
		
		fprintf(stderr, "could not initialise memory for engine!\n");
		return false;
	}
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool engine_delete(engine_t** instance)
{
	if (!*instance) {
		
		fprintf(stderr, "engine instance is invalid!\n");
		return false;
	}
	
	if (!scene_delete(&(*instance)->scene)) {
		
		fprintf(stderr, "could not delete scene!\n");
		return false;
	}
	
	free(*instance);
	*instance = 0;
	
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
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool process_start(engine_t* engine)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	initscr();
	cbreak();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	timeout(0);
	
	if (!scene_init(&engine->scene)) {
		
		fprintf(stderr, "could not initialise scene!\n");
		return false;
	}
	
	engine->state.process_faster_pipeline = process_faster_pipeline;
	engine->state.process_stable_pipeline = process_stable_pipeline;
	
	engine->metrics.ticks_per_frame = ((float)CLOCKS_PER_SEC / engine->params.refresh_rate);
	
	bool active = true;
	while(active) {
		
		engine->metrics.ticks_s = engine->metrics.ticks_e;
		engine->metrics.ticks_e = clock();
		engine->metrics.ticks_d = engine->metrics.ticks_e - engine->metrics.ticks_s;
		
		if ((active = active && engine->state.process_faster_pipeline(engine))) {
			
			engine->metrics.ticks_since_frame += engine->metrics.ticks_d;
			
			if (engine->metrics.ticks_since_frame >= engine->metrics.ticks_per_frame) {
				
				engine->metrics.frames += 1;
				if (engine->metrics.frames >= engine->params.refresh_rate) {
					
					engine->metrics.frames = 0;
				}
				engine->metrics.ticks_since_frame = 0;
				
				active = active && engine->state.process_stable_pipeline(engine);
			}
		}
	}
	
	endwin();
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
static bool process_faster_pipeline(engine_t* engine)
{
	if (!_input_system(engine)) {
		
		fprintf(stderr, "error occured in input system\n");
		return false;
	}
	if (!_event_system(engine)) {
		
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
	if (!_physics_system(engine)) {
		
		fprintf(stderr, "error occured in physics system\n");
		return false;
	}
	if (!_render_system(engine)) {
		
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
static bool _render_system(engine_t* engine)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	clear();
	
	if (!scene_render(&engine->scene)) {
		
		fprintf(stderr, "could not render scene!\n");
		return false;
	}
	
	char str[50];
	
	sprintf(str, "metrics.ticks_s: %ld\n", engine->metrics.ticks_s);
	mvaddnstr(0, 0, str, 30);
	sprintf(str, "metrics.ticks_e: %ld\n", engine->metrics.ticks_e);
	mvaddnstr(1, 0, str, 30);
	sprintf(str, "metrics.ticks_d: %ld\n", engine->metrics.ticks_d);
	mvaddnstr(2, 0, str, 30);
	sprintf(str, "metrics.ticks_since_frame: %ld\n", engine->metrics.ticks_since_frame);
	mvaddnstr(3, 0, str, 30);
	sprintf(str, "metrics.frames: %d\n", engine->metrics.frames);
	mvaddnstr(4, 0, str, 30);
	
	refresh();
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
static bool _input_system(engine_t* engine)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	int16_t ch = getch();
	if (ch == -1) {
		
		return true;
	}
	
	if ((char)ch == 'q') {
		
		return false;
	}
	
	if (!scene_process_input(&engine->scene, ch)) {
		
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
static bool _event_system(engine_t* engine)
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
static bool _physics_system(engine_t* engine)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	return true;
}

/*******************************************************************************
*  
*  END engine.c
*  
*******************************************************************************/
