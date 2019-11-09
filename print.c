#include <stdio.h>
#include "libs_eng.h"
void print_faces(face **faces);
void print_vertex(const vert_t *vertices)
{
	int pos = 0;
	const vert_t *v = vertices;
	while (v != NULL)
	{
		printf("Vertex %d x: %9f, y: %9f, z: %9f\n", pos, v->x, v->y, v->z);
		if (v->next == NULL)
			return;
		v = v->next;
		pos++;
	}
	return;
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
