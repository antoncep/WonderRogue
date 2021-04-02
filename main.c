/*******************************************************************************
*  
*  main.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "engine.h"

/*******************************************************************************
*  
*  program entry point
*  
*******************************************************************************/
int main(int argc, char *argv[])
{
	engine_struct *engine = init_engine();
	if (!engine) {
		
		printf("could not initialize engine!\n");
		return -1;
	}
	
	engine->new_game(engine, "Tomb of Bones", "Player");
	do {
		engine->render_screen(engine);
		
	} while(engine->handle_input(engine) != 'q');
	
	if (engine && !stop_engine(engine)) {
		
		printf("could not free engine memory!\n");
		return -1;
	}
	
	return 0;
}

/*******************************************************************************
*  
*  END main.c
*  
*******************************************************************************/
