/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mause_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:13:59 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:14:01 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	mouse_press(int button, int x, int y, void *param)
{
	Scene			*scene;
	int				type;
	s_nearest_ctx	ctx;
	Ray				*ray;

	scene = (Scene *)param;
	(void)button;
	ctx = (s_nearest_ctx){0, 0, 10};
	ray = generate_ray((Vector2){(double)x, (double)y}, \
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
	return (0);
}
