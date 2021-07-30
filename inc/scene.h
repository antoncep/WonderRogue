#ifndef _SCENE_H_
#define _SCENE_H_
/*******************************************************************************
*  
*  scene.h
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

typedef struct Scene scene_t;

bool scene_create(scene_t**);
bool scene_delete(scene_t**);

bool scene_init(scene_t*);
bool scene_process_input(scene_t*, int16_t);
bool scene_render(scene_t*);

/*******************************************************************************
*  
*  END scene.h
*  
*******************************************************************************/
#endif // _SCENE_H_
