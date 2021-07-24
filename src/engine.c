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
	scene_t scene;
};

static bool initialise(engine_t*);
static bool processing(engine_t*);

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
bool engine_run_state_cycle(engine_t* engine)
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
	
	if (!initialise(engine)) {
		
		fprintf(stderr, "could not initialise engine!\n");
		return 1;
	}
	while(processing(engine));
	
	endwin();
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
static bool initialise(engine_t* engine)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	if (!scene_init(&engine->scene)) {
		
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
static bool processing(engine_t* engine)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	if (!_render_system(engine)) {
		
		fprintf(stderr, "error occured in render system\n");
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
	if (!_physics_system(engine)) {
		
		fprintf(stderr, "error occured in physics system\n");
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
