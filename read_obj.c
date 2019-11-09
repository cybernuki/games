#include <stdio.h>
#include "libs_eng.h"
vert_t *get_vert(char *s, vert_t **vertices);
polygon *get_polys(char *s, polygon **pols);
face *get_face(char *pol, face **faces);
mesh *readfile(char *name)
{
	FILE *file;
	char *c = malloc(100);
	mesh *mes;
	vert_t *verx;
	polygon *polys;

	mes = malloc(sizeof(mesh));
	if (mes == NULL)
	{
		printf("Pailas con la mesh\n");
		return (NULL);
	}
	verx = NULL;
	polys = NULL;

	file = fopen(name, "r");
	if (file == NULL)
	{
		printf("File doesn't exists %s", name);
		return (0);
	}
	c = fgets(c, 99, file);

	while (c != NULL)
	{

		if (*c == 'v' && *(c + 1) == ' ')
		{
			if (get_vert(c, &verx) == NULL)
				printf("Paiiiilas con el vertex papa");
		}
		if (*c == 'f' && *(c + 1) == ' ')
			get_polys(c, &polys);
		c = fgets(c,99, file);
		}
	fclose(file);
	mes->vertx = verx;
	mes->polys = polys;
	return (mes);
}

vert_t *get_vert(char *s, vert_t **vertices)
{
	int p = 0, vert = 0;
	char ver[40];
	float verx[4];
	vert_t *vertex;
	vert_t *v = *vertices;

	vertex = malloc(sizeof(vert_t));

	if (vertex == NULL)
		return (NULL);

	s += 2;
	while(*s != '\0')
	{

		ver[p] = *s;

		if (*s == 32 || *s == 10)
		{
			ver[p] = '\0';
			verx[vert] =((float) atof(ver));
			vert++;
			p = 0;
		}
		else if (*s == 0)
			break;
		else
			p++;
		s++;
	}

	vertex->x = verx[0];
	vertex->y = verx[1];
	vertex->z = verx[2];
	vertex->next = NULL;

	if (*vertices == NULL)
	{
		vertex->next = *vertices;
		*vertices = vertex;
	}
	else
	{

		while (v != NULL)
		{

			if (v->next == NULL)
			{
				v->next = vertex;
				v = vertex;
				return (vertex);
			}
			v = v->next;

		}

	}
	return (vertex);
}

polygon *get_polys(char *s, polygon **pols)
{
	polygon *polys, *ps = *pols;
	int i = 0;
	char pol[8];
	face *faces;

	s += 2;
	polys = malloc(sizeof(polygon));
	faces = NULL;
	if (polys == NULL)
		return (NULL);
	while (*s != '\0')
	{
		pol[i] = *s;
		if (*s == ' ' || *s == '\n')
		{
			pol[i] = '\0';
			get_face(pol, &faces);
			i = 0;
		}
		else
			i++;
		s++;
	}
	polys->faces = faces;

	if (*pols == NULL)
	{
		polys->next = *pols;
		*pols = polys;
	}
	else
	{
		while (ps != NULL)
		{
			if (ps->next == NULL)
			{
				ps->next = polys;
				ps = polys;
				return (polys);
			}
			ps = ps->next;
		}
	}
	return (polys);
}


face *get_face(char *pol, face **faces)
{
	char p[10], *y = pol;
	int i = 0, a, b;
	face *fac, *fs = *faces;

	fac = malloc(sizeof(face));
	while (*y != '\0')
	{
		p[i] = *y;
		if (*y == '/')
		{
			p[i] = '\0';
			a = atoi(p);
			i = 0;
		}
		else
			i++;
		y++;
	}
	p[i] = '\0';
	b = atoi(p);
	fac->a = a;
	fac->b = b;
	if (*faces == NULL)
	{
		fac->next = *faces;
		*faces = fac;
	}
	else
	{
		while (fs != NULL)
		{
			if (fs->next == NULL)
			{
				fs->next = fac;
				fs = fac;
				return (fac);
			}
			fs = fs->next;
		}
	}
	return (fac);
}
