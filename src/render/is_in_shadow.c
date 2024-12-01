/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:47 by adherrer          #+#    #+#             */
/*   Updated: 2024/12/01 17:51:25 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	is_in_shadow(t_scene scene, t_vector3 l_pos, t_vector3 hit_pt)
{
	t_ray			sr;
	double			t;
	int				i;
	int				j;
	const void		*obj[5][2] = {
	{(const void *)&scene.n_planes, (void *)scene.planes},
	{(const void *)&scene.n_spheres, (void *)scene.spheres},
	{(const void *)&scene.n_triangles, (void *)scene.triangles},
	{(const void *)&scene.n_cylinders, (void *)scene.cylinders},
	{(const void *)&(double){distance(hit_pt, l_pos)}, NULL}
	};

	sr.direction = ((sr.origin = hit_pt), norm_subtract(hit_pt, l_pos));
	i = ((t = ((j = -1), 0)), -1);
	while (++j < 4)
	{
		i = -1;
		while (++i < *((int *)obj[j][0]))
		{
			if (scene.isc[j] && scene.isc[j](&sr, ((void *)obj[j][1] + i), &t))
				if (t > 0 && t < *((double *)obj[4][0]))
					return (t);
		}
	}
	return (0);
}
