#include <stdio.h>
#include "libs_eng.h"
vert_t *project_vertex(vert_t **vertx, camara *cam, viewport *view);
void draw_polygons(vert_t **vertex)
{
	(void) vertex;
}

vert_t *draw_vertex(mesh *obj, camara *cam, viewport *view)
{
	vert_t *transformed_vertx, *head;

	transformed_vertx = NULL;
/*	print_vertex((obj->vertx));*/
	head = transf_vertex(obj, &transformed_vertx);
        project_vertex(&head, cam, view);
/*	print_vertex(head);*/
	return (head);
}

vert_t *project_vertex(vert_t **vertx, camara *cam, viewport *view)
{
	vert_t *list = *vertx;

	while (list != NULL)
	{
		vert_t *pr = project(list, cam, view);

		list->x = pr->x;
		list->y = pr->y;
		list->z = pr->z;
				printf("\033[0m%s %d:  v: %.2f %.2f %.2f\n", __FILE__,__LINE__,
		       list->x, list->y, list->z);
		list = list->next;
	}
	return (*vertx);
}
