#include "../main.h"

int	render_point(Scene *scene, int x, int y)
{
	Ray				*ray;
	s_nearest_ctx	ctx;
	int				result;

	result = 0;
	ctx = (s_nearest_ctx){0 , 0, 10};
	ray = generate_ray(x, y, scene->width, scene->height, *scene->cameras);
	if (!ray)
		return (0);
	ctx.type = find_nearest_obj(*scene, ray, &ctx);
	if (scene->render[ctx.type] && ctx.id_o >= 0)
		result = scene->render[ctx.type](scene, resolve_hit_point(*ray, ctx.dist), ctx.id_o);
	return (free(ray), result);
}

int	sampling(int x, int y, Scene *scene, int samples_per_pixel)
{
	Color	final_color;
	Color	sample_color;
	double	u;
	double	v;
	int		s;

	s = -1;
	final_color = (Color){0, 0, 0};
	sample_color = (Color){0, 0, 0};
	while (++s < samples_per_pixel)
	{
		u = (x + random_double()) / (double)scene->width;
		v = (y + random_double()) / (double)scene->height;
		addint_to_color(&sample_color, render_point(scene, x + u, y + v));
		final_color.r += sample_color.r;
		final_color.g += sample_color.g;
		final_color.b += sample_color.b;
	}
	final_color.r *= (1.0f / samples_per_pixel);
	final_color.g *= (1.0f / samples_per_pixel);
	final_color.b *= (1.0f / samples_per_pixel);
	return (colornormal_to_int(final_color));
}

void	render_scene(Scene *scene, int samples_per_pixel)
{
	time_t	start;
	double	min_dist;
	int		x;
	int		y;
	double	elapsed;

	init_rfc_render_fun(scene);
	init_render_fun(scene);
	init_intersect_fun(scene);
	start = clock();
	y = -1;
	while (++y < scene->height)
	{
		x = -1;
		while (++x < scene->width)
		{
			set_color(&scene->img->buffer[idxpixel(scene->width, x, y)], 0,
				sampling(x, y, scene, samples_per_pixel), 0);
		}
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->img, 0, 0);
	elapsed = (double)(clock() - start) / CLOCKS_PER_SEC ;
	printf("Render: %.3f sec\n", elapsed);
}
