/*******************************************************************************
*  
*  scene.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "vector2d.h"
#include "dungeon.h"
#include "player.h"
#include "scene_node.h"
#include "scene.h"

struct Scene {
	
	dungeon_t* dungeon;
	player_t* player;
};

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool scene_create(scene_t** scene)
{
	if (*scene) {
		
		fprintf(stderr, "invalid handle!\n");
		return false;
	}
	
	*scene = malloc(sizeof **scene);
	if (!*scene) {
		
		fprintf(stderr, "could not allocate memory for scene!\n");
		return false;
	}
	
	if (!memset(*scene, 0, sizeof **scene)) {
		
		fprintf(stderr, "could not initialise memory for scene!\n");
		return false;
	}
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool scene_delete(scene_t** scene)
{
	if (!*scene) {
		
		fprintf(stderr, "invalid handle!\n");
		return false;
	}
	
	if ((*scene)->dungeon && !dungeon_delete(&(*scene)->dungeon)) {
		
		fprintf(stderr, "could not delete dungeon!\n");
		return false;
	}
	
	if ((*scene)->player && !player_delete(&(*scene)->player)) {
		
		fprintf(stderr, "could not delete player!\n");
		return false;
	}
	
	free(*scene);
	*scene = 0;
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool scene_input(scene_t* scene, int16_t ch)
{
	if (!scene) {
		
		fprintf(stderr, "invalid scene!\n");
		return false;
	}
	
	if (!scene->dungeon) {
		
		fprintf(stderr, "invalid dungeon!\n");
		return false;
	}
	if (!scene->player) {
		
		fprintf(stderr, "invalid player!\n");
		return false;
	}
	
	dungeon_input(scene->dungeon, ch);
	
	player_input(scene->player, ch);
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool scene_render(scene_t* scene, bool(*draw_ch)(int16_t,int,int))
{
	if (!scene) {
		
		fprintf(stderr, "invalid scene!\n");
		return false;
	}
	
	if (!scene->dungeon) {
		
		fprintf(stderr, "invalid dungeon!\n");
		return false;
	}
	if (!scene->player) {
		
		fprintf(stderr, "invalid player!\n");
		return false;
	}
	
	dungeon_render(scene->dungeon, draw_ch);
	
	player_render(scene->player, draw_ch);
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool scene_init(scene_t* scene)
{
	if (!scene) {
		
		fprintf(stderr, "invalid scene!\n");
		return false;
	}
	
	if (scene->dungeon && !dungeon_delete(&scene->dungeon)) {
		
		fprintf(stderr, "could not delete dungeon!\n");
		return false;
	}
	if (!dungeon_create(&scene->dungeon, "dungeon_name", 1, 350, 350)) {
		
		fprintf(stderr, "could not create dungeon!\n");
		return false;
	}
	
	if (scene->player && !player_delete(&scene->player)) {
		
		fprintf(stderr, "could not delete player!\n");
		return false;
	}
	if (!player_create(&scene->player, "player_name", (vec2d_t){ 7, 7 })) {
		
		fprintf(stderr, "could not create player!\n");
		return false;
	}
	
	return true;
}

/*******************************************************************************
*  
*  END scene.c
*  
*******************************************************************************/
