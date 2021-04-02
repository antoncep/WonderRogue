/*******************************************************************************
*  
*  vector2d.c
*  
*  author: AC Pretorius
*  date  : 01/04/2021
*  
*******************************************************************************/

#include <math.h>
#include "vector2d.h"

/*******************************************************************************
*  
*  take vector2d_struct to normalize and return new vector2d_struct
*  
*******************************************************************************/
vector2d_struct vector2d_normalize(vector2d_struct vector)
{
	float length = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	vector.x /= length;
	vector.y /= length;
	return vector;
}

/*******************************************************************************
*  
*  take 2 vector2d_structs to add and return new vector2d_struct
*  
*******************************************************************************/
vector2d_struct vector2d_add(vector2d_struct vector1, vector2d_struct vector2)
{
	vector1.x += vector2.x;
	vector1.y += vector2.y;
	return vector1;
}

/*******************************************************************************
*  
*  take 2 vector2d_structs to subtract and return new vector2d_struct
*  
*******************************************************************************/
vector2d_struct vector2d_sub(vector2d_struct vector1, vector2d_struct vector2)
{
	vector1.x -= vector2.x;
	vector1.y -= vector2.y;
	return vector1;
}

/*******************************************************************************
*  
*  take 2 vector2d_structs to calculate dot product and return new vector2d_struct
*  
*******************************************************************************/
vector2d_struct vector2d_dot(vector2d_struct vector1, vector2d_struct vector2)
{
	vector2d_struct result;
	result = vector1;
	return result;
}

/*******************************************************************************
*  
*  END vector2d.c
*  
*******************************************************************************/
