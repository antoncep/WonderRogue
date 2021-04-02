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

typedef struct vector2d_struct {
	
	float x;
	float y;
	
} vector2d_struct;

vector2d_struct vector2d_normalize(vector2d_struct);
vector2d_struct vector2d_add(vector2d_struct, vector2d_struct);
vector2d_struct vector2d_sub(vector2d_struct, vector2d_struct);
vector2d_struct vector2d_dot(vector2d_struct, vector2d_struct);

/*******************************************************************************
*  
*  END vector2d.h
*  
*******************************************************************************/
#endif // _VECTOR2D_H_
