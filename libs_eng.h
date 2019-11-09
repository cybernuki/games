#ifndef LIBS_ENG
#define LIBS_ENG

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>

typedef struct x_renderer
{
	Display *dis;
	Window window;
	int screen;
} xrend_t;

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
	vert_t *vertx;
	polygon *polys;
	float scala;
	struct Transformation *transform;
} mesh;

typedef struct Scene
{
	struct Mesh *obj;
	struct Camara *camara;
	struct Viewport *viewp;
} scene;


mesh *readfile(char *name);
void print_vertex(const vert_t *vertices);
void print_polygons(polygon **polygons);
vert_t *project(vert_t *vertice, camara *cam, viewport *viewp);
vert_t *draw_vertex(mesh *obj, camara *cam, viewport *view, xrend_t *render);
vert_t *transf_vertex(mesh *obj, vert_t **new_vertlist);
vert_t sum_vec(vert_t vec1, vert_t vec2);
vert_t sus_vec(vert_t vec1, vert_t vec2);
vert_t mul_vec(vert_t vec1, vert_t vec2);
vert_t div_vec(vert_t vec1, vert_t vec2);
scene *init_engine();
#endif /* LIBS_ENG */
