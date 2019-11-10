#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs_eng.h"

void rend(Display *dis, Window window, int screen);

scene *scn;

int main(void)
{
	Display *dis;
	Window window;
	XEvent event;
	scn = init_engine();
	int screen;

	dis = XOpenDisplay(NULL);
	if (dis == NULL)
	{
		printf("\033[31mError opening display\n\033[0m");
		exit(1);
	}
	screen = DefaultScreen(dis);
	window = XCreateSimpleWindow(dis, RootWindow(dis, screen), 0, 0,
				     600, 600, 1, BlackPixel(dis, screen),
				     WhitePixel(dis, screen));
	XSelectInput(dis, window, ExposureMask | KeyPressMask);
	XMapWindow(dis, window);
	xrend_t *render = malloc(sizeof(xrend_t));
	render->dis = dis;
	render->window = window;
	render-> screen = screen;
	while (1)
	{
		XNextEvent(dis, &event);
		if (event.type == Expose)
		{
			printf("%s %d:  redrawing\n", __FILE__,__LINE__);
			rend(dis, window, screen);
		}
		if (event.type == KeyPress)
		{
		    if (key_pressed(event.xkey.keycode) == 1)
		    {
			    rend(dis, window, screen);
		    }
		    if (event.xkey.keycode == 0x09)
			break;
		}
	}
	XCloseDisplay(dis);
	return (0);
}

void rend(Display *dis, Window window, int screen)
{
	vert_t *vrtx;
	XClearWindow(dis, window);
	*(scn->camara->target) = get_target_origin(scn->obj);
	vrtx = draw_vertex(scn->obj, scn->camara,
			   scn->viewp);
	int pos ='1';
	while (vrtx != NULL)
	{
/*		printf("vert: %c\n", pos);*/
		XFillRectangle(dis, window,
		DefaultGC(dis, screen), vrtx->x, vrtx->y, 4 , 4);
		XDrawString(dis, window, DefaultGC(dis, screen),
			    vrtx->x, vrtx->y,
			    (char *) &pos, 1);
		vrtx = vrtx->next;
		pos++;

	}
	print_polygons(&(scn->obj->polys));
}
