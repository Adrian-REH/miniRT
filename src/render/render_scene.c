#include "../main.h"

int calculate_pixel_color(int x, int y, Scene *scene, int samples_per_pixel)
{
    Color final_color = {0, 0, 0};  // Color acumulado (R, G, B)
    Color sample_color = {0, 0, 0};  // Color acumulado (R, G, B)
    float inv_samples = 1.0f / samples_per_pixel;

    for (int s = 0; s < samples_per_pixel; s++) {
        // Calcular pequeñas desviaciones aleatorias dentro del píxel (jittering)
        double u = (x + random_double()) / (double)WINX;
        double v = (y + random_double()) / (double)WINY;

        // Generar rayo para la posición u, v dentro del píxel
		Ray ray = *generate_ray(x + u, y + v, WINX, WINY, *scene->cameras); 
		double t = 0;
		double min_dist = 90000000;
		int type;
		int id;
		type = find_nearest_obj(*scene, &ray, &t, &id);
		if (type == PLANE){
			double md= 900000;
			int hit_color = 0;
			Vector3 *hit_pt = hit_point(ray, t);
			Vector3 *hit_rfc;
			Vector3 *dir_pt = normalize_withpoint(scene->cameras->pos , *hit_pt);
			Vector3 *rfc = reflect(*dir_pt, scene->planes[id].normal);
			if (dot(scene->planes[id].normal, *rfc) < 0)
				invnormal(rfc);
			Ray rayrfc = {*hit_pt , *rfc};
			int j = -1;

			//Si hay reflexion entonces pasa esto
			while (++j < scene->n_planes){

				if (intersect_plane(&rayrfc, &scene->planes[j], &t) && (t < md))
				{
					hit_rfc = hit_point(rayrfc, t);
					//El plano que emitio el rayo no deberia ser solucion para la reflexion
					if (!plane_solution_point(scene->planes[id], *hit_rfc))
					{
						md = t;
						hit_color = render_point_plane(*scene, *hit_rfc, j);
						int current_pixel = render_point_plane(*scene, *hit_pt, id);
						current_pixel = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene->planes[id].mater_prop)->color;
						set_color(&scene->img->buffer[idxpixel(x, y)], 0, current_pixel, 0);
						addint_to_color(&sample_color, current_pixel);
					}
					free(hit_rfc);
				}
			}
			j = -1;
			while (++j < scene->n_spheres)
			{
				if (intersect_sphere(&rayrfc, &scene->spheres[j], &t) && (t < md)){
					hit_rfc = hit_point(rayrfc, t);
					if (!plane_solution_point(scene->planes[id], *hit_rfc)){
						md = t;
						hit_color = render_point_sphere(*scene, *hit_rfc, j);
						
						int current_pixel = render_point_plane(*scene, *hit_pt, id);
						current_pixel = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene->planes[id].mater_prop)->color;
						set_color(&scene->img->buffer[idxpixel(x, y)], 0, current_pixel, 0);
						addint_to_color(&sample_color, current_pixel);
					}
					free(hit_rfc);
				}
			}
			
			free(hit_pt);
			free(dir_pt);
			free(rfc);
		}
		
		if (type == SPHERE)
		{
			double md= 900000;
			int hit_color = 0;
			Vector3 *hit_pt = hit_point(ray, t);
			Vector3 *hit_rfc;
			Vector3 *dir_pt = normalize_withpoint(scene->cameras->pos , *hit_pt);
			Vector3 *n_sphere = normal_sphere(*hit_pt, scene->spheres[id]);
			Vector3 *rfc = reflect(*dir_pt, *n_sphere);
			if (dot(*n_sphere, *rfc) < 0)
				invnormal(rfc);
			Ray rayrfc = {*hit_pt , *rfc};
			int j = -1;
			//Verificador de planos o objetos mas cercanos para optimizar
			while (++j < scene->n_planes)
			{
				if (intersect_plane(&rayrfc, &scene->planes[j], &t) && (t < md))
				{
					hit_rfc = hit_point(rayrfc, t);
					//El plano que emitio el rayo no deberia ser solucion para la reflexion
					if (!sphere_solution_point(scene->spheres[id], *hit_rfc))
					{
						md = t;
						hit_color = render_point_plane(*scene, *hit_rfc, j);
						int current_pixel = render_point_sphere(*scene, *hit_pt, id);
						current_pixel = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.5, 0.9, 0, scene->spheres[id].mater_prop)->color;
						set_color(&scene->img->buffer[idxpixel(x, y)], 0, hit_color, 0);
						addint_to_color(&sample_color, hit_color);
					}
					free(hit_rfc);
				}
			}
			j = -1;
			while (++j < scene->n_spheres)
			{
				if (intersect_sphere(&rayrfc, &scene->spheres[j], &t) && (t < md))
				{
					hit_rfc = hit_point(rayrfc, t);
					//El plano que emitio el rayo no deberia ser solucion para la reflexion
					if (!sphere_solution_point(scene->spheres[id], *hit_rfc))
					{
						md = t;
						hit_color = render_point_sphere(*scene, *hit_rfc, j);
						int current_pixel = render_point_sphere(*scene, *hit_pt, id);
						current_pixel = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.5, 0.9, 0, scene->spheres[id].mater_prop)->color;
						set_color(&scene->img->buffer[idxpixel(x, y)], 0, hit_color, 0);
						addint_to_color(&sample_color, hit_color);
					}
					free(hit_rfc);
				}
			}

			free(hit_pt);
			free(dir_pt);
			free(n_sphere);
			free(rfc);
		}
			
		if (intersect_sphere(&ray, &scene->spheres[1], &t)) //para la esfera de luz
		{
			Vector3 *hit_pt = hit_point(ray, t);
			addint_to_color(&sample_color, 0xFFFFFF);
			free(hit_pt);
		}
        // Acumular el color de esta muestra
        final_color.r += sample_color.r;
        final_color.g += sample_color.g;
        final_color.b += sample_color.b;
    }
    // Promediar el color acumulado dividiendo por el número de muestras
	final_color.r *= inv_samples;
	final_color.g *= inv_samples;
	final_color.b *= inv_samples;

	return colornormal_to_int(final_color);
}

void render_scene(Scene *scene, int samples_per_pixel)
{
	time_t start, end;
	double min_dist;
	int alpha = 0;
	start = clock();
    for (int y = 0; y < WINY ; y++) {
        for (int x = 0; x < WINX ; x++) {
            // Calcula el color del píxel con multiple-sampling (anti-aliasing)
         	int color = calculate_pixel_color(x, y, scene, samples_per_pixel);
            // Guardar o mostrar el color final del píxel
           set_color(&scene->img->buffer[idxpixel(x, y)], 0, color, 0);
        }
    }
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->img, 0, 0);
	end = clock();
	double elapsed = (double)(end - start) / CLOCKS_PER_SEC * 1000; // Convertido a milisegundos
	printf("Elapsed time: %.3f milliseconds\n", elapsed);
}
