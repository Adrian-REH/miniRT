#include "../main.h"

int render_point_sphere(Scene scene, Vector3 hit_pt, int nb_sphere)
{
	RenderContext	ctx;
	Vector3 cam_dir;
	Vector3 light_dir;
	Color *current_color;
	Ray rayslight;
	double d;

	ctx = (RenderContext){
		.scene = &scene,
		.mater_prop = scene.spheres[nb_sphere].mater_prop,
		.normal = norm_subtract(scene.spheres[nb_sphere].center, hit_pt),
		.hit_pt = hit_pt,
		.funcs = {
			.calculate_intensity = calculate_intensity,
			.calculate_attenuation = calculate_attenuation,
			.reflect = reflect
		}
	};
	cam_dir = norm_subtract(scene.cameras->pos, hit_pt);
	light_dir = norm_subtract(scene.lights->point, hit_pt);
	rayslight = (Ray){scene.lights->point, light_dir};
	if (intersect_sphere(&rayslight, scene.spheres, &d))
	{
		d = is_in_shadow(scene, scene.lights->point, hit_pt);
		if (d)
			current_color = apply_shadow(&ctx, &light_dir, &cam_dir, hit_point(rayslight, d));
		else 
			current_color = apply_lighting(&ctx, &light_dir, &cam_dir);
	}
	else
		current_color = apply_ambient(&ctx);
	return current_color->color;
}

int	render_reflect_sphere(Scene *scene, Ray rayrfc, int id, int type)
{
	double t = 0;
	double md = 900000000;
	int j = -1;
	Vector3 *hit_rfc;
	int hit_color = 0;

	while (++j < scene->n_spheres)
	{
		if (intersect_sphere(&rayrfc, &scene->spheres[j], &t) && (t < md)){
			hit_rfc = hit_point(rayrfc, t);
			if (!obj_solution_point(*scene, *hit_rfc, type, id))
			{
				md = t;
				hit_color = render_point_sphere(*scene, *hit_rfc, j);
			}
			free(hit_rfc);
		}
	}
	return hit_color;
}


int	render_sphere(Scene *scene, Vector3 hit_pt, int id)
{
	double t = 0;
	int hit_color = 0;
	int result = 0;
	int idx = id;
	int j = -1;
	//Verificador de planos o objetos mas cercanos para optimizar
	int current_pixel = render_point_sphere(*scene, hit_pt, id);
	//Se confunde consigo mismo para buscar el mas cercano
	//Solucion: Intentar identificar el cuerpo donde sale y hacer que no se autointersecte.
	if (scene->spheres[id].mater_prop.reflect)
	{
		Vector3 *n_sphere = normal_sphere(hit_pt, scene->spheres[id]);
		Ray *rayrfc = generate_reflect_ray(scene, hit_pt, *n_sphere);
		int type = find_nearest_obj(*scene, rayrfc, &t, &idx, SPHERE);
		if (scene->rfc[type])
		{
			hit_color = scene->rfc[type](scene, *rayrfc, id, SPHERE);
			result = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene->spheres[id].mater_prop)->color;
		}
		free(rayrfc);
		free(n_sphere);
		return hit_color;
	}
	return current_pixel;
}
