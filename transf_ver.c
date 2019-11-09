#include "libs_eng.h"

vert_t rotate(vert_t vertex, mesh *obj)
{
	printf("%s %d:  rotating \n", __FILE__,__LINE__);
	double tempx = vertex.x;
	double tempy = vertex.y;
	double tempz = vertex.z;

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
	return (result);

}

vert_t scalar(vert_t vert, float scale)
{
	printf("%s %d:  scaling \n", __FILE__,__LINE__);
	vert_t scal = {scale, scale, scale, NULL};
	return(mul_vec(vert, scal));
}
vert_t translate(vert_t vert, vert_t trans)
{
	printf("%s %d:  translating \n", __FILE__,__LINE__);
	vert_t res = sum_vec(vert, trans);
	return (res);
}
vert_t *add_vertex_node(vert_t **newlist, vert_t vertex)
{

	vert_t *new_vertex = malloc(sizeof(vert_t));
	vert_t *giro = *newlist;

	if (new_vertex == NULL)
	{
		return (NULL);
	}

	new_vertex->x = vertex.x;
	new_vertex->y = vertex.y;
	new_vertex->z = vertex.z;
	new_vertex->next = NULL;

	if (*newlist == NULL)
	{

		new_vertex->next = *newlist;
		*newlist = new_vertex;
	}
	else
	{

		while (giro->next != NULL)
		{
			giro = giro->next;
		}
		giro->next = new_vertex;
	}

	return (new_vertex);
}
vert_t *transf_vertex(mesh *obj, vert_t **new_vertlist)
{
	vert_t *vertices = obj->vertx;
	vert_t *newlist;
	vert_t  dummy;
	int pos = 0;

	newlist = NULL;

	while (vertices != NULL)
	{

		dummy = translate(
			rotate(
			scalar(*vertices, obj->scala),
			obj),
			*obj->transform->translation);
		add_vertex_node(&newlist, dummy);
		printf("%s %d: vert %d:  x %f y %f z %f\n",__FILE__, __LINE__,
		       pos, dummy.x, dummy.y, dummy.z);

		vertices = vertices->next;
		pos++;
	}
	if (newlist != NULL)
	{
		printf("%s %d:  nodes ready\n", __FILE__, __LINE__);
		*new_vertlist = newlist;
		return (newlist);
	}
	else
	{
		printf("%s %d:  nodes fail\n", __FILE__, __LINE__);
		return (NULL);
	}
}
