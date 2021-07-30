/*******************************************************************************
*  
*  engine.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include "stopwatch.h"
#include "scene.h"
#include "engine.h"

struct Engine {
	
	stopwatch_t* stopwatch;
	engine_metrics_t metrics;
	engine_params_t params;
	engine_state_t state;
	scene_t* scene;
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
bool engine_create(engine_t** engine)
{
	if (*engine) {
		
		fprintf(stderr, "invalid handle!\n");
		return 0;
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
	
	if (!scene_create(&(*engine)->scene)) {
		
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
		return 0;
	}
	
	if ((*engine)->scene && !scene_delete(&(*engine)->scene)) {
		
		fprintf(stderr, "could not delete scene!\n");
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
	
	initscr();
	cbreak();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	timeout(25);
	
	if (!scene_init(engine->scene)) {
		
		fprintf(stderr, "could not initialise scene!\n");
		return false;
	}
	
	engine->state.process_faster_pipeline = process_faster_pipeline;
	engine->state.process_stable_pipeline = process_stable_pipeline;
	
	engine->metrics.ticks_per_second = NANOSECS_IN_SECOND;
	engine->metrics.ticks_per_frame = engine->metrics.ticks_per_second / engine->params.refresh_rate;
	
	stopwatch_start(engine->stopwatch);
	while (stopwatch_stamp(engine->stopwatch)) {
		
		if (!engine->state.process_faster_pipeline(engine)) {
			
			fprintf(stderr, "faster pipeline break!\n");
			break;
		}
		
		engine->metrics.ticks_since_frame += stopwatch_delta(engine->stopwatch);
		if (engine->metrics.ticks_since_frame >= engine->metrics.ticks_per_frame) {
			
			engine->metrics.total_frames += 1;
			engine->metrics.ticks_since_frame = engine->metrics.ticks_since_frame % engine->metrics.ticks_per_frame;
			
			if (!engine->state.process_stable_pipeline(engine)) {
				
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
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
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
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
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
	
	if (!scene_render(engine->scene)) {
		
		fprintf(stderr, "could not render scene!\n");
		return false;
	}
	
	char str[50];
	
	sprintf(str, "metrics.ticks_since_frame: %ld\n", engine->metrics.ticks_since_frame);
	mvaddnstr(0, 0, str, 50);
	sprintf(str, "metrics.total_seconds: %ld\n", engine->metrics.total_seconds);
	mvaddnstr(1, 0, str, 50);
	sprintf(str, "metrics.total_frames: %ld\n", engine->metrics.total_frames);
	mvaddnstr(2, 0, str, 50);
	sprintf(str, "metrics.frames_per_second: %ld\n", engine->metrics.frames_per_second);
	mvaddnstr(3, 0, str, 50);
	
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
	
	if (!scene_process_input(engine->scene, ch)) {
		
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
