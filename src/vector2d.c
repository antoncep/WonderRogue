/*******************************************************************************
*  
*  vector2d.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include "vector2d.h"
#include <math.h>

/*******************************************************************************
*  
*  take vec2d_t to normalise and return new vec2d_t
*  
*******************************************************************************/
vec2d_t vector2d_normalise(vec2d_t vector_v)
{
	float length = sqrt(pow(vector_v.x, 2) + pow(vector_v.y, 2));
	vector_v.x /= length;
	vector_v.y /= length;
	return vector_v;
}

/*******************************************************************************
*  
*  take 2 vec2d_t to add and return new vec2d_t
*  
*******************************************************************************/
vec2d_t vector2d_add(vec2d_t vector_v, vec2d_t vector_w)
{
	vector_v.x += vector_w.x;
	vector_v.y += vector_w.y;
	return vector_v;
}

/*******************************************************************************
*  
*  take 2 vec2d_t to subtract and return new vec2d_t
*  
*******************************************************************************/
vec2d_t vector2d_sub(vec2d_t vector_v, vec2d_t vector_w)
{
	vector_v.x -= vector_w.x;
	vector_v.y -= vector_w.y;
	return vector_v;
}

/*******************************************************************************
*  
*  take 2 vec2d_t to calculate dot product and return float
*  
*******************************************************************************/
float vector2d_dot(vec2d_t vector_v, vec2d_t vector_w)
{
	vector_v.x *= vector_w.x;
	vector_v.y *= vector_w.y;
	return vector_v.x + vector_v.y;
}

/*******************************************************************************
*  
*  END vector2d.c
*  
*******************************************************************************/
