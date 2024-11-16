/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_square.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:37 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 16:05:39 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	parser_square(Scene *scene, char **data)
{
    Vector3 center = {0, 0, 0};
    Vector3 normal = {0, 0, 0};
    double side = 0;
    Color color = {0, 0, 0};

   // printf(" SQUARE ----->1|%s| 2|%s| 3|%s| 4|%s| 5 |%s| \n", data[0], data[1], data[2], data[3], data[4]);
    char **args = ft_split(data[1], ',');
    if (ft_sarrsize(args) != 3)
    {
        printf("Error: %s not contain coor x, x ,y\n", data[1]);
        exit(1);
    }
    scene->squares = malloc(sizeof(Square) * 1);

    center.x = atof(args[0]);
    center.y = atof(args[1]);
    center.z = atof(args[2]);

    ft_free_p2(args);

    args = ft_split(data[2], ',');
    if (ft_sarrsize(args) != 3)
    {
        printf("Error: %s not contain normal x, x ,y\n", data[2]);
        exit(1);
    }

    normal.x = atof(args[0]);
    normal.y = atof(args[1]);
    normal.z = atof(args[2]);



    if (data[3] == NULL)
    {
        printf("Error: %s not contain side\n", data[3]);
        exit(1);
    }
    side = atof(data[3]);

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
        printf("Error: %s  r outside color range\n", data[3]);
        exit(1);
    }
    if (color.g < 0 || color.g > 255)
    {
        printf("Error: %s g outside color range\n", data[3]);
        exit(1);
    }
    if (color.b < 0 || color.b > 255)
    {
        printf("Error: %s b outside color range\n", data[3]);
        exit(1);
    }

    scene->squares->center = center;
    scene->squares->normal = normal;
    scene->squares->side = side;
    //scene->squares->color = rgb_to_color((int)color.r, (int)color.g, (int)color.b);

    printf(" SQUARE %s %s %s %s",data[0], data[1], data[2], data[3]);

    


   
    /*
   
:
7. `sq 0,100,40 0,0,1.0 30 42,42,0`
   - Defines a square with a center at (0, 100, 40),
    a normal vector (0, 0, 1.0), 
    a side length of 30, and a 
    color (RGB: 42, 42, 0).

9. `tr 10,20,10 10,10,20 20,10,10 0,0,255`
   - Defines a triangle with vertices at 
   (10, 20, 10), (10, 10, 20), and (20, 10, 10)
    with a color (RGB: 0, 0, 255).

    tr 10,20,10 10,10,20 20,10,10 0,0,255:

This likely draws a triangle.
Defined by the points 10,20,10, 10,10,20, and 20,10,10.
Filled with the color 0,0,255 (blue).

sq 0,100,40 0,0,1.0 30 42,42,0:

This might draw a square or rectangle.
Positioned at 0,100,40.
With dimensions of 30 units.
Filled with the color 42,42,0 (a dark green).
    
    */
    printf("Square\n");
}