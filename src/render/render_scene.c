#include "../main.h"

int sampling(int x, int y, Scene *scene, int samples_per_pixel)
{
    Color final_color = {0, 0, 0};  // Color acumulado (R, G, B)
    Color sample_color = {0, 0, 0};  // Color acumulado (R, G, B)
    float inv_samples = 1.0f / samples_per_pixel;

    for (int s = 0; s < samples_per_pixel; s++)
	{
        // Calcular pequeñas desviaciones aleatorias dentro del píxel (jittering)
        double u = (x + random_double()) / (double)WINX;
        double v = (y + random_double()) / (double)WINY;

        // Generar rayo para la posición u, v dentro del píxel
		Ray *ray = generate_ray(x + u, y + v, WINX, WINY, *scene->cameras);
		if (!ray)
			return 0;
		double t = 0;
		double min_dist = 90000000;
		int type;
		int id = 0;
		int hit_color;
		double d;
		type = find_nearest_obj(*scene, ray, &t, &id, 10);
		if (x == 5 && y == 5)
		{
			printf("Select: Type: %d, idx: %d, pos: %d, %d \n", type, id, x,y);
		}
		Vector3 *hit_pt = hit_point(*ray, t);
		if (scene->render[type] && id >= 0)
			addint_to_color(&sample_color, scene->render[type](scene, *hit_pt, id));

        // Acumular el color de esta muestra
        final_color.r += sample_color.r;
        final_color.g += sample_color.g;
        final_color.b += sample_color.b;
		free(ray);
    }
    // Promediar el color acumulado dividiendo por el número de muestras
	final_color.r *= inv_samples;
	final_color.g *= inv_samples;
	final_color.b *= inv_samples;

	return colornormal_to_int(final_color);
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
            // Calcula el color del píxel con multiple-sampling (anti-aliasing)
         	int color = sampling(x, y, scene, samples_per_pixel);
            // Guardar o mostrar el color final del píxel
          set_color(&scene->img->buffer[idxpixel(x, y)], 0, color, 0);
        }
    }
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->img, 0, 0);
	end = clock();
	double elapsed = (double)(end - start) / CLOCKS_PER_SEC ; // Convertido a milisegundos
	printf("Elapsed time: %.3f sec\n", elapsed);
}
