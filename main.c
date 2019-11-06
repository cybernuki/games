#include <GL/glut.h>
#include "libs_eng.h"

void displayMe(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	printf("setting camara\n");
	camara *cam = malloc(sizeof(camara));
	vert_t c_target = {0,0,0, NULL}, *tar = &c_target;
	vert_t c_up = {0,0,0, NULL}, *upc = &c_up;
	vert_t c_center = {0,0,2, NULL}, *cen = &c_center;;
	vert_t c_rotation = {0,0,3.1416, NULL}, *rot = &c_rotation;;
	cam->target = tar;
	cam->up = upc;
	cam->center = cen;
	cam->zoom = (float) 1.0;
	transform *ctr = malloc(sizeof(transform));
	ctr->rotation = rot;
	ctr->translation = cen;
	cam->transform = ctr;

	printf("camara done\n");

       	printf("setting viewport\n");
	viewport *viewp = malloc(sizeof(viewport));
	viewp->width = 300;
	viewp->height = 200;
	viewp->pos = malloc(sizeof(vert_t));
	viewp->pos->x = 0;
	viewp->pos->y = 150;
	viewp->pos->z = cam->center->z + 100;
	viewp->up = malloc(sizeof(vert_t));
	viewp->up->x = 0;
	viewp->up->y = 180;
	viewp->up->z = 0;
       	printf("viewport done\n");

	mesh *obj;
	transform *tr;
	tr = malloc(sizeof(transform));
	vert_t translation = {0,0,0, NULL};
	vert_t rotation = {0,0,0, NULL};
	tr->translation = &translation;
	tr->rotation = &rotation;

	obj = readfile("objects/cubo.txt");
	obj->transform = tr;

	draw_vertex(*(obj->vertx), cam, viewp);
/*
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Snake");
	glutDisplayFunc(displayMe);
	glutMainLoop(); */
	return (0);
}
