/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mause_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:13:59 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 19:45:47 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	mouse_press(int button, int x, int y, void *param)
{
	t_scene			*scene;
	int				type;
	t_nearest_ctx	ctx;
	t_ray				*ray;

	scene = (t_scene *)param;
	(void)button;
	ctx = (t_nearest_ctx){0, 0, 10};
	ray = generate_ray((t_vector2){(double)x, (double)y}, \
		scene->width, scene->height, *scene->cameras);
	type = find_nearest_obj(*scene, ray, &ctx);
	if (ctx.id_o >= 0)
	{
		scene->pos_obj->type = type;
		scene->pos_obj->idx = ctx.id_o;
	}
	else
	{
		scene->pos_obj->type = CAMERA;
		scene->pos_obj->idx = 0;
	}
	free(ray);
	return (0);
}
