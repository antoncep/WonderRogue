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

#include "dungeon.h"

typedef struct engine_struct {
	
	dungeon_struct *dungeon;
	
	void (*render_screen)(struct engine_struct *);
	char (*handle_input)(struct engine_struct *);
	void (*new_game)(struct engine_struct *);
	
} engine_struct;

engine_struct *init_engine(void);
int stop_engine(engine_struct *);

/*******************************************************************************
*  
*  END engine.h
*  
*******************************************************************************/
#endif // _ENGINE_H_
