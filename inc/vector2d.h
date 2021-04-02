#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

#include <stdint.h>

typedef struct {
	
	int32_t x;
	int32_t y;
	
} vector2d_struct;

vector2d_struct vector2d_normalize(vector2d_struct vector);
vector2d_struct vector2d_add(vector2d_struct vector1, vector2d_struct vector2);
vector2d_struct vector2d_sub(vector2d_struct vector1, vector2d_struct vector2);
vector2d_struct vector2d_dot(vector2d_struct vector1, vector2d_struct vector2);

#endif // _VECTOR2D_H_
