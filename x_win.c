#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs_eng.h"

void rend(Display *dis, Window window, int screen);
void scanline(polygon **polys, vert_t **list, Display *dis, Window window, int screen);
void print_v(vert_t *ver, int line);

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
	XSetForeground(dis, DefaultGC(dis, screen), 0x00000000);
	*(scn->camara->target) = get_target_origin(scn->obj);
	vrtx = draw_vertex(&(scn->obj), scn->camara,
			   scn->viewp);
	int pos ='1';
	vert_t *vt = *(&(vrtx));
	while (vt != NULL)
	{
/*		printf("vert: %c\n", pos);*/
/*		XFillRectangle(dis, window,
		DefaultGC(dis, screen), vt->x, vt->y, 4 , 4);*/
/*		XDrawString(dis, window, DefaultGC(dis, screen),
			    vt->x, vt->y,
			    (char *) &pos, 1);*/
		vt = vt->next;
		pos++;

	}
/*	print_polygons(&(scn->obj->polys));*/
	XSetForeground(dis, DefaultGC(dis, screen), 0x00000000);
	scanline(&(scn->obj->polys), &vrtx, dis,window, screen);

}

vert_t *get_vertx(int pos, vert_t *list)
{
	printf("vertx # %d\n", pos);
	int indx = 1;
	while (list)
	{
		if (pos == indx)
		{
			return (list);
		}
		else
		{
			indx++;
			list = list->next;
		}
	}
	return (NULL);
}

void print_v(vert_t *ver, int line)
{
	printf("%s %d:  x: %.2f y: %.2f z: %.2f\n",__FILE__, line, ver->x, ver->y, ver->z);
}

void scanline(polygon **polys, vert_t **list, Display *dis, Window window, int screen)
{
	printf("init scanline\n");
	polygon *ps = *polys;
	vert_t *vrtx = *list;
	vert_t *arr[3];
	int position = 1;

	const char *font = "*schumacher*-16-*";
	XFontStruct *f = XLoadQueryFont(dis, font);
	if (! f )
		f = XLoadQueryFont(dis, "fixed");
	XSetFont(dis, DefaultGC(dis, screen), f->fid);
	while (ps != NULL)
	{
		vrtx = *list;
		arr[0] = get_vertx(ps->faces->a,
				      vrtx);

		arr[1] = get_vertx(ps->faces->next->a,
				      vrtx);

		arr[2] = get_vertx(ps->faces->next->next->a,
				      vrtx);
		vert_t *tmp;
		if (arr[1]->y < arr[0]->y)
		{
			tmp = arr[0];
			arr[0] = arr[1];
			arr[1] = tmp;
			printf("flipped 1 to 0\n");
		}

		if (arr[2]->y < arr[1]->y)
		{
			tmp = arr[1];
			arr[1] = arr[2];
			arr[2] = tmp;
			printf("flipped 2 to 1\n");
		}
		if (arr[1]->y < arr[0]->y)
		{
			tmp = arr[0];
			arr[0] = arr[1];
			arr[1] = tmp;
			printf("flipped 1 to 0\n");
		}

		if ((position) != 0)
		{
/*		XDrawString(dis, window, DefaultGC(dis, screen),
			    arr[0]->x + 4, arr[0]->y - 4,
			    "0", 1);
		XDrawString(dis, window, DefaultGC(dis, screen),
			    arr[1]->x + 4, arr[1]->y - 4,
			    "1", 1);
		XDrawString(dis, window, DefaultGC(dis, screen),
			    arr[2]->x + 4, arr[2]->y - 4,
			    "2", 1);*/
		for (int y = 0; y < (arr[2]->y - arr[0]->y); y++)
		{

			float r;
			float Y = arr[2]->y - arr[0]->y;
			float X = arr[2]->x - arr[0]->x;
			printf("%.2f %.2f %.2f\n", arr[0]->x, arr[1]->x, arr[2]->x);
			r = ((y * X) / Y) + arr[0]->x;
			printf("result x %.2f  ", r);
			XSetForeground(dis, DefaultGC(dis, screen), 0x00fb1010);
			/*	XFillRectangle(dis, window,
				   DefaultGC(dis, screen),
				       r , y + arr[0]->y,
				       4, 4);*/
			float tmpX, tmpY, tmpR = r;
			if ((y + arr[0]->y) >= arr[1]->y)
			{
				printf(" > ");

				X = arr[2]->x - arr[1]->x;
				Y = arr[2]->y - arr[1]->y;
				tmpX = arr[1]->x;
				tmpY = y - (arr[1]->y - arr[0]->y);
				XSetForeground(dis, DefaultGC(dis, screen), 0x0034acfb);
			}
			else
			{
				X = arr[1]->x - arr[0]->x;
				Y = arr[1]->y - arr[0]->y;
				tmpX = arr[0]->x;
				tmpY = y;
				XSetForeground(dis, DefaultGC(dis, screen), 0x00fb10ac);

			}
			r = ((tmpY * X) / Y);
			r += tmpX;
			printf("result x %.2f tmpy: %.2f\n", r, tmpY);


/*			XFillRectangle(dis, window,
				   DefaultGC(dis, screen),
				       r , y + arr[0]->y,
				       4, 4);*/


			XDrawLine(dis, window, DefaultGC(dis, screen),
			  (int) tmpR, (int) y + arr[0]->y,
			  (int) r, (int) y + arr[0]->y);

		}

		}

				XSetForeground(dis, DefaultGC(dis, screen), 0x00000000);
	      	XDrawLine(dis, window, DefaultGC(dis, screen),
			  (int) arr[0]->x, (int) arr[0]->y,
			  (int) arr[1]->x, (int) arr[1]->y);


		XDrawLine(dis, window, DefaultGC(dis, screen),
			  (int) arr[1]->x, (int) arr[1]->y,
			  (int) arr[2]->x, (int) arr[2]->y);

		XDrawLine(dis, window, DefaultGC(dis, screen),
			  (int) arr[2]->x, (int) arr[2]->y,
			  (int) arr[0]->x, (int) arr[0]->y);

		print_v(arr[0], __LINE__);
		print_v(arr[1], __LINE__);
		print_v(arr[2], __LINE__);



		printf("\n");
		position++;
		ps = ps->next;
	}

}
