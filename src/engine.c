/*******************************************************************************
*  
*  engine.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include "engine.h"
#include "dungeon.h"
#include "player.h"

struct Engine {
	
	dungeon_t* dungeon;
	player_t* player;
};

static engine_t* engine_instance(void);
static bool engine_init(engine_t**);
static bool engine_stop(engine_t**);

static bool initialise(engine_t*);
static bool processing(engine_t*);

static bool _render_system(engine_t*);
static bool _input_system(engine_t*);
static bool _event_system(engine_t*);
static bool _physics_system(engine_t*);

static bool _init_game(engine_t*, str_t, str_t);

/*******************************************************************************
*  
*  
*  
*******************************************************************************/
bool engine(engine_command_f command, engine_command_data_t data)
{
	return command(engine_instance(), data);
}

/*******************************************************************************
*  
*  
*  
*******************************************************************************/
bool engine_set_parameters(engine_t* engine, engine_command_data_t data)
{
	engine_params_t* engine_params = data;
	
	fprintf(stderr, "window: %dx%d\n",
		engine_params->window_width,
		engine_params->window_height);
	
	return true;
}

/*******************************************************************************
*  
*  
*  
*******************************************************************************/
bool engine_run_loop(engine_t* engine, engine_command_data_t data)
{
	if (!initialise(engine)) {
		
		fprintf(stderr, "could not initialise engine!\n");
		return 1;
	}
	while(processing(engine));
	
	return true;
}

/*******************************************************************************
*  
*  get/create engine instance and return engine_t*
*  
*******************************************************************************/
static engine_t* engine_instance(void)
{
	static engine_t* instance;
	
	if (!instance) engine_init(&instance);
	
	return instance;
}

/*******************************************************************************
*  
*  initialise new engine and return engine_t*
*  
*******************************************************************************/
static bool engine_init(engine_t** engine)
{
	*engine = malloc(sizeof **engine);
	if (!*engine) {
		
		fprintf(stderr, "could not allocate memory for engine!\n");
		return false;
	}
	
	(*engine)->dungeon = NULL;
	(*engine)->player = NULL;
	
	initscr();
	cbreak();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	
	return true;
}

/*******************************************************************************
*  
*  take engine_t* and free memory for members and self
*  
*******************************************************************************/
static bool engine_stop(engine_t** engine)
{
	if (!*engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	endwin();
	
	if ((*engine)->dungeon && !destruct_dungeon((*engine)->dungeon)) {
		
		fprintf(stderr, "could not destruct dungeon!\n");
		return false;
	}
	(*engine)->dungeon = NULL;
	
	if ((*engine)->player && !destruct_player((*engine)->player)) {
		
		fprintf(stderr, "could not destruct player!\n");
		return false;
	}
	(*engine)->player = NULL;
	
	free(*engine);
	*engine = NULL;
	
	return true;
}

/*******************************************************************************
*  
*  take engine_t* then load engine initial state and return bool
*  
*******************************************************************************/
static bool initialise(engine_t* engine)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	_init_game(engine, "Tomb of Bones", "Player");
	
	return true;
}

/*******************************************************************************
*  
*  take engine_t* then process engine tick and return bool
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
*  take engine_t* then process rendering and return bool
*  
*******************************************************************************/
static bool _render_system(engine_t* engine)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	if (!engine->dungeon) {
		
		fprintf(stderr, "invalid dungeon!\n");
		return false;
	}
	if (!engine->player) {
		
		fprintf(stderr, "invalid player!\n");
		return false;
	}
	
	clear();
	
	for (int32_t map_y = 0; map_y < LINES; map_y++) {
		move(map_y, 0);
		for (int32_t map_x = 0; map_x < COLS; map_x++) {
			addch((*engine->dungeon->zlevels[0]).tiles[(map_y * COLS) + map_x].symbol);
		}
	}
	
	move(engine->player->position.y, engine->player->position.x);
	addch(engine->player->symbol);
	
	refresh();
	
	return true;
}

/*******************************************************************************
*  
*  take engine_t* then process input and return bool
*  
*******************************************************************************/
static bool _input_system(engine_t* engine)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	if (!engine->dungeon) {
		
		fprintf(stderr, "invalid dungeon!\n");
		return false;
	}
	if (!engine->player) {
		
		fprintf(stderr, "invalid player!\n");
		return false;
	}
	
	int16_t ch = getch();
	
	if ((char)ch == 'q') {
		
		return false;
	}
	
	switch (ch) {
		
		case KEY_UP:
			engine->player->move_toward(engine->player, (vec2d_t){ 0.0, -1.0 });
			break;
		
		case KEY_DOWN:
			engine->player->move_toward(engine->player, (vec2d_t){ 0.0, 1.0 });
			break;
		
		case KEY_LEFT:
			engine->player->move_toward(engine->player, (vec2d_t){ -1.0, 0.0 });
			break;
		
		case KEY_RIGHT:
			engine->player->move_toward(engine->player, (vec2d_t){ 1.0, 0.0 });
			break;
		
		default:
			fprintf(stderr, "unhandled input!\n");
	}
	
	return true;
}

/*******************************************************************************
*  
*  take engine_t* then process events and return bool
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
*  take engine_t* then process physics and return bool
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
*  take engine_t* and initialise new dungeon for gameplay
*  
*******************************************************************************/
static bool _init_game(engine_t* engine, str_t dungeon_name, str_t player_name)
{
	if (!engine) {
		
		fprintf(stderr, "invalid engine!\n");
		return false;
	}
	
	if (engine->dungeon && !destruct_dungeon(engine->dungeon)) {
		
		fprintf(stderr, "could not destruct dungeon!\n");
		return false;
	}
	engine->dungeon = create_dungeon(dungeon_name, 1, 350, 350);
	if (!engine->dungeon) {
		
		fprintf(stderr, "could not create dungeon!\n");
		return false;
	}
	
	if (engine->player && !destruct_player(engine->player)) {
		
		fprintf(stderr, "could not destruct player!\n");
		return false;
	}
	engine->player = create_player(player_name, (vec2d_t){ 0.0, 0.0 });
	if (!engine->player) {
		
		fprintf(stderr, "could not create player!\n");
		return false;
	}
	
	return true;
}

/*******************************************************************************
*  
*  END engine.c
*  
*******************************************************************************/
