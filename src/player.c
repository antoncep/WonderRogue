/*******************************************************************************
*  
*  player.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <string.h>
#include <malloc.h>
#include "player.h"

static bool move(player_struct *, vector2d_struct);

/*******************************************************************************
*  
*  initialize player and return player_struct *
*  
*******************************************************************************/
player_struct *create_player(char *name, vector2d_struct position)
{
	player_struct *player = NULL;
	
	player = (player_struct *)malloc(sizeof(player_struct));
	if (!player) {
		
		printf("could not allocate memory for player!\n");
		return NULL;
	}
	
	//name[PNAM_LENGTH - 1] = '\0';
	strncpy(player->name, name, PNAM_LENGTH);
	
	player->symbol   = PSYM_NORMAL;
	player->position = position;
	
	player->move = move;
	
	return player;
}

/*******************************************************************************
*  
*  take player_struct * and free memory for members and self
*  
*******************************************************************************/
bool destruct_player(player_struct *player)
{
	if (!player) {
		
		printf("invalid player!\n");
		return false;
	}
	
	free(player);
	player = NULL;
	
	return true;
}

/*******************************************************************************
*  
*  take player_struct * and vector2d_struct and update position
*  
*******************************************************************************/
static bool move(player_struct *player, vector2d_struct direction)
{
	if (!player) {
		
		printf("invalid player!\n");
		return false;
	}
	
	direction = vector2d_normalize(direction);
	
	player->position = vector2d_add(player->position, direction);
	
	return true;
}

/*******************************************************************************
*  
*  END player.c
*  
*******************************************************************************/
