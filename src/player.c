#include "player.h"

void player_move(player_struct *player, vector2d_struct direction)
{
	direction = vector2d_normalize(direction);
	
	player->position = vector2d_add(player->position, direction);
	
	return;
}
