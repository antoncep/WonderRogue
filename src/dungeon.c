#include <string.h>
#include <malloc.h>
#include "dungeon.h"

dungeon_struct *create_dungeon(uint32_t num_zlevels, uint32_t size_x, uint32_t size_y)
{
	dungeon_struct *dungeon = NULL;
	
	dungeon = (dungeon_struct*)malloc(sizeof(dungeon_struct) + (num_zlevels * sizeof(void*)));
	if (!dungeon)
		return NULL;
	
	strncpy(dungeon->name, "The tomb of Kalym", 24);
	
	dungeon->type = (num_zlevels > 0) ? DNGN_FINITE : DNGN_INFINITE;
	
	dungeon->num_zlevels = num_zlevels;
	
	for (uint32_t z = 0; z < dungeon->num_zlevels; z++) {
		
		dungeon->zlevels[z] = create_dlevel(z, size_x, size_y);
		if (!dungeon->zlevels[z]) {
			delete_dungeon(dungeon);
			return NULL;
		}
	}
	
	return dungeon;
}

int32_t delete_dungeon(dungeon_struct *dungeon)
{
	if (!dungeon)
		return -1;
	
	for (uint32_t z = dungeon->num_zlevels - 1; z < dungeon->num_zlevels; z--) {
		
		if (dungeon->zlevels[z])
			free(dungeon->zlevels[z]);
	}
	
	free(dungeon);
	
	return 0;
}

dlevel_struct *create_dlevel(uint32_t zlevel, uint32_t size_x, uint32_t size_y)
{
	dlevel_struct *dlevel = NULL;
	
	dlevel = (dlevel_struct*)malloc(sizeof(dlevel_struct) + (size_x * size_y * sizeof(dtile_struct)));
	if (!dlevel)
		return NULL;
	
	dlevel->zlevel = zlevel;
	
	dlevel->type = (dlevel->zlevel == 0) ? DLVL_SAFE : DLVL_MONSTER;
	
	dlevel->size.x = size_x;
	dlevel->size.y = size_y;
	
	for (uint32_t tile_y = 0; tile_y < dlevel->size.y; tile_y++) {
		for (uint32_t tile_x = 0; tile_x < dlevel->size.x; tile_x++) {
			
			dlevel->tiles[(tile_y * dlevel->size.y) + tile_x].bgcolor = 0x000000;
			dlevel->tiles[(tile_y * dlevel->size.y) + tile_x].fgcolor = 0xFFFFFF;
			dlevel->tiles[(tile_y * dlevel->size.y) + tile_x].symbol = DSYM_FLOOR;
		}
	}
	
	return dlevel;
}
