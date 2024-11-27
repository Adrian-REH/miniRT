/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:46 by razamora          #+#    #+#             */
/*   Updated: 2024/11/18 18:47:56 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	parser_resolution(t_scene *scene, char **data)
{
	if (data[1] == NULL || data[2] == NULL)
	{
		printf("Error: Resolution not contain width or height\n");
		exit(1);
	}
	scene->width = ft_limit(10, 4000, ft_atoi(data[1]));
	scene->height = ft_limit(10, 4000, ft_atoi(data[2]));
	return (0);
}
