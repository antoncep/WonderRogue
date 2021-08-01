#ifndef _SCENE_NODE_H_
#define _SCENE_NODE_H_
/*******************************************************************************
*  
*  scene_node.h
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

typedef struct SceneNode scene_node_t;

bool scene_node_create(scene_node_t**);
bool scene_node_delete(scene_node_t**);

bool scene_node_input(scene_node_t*, int16_t);
bool scene_node_render(scene_node_t*, bool(*)(int16_t,int,int));

/*******************************************************************************
*  
*  END scene_node.h
*  
*******************************************************************************/
#endif // _SCENE_NODE_H_
