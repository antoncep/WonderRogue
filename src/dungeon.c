/*******************************************************************************
*  
*  dungeon.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include "dungeon.h"

static dlevel_t *create_dlevel(uint32_t, uint32_t, uint32_t);

/*******************************************************************************
*  
*  initialize dungeon and return dungeon_t *
*  
*******************************************************************************/
dungeon_t *create_dungeon(str_t name, uint32_t num_zlevels, uint32_t size_x, uint32_t size_y)
{
	dungeon_t *dungeon = NULL;
	
	dungeon = (dungeon_t *)malloc(sizeof(dungeon_t) + (num_zlevels * sizeof(dlevel_t *)));
	if (!dungeon) {
		
		printf("could not allocate memory for dungeon!\n");
		return NULL;
	}
	
	strncpy(dungeon->name, name, DNAM_LENGTH);
	dungeon->name[DNAM_LENGTH - 1] = '\0';
	
	dungeon->type        = (num_zlevels > 0) ? DNGN_FINITE : DNGN_INFINITE;
	dungeon->num_zlevels = num_zlevels;
	
	for (uint32_t z = 0; z < dungeon->num_zlevels; z++) {
		
		dungeon->zlevels[z] = create_dlevel(z, size_x, size_y);
		if (!dungeon->zlevels[z]) {
			
			if (dungeon && !destruct_dungeon(dungeon)) {
				
				printf("could not destruct dungeon!\n");
				return false;
			}
			printf("could not create dlevel!\n");
			return NULL;
		}
	}
	
	return dungeon;
}

/*******************************************************************************
*  
*  take dungeon_t * and free memory for members and self
*  
*******************************************************************************/
bool destruct_dungeon(dungeon_t *dungeon)
{
	if (!dungeon) {
		
		printf("invalid dungeon!\n");
		return false;
	}
	
	for (uint32_t z = dungeon->num_zlevels - 1; z < dungeon->num_zlevels; z--) {
		
		if (dungeon->zlevels[z]) {
			
			free(dungeon->zlevels[z]);
			dungeon->zlevels[z] = NULL;
		}
	}
	
	free(dungeon);
	dungeon = NULL;
	
	return true;
}

/*******************************************************************************
*  
*  take zlevel and size and return dlevel_t *
*  
*******************************************************************************/
static dlevel_t *create_dlevel(uint32_t zlevel, uint32_t size_x, uint32_t size_y)
{
	dlevel_t *dlevel = NULL;
	
	dlevel = (dlevel_t *)malloc(sizeof(dlevel_t) + (size_x * size_y * sizeof(dtile_t)));
	if (!dlevel) {
		
		printf("could not allocate memory for dlevel!\n");
		return NULL;
	}
	
	dlevel->zlevel = zlevel;
	dlevel->type   = (dlevel->zlevel == 0) ? DLVL_SAFE : DLVL_MONSTER;
	dlevel->size   = (vec2d_t){ size_x, size_y };
	
	uint32_t idx = 0;
	for (uint32_t tile_y = 0; tile_y < dlevel->size.y; tile_y++) {
		for (uint32_t tile_x = 0; tile_x < dlevel->size.x; tile_x++) {
			
			idx = (tile_y * dlevel->size.y) + tile_x;
			dlevel->tiles[idx].bgcolor = 0x000000;
			dlevel->tiles[idx].fgcolor = 0xFFFFFF;
			dlevel->tiles[idx].symbol = DSYM_FLOOR;
		}
	}
	
	return dlevel;
}

/*******************************************************************************
*  
*  END dungeon.c
*  
*******************************************************************************/
