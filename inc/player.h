#ifndef _PLAYER_H_
#define _PLAYER_H_
/*******************************************************************************
*  
*  player.h
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "vector2d.h"

#define PNAM_LENGTH 24

typedef enum PlayerSymbol player_sym_t;
enum PlayerSymbol {
	
	PSYM_NORMAL = '@',
};

typedef struct Player player_t;

bool player_create(player_t**, char*, vec2d_t);
bool player_delete(player_t**);

bool player_render(player_t*, bool(*)(int,int,char));

bool player_move_toward(player_t*, vec2d_t);

/*******************************************************************************
*  
*  END player.h
*  
*******************************************************************************/
#endif // _PLAYER_H_
