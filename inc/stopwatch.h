#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_
/*******************************************************************************
*  
*  stopwatch.h
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#define MILLISEC_PER_SECOND 1e3
#define MICROSEC_PER_SECOND 1e6
#define NANOSECS_PER_SECOND 1e9

typedef struct Stopwatch stopwatch_t;

bool stopwatch_create(stopwatch_t**);
bool stopwatch_delete(stopwatch_t**);

uint64_t stopwatch_start(stopwatch_t*);
uint64_t stopwatch_stamp(stopwatch_t*);
uint64_t stopwatch_check(stopwatch_t*);
uint64_t stopwatch_delta(stopwatch_t*);

/*******************************************************************************
*  
*  END stopwatch.h
*  
*******************************************************************************/
#endif // _STOPWATCH_H_
