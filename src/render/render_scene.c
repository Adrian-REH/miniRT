#include "../main.h"

int	render_point(Scene *scene, int x, int y)
{
	int result;
	Vector3 *hit_pt;
	Ray *ray;
	double t = 0;
	int type;
	int id = 0;

	result = 0;
	ray = generate_ray(x, y, scene->width, scene->height, *scene->cameras);
	if (!ray)
		return 0;
	type = find_nearest_obj(*scene, ray, &t, &id, 10);
	hit_pt = hit_point(*ray, t);
	if (scene->render[type] && id >= 0)
		result = scene->render[type](scene, *hit_pt, id);
	free(ray);
	return result;
}

int sampling(int x, int y, Scene *scene, int samples_per_pixel)
{
	Color final_color = {0, 0, 0};  // Color acumulado (R, G, B)
	Color sample_color = {0, 0, 0};  // Color acumulado (R, G, B)
	float inv_samples = 1.0f / samples_per_pixel;
	double u;
	double v;

	for (int s = 0; s < samples_per_pixel; s++)
	{
		// Calcular pequeñas desviaciones aleatorias dentro del píxel (jittering)
		u = (x + random_double()) / (double)WINX;
		v = (y + random_double()) / (double)WINY;
		addint_to_color(&sample_color, render_point(scene, x + u, y + v));
		final_color.r += sample_color.r;
		final_color.g += sample_color.g;
		final_color.b += sample_color.b;
	}
	final_color.r *= inv_samples;
	final_color.g *= inv_samples;
	final_color.b *= inv_samples;

	return (colornormal_to_int(final_color));
}

void render_scene(Scene *scene, int samples_per_pixel)
{
	init_rfc_render_fun(scene);
	init_render_fun(scene);
	init_intersect_fun(scene);
	time_t start, end;
	double min_dist;
	int alpha = 0;
	start = clock();
    for (int y = 0; y < WINY ; y++) {
        for (int x = 0; x < WINX ; x++) {
         	int color = sampling(x, y, scene, samples_per_pixel);
          set_color(&scene->img->buffer[idxpixel(x, y)], 0, color, 0);
        }
    }
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->img, 0, 0);
	end = clock();
	double elapsed = (double)(end - start) / CLOCKS_PER_SEC ; // Convertido a milisegundos
	printf("Render: %.3f sec\n", elapsed);
}
