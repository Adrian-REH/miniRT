#include "../main.h"

int	render_point_plane(Scene scene, Vector3 hit_pt, int n_plane)
{
	const RenderContext	ctx = {
		.scene = &scene,
		.mater_prop = scene.planes[n_plane].mater_prop,
		.normal = scene.planes[n_plane].normal,
		.hit_pt = hit_pt,
		.funcs = {
			.calculate_intensity = calculate_intensity,
			.calculate_attenuation = calculate_attenuation,
			.reflect = reflect
		}
	};

	Vector3 *cam_dir = normalize_withpoint(scene.cameras->pos, hit_pt);
	Vector3 *light_dir = normalize_withpoint(scene.lights->point, hit_pt);
	Ray rayslight = {scene.lights->point, *light_dir};

	double d;
	Color *current_color;
	if (intersect_plane(&rayslight, &scene.planes[n_plane], &d)) {
		double t = is_in_shadow(scene, scene.lights->point, hit_pt);
		if (t) {
			current_color = apply_shadow(&ctx, light_dir, cam_dir, hit_point(rayslight, t));
		} else {
			current_color = apply_lighting(&ctx, light_dir, cam_dir);
		}
	}
	else
		current_color = apply_ambient(&ctx);
	int result = current_color->color;
	free(cam_dir);
	free(light_dir);
	return result;
}

int	render_reflect_plane(Scene *scene, Ray rayrfc, int id, int type)
{
	double t = 0;
	double md = 900000000;
	int j = -1;
	Vector3 *hit_rfc;
	int hit_color = 0;

	while (++j < scene->n_planes)
	{
		if (intersect_plane(&rayrfc, &scene->planes[j], &t) && (t < md))
		{
			hit_rfc = hit_point(rayrfc, t);
			if (!obj_solution_point(*scene, *hit_rfc, type, id))
			{
				md = t;
				hit_color = render_point_plane(*scene, *hit_rfc, j);
			}
			free(hit_rfc);
		}
	}
	return hit_color;
}

int	render_plane(Scene *scene, Vector3 hit_pt, int id)
{
	double t = 0;
	int idx = id;
	int hit_color = 0;
	int tmp[2] = {0 , 0};
	int result = 0;
	int current_pixel = render_point_plane(*scene, hit_pt, id);

	//Si hay reflexion entonces ...
	//Genero un ray
	if (scene->planes[id].mater_prop.reflect)
	{
		Ray *rayrfc = generate_reflect_ray(scene, hit_pt, scene->planes[id].normal);
		//Hago la reflexion
		Vector3 *hit_rfc;
		int j = -1;
		int type = find_nearest_obj(*scene, rayrfc, &t, &idx, PLANE);
		if (scene->rfc[type])
		{
			hit_color = scene->rfc[type](scene, *rayrfc, id, PLANE);
			result = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene->planes[id].mater_prop)->color;
		}
		free(rayrfc);
		return result;
	}
	return current_pixel;
}
