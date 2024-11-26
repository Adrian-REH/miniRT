/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:20:53 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:20:54 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	key_press(int key, Scene *param)
{
	t_map_fun		map_fun;
	const t_map_fun	controls[10] = {
	{XK_a, (void (*)(void *))control_a},
	{XK_d, (void (*)(void *))control_d},
	{XK_w, (void (*)(void *))control_w},
	{XK_s, (void (*)(void *))control_s},
	{XK_Left, (void (*)(void *))control_left},
	{XK_Up, (void (*)(void *))control_up},
	{XK_Right, (void (*)(void *))control_right},
	{XK_Down, (void (*)(void *))control_down},
	{XK_Escape, (void (*)(void *))control_escape},
	{0, NULL}
	};

	if (param->n_interaction >= 1)
		return (0);
	param->n_interaction++;
	map_fun = map_fun_get(controls, key);
	if (map_fun.func)
		map_fun.func(param);
	param->n_interaction--;
	return (0);
}
