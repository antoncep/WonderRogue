#include "hashseed.h"

int32_t strhash(char *string)
{
	int32_t hash = 17;
	int32_t indx = 0;
	
	while (string && string[indx]) {
		
		hash = (hash * 31) ^ string[indx++];
	}
	
	return hash;
}
