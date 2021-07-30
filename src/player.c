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
#include "player.h"

struct Player {
	
	char name[PNAM_LENGTH];
	player_sym_t symbol;
	vec2d_t position;
};

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool player_create(player_t** player, char* name, vec2d_t position)
{
	if (*player) {
		
		fprintf(stderr, "invalid handle!\n");
		return 0;
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
		return 0;
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
bool player_render(player_t* player, bool(*draw)(int,int,char))
{
	if (!player) {
		
		fprintf(stderr, "invalid player!\n");
		return false;
	}
	
	draw(player->position.x, player->position.y, player->symbol);
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool player_move_toward(player_t* player, vec2d_t direction)
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
