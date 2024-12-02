/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fun_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:54:27 by razamora          #+#    #+#             */
/*   Updated: 2024/11/21 21:05:40 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

t_map_fun	map_fun_get(const t_map_fun *map_fun, int key)
{
	int	i;

	i = -1;
	while (map_fun[++i].key)
	{
		if (map_fun[i].key == key && map_fun[i].func)
			return (map_fun[i]);
	}
	return (map_fun[i]);
}
