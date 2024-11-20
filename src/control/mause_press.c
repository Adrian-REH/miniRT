#include "../main.h"

int	mouse_press(int button, int x, int y, void *param)
{
	Scene	*scene;
	int type;
	int idx = 0;
	double t = 0;

	scene = (Scene *)param;
	Ray *ray = generate_ray((double)x, (double)y, WINX, WINY, *scene->cameras);
	type = find_nearest_obj(*scene, ray, &t, &idx, 10);
	if (idx >= 0)
	{
		scene->pos_obj->type = type;
		scene->pos_obj->idx = idx;
	}
	else
	{
		scene->pos_obj->type = CAMERA;
		scene->pos_obj->idx = 0;
	}
	return (0);
}
