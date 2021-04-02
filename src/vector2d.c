#include <math.h>
#include "vector2d.h"

vector2d_struct vector2d_normalize(vector2d_struct vector)
{
	int32_t length = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	vector.x /= length;
	vector.y /= length;
	return vector;
}

vector2d_struct vector2d_add(vector2d_struct vector1, vector2d_struct vector2)
{
	vector1.x += vector2.x;
	vector1.y += vector2.y;
	return vector1;
}

vector2d_struct vector2d_sub(vector2d_struct vector1, vector2d_struct vector2)
{
	vector1.x -= vector2.x;
	vector1.y -= vector2.y;
	return vector1;
}

vector2d_struct vector2d_dot(vector2d_struct vector1, vector2d_struct vector2)
{
	vector2d_struct result;
	result = vector1;
	return result;
}
