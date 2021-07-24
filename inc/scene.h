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

#include "engine.h"

typedef struct Dungeon dungeon_t;
typedef struct Player player_t;

typedef struct Scene scene_t;
struct Scene {
	
	dungeon_t* dungeon;
	player_t* player;
};

scene_t* scene_create(void);
bool scene_delete(scene_t*);

bool scene_init(scene_t*);
bool scene_process_input(scene_t*, int16_t);
bool scene_render(scene_t*);

/*******************************************************************************
*  
*  END scene.h
*  
*******************************************************************************/
#endif // _SCENE_H_
