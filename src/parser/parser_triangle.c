/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_triangle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:34 by razamora          #+#    #+#             */
/*   Updated: 2024/11/17 15:22:41 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int parser_triangle(Scene *scene, char **data)
{
    printf("Triangle\n");
    
    printf("Triangle ----->1|%s| 2|%s| 3|%s| 4|%s| 5 |%s| \n", data[0], data[1], data[2], data[3], data[4]);
    Vector3 vertex1 = {0, 0, 0};
    Vector3 vertex2 = {0, 0, 0};
    Vector3 vertex3 = {0, 0, 0};
    Color color = {0, 0, 0};
    
   
    scene->triangles = ft_realloc(scene->triangles, sizeof(Triangle) * scene->n_triangles, sizeof(Triangle) * (scene->n_triangles + 2));

    vertex1 = ft_coordinate(data[1]);
    vertex2 = ft_coordinate(data[2]);
    vertex3 = ft_coordinate(data[3]);
    color = ft_color(data[4]);
  
    Vector3 dir1 = substract(vertex1, vertex2);
    Vector3 dir2 = substract(vertex1, vertex3);
    //scene->triangles->color = rgb_to_color((int)color.r, (int)color.g, (int)color.b);
    scene->triangles->vertex1 = &vertex1;
    scene->triangles->vertex2 = &vertex2;
    scene->triangles->vertex3 = &vertex3;
    scene->triangles->p_triangle = malloc(sizeof(Plane));
    scene->triangles->p_triangle->normal = cross_v3(dir1, dir2);
    scene->triangles->p_triangle->point = vertex1;
	scene->triangles->mater_prop.vColor = rgb_to_color(color.r, color.g, color.b);
	scene->triangles->mater_prop.reflect = 1;
	scene->triangles->mater_prop.absorption[R] = 1 - scene->triangles->mater_prop.vColor->r;
	scene->triangles->mater_prop.absorption[G] = 1 - scene->triangles->mater_prop.vColor->g;
	scene->triangles->mater_prop.absorption[B] = 1 - scene->triangles->mater_prop.vColor->b;
    scene->n_triangles++;

/* 
	scene->n_triangles = 0;
	scene->triangle =  malloc(sizeof(Triangle) * 1);
	scene->triangle->vertex[0] = (Vector3){-3, 1, 1};
	scene->triangle->vertex[1] = (Vector3){3, 1, 1};
	scene->triangle->vertex[2] = (Vector3){0, -3, 1};
	scene->triangle->dir[0] = normalize_withpoint(scene->triangle->vertex[0], scene->triangle->vertex[1]);
	scene->triangle->dir[1] = normalize_withpoint(scene->triangle->vertex[2], scene->triangle->vertex[0]);
	scene->triangle->dir[2] = normalize_withpoint(scene->triangle->vertex[2], scene->triangle->vertex[0]);
	scene->triangle->n_vertex = 3;
	scene->triangle->mater_prop.vColor = int_to_color(0xFFFFFF);
	scene->triangle->mater_prop.reflect = 1;
	scene->triangle->mater_prop.absorption[R] = 1 - scene->triangle->mater_prop.vColor->r;
	scene->triangle->mater_prop.absorption[G] = 1 - scene->triangle->mater_prop.vColor->g;
	scene->triangle->mater_prop.absorption[B] = 1 - scene->triangle->mater_prop.vColor->b;
	scene->triangle->p_triangle = malloc(sizeof(Plane));
	scene->triangle->p_triangle->normal = cross_v3(*(scene->triangle->dir[0]), *(scene->triangle->dir[1]));
	scene->triangle->p_triangle->point = scene->triangle->vertex[0];
	scene->n_triangles++;
 */
}
