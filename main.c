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
*  function
*  
*******************************************************************************/
int main(int argc, char* argv[])
{
	engine_params_t params = {0};
	
	params.window_width = 1920;
	params.window_height = 1080;
	params.refresh_rate = 60;
	
	ngn(engine_create);
	
	if (!engine_params_set(ngn(0), &params)) {
		
		fprintf(stderr, "could not set parameters!\n");
		return 1;
	}
	
	if (!process_start(ngn(0))) {
		
		fprintf(stderr, "could not execute run loop!\n");
		return 1;
	}
	
	ngn(engine_delete);
	
	return 0;
}

/*******************************************************************************
*  
*  END main.c
*  
*******************************************************************************/
