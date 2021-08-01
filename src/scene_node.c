/*******************************************************************************
*  
*  scene_node.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "scene_node.h"

struct SceneNode {
	
	void* object_instance;
	bool (*object_input)(scene_node_t*, int16_t);
	bool (*object_render)(scene_node_t*, bool(*)(int16_t,int,int));
	scene_node_t* parent;
	scene_node_t* children[];
};

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool scene_node_create(scene_node_t** scene_node)
{
	if (*scene_node) {
		
		fprintf(stderr, "invalid handle!\n");
		return false;
	}
	
	*scene_node = malloc(sizeof **scene_node);
	if (!*scene_node) {
		
		fprintf(stderr, "could not allocate memory for scene node!\n");
		return false;
	}
	
	if (!memset(*scene_node, 0, sizeof **scene_node)) {
		
		fprintf(stderr, "could not initialise memory for scene node!\n");
		return false;
	}
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool scene_node_delete(scene_node_t** scene_node)
{
	if (!*scene_node) {
		
		fprintf(stderr, "invalid handle!\n");
		return false;
	}
	
	free(*scene_node);
	*scene_node = 0;
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool scene_node_input(scene_node_t* scene_node, int16_t ch)
{
	if (!scene_node) {
		
		fprintf(stderr, "invalid scene node!\n");
		return false;
	}
	
	scene_node->object_input(scene_node->object_instance, ch);
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool scene_node_render(scene_node_t* scene_node, bool(*draw_ch)(int16_t,int,int))
{
	if (!scene_node) {
		
		fprintf(stderr, "invalid scene node!\n");
		return false;
	}
	
	scene_node->object_render(scene_node->object_instance, draw_ch);
	
	return true;
}

/*******************************************************************************
*  
*  END scene_node.c
*  
*******************************************************************************/
