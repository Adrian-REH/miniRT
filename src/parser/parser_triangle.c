/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_triangle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:34 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 17:22:01 by razamora         ###   ########.fr       */
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
    
    char **args = ft_split(data[1], ',');
    if (ft_sarrsize(args) != 3)
    {
        printf("Error: %s not contain coor x, x ,y\n", data[1]);
        exit(1);
    }
    scene->triangles = malloc(sizeof(Triangle) * 1);
    
    vertex1.x = atof(args[0]);
    vertex1.y = atof(args[1]);
    vertex1.z = atof(args[2]);
    
    ft_free_p2(args);
    
    args = ft_split(data[2], ',');
    if (ft_sarrsize(args) != 3)
    {
        printf("Error: %s not contain normal x, x ,y\n", data[2]);
        exit(1);
    }
    
    vertex2.x = atof(args[0]);
    vertex2.y = atof(args[1]);
    vertex2.z = atof(args[2]);
    
    ft_free_p2(args);
    args = ft_split(data[3], ',');
    if (ft_sarrsize(args) != 3)
    {
        printf("Error: %s not contain normal x, x ,y\n", data[3]);
        exit(1);
    }
    
    vertex3.x = atof(args[0]);
    vertex3.y = atof(args[1]);
    vertex3.z = atof(args[2]);
    
    ft_free_p2(args);
    args = ft_split(data[4], ',');
    if (ft_sarrsize(args) != 3)
    {
        printf("Error: %s not contain color r, g, b\n", data[4]);
        exit(1);
    }   
    color.r = atof(args[0]);
    color.g = atof(args[1]);
    color.b = atof(args[2]);
    if (color.r < 0 || color.r > 255)
    {
        printf("Error: %s  r outside color range\n", data[4]);
        exit(1);
    }
    if (color.g < 0 || color.g > 255)
    {
        printf("Error: %s g outside color range\n", data[4]);
        exit(1);
    }
    if (color.b < 0 || color.b > 255)
    {
        printf("Error: %s b outside color range\n", data[4]);
        exit(1);
    }
    //scene->triangles->color = rgb_to_color((int)color.r, (int)color.g, (int)color.b);
    scene->triangles->vertex1 = &vertex1;
    scene->triangles->vertex2 = &vertex2;
    scene->triangles->vertex3 = &vertex3;
   


}
