/*******************************************************************************
*  
*  main.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include "engine.h"

/*******************************************************************************
*  
*  program entry point
*  
*******************************************************************************/
int main(int argc, char* argv[])
{
	engine_params_t engine_params = {0};
	
	engine_params.window_width = 1920;
	engine_params.window_height = 1080;
	
	if (!engine(engine_set_parameters, &engine_params)) {
		
		fprintf(stderr, "could not set parameters!\n");
		return 1;
	}
	
	if (!engine(engine_run_loop, NULL)) {
		
		fprintf(stderr, "could not execute run loop!\n");
		return 1;
	}
	
	return 0;
}

/*******************************************************************************
*  
*  END main.c
*  
*******************************************************************************/
