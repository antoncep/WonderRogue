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

typedef struct dungeon_t dungeon_struct;
typedef struct player_t player_struct;

typedef struct engine_t engine_struct;
struct engine_t {
	
	dungeon_struct *dungeon;
	player_struct *player;
	
	bool (*init_game)(engine_struct *, char *, char *);
	bool (*render_screen)(engine_struct *);
	char (*handle_input)(engine_struct *);
	
};

engine_struct *create_engine(void);
bool destruct_engine(engine_struct *);

/*******************************************************************************
*  
*  END engine.h
*  
*******************************************************************************/
#endif // _ENGINE_H_
