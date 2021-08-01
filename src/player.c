/*******************************************************************************
*  
*  player.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "scene_node.h"
#include "player.h"

struct Player {
	
	char name[PNAM_LENGTH];
	player_sym_t symbol;
	vec2d_t position;
};

static bool player_move_toward(player_t*, vec2d_t);

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool player_create(player_t** player, char* name, vec2d_t position)
{
	if (*player) {
		
		fprintf(stderr, "invalid handle!\n");
		return false;
	}
	
	*player = malloc(sizeof **player);
	if (!*player) {
		
		fprintf(stderr, "could not allocate memory for player!\n");
		return false;
	}
	
	if (!memset(*player, 0, sizeof **player)) {
		
		fprintf(stderr, "could not initialise memory for player!\n");
		return false;
	}
	
	strncpy((*player)->name, name, PNAM_LENGTH);
	(*player)->name[PNAM_LENGTH - 1] = '\0';
	
	(*player)->symbol   = PSYM_NORMAL;
	(*player)->position = position;
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool player_delete(player_t** player)
{
	if (!*player) {
		
		fprintf(stderr, "invalid handle!\n");
		return false;
	}
	
	free(*player);
	*player = 0;
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool player_input(player_t* player, int16_t ch)
{
	if (!player) {
		
		fprintf(stderr, "invalid player!\n");
		return false;
	}
	
	switch (ch) {
		
		case 0403:
			player_move_toward(player, VEC2D_UP);
			break;
		
		case 0402:
			player_move_toward(player, VEC2D_DOWN);
			break;
		
		case 0404:
			player_move_toward(player, VEC2D_LEFT);
			break;
		
		case 0405:
			player_move_toward(player, VEC2D_RIGHT);
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
bool player_render(player_t* player, bool(*draw_ch)(int16_t,int,int))
{
	if (!player) {
		
		fprintf(stderr, "invalid player!\n");
		return false;
	}
	
	draw_ch(player->symbol, player->position.x, player->position.y);
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
static bool player_move_toward(player_t* player, vec2d_t direction)
{
	if (!player) {
		
		fprintf(stderr, "invalid player!\n");
		return false;
	}
	
	direction = vector2d_normalise(direction);
	
	player->position = vector2d_add(player->position, direction);
	
	return true;
}

/*******************************************************************************
*  
*  END player.c
*  
*******************************************************************************/
