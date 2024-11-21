#include "../main.h"

int	mouse_press(int button, int x, int y, void *param)
{
	Scene	*scene;
	int type;
	s_nearest_ctx ctx;

	scene = (Scene *)param;
	ctx = (s_nearest_ctx){0, 0, 10};
	Ray *ray = generate_ray((double)x, (double)y, scene->width, scene->height, *scene->cameras);
	type = find_nearest_obj(*scene, ray, &ctx);
	if (ctx.id_o >= 0)
	{
		scene->pos_obj->type = type;
		scene->pos_obj->idx = ctx.id_o;
	}
	else
	{
		scene->pos_obj->type = CAMERA;
		scene->pos_obj->idx = 0;
	}
	return (0);
}
