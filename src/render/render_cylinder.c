#include "../main.h"

int	render_point_cylinder(Scene scene, Vector3 hit_pt, int n_cyl)
{
	RenderContext	ctx;
	Vector3			cam_dir;
	Vector3			light_dir;
	Color			*current_color;
	Ray				rayslight;
	double			d;

	ctx = build_render_ctx(&scene, scene.cylinders[n_cyl].mater_prop, \
		normal_cylinder(hit_pt, scene.cylinders[n_cyl]), hit_pt);
	cam_dir = norm_subtract(scene.cameras->pos, hit_pt);
	light_dir = norm_subtract(scene.lights->point, hit_pt);
	rayslight = (Ray){scene.lights->point, light_dir};
	if (intersect_cylinder(&rayslight, &scene.cylinders[n_cyl], &d))
	{
		d = is_in_shadow(scene, scene.lights->point, hit_pt);
		if (d)
			current_color = apply_shadow(&ctx, &light_dir, &cam_dir, \
				hit_point(rayslight, d));
		else
			current_color = apply_lighting(&ctx, &light_dir, &cam_dir);
	}
	else
		current_color = apply_ambient(&ctx);
	return (current_color->color);
}

int	render_reflect_cylinder(Scene *scene, Ray rayrfc, int id, int type)
{
	double	t;
	double	md;
	int		j;
	Vector3	*hit_rfc;
	int		hit_color;

	t = 0;
	hit_color = 0;
	j = -1;
	md = 900000000;
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
	return (hit_color);
}

int	render_cylinder(Scene *scene, Vector3 hit_pt, int id)
{
	int		hit_color;
	int		result;
	int		current_pixel;
	Ray		rayrfc;
	int		type;
	Color *color;

	current_pixel = render_point_cylinder(*scene, hit_pt, id);
	result = ((hit_color = 0), 0);
	if (scene->cylinders[id].mater_prop.reflect)
	{
		rayrfc = generate_reflect_ray(scene, hit_pt, \
			normal_cylinder(hit_pt, scene->cylinders[id]));
		type = find_nearest_obj(*scene, &rayrfc, &(int){0}, &(int){id}, 3);
		if (scene->rfc[type])
		{
			hit_color = scene->rfc[type](scene, rayrfc, id, CYLINDER);
			color = illuminate_surface(int_to_color(hit_color), \
				int_to_color(current_pixel), 0.7, 0.9, 0, \
					scene->cylinders[id].mater_prop);
			result = color->color;
			free(color);
		}
		return (result);
	}
	return (current_pixel);
}
