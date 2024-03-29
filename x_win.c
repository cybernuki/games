#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs_eng.h"

void rend(Display *display, Window window, int screen);
void scanline(polygon **polys, vert_t **list, Display *display, Window window, int screen);
void print_v(vert_t *ver, int line);

scene *scn;

int main(void)
{
	Display *dis;
	Window window;
	XEvent event;
	int screen;
	scn = init_engine();
	printf("Engine done\n");
	dis = XOpenDisplay(NULL);
	if (dis == NULL)
	  {
	    printf("Pailas display\n");
	    exit(1);
	  }
	printf("Display Opened\n");
	screen = DefaultScreen(dis);
	printf("screen setted\n");
	window = XCreateSimpleWindow(dis, RootWindow(dis, screen),10, 10 , 400, 400, 1, BlackPixel(dis, screen), WhitePixel(dis, screen));
	screen = DefaultScreen(dis);
	XSelectInput(dis, window, ExposureMask | KeyPressMask);
	printf("window created\n");
	XMapWindow(dis, window);
	printf("map created\n");
	
	
	while (1)
	{
	  printf("looping\n");
	  XNextEvent(dis, &event);
	  if (event.type == Expose)
	  {
	    printf("Expose\n");
	    rend(dis, window, screen);
	  }
		
	if (event.type == KeyPress)
	{
	  if (event.xkey.keycode == 0x99)
	  break;
	  key_pressed(event.xkey.keycode);
	  rend(dis, window, screen);
	}
	}

	return (0);
}

void rend(Display *display, Window window, int screen)
{
	vert_t *vrtx;
	XClearWindow(display, window);
	*(scn->camara->target) = get_target_origin(scn->obj);
	vrtx = draw_vertex(&(scn->obj), scn->camara,
			   scn->viewp);
	int pos ='1';
	vert_t *vt = *(&(vrtx));
	while (vt != NULL)
	{
		vt = vt->next;
		pos++;

	}


	scanline(&(scn->obj->polys), &vrtx, display, window, screen);

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

void scanline(polygon **polys, vert_t **list, Display *display, Window window, int screen)
{
	(void) window;
	(void) display;
	(void) screen;
	printf("init scanline\n");
	polygon *ps = *polys;
	vert_t *vrtx = *list;
	vert_t *arr[3];
	int position = 1;

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
		for (int y = 0; y < (arr[2]->y - arr[0]->y); y++)
		{

			float r;
			float Y = arr[2]->y - arr[0]->y;
			float X = arr[2]->x - arr[0]->x;
			printf("%.2f %.2f %.2f\n", arr[0]->x, arr[1]->x, arr[2]->x);
			r = ((y * X) / Y) + arr[0]->x;
			printf("result x %.2f  ", r);
			float tmpX, tmpY, tmpR = r;
			if ((y + arr[0]->y) >= arr[1]->y)
			{
				printf(" > ");

				X = arr[2]->x - arr[1]->x;
				Y = arr[2]->y - arr[1]->y;
				tmpX = arr[1]->x;
				tmpY = y - (arr[1]->y - arr[0]->y);
			}
			else
			{
				X = arr[1]->x - arr[0]->x;
				Y = arr[1]->y - arr[0]->y;
				tmpX = arr[0]->x;
				tmpY = y;

			}
			r = ((tmpY * X) / Y);
			r += tmpX;
			(void) tmpR;
			printf("result x %.2f tmpy: %.2f\n", r, tmpY);
			XDrawLine(display, window, DefaultGC(display, screen),
				  arr[0]->x , arr[0]->y,
				  arr[1]->x , arr[1]->y);
			XDrawLine(display, window, DefaultGC(display, screen),
				  arr[1]->x , arr[1]->y,
				  arr[2]->x , arr[2]->y);
			XDrawLine(display, window, DefaultGC(display, screen),
				  arr[2]->x , arr[2]->y,
				  arr[0]->x , arr[0]->y);




		}

		}

		print_v(arr[0], __LINE__);
		print_v(arr[1], __LINE__);
		print_v(arr[2], __LINE__);



		printf("\n");
		position++;
		ps = ps->next;
	}

}
