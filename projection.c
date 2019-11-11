#include "libs_eng.h"
vert_t *zoom_p(camara *cam, vert_t *vertice);
vert_t *translate_p(camara *cam, vert_t *vertice);
vert_t *rotate_p(camara *cam, vert_t *vertice);
vert_t *pr(viewport *viewp, vert_t *point);
vert_t *project(vert_t *vertice, camara *cam, viewport *viewp)
{

	vert_t *p;
/*	printf("%s %d:  initial: %.2f %.2f %.2f\n", __FILE__, __LINE__, vertice->x, vertice->y, vertice->z);	*/
	p = rotate_p(cam, vertice);

	p = translate_p(cam, p);

	p = zoom_p(cam, p);
/*	printf("\033[36m%s %d:  zoomed: %.2f %.2f %.2f\n", __FILE__, __LINE__, p->x, p->y, p->z);	*/

	p->x = (( p->x)*(viewp->pos->z + 1))/p->z;
	p->y = (( p->y)*(viewp->pos->z + 1))/p->z;
	p->z = (( p->z)*(viewp->pos->z + 1))/p->z;

/*	printf("\033[36m%s %d:  projected: %.2f %.2f %.2f\n", __FILE__, __LINE__, p->x, p->y, p->z);	*/
	p = pr(viewp, p);

/*	printf("%s %d:  vert: %f %f %f\n", __FILE__, __LINE__, p>x, p->y, p->z);*/
	return (p);
}
vert_t *pr(viewport *viewp, vert_t *point)
{
/*    printf("%s %d:  before: %d %d point: %.2f %.2f %.2f\n", __FILE__, __LINE__, viewp->width, viewp->height, point->x, point->y, point->z);*/

	point->x = ((point->x*400)/viewp->width)+200;
	point->y = ((point->y*400)/viewp->height)+200;
	/*       printf("%s %d:  viewp: %d %d point: %.2f %.2f %.2f\n", __FILE__, __LINE__, viewp->width, viewp->height, point->x, point->y, point->z);*/


	return (point);

}

vert_t *zoom_p(camara *cam, vert_t *vertice)
{

        float scale = powf(cam->zoom, 2);
/*	printf("\033[33m%s %d:  before zoom: %.2f %.2f %.2f\n", __FILE__, __LINE__, vertice->x, vertice->y, vertice->z);*/
	vertice->x = vertice->x * scale;
	vertice->y = vertice->y * scale;
	vertice->z = vertice->z * 1;
/*	printf("\033[32m%s %d:  zoomed: %.2f %.2f %.2f\n", __FILE__, __LINE__, vertice->x, vertice->y, vertice->z);*/
	return (vertice);
}

vert_t *translate_p(camara *cam, vert_t *vertice)
{

/*	printf("\033[33m%s %d:  before transl: %.2f %.2f %.2f\n", __FILE__, __LINE__, vertice->x, vertice->y, vertice->z);*/

        vertice->x += cam->center->x + cam->transform->translation->x;
	vertice->y += cam->center->y + cam->transform->translation->y;
	vertice->z += cam->center->z + cam->transform->translation->z;

/*	printf("\033[33m%s %d:  translated: %.2f %.2f %.2f\n", __FILE__, __LINE__, vertice->x, vertice->y, vertice->z);*/
	return (vertice);
}

vert_t *rotate_p(camara *cam, vert_t *vertice)
{
        float tempx = vertice->x - cam->center->x;
        float tempy = vertice->y - cam->center->y;
	float tempz = vertice->z - cam->center->z;


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

	vertice->x = tempx;
        vertice->y = tempy;
	vertice->z = tempz;


/*	printf("\033[34m%s %d:  rotated: %.2f %.2f %.2f\n", __FILE__, __LINE__, vertice->x, vertice->y, vertice->z);*/

	return (vertice);

}
