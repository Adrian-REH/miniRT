#include "../main.h"

int	render_point_triangle(Scene scene, Vector3 hit_pt, int n_triangle)
{
	RenderContext	ctx;
	int				color;
	int				i;

	ctx = build_render_ctx(&scene, scene.triangles[n_triangle].mater_prop, \
		scene.triangles[n_triangle].p_triangle->normal, hit_pt);
	i = -1;
	while (++i < scene.n_lights)
	{
		ctx.rayl = (Ray){scene.lights[i].point, 0};
		ctx.rayl.direction = norm_subtract(scene.lights[i].point, hit_pt);
		color = render_light(scene, ctx, &scene.triangles[n_triangle], 2);
	}
	return (color);
}

int	render_reflect_triangle(Scene *scene, Ray rayrfc, int id, int type)
{
	double	t;
	double	md;
	int		j;
	Vector3	*hit_rfc;
	int		hit_color;

	md = 900000000;
	t = 0;
	j = -1;
	hit_color = 0;
	while (++j < scene->n_triangles)
	{
		if (intersect_triangle(&rayrfc, &scene->triangles[j], &t) && (t < md))
		{
			hit_rfc = hit_point(rayrfc, t);
			if (!obj_solution_point(*scene, *hit_rfc, type, id))
			{
				md = t;
				hit_color = render_point_triangle(*scene, *hit_rfc, j);
			}
			free(hit_rfc);
		}
	}
	return (hit_color);
}

int	render_triangle(Scene *scene, Vector3 hit_pt, int id)
{
	Ray		rayrfc;
	int		hit_color;
	int		current_pixel;
	int		type;
	Color	result;

	current_pixel = render_point_triangle(*scene, hit_pt, id);
	result = ((hit_color = 0), (Color){0});
	if (scene->triangles[id].mater_prop.reflect)
	{
		rayrfc = generate_reflect_ray(scene, hit_pt, \
			scene->triangles[id].p_triangle->normal);
		type = find_nearest_obj(*scene, &rayrfc, &(double){0}, &(int){id}, 2);
		if (scene->rfc[type])
		{
			hit_color = scene->rfc[type](scene, rayrfc, id, TRIANGLE);
			result = illuminate_surface(int_to_color(hit_color), \
				int_to_color(current_pixel), 0.6, 0.9, 0, \
					scene->triangles[id].mater_prop);
		}
		return (hit_color);
	}
	return (current_pixel);
}
