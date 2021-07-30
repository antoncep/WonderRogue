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

#define VEC2D_UP (vec2d_t){ 0.0, -1.0 }
#define VEC2D_DOWN (vec2d_t){ 0.0, 1.0 }
#define VEC2D_LEFT (vec2d_t){ -1.0, 0.0 }
#define VEC2D_RIGHT (vec2d_t){ 1.0, 0.0 }

typedef struct Vector2D vec2d_t;
struct Vector2D {
	
	double x;
	double y;
};

vec2d_t vector2d_normalise(vec2d_t);
vec2d_t vector2d_add(vec2d_t, vec2d_t);
vec2d_t vector2d_sub(vec2d_t, vec2d_t);
double vector2d_dot(vec2d_t, vec2d_t);

/*******************************************************************************
*  
*  END vector2d.h
*  
*******************************************************************************/
#endif // _VECTOR2D_H_
