/*******************************************************************************
*  
*  main.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include "engine.h"
#include <stdlib.h>
#include <stdio.h>

/*******************************************************************************
*  
*  program entry point
*  
*******************************************************************************/
int main(int argc, char *argv[])
{
	engine_struct *engine = create_engine();
	if (!engine) {
		
		printf("could not initialize engine!\n");
		return -1;
	}
	
	engine->init_game(engine, "Tomb of Bones", "Player");
	do {
		engine->render_screen(engine);
		
	} while(engine->handle_input(engine) != 'q');
	
	if (engine && !destruct_engine(engine)) {
		
		printf("could not stop engine!\n");
		return -1;
	}
	
	return 0;
}

/*******************************************************************************
*  
*  END main.c
*  
*******************************************************************************/
