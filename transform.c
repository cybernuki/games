#include "libs_eng.h"

vert_t *rotate(vert_t *vertex, mesh *obj)
{
	
	double tempx = vertex->x;
	double tempy = vertex->y;
	double tempz = vertex->z;

	double overx = obj->transform->rotation->x;
	double overy = obj->transform->rotation->y;
	double overz = obj->transform->rotation->z;

	double i = (1)*(tempx)+(0)*(tempy)+(0)*(tempz);
	double j = (0)*(tempx)+(cos(overx))*(tempy)+(sin(overx))*(tempz);
	double k = (0)*(tempx)+(sin(overx))*(tempy)+(cos(overx))*(tempz);
	tempx = i;
	tempy = j;
	tempz = k;

	i = (cos(overy))*(tempx)+(0)*(tempy)+(sin(overy))*(tempz);
	j = (0)*(tempx)+(1)*(tempy)+(0)*(tempz);
	k = (-(sin(overy)))*(tempx)+(0)*(tempy)+(cos(overy))*(tempz);

	tempx = i;
	tempy = j;
	tempz = k;

	i = (cos(overz))*(tempx)+(-(sin(overz)))*(tempy)+(0)*(tempz);
	j = (sin(overz))*(tempx)+(cos(overz))*(tempy)+(0)*(tempz);
	k = (0)*(tempx)+(0)*(tempy)+(1)*(tempz);

	tempx = i;
	tempy = j;
	tempz = k;

	vert_t result = {tempx, tempy, tempz, NULL};
	vert_t *r = &result;
	return (r);

}

void translate()
{

}
