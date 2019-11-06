#include <stdio.h>
#include "libs_eng.h"

void draw_polygons(vert_t **vertex)
{
	vert_t *l = *vertex;
	glBegin(GL_POLYGON);
	while (l != NULL)
	{
		glVertex2f(l->x, l->y);
		l = l->next;
	}
	glEnd();
	glFlush();
}

void draw_vertex(vert_t *vertex, camara *cam, viewport *view)
{
	vert_t *v = vertex;
	int pos = 0;
	while (v != NULL)
	{
		vert_t p = project(*v, cam ,view);
		printf("vertx # %d x: %d y: %d z: %d", pos, (int) p.x, (int) p.y,(int) p.z);
		v = v->next;
		pos++;
	}
}