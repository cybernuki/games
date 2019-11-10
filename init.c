#include <GL/glut.h>
#include "libs_eng.h"

scene *init_engine()
{
	camara *cam = malloc(sizeof(camara));
	vert_t *c_target = malloc(sizeof(vert_t));
	vert_t *c_up = malloc(sizeof(vert_t));
	vert_t *c_center = malloc(sizeof(vert_t));

	c_center->x = 0;
	c_center->y = 0;
	c_center->z = -10;
	c_up->x = 0;
	c_up->y = 2;
	c_up->z = 0;
	c_target->x = 0.0101;
	c_target->y = 0.0101;
	c_target->z = 6.0101;

	vert_t *c_rotation = malloc (sizeof(vert_t));
	c_rotation->x = 0;
	c_rotation->y = 0;
	c_rotation->z = 0;

	vert_t *c_translation = malloc (sizeof(vert_t));
	c_translation->x = 0;
	c_translation->y = 0;
	c_translation->z = 0;

       	cam->target = c_target;
	cam->up = c_up;
	cam->center = c_center;
	cam->zoom =  2.4;
	transform *ctr = malloc(sizeof(transform));
	ctr->rotation = c_rotation;
	ctr->translation = c_translation;
	cam->transform = ctr;

	printf("camara done\n");

       	printf("setting viewport\n");
	viewport *viewp = malloc(sizeof(viewport));
	viewp->width = 300;
	viewp->height = 300;
	viewp->pos = malloc(sizeof(vert_t));
	viewp->pos->x = 0;
	viewp->pos->y = 0;
	viewp->pos->z = cam->center->z + 30;
	viewp->up = malloc(sizeof(vert_t));
	viewp->up->x = 0;
	viewp->up->y = -150;
	viewp->up->z = cam->center->z + 30;
       	printf("viewport done\n");

	mesh *obj;
       	printf("transf setted\n");
	obj = readfile("objects/cubo.txt");
	printf("file readed\n");

	vert_t *obj_trans = malloc(sizeof(vert_t));
	obj_trans->x = 0;
	obj_trans->y = 0;
	obj_trans->z = 6;


	vert_t *obj_rotat = malloc(sizeof(vert_t));
	obj_rotat->x = 0;
	obj_rotat->y = 0;
	obj_rotat->z = 0;

	transform *tr = malloc(sizeof(transform));
	tr->translation = obj_trans;
	tr->rotation = obj_rotat;
	obj->transform = tr;
	obj->scala = 1;
	obj->origin = set_center_origin(&(obj->vertx));

       	printf("mesh  done\n");

	scene *scen = malloc(sizeof(scene));
	scen->obj = obj;
	scen->camara = cam;
	scen->viewp = viewp;

	printf("returning screen\n");
	return (scen);
}
