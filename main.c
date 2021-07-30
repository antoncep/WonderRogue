/*******************************************************************************
*  
*  main.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include "stopwatch.h"
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
	params.refresh_rate = 30;
	
	stopwatch_t* stopwatch = 0;
	stopwatch_create(&stopwatch);
	uint64_t delta_time = stopwatch_start(stopwatch);
	
	engine_t* engine = 0;
	engine_create(&engine);
	
	if (!engine_params_set(engine, &params)) {
		
		fprintf(stderr, "could not set parameters!\n");
		return 1;
	}
	
	if (!engine_state_loop(engine)) {
		
		fprintf(stderr, "could not execute run loop!\n");
		return 1;
	}
	
	engine_delete(&engine);
	
	delta_time = stopwatch_stamp(stopwatch);
	stopwatch_delete(&stopwatch);
	
	fprintf(stderr, "total runtime: %f sec\n", ((double)delta_time / NANOSECS_IN_SECOND));
	
	return 0;
}

/*******************************************************************************
*  
*  END main.c
*  
*******************************************************************************/
