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

#include "engine.h"

#define DNAM_LENGTH 24

typedef enum DungeonTileSymbol dtile_sym_t;
enum DungeonTileSymbol {
	
	DSYM_EMPTY = ' ',
	DSYM_FLOOR = '.',
	DSYM_WALL  = '#',
	
};

typedef struct DungeonTile dtile_t;
struct DungeonTile {
	
	uint32_t bgcolor;
	uint32_t fgcolor;
	dtile_sym_t symbol;
	
};

typedef struct DungeonRoom droom_t;
struct DungeonRoom {
	
	vec2d_t position;
	vec2d_t size;
	dtile_t tiles[];
	
};

typedef enum DungeonLevelType dlevel_typ_t;
enum DungeonLevelType {
	
	DLVL_SAFE,
	DLVL_MONSTER,
	DLVL_BOSS,
	
};

typedef struct DungeonLevel dlevel_t;
struct DungeonLevel {
	
	uint32_t zlevel;
	dlevel_typ_t type;
	vec2d_t size;
	dtile_t tiles[];
	
};

typedef enum DungeonType dungeon_typ_t;
enum DungeonType {
	
	DNGN_FINITE,
	DNGN_INFINITE,
	
};

typedef struct Dungeon dungeon_t;
struct Dungeon {
	
	char name[DNAM_LENGTH];
	dungeon_typ_t type;
	uint32_t num_zlevels;
	dlevel_t *zlevels[];
	
};

dungeon_t *create_dungeon(str_t, uint32_t, uint32_t, uint32_t);
bool destruct_dungeon(dungeon_t *);

/*******************************************************************************
*  
*  END dungeon.h
*  
*******************************************************************************/
#endif // _DUNGEON_H_
