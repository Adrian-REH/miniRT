/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:57 by razamora          #+#    #+#             */
/*   Updated: 2024/11/17 15:35:58 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../main.h"



/**
 * Re alocar la memoria de scene->planes para guardar los datos del nuevo plano.
 */
int	parser_plane(Scene *scene, char **data)
{
	// printf("Plane\n");
	// return 0;

	// data[0] -> typo 
	// data[1] -> Point inside of plane 
	// data[2] -> Normal 
	// data[3] -> Color RGB

	Plane	plane_null;
	//sizeof(Plane) * scene->n_planes : el size de la memoria que existe
	//sizeof(Plane) * (scene->n_planes + 2) : el size de la memoria que existe mas la que queremos agregar mas el plane_null
	scene->planes = ft_realloc(scene->planes, sizeof(Plane) * scene->n_planes, sizeof(Plane) * (scene->n_planes + 2));
	//Agregar los datos necesarios para el plano en la posicion scene->n_planes
	// "0.0,0.0,0.0" -> Vector3 normal = {0.0, 0.0 ,0.0}
	int i = -1;
	Vector3 normal = {0.0, 0.0, 0.0};
	Vector3  point = {0.0, 0.0, 0.0};
	Color color = {0, 0, 0};
	char **args = ft_split(data[2], ',');



	normal = ft_normalizate(data[2]);
	point = ft_coordinate(data[1]);
	color = ft_color(data[3]);
	scene->planes[scene->n_planes].mater_prop.vColor = rgb_to_color((int)color.r, (int)color.g, (int)color.b);
	scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->g;
	scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->b;
	scene->planes[scene->n_planes].normal = normal;
	scene->planes[scene->n_planes].point = point;


	// "0.0,0.0,0.0" -> Vector3 point = {0.0, 0.0 ,0.0}
	//scene->planes[scene->n_planes].point = (Vector3)str_to_Vecotr3(data[2]); 
	// "255,0,255" -> int r= 255; int g = 0; int b = 255;
	//scene->planes[scene->n_planes].mater_prop.vColor = (Color)rgb_to_color(r, g, b);
	//scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor.r;
	//scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 - scene->planes[scene->n_planes].mater_prop.vColor.g;
	//scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 - scene->planes[scene->n_planes].mater_prop.vColor.b;
	//Es importante iterar a uno mas para asigar el null.
	scene->n_planes++;
	ft_bzero(&plane_null, sizeof(Plane));
	scene->planes[scene->n_planes] = plane_null;
	//Re alocas el conjunto de planos

}