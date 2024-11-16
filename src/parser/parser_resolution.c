/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:46 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 16:05:47 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	parser_resolution(Scene *scene, char **data)
{
	scene->width = ft_atoi(data[1]);
	scene->height = ft_atoi(data[2]);
	return (0);
}
