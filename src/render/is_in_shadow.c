/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:47 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/30 18:54:03 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	is_in_shadow(t_scene scene, t_vector3 light_pos, t_vector3 hit_point)
{
	t_ray			shadow_ray;
	double			t;
	int				i;
	int				j;
	const void		*obj_data[5][2] = {
		{(const void *)&scene.n_planes, (void *)scene.planes},
		{(const void *)&scene.n_spheres, (void *)scene.spheres},
		{(const void *)&scene.n_triangles, (void *)scene.triangles},
		{(const void *)&scene.n_cylinders, (void *)scene.cylinders},
		{(const void *)&(double){distance(hit_point, light_pos)}, NULL}
	};

	shadow_ray.origin = hit_point;
	shadow_ray.direction = norm_subtract(hit_point, light_pos);
	i = ((t = ((j = -1), 0)), -1);
	while (++j < 4)
	{
		i = -1;
		while (++i < *((int *)obj_data[j][0]))
		{
			if (scene.isc[i] && scene.isc[i](&shadow_ray, ((void *)obj_data[j][1] + i), &t))
				if (t > 0 && t < *((double *)obj_data[4][0]))
					return (t);
		}
	}
	return (0);
}
