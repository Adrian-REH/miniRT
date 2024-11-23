#include "../main.h"

int	render_point_sphere(Scene scene, Vector3 hit_pt, int nb_sphere)
{
	RenderContext	ctx;
	int				color;
	int				i;

	ctx = build_render_ctx(&scene, scene.spheres[nb_sphere].mater_prop, \
		norm_subtract(scene.spheres[nb_sphere].center, hit_pt), hit_pt);
	i = -1;
	color = 0;
	while (++i < scene.n_lights)
	{
		ctx.rayl = (Ray){scene.lights[i].point, \
			norm_subtract(scene.lights[i].point, hit_pt)};
		color = render_light(scene, ctx, &scene.spheres[nb_sphere], SPHERE);
	}
	return (color);
}

int	render_reflect_sphere(Scene *scene, Ray rayrfc, int id, int type)
{
	double	t;
	double	md;
	int		j;
	Vector3	*hit_rfc;
	int		hit_color;

	t = 0;
	md = 900000000;
	j = -1;
	hit_color = 0;
	while (++j < scene->n_spheres)
	{
		if (intersect_sphere(&rayrfc, &scene->spheres[j], &t) && (t < md))
		{
			hit_rfc = hit_point(rayrfc, t);
			if (!obj_solution_point(*scene, *hit_rfc, type, id))
			{
				md = t;
				hit_color = render_point_sphere(*scene, *hit_rfc, j);
			}
			free(hit_rfc);
		}
	}
	return (hit_color);
}

int	render_sphere(Scene *scene, Vector3 hit_pt, int id)
{
	int		hit_color;
	Color	result;
	int		current_pixel;
	Ray		rayrfc;
	int		type;

	hit_color = 0;
	result = (Color){0, 0, 0, 0};
	(void)result;
	current_pixel = render_point_sphere(*scene, hit_pt, id);
	if (scene->spheres[id].mater_prop.reflect)
	{
		rayrfc = generate_reflect_ray(scene, hit_pt, \
		norm_subtract(scene->spheres[id].center, hit_pt));
		type = find_nearest_obj(*scene, &rayrfc, &(s_nearest_ctx){0, id, 1});
		if (scene->rfc[type])
		{
			hit_color = scene->rfc[type](scene, rayrfc, id, SPHERE);
			result = illuminate_surface(int_to_color(hit_color), \
				int_to_color(current_pixel), 0.7, 0.9, 0, \
					scene->spheres[id].mater_prop);
		}
		return (hit_color);
	}
	return (current_pixel);
}
