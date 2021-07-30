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
#include <ncurses.h>
#include "vector2d.h"
#include "dungeon.h"
#include "player.h"
#include "scene.h"

struct Scene {
	
	dungeon_t* dungeon;
	player_t* player;
};

static bool ncurses_draw(int, int, char);

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool scene_create(scene_t** scene)
{
	if (*scene) {
		
		fprintf(stderr, "invalid handle!\n");
		return 0;
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
		return 0;
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
	dungeon_create(&scene->dungeon, "dungeon_name", 1, 350, 350);
	if (!scene->dungeon) {
		
		fprintf(stderr, "could not create dungeon!\n");
		return false;
	}
	
	if (scene->player && !player_delete(&scene->player)) {
		
		fprintf(stderr, "could not delete player!\n");
		return false;
	}
	player_create(&scene->player, "player_name", (vec2d_t){ 7, 7 });
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
			player_move_toward(scene->player, VEC2D_UP);
			break;
		
		case KEY_DOWN:
			player_move_toward(scene->player, VEC2D_DOWN);
			break;
		
		case KEY_LEFT:
			player_move_toward(scene->player, VEC2D_LEFT);
			break;
		
		case KEY_RIGHT:
			player_move_toward(scene->player, VEC2D_RIGHT);
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
	
	dungeon_render(scene->dungeon, ncurses_draw, COLS, LINES);
	
	player_render(scene->player, ncurses_draw);
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
static bool ncurses_draw(int pox_x, int pos_y, char symbol)
{
	move(pos_y, pox_x);
	addch(symbol);
	
	return true;
}

/*******************************************************************************
*  
*  END scene.c
*  
*******************************************************************************/
