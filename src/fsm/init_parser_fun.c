/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser_fun.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:20:47 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:22:12 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	init_parser_fun(Scene *scene)
{
	scene->parser[0] = (int (*)(void *, void *))parser_resolution;
	scene->parser[1] = (int (*)(void *, void *))parser_ambient;
	scene->parser[2] = (int (*)(void *, void *))parser_camera;
	scene->parser[3] = (int (*)(void *, void *))parser_light;
	scene->parser[4] = (int (*)(void *, void *))parser_plane;
	scene->parser[5] = (int (*)(void *, void *))parser_sphere;
	scene->parser[6] = (int (*)(void *, void *))parser_square;
	scene->parser[7] = (int (*)(void *, void *))parser_cylinder;
	scene->parser[8] = (int (*)(void *, void *))parser_triangle;
	scene->parser[9] = NULL;
}
