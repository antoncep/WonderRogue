/*******************************************************************************
*  
*  dungeon.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "dungeon.h"

struct Dungeon {
	
	char name[DNAM_LENGTH];
	uint32_t num_zlevels;
	uint32_t cur_zlevel;
	dlevel_t* zlevels[];
};

static dlevel_t* create_dlevel(uint32_t, uint32_t, uint32_t);

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool dungeon_create(dungeon_t** dungeon, char* name, uint32_t num_zlevels, uint32_t size_x, uint32_t size_y)
{
	if (*dungeon) {
		
		fprintf(stderr, "invalid handle!\n");
		return 0;
	}
	
	*dungeon = malloc(sizeof **dungeon);
	if (!*dungeon) {
		
		fprintf(stderr, "could not allocate memory for dungeon!\n");
		return false;
	}
	
	if (!memset(*dungeon, 0, sizeof **dungeon)) {
		
		fprintf(stderr, "could not initialise memory for dungeon!\n");
		return false;
	}
	
	strncpy((*dungeon)->name, name, DNAM_LENGTH);
	(*dungeon)->name[DNAM_LENGTH - 1] = '\0';
	
	(*dungeon)->num_zlevels = num_zlevels;
	
	for (uint32_t z = 0; z < (*dungeon)->num_zlevels; z++) {
		
		(*dungeon)->zlevels[z] = create_dlevel(z, size_x, size_y);
		if (!(*dungeon)->zlevels[z]) {
			
			if ((*dungeon) && !dungeon_delete(dungeon)) {
				
				fprintf(stderr, "could not delete dungeon!\n");
				return false;
			}
			fprintf(stderr, "could not create dlevel!\n");
			return NULL;
		}
	}
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool dungeon_delete(dungeon_t** dungeon)
{
	if (!*dungeon) {
		
		fprintf(stderr, "invalid handle!\n");
		return 0;
	}
	
	for (uint32_t z = (*dungeon)->num_zlevels - 1; z < (*dungeon)->num_zlevels; z--) {
		
		if ((*dungeon)->zlevels[z]) {
			
			free((*dungeon)->zlevels[z]);
			(*dungeon)->zlevels[z] = NULL;
		}
	}
	
	free(*dungeon);
	*dungeon = 0;
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
bool dungeon_render(dungeon_t* dungeon, bool(*draw)(int,int,char), int max_x, int max_y)
{
	if (!dungeon) {
		
		fprintf(stderr, "invalid handle!\n");
		return 0;
	}
	
	for (int32_t map_y = 0; map_y < max_y; map_y++) {
		for (int32_t map_x = 0; map_x < max_x; map_x++) {
			draw(map_x, map_y, (*dungeon->zlevels[0]).tiles[(map_y * max_x) + map_x].symbol);
		}
	}
	
	return true;
}

/*******************************************************************************
*  
*  function
*  
*******************************************************************************/
static dlevel_t* create_dlevel(uint32_t zlevel, uint32_t size_x, uint32_t size_y)
{
	dlevel_t* dlevel = NULL;
	
	dlevel = (dlevel_t*)malloc(sizeof(dlevel_t) + (size_x * size_y * sizeof(dtile_t)));
	if (!dlevel) {
		
		fprintf(stderr, "could not allocate memory for dlevel!\n");
		return NULL;
	}
	
	dlevel->zlevel = zlevel;
	dlevel->type   = (dlevel->zlevel == 0) ? DLVL_SAFE : DLVL_MONSTER;
	dlevel->size   = (vec2d_t){ size_x, size_y };
	
	uint32_t idx = 0;
	for (uint32_t tile_y = 0; tile_y < dlevel->size.y; tile_y++) {
		for (uint32_t tile_x = 0; tile_x < dlevel->size.x; tile_x++) {
			
			idx = (tile_y * dlevel->size.y) + tile_x;
			dlevel->tiles[idx].bgcolour = 0x000000;
			dlevel->tiles[idx].fgcolour = 0xFFFFFF;
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
