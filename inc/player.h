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

typedef enum player_symbol_enum {
	
	PSYM_NORMAL = '@',
	
} player_symbol_enum;

typedef struct player_struct {
	
	char name[PNAM_LENGTH];
	player_symbol_enum symbol;
	vector2d_struct position;
	
	bool (*move)(struct player_struct *, vector2d_struct);
	
} player_struct;

player_struct *create_player(char *, vector2d_struct);
bool destruct_player(player_struct *);

/*******************************************************************************
*  
*  END player.h
*  
*******************************************************************************/
#endif // _PLAYER_H_
