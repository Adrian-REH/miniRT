#include "../main.h"


int render_point_cylinder(Scene scene, Vector3 hit_pt, int n_cyl)
{
	RenderContext	ctx;
	Vector3 cam_dir;
	Vector3 light_dir;
	Color *current_color;
	Ray rayslight;
	double d;
	Vector3 *dir_cyl;

	dir_cyl = normal_cylinder(hit_pt, scene.cylinders[n_cyl]);
	ctx = (RenderContext){
		.scene = &scene,
		.mater_prop = scene.cylinders[n_cyl].mater_prop,
		.normal = *dir_cyl,
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
	if (intersect_cylinder(&rayslight, &scene.cylinders[n_cyl], &d))
	{
		d = is_in_shadow(scene, scene.lights->point, hit_pt);
		if (d)
			current_color = apply_shadow(&ctx, &light_dir, &cam_dir, hit_point(rayslight, d));
		else 
			current_color = apply_lighting(&ctx, &light_dir, &cam_dir);
	}
	else
		current_color = apply_ambient(&ctx);
	free(dir_cyl);
	return current_color->color;
}

int	render_reflect_cylinder(Scene *scene, Ray rayrfc, int id, int type)
{
	double t = 0;
	double md = 900000000;
	int j = -1;
	Vector3 *hit_rfc;
	int hit_color = 0;

	while (++j < scene->n_triangles)
	{
		if (intersect_cylinder(&rayrfc, &scene->cylinders[j], &t) && (t < md))
		{
			hit_rfc = hit_point(rayrfc, t);
			if (!obj_solution_point(*scene, *hit_rfc, type, id))
			{
				md = t;
				hit_color = render_point_cylinder(*scene, *hit_rfc, j);
			}
			free(hit_rfc);
		}
	}
	return hit_color;
}

int	render_cylinder(Scene *scene, Vector3 hit_pt, int id)
{
	double t = 0;
	int idx = id;
	int hit_color = 0;
	int tmp[2] = {0 , 0};
	int result = 0;
	int current_pixel = render_point_cylinder(*scene, hit_pt, id);
	Ray rayrfc;

	if (scene->cylinders[id].mater_prop.reflect)
	{
		rayrfc = generate_reflect_ray(scene, hit_pt, scene->triangles[id].p_triangle->normal);
		int type = find_nearest_obj(*scene, &rayrfc, &t, &idx, CYLINDER);
		if (scene->rfc[type])
		{
			hit_color = scene->rfc[type](scene, rayrfc, id, CYLINDER);
			result = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.6, 0.9, 0, scene->cylinders[id].mater_prop)->color;
		}
		return hit_color;
	}
	return current_pixel;

}
