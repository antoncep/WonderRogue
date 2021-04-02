#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdint.h>
#include "vector2d.h"

typedef enum {
	
	PSYM_NORMAL = '@',
	
} player_symbol_enum;

typedef struct {
	
	char name[24];
	player_symbol_enum symbol;
	vector2d_struct position;
	
} player_struct;

void player_move(player_struct *player, vector2d_struct direction);

#endif // _PLAYER_H_
