/*******************************************************************************
*  
*  player.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include "player.h"

static bool move_toward(player_t*, vec2d_t);

/*******************************************************************************
*  
*  initialise player and return player_t*
*  
*******************************************************************************/
player_t* create_player(str_t name, vec2d_t position)
{
	player_t* player = NULL;
	
	player = (player_t*)malloc(sizeof(player_t));
	if (!player) {
		
		fprintf(stderr, "could not allocate memory for player!\n");
		return NULL;
	}
	
	strncpy(player->name, name, PNAM_LENGTH);
	player->name[PNAM_LENGTH - 1] = '\0';
	
	player->symbol   = PSYM_NORMAL;
	player->position = position;
	
	player->move_toward = move_toward;
	
	return player;
}

/*******************************************************************************
*  
*  take player_t* and free memory for members and self
*  
*******************************************************************************/
bool destruct_player(player_t* player)
{
	if (!player) {
		
		fprintf(stderr, "invalid player!\n");
		return false;
	}
	
	free(player);
	player = NULL;
	
	return true;
}

/*******************************************************************************
*  
*  take player_t* and vec2d_t and update position
*  
*******************************************************************************/
static bool move_toward(player_t* player, vec2d_t direction)
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
