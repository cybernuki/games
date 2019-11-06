#include <stdio.h>
#include "libs_eng.h"
void print_faces(face **faces);
void print_vertex(vert_t **vertices)
{
	int pos = 1;
	vert_t *v = *vertices;
	while (v != NULL)
	{
		printf("vertex #%d x: %f, y: %f, z: %f\n", pos, v->x, v->y, v->z);
		v = v->next;
		pos++;
	}
}

void print_polygons(polygon **polygons)
{
	int pos = 1;
	polygon *p = *polygons;
	if (p == NULL)
		printf("pailas");
	while (p != NULL)
	{
		print_faces(&p->faces);
		p = p->next;
		pos++;
	}
}

void print_faces(face **faces)
{

	face *f = *faces;

	while (f != NULL)
	{
		printf("%d/%d\n", f->a, f->b);
		f = f->next;
	}
}
