#ifndef _DUNGEON_H_
#define _DUNGEON_H_
/*******************************************************************************
*  
*  dungeon.h
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "vector2d.h"

#define DNAM_LENGTH 24

typedef enum dtile_symbol_enum {
	
	DSYM_EMPTY = ' ',
	DSYM_FLOOR = '.',
	DSYM_WALL  = '#',
	
} dtile_symbol_enum;

typedef struct dtile_struct {
	
	uint32_t bgcolor;
	uint32_t fgcolor;
	dtile_symbol_enum symbol;
	
} dtile_struct;

typedef struct droom_struct {
	
	vector2d_struct position;
	vector2d_struct size;
	dtile_struct tiles[];
	
} droom_struct;

typedef enum dlevel_type_enum {
	
	DLVL_SAFE,
	DLVL_MONSTER,
	DLVL_BOSS,
	
} dlevel_type_enum;

typedef struct dlevel_struct {
	
	uint32_t zlevel;
	dlevel_type_enum type;
	vector2d_struct size;
	dtile_struct tiles[];
	
} dlevel_struct;

typedef enum dungeon_type_enum {
	
	DNGN_FINITE,
	DNGN_INFINITE,
	
} dungeon_type_enum;

typedef struct dungeon_struct {
	
	char name[DNAM_LENGTH];
	dungeon_type_enum type;
	uint32_t num_zlevels;
	dlevel_struct *zlevels[];
	
} dungeon_struct;

dungeon_struct *create_dungeon(char *, uint32_t, uint32_t, uint32_t);
bool destruct_dungeon(dungeon_struct *);

/*******************************************************************************
*  
*  END dungeon.h
*  
*******************************************************************************/
#endif // _DUNGEON_H_
