#include "libs_eng.h"
vert_t *zoom_p(camara *cam, vert_t *vertice);
vert_t *translate_p(camara *cam, vert_t *vertice);
vert_t *rotate_p(camara *cam, vert_t vertice);
vert_t *pr(vert_t *point, viewport *viewp);
vert_t project(vert_t vertice, camara *cam, viewport *viewp)
{

	vert_t  *p;
	p = rotate_p(cam, vertice);

	p = translate_p(cam, p);

	p = zoom_p(cam, p);

	printf("vertex done\n");

	p->x = (p->x*viewp->pos->z)/p->z;
	p->y = (p->y*viewp->pos->z)/p->z;
        p->z = (p->z*viewp->pos->z)/p->z;
/*	printf("vert: x: %f y: %f\n%f\n", p->x, p->y, p->z);*/
	p = pr(p, viewp);
	return (*p);
}
vert_t *pr(vert_t *point, viewport *viewp)
{
	float x = ((point->x*640)/viewp->width) + 320;
	float y = ((point->y*480)/viewp->height) + 240;
	vert_t *r = &((vert_t) {x, y, 0, NULL});
	return (r);
}

vert_t *zoom_p(camara *cam, vert_t *vertice)
{

	(void) cam;
        float scale = powf(1, 2);

	vertice->x = vertice->x * scale;
	vertice->y = vertice->y * scale;
	vertice->z = vertice->z;

	return (vertice);
}

vert_t *translate_p(camara *cam, vert_t *vertice)
{

	vert_t temp = {0,0,0,NULL};
	temp.x = vertice->x + cam->center->x;
	temp.y = vertice->y + cam->center->y;
	temp.z = vertice->z + cam->center->z;

	vert_t *r = &temp;
	return (r);
}

vert_t *rotate_p(camara *cam, vert_t vertice)
{

	vert_t *center = cam->center;

        float tempx = vertice.x - center->x;
        float tempy = vertice.y - center->y;
	float tempz = vertice.z - center->z;


        float overx = cam->transform->rotation->x;
        float overy = cam->transform->rotation->y;
        float overz = cam->transform->rotation->z;

        float i = (1)*(tempx)+(0)*(tempy)+(0)*(tempz);
	float j = (0)*(tempx)+(cos(overx))*(tempy)+(-(sin(overx)))*(tempz);
        float k = (0)*(tempx)+(sin(overx))*(tempy)+(cos(overx))*(tempz);

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

	vert_t res = {tempx, tempy, tempz, NULL};
	vert_t *r = &res;
	return (r);

}
