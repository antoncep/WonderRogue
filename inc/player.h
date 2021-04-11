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

#include "engine.h"

#define PNAM_LENGTH 24

typedef enum PlayerSymbol player_sym_t;
enum PlayerSymbol {
	
	PSYM_NORMAL = '@',
	
};

typedef struct Player player_t;
struct Player {
	
	char name[PNAM_LENGTH];
	player_sym_t symbol;
	vec2d_t position;
	
	bool (*move_toward)(player_t *, vec2d_t);
	
};

player_t *create_player(str_t, vec2d_t);
bool destruct_player(player_t *);

/*******************************************************************************
*  
*  END player.h
*  
*******************************************************************************/
#endif // _PLAYER_H_
