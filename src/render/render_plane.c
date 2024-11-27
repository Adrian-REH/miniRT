/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:13:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 19:18:19 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	render_point_plane(Scene scene, t_vector3 hit_pt, int n_plane)
{
	RenderContext	ctx;
	int				color;
	int				i;

	ctx = build_render_ctx(&scene, scene.planes[n_plane].mater_prop, \
		scene.planes[n_plane].normal, hit_pt);
	i = -1;
	color = 0;
	while (++i < scene.n_lights)
	{
		ctx.rayl = (Ray){scene.lights[i].point, \
			norm_subtract(scene.lights[i].point, hit_pt)};
		color = render_light(scene, ctx, &scene.planes[n_plane], PLANE);
	}
	return (color);
}

int	render_reflect_plane(Scene *scene, Ray rayrfc, int id, int type)
{
	double	t;
	double	md;
	int		j;
	t_vector3	*hit_rfc;
	int		hit_color;

	md = 900000000;
	j = -1;
	t = 0;
	hit_color = 0;
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
	return (hit_color);
}

int	render_plane(Scene *scene, t_vector3 hit_pt, int id)
{
	int		hit_color;
	t_color	result;
	int		current_pixel;
	Ray		rayrfc;
	int		type;

	current_pixel = render_point_plane(*scene, hit_pt, id);
	result = (t_color){0};
	hit_color = 0;
	if (scene->planes[id].mater_prop.reflect)
	{
		rayrfc = generate_reflect_ray(scene, hit_pt, scene->planes[id].normal);
		type = find_nearest_obj(*scene, &rayrfc, &(t_nearest_ctx){0, id, 0});
		if (scene->rfc[type])
		{
			hit_color = scene->rfc[type](scene, rayrfc, id, PLANE);
			result = illuminate_surface(int_to_color(hit_color), \
				int_to_color(current_pixel), 0.7, \
					scene->planes[id].mater_prop);
		}
		return (result.color);
	}
	return (current_pixel);
}
