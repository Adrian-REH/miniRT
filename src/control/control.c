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

void	mlx_listen_meta(Scene *scene)
{
	mlx_hook(scene->win, 4, 1L << 2, mouse_press, scene);
	mlx_hook(scene->win, 2, 1, key_press, scene);
	mlx_hook(scene->win, 17, 1, terminate_program, scene);
	mlx_loop(scene->mlx);
}
