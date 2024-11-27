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

int	is_in_shadow(Scene scene, t_vector3 light_pos, t_vector3 hit_point)
{
	Ray				shadow_ray;
	double			t;
	int				i;
	int				j;
	const double	n_objs[5] = {
		scene.n_planes,
		scene.n_spheres,
		scene.n_triangles,
		scene.n_cylinders,
		distance(hit_point, light_pos)
	};

	shadow_ray.origin = hit_point;
	shadow_ray.direction = norm_subtract(hit_point, light_pos);
	i = ((t = ((j = -1), 0)), -1);
	while (++j < 4)
	{
		while (++i < n_objs[j])
		{
			if (scene.isc[i] && scene.isc[i](&shadow_ray, &scene.planes[i], &t))
				if (t > 0 && t < n_objs[4])
					return (t);
		}
	}
	return (0);
}
