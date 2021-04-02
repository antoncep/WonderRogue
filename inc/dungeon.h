#ifndef _DUNGEON_H_
#define _DUNGEON_H_

#include <stdint.h>
#include "vector2d.h"

typedef enum {
	
	DSYM_EMPTY = ' ',
	DSYM_FLOOR = '.',
	DSYM_WALL  = '#',
	
} dtile_symbol_enum;

typedef struct {
	
	uint32_t bgcolor;
	uint32_t fgcolor;
	dtile_symbol_enum symbol;
	
} dtile_struct;

typedef struct {
	
	vector2d_struct position;
	vector2d_struct size;
	dtile_struct tiles[];
	
} droom_struct;

typedef enum {
	
	DLVL_SAFE,
	DLVL_MONSTER,
	DLVL_BOSS,
	
} dlevel_type_enum;

typedef struct {
	
	uint32_t zlevel;
	dlevel_type_enum type;
	vector2d_struct size;
	dtile_struct tiles[];
	
} dlevel_struct;

typedef enum {
	
	DNGN_FINITE,
	DNGN_INFINITE,
	
} dungeon_type_enum;

typedef struct {
	
	char name[24];
	dungeon_type_enum type;
	uint32_t num_zlevels;
	dlevel_struct *zlevels[];
	
} dungeon_struct;

dungeon_struct *create_dungeon(uint32_t num_zlevels, uint32_t size_x, uint32_t size_y);
int32_t delete_dungeon(dungeon_struct *dungeon);
dlevel_struct *create_dlevel(uint32_t zlevel, uint32_t size_x, uint32_t size_y);

#endif // _DUNGEON_H_
