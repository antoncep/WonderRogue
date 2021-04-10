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

typedef struct vector2d_t vec2d_t;

typedef enum dtile_symbol_t dtile_symbol_enum;
enum dtile_symbol_t {
	
	DSYM_EMPTY = ' ',
	DSYM_FLOOR = '.',
	DSYM_WALL  = '#',
	
};

typedef struct dtile_t dtile_struct;
struct dtile_t {
	
	uint32_t bgcolor;
	uint32_t fgcolor;
	dtile_symbol_enum symbol;
	
};

typedef struct droom_t droom_struct;
struct droom_t {
	
	vec2d_t position;
	vec2d_t size;
	dtile_struct tiles[];
	
};

typedef enum dlevel_type_t dlevel_type_enum;
enum dlevel_type_t {
	
	DLVL_SAFE,
	DLVL_MONSTER,
	DLVL_BOSS,
	
};

typedef struct dlevel_t dlevel_struct;
struct dlevel_t {
	
	uint32_t zlevel;
	dlevel_type_enum type;
	vec2d_t size;
	dtile_struct tiles[];
	
};

typedef enum dungeon_type_t dungeon_type_enum;
enum dungeon_type_t {
	
	DNGN_FINITE,
	DNGN_INFINITE,
	
};

typedef struct dungeon_t dungeon_struct;
struct dungeon_t {
	
	char name[DNAM_LENGTH];
	dungeon_type_enum type;
	uint32_t num_zlevels;
	dlevel_struct *zlevels[];
	
};

dungeon_struct *create_dungeon(char *, uint32_t, uint32_t, uint32_t);
bool destruct_dungeon(dungeon_struct *);

/*******************************************************************************
*  
*  END dungeon.h
*  
*******************************************************************************/
#endif // _DUNGEON_H_
