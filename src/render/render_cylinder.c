/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:47 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:23:48 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	render_point_cylinder(Scene scene, Vector3 hit_pt, int n_cyl)
{
	RenderContext	ctx;
	int				color;
	int				i;

	ctx = build_render_ctx(&scene, scene.cylinders[n_cyl].mater_prop, \
		normal_cylinder(hit_pt, scene.cylinders[n_cyl]), hit_pt);
	i = -1;
	color = 0;
	while (++i < scene.n_lights)
	{
		ctx.rayl = (Ray){scene.lights[i].point, {0, 0, 0}};
		ctx.rayl.direction = norm_subtract(scene.lights[i].point, hit_pt);
		color = render_light(scene, ctx, &scene.cylinders[n_cyl], CYLINDER);
	}
	return (color);
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
	int			hit_color;
	Color		result;
	int			current_pixel;
	Ray			rayrfc;
	int			type;

	current_pixel = render_point_cylinder(*scene, hit_pt, id);
	result = ((hit_color = 0), (Color){0});
	if (scene->cylinders[id].mater_prop.reflect)
	{
		rayrfc = generate_reflect_ray(scene, hit_pt, \
			normal_cylinder(hit_pt, scene->cylinders[id]));
		type = find_nearest_obj(*scene, &rayrfc, &(s_nearest_ctx){0, id, 3});
		if (scene->rfc[type])
		{
			hit_color = scene->rfc[type](scene, rayrfc, id, CYLINDER);
			result = illuminate_surface(int_to_color(hit_color), \
				int_to_color(current_pixel), 0.7, \
					scene->cylinders[id].mater_prop);
		}
		return (result.color);
	}
	return (current_pixel);
}
