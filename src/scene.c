/*******************************************************************************
*  
*  scene.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include "scene.h"
#include "dungeon.h"
#include "player.h"

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
scene_t* scene_create(void)
{
	scene_t* scene = 0;
	
	return scene;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool scene_delete(scene_t* scene)
{
	if (!scene) {
		
		fprintf(stderr, "invalid scene!\n");
		return false;
	}
	
	if (scene->dungeon && !destruct_dungeon(scene->dungeon)) {
		
		fprintf(stderr, "could not destruct dungeon!\n");
		return false;
	}
	scene->dungeon = 0;
	
	if (scene->player && !destruct_player(scene->player)) {
		
		fprintf(stderr, "could not destruct player!\n");
		return false;
	}
	scene->player = 0;
	
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
	
	if (scene->dungeon && !destruct_dungeon(scene->dungeon)) {
		
		fprintf(stderr, "could not destruct dungeon!\n");
		return false;
	}
	scene->dungeon = create_dungeon("dungeon_name", 1, 350, 350);
	if (!scene->dungeon) {
		
		fprintf(stderr, "could not create dungeon!\n");
		return false;
	}
	
	if (scene->player && !destruct_player(scene->player)) {
		
		fprintf(stderr, "could not destruct player!\n");
		return false;
	}
	scene->player = create_player("player_name", (vec2d_t){ 0.0, 0.0 });
	if (!scene->player) {
		
		fprintf(stderr, "could not create player!\n");
		return false;
	}
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool scene_process_input(scene_t* scene, int16_t ch)
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
	
	switch (ch) {
		
		case KEY_UP:
			scene->player->move_toward(scene->player, (vec2d_t){ 0.0, -1.0 });
			break;
		
		case KEY_DOWN:
			scene->player->move_toward(scene->player, (vec2d_t){ 0.0, 1.0 });
			break;
		
		case KEY_LEFT:
			scene->player->move_toward(scene->player, (vec2d_t){ -1.0, 0.0 });
			break;
		
		case KEY_RIGHT:
			scene->player->move_toward(scene->player, (vec2d_t){ 1.0, 0.0 });
			break;
		
		default:
			fprintf(stderr, "unhandled input!\n");
	}
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool scene_render(scene_t* scene)
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
	
	for (int32_t map_y = 0; map_y < LINES; map_y++) {
		move(map_y, 0);
		for (int32_t map_x = 0; map_x < COLS; map_x++) {
			addch((*scene->dungeon->zlevels[0]).tiles[(map_y * COLS) + map_x].symbol);
		}
	}
	
	move(scene->player->position.y, scene->player->position.x);
	addch(scene->player->symbol);
	
	return true;
}

/*******************************************************************************
*  
*  END scene.c
*  
*******************************************************************************/
