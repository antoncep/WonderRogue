/*******************************************************************************
*  
*  stopwatch.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include "stopwatch.h"

struct Stopwatch {
	
	uint64_t ticks_s;
	uint64_t ticks_e;
	uint64_t ticks_d;
};

static uint64_t clock_monotonic_timestamp(void);

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool stopwatch_create(stopwatch_t** stopwatch)
{
	if (*stopwatch) {
		
		fprintf(stderr, "invalid handle!\n");
		return false;
	}
	
	*stopwatch = malloc(sizeof **stopwatch);
	if (!*stopwatch) {
		
		fprintf(stderr, "could not allocate memory for stopwatch!\n");
		return false;
	}
	
	if (!memset(*stopwatch, 0, sizeof **stopwatch)) {
		
		fprintf(stderr, "could not initialise memory for stopwatch!\n");
		return false;
	}
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool stopwatch_delete(stopwatch_t** stopwatch)
{
	if (!*stopwatch) {
		
		fprintf(stderr, "invalid handle!\n");
		return false;
	}
	
	free(*stopwatch);
	*stopwatch = 0;
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
uint64_t stopwatch_start(stopwatch_t* stopwatch)
{
	if (!stopwatch) {
		
		fprintf(stderr, "invalid stopwatch!\n");
		return 0;
	}
	
	stopwatch->ticks_s = clock_monotonic_timestamp();
	stopwatch->ticks_e = clock_monotonic_timestamp();
	stopwatch->ticks_d = stopwatch->ticks_e - stopwatch->ticks_s;
	
	return stopwatch->ticks_d;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
uint64_t stopwatch_stamp(stopwatch_t* stopwatch)
{
	if (!stopwatch) {
		
		fprintf(stderr, "invalid stopwatch!\n");
		return 0;
	}
	
	stopwatch->ticks_s = stopwatch->ticks_e;
	stopwatch->ticks_e = clock_monotonic_timestamp();
	stopwatch->ticks_d = stopwatch->ticks_e - stopwatch->ticks_s;
	
	return stopwatch->ticks_d;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
uint64_t stopwatch_check(stopwatch_t* stopwatch)
{
	if (!stopwatch) {
		
		fprintf(stderr, "invalid stopwatch!\n");
		return 0;
	}
	
	stopwatch->ticks_d = clock_monotonic_timestamp() - stopwatch->ticks_s;
	
	return stopwatch->ticks_d;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
uint64_t stopwatch_delta(stopwatch_t* stopwatch)
{
	if (!stopwatch) {
		
		fprintf(stderr, "invalid stopwatch!\n");
		return 0;
	}
	
	stopwatch->ticks_d = stopwatch->ticks_e - stopwatch->ticks_s;
	
	return stopwatch->ticks_d;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
static uint64_t clock_monotonic_timestamp(void)
{
	struct timespec clock_monotonic = {0};
	
	if (clock_gettime(CLOCK_MONOTONIC, &clock_monotonic)) {
		
		fprintf(stderr, "could not get time from clock!\n");
		return 0;
	}
	
	return ((clock_monotonic.tv_sec * NANOSECS_PER_SECOND) + clock_monotonic.tv_nsec);
}

/*******************************************************************************
*  
*  END stopwatch.c
*  
*******************************************************************************/
