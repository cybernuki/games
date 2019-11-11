#include "libs_eng.h"

extern scene *scn;

int key_pressed(int code)
{
    printf("key pressed: code %d\n", code);
    switch (code)
    {
    case 27:  /* R */
		printf("cam zoom: %2.f  ", scn->camara->zoom);
		scn->camara->zoom += 0.4;
		printf("zoom in\n");
		return(1);
	    break;
        case 41: /* F */
		printf("cam zoom: %2.f  ", scn->camara->zoom);
		scn->camara->zoom -= 0.4;
		printf("zoom out\n");
		return(1);
	    break;
	case 38: /* A */
		printf("cam left: %2.f  ", scn->camara->zoom);
		scn->camara->transform->translation->x -= 0.4;
		printf("zoom in\n");
		return(1);
	    break;
	case 40: /* D */
		printf("cam right: %2.f  ", scn->camara->zoom);
		scn->camara->transform->translation->x += 0.4;
		printf("zoom in\n");
		return(1);
	    break;
	case 25: /* W */
		printf("cam up: %2.f  ", scn->camara->zoom);
		scn->camara->transform->translation->y -= 0.4;
		printf("zoom in\n");
		return(1);
	    break;
	case 39: /* S */
		printf("cam down: %2.f  ", scn->camara->zoom);
		scn->camara->transform->translation->y += 0.4;
		printf("zoom in\n");
		return(1);
	    break;
	case 28: /* T */
		printf("cam up: %2.f  ", scn->camara->zoom);
		scn->obj->transform->rotation->z -= 0.19;
		printf("zoom in\n");
		return(1);
	    break;
	case 42: /* G */
		printf("cam down: %2.f  ", scn->camara->zoom);
		scn->obj->transform->rotation->z += 0.19;
		printf("zoom in\n");
		return(1);
	    break;
        case 55: /* V */
		printf("cam up: %2.f  ", scn->camara->zoom);
		scn->obj->transform->rotation->y -= 0.19;
		printf("zoom in\n");
		return(1);
	    break;
	case 56: /* B */
		printf("cam down: %2.f  ", scn->camara->zoom);
		scn->obj->transform->rotation->y += 0.19;
		printf("zoom in\n");
		return(1);
	    break;
	case 53: /* X */
		printf("cam up: %2.f  ", scn->camara->zoom);
		scn->obj->transform->rotation->x -= 0.19;
		printf("zoom in\n");
		return(1);
	    break;
	case 54: /* C */
		printf("cam down: %2.f  ", scn->camara->zoom);
		scn->obj->transform->rotation->x += 0.19;
		printf("zoom in\n");
		return(1);
	    break;

	default:
	    break;
    }
    return (0);
}
