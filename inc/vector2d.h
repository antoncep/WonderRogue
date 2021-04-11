#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_
/*******************************************************************************
*  
*  vector2d.h
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

typedef struct Vector2D vec2d_t;
struct Vector2D {
	
	float x;
	float y;
	
};

vec2d_t vector2d_normalize(vec2d_t);
vec2d_t vector2d_add(vec2d_t, vec2d_t);
vec2d_t vector2d_sub(vec2d_t, vec2d_t);
float vector2d_dot(vec2d_t, vec2d_t);

/*******************************************************************************
*  
*  END vector2d.h
*  
*******************************************************************************/
#endif // _VECTOR2D_H_
