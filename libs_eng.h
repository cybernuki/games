#ifndef LIBS_ENG
#define LIBS_ENG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
typedef struct Vertx
{
	float x;
        float y;
        float z;
	struct Vertx *next;
} vert_t;


typedef struct Transformation
{
	vert_t *translation;
	vert_t *rotation;
}transform;

typedef struct Camara
{
	vert_t *target;
	vert_t *up;
	vert_t *center;
	float zoom;
	struct Transformation *transform;
} camara;

typedef struct Viewport
{
	int width;
	int height;
	vert_t *pos;
	vert_t *up;
	struct Transformation *transform;
} viewport;

typedef struct Face
{
	int a;
	int b;
	struct Face *next;
} face;

typedef struct Polygon
{
	struct Face *faces;
	struct Polygon *next;
} polygon;


typedef struct Mesh
{
	vert_t **vertx;
	polygon *polys;
	struct Transformation *transform;
} mesh;
mesh *readfile(char *name);
void print_vertex(vert_t **vertices);
void print_polygons(polygon **polygons);
vert_t project(vert_t vertice, camara *cam, viewport *viewp);
void draw_vertex(vert_t *vertex, camara *cam, viewport *view);
#endif /* LIBS_ENG */
