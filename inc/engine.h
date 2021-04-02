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
#include "dungeon.h"
#include "player.h"

typedef struct engine_struct {
	
	dungeon_struct *dungeon;
	player_struct *player;
	
	bool (*render_screen)(struct engine_struct *);
	char (*handle_input)(struct engine_struct *);
	bool (*new_game)(struct engine_struct *, char *, char *);
	
} engine_struct;

engine_struct *init_engine(void);
bool stop_engine(engine_struct *);

/*******************************************************************************
*  
*  END engine.h
*  
*******************************************************************************/
#endif // _ENGINE_H_
