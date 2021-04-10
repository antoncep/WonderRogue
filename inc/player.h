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

typedef enum player_symbol_t player_symbol_enum;
enum player_symbol_t {
	
	PSYM_NORMAL = '@',
	
};

typedef struct player_t player_struct;
struct player_t {
	
	char name[PNAM_LENGTH];
	player_symbol_enum symbol;
	vec2d_t position;
	
	bool (*move_toward)(player_struct *, vec2d_t);
	
};

player_struct *create_player(char *, vec2d_t);
bool destruct_player(player_struct *);

/*******************************************************************************
*  
*  END player.h
*  
*******************************************************************************/
#endif // _PLAYER_H_
