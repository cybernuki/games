#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs_eng.h"

void rend(SDL_Window *window, SDL_Renderer *renderer);
void scanline(polygon **polys, vert_t **list, SDL_Window *window, SDL_Renderer *renderer);
void print_v(vert_t *ver, int line);

scene *scn;

int main(void)
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;


	scn = init_engine();
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		printf("Error\n");
		exit(1);
	}
	window = SDL_CreateWindow("Games", 10, 10, 600, 600, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("pailas\n");
		exit(1);
	}
	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
	
	printf("%s %d\n", __FILE__, __LINE__);
/*	SDL_FillRect(sur, NULL, SDL_MapRGB(sur->format, 0xFF, 0xFF, 0xFF));
	printf("%s %d\n", __FILE__, __LINE__);
	SDL_UpdateWindowSurface(window);
	printf("%s %d\n", __FILE__, __LINE__);*/
	SDL_Delay(5000);
/*	while (1)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			break;
		if (event.type == SDL_KEYDOWN)
		{

		    rend(window, renderer);
		    if (event.key.keysym.sym == SDLK_ESCAPE)
			break;
		}
		}*/

	SDL_DestroyWindow(window);
	SDL_Quit();
	(void) event;
	
	(void) renderer;
	return (0);
}

void rend(SDL_Window *window, SDL_Renderer *renderer)
{
	vert_t *vrtx;

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


	scanline(&(scn->obj->polys), &vrtx, window, renderer);

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

void scanline(polygon **polys, vert_t **list, SDL_Window *window, SDL_Renderer *renderer)
{
	(void) window;
	(void) renderer;
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
			printf("result x %.2f tmpy: %.2f\n", r, tmpY);
			(void) tmpR;




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
