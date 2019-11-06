#include "libs_eng.h"


vert_t sum_vec(vert_t vec1, vert_t vec2)
{
	double x = vec1.x + vec2.x;
	double y = vec1.y + vec2.y;
	double z = vec1.z + vec2.z;

	vert_t result = {x, y, z, NULL};
	return (result);
}

vert_t sus_vec(vert_t vec1, vert_t vec2)
{
	double x = vec1.x - vec2.x;
	double y = vec1.y - vec2.y;
	double z = vec1.z - vec2.z;

	vert_t result = {x, y, z, NULL};
	return (result);

}

vert_t mul_vec(vert_t vec1, vert_t vec2)
{
	double x = vec1.x * vec2.x;
	double y = vec1.y * vec2.y;
	double z = vec1.z * vec2.z;

	vert_t result = {x, y, z, NULL};
	return (result);

}

vert_t div_vec(vert_t vec1, vert_t vec2)
{
	double x = vec1.x / vec2.x;
	double y = vec1.y / vec2.y;
	double z = vec1.z / vec2.z;

	vert_t result = {x, y, z, NULL};
	return (result);

}
