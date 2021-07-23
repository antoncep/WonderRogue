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
	
	dtile_sym_t symbol;
	uint32_t bgcolour;
	uint32_t fgcolour;
};

typedef struct DungeonRoom droom_t;
struct DungeonRoom {
	
	vec2d_t position;
	vec2d_t size;
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

typedef struct Dungeon dungeon_t;
struct Dungeon {
	
	char name[DNAM_LENGTH];
	uint32_t num_zlevels;
	uint32_t cur_zlevel;
	dlevel_t* zlevels[];
};

dungeon_t* create_dungeon(str_t, uint32_t, uint32_t, uint32_t);
bool destruct_dungeon(dungeon_t*);

/*******************************************************************************
*  
*  END dungeon.h
*  
*******************************************************************************/
#endif // _DUNGEON_H_
