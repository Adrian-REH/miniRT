/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_square.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:37 by razamora          #+#    #+#             */
/*   Updated: 2024/11/17 15:46:40 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"


static double side_square(char *data)
{
    double side;
    if (data == NULL)
    {
        printf("Error: %s not contain side\n", data);
        exit(1);
    }
    side = atof(data);
    return (side);
}

int	parser_square(Scene *scene, char **data)
{
    Vector3 center = {0, 0, 0};
    Vector3 normal = {0, 0, 0};
    double side = 0;
    Color color = {0, 0, 0};

   // printf(" SQUARE ----->1|%s| 2|%s| 3|%s| 4|%s| 5 |%s| \n", data[0], data[1], data[2], data[3], data[4]);
    //CENTER

	scene->squares = ft_realloc(scene->squares, sizeof(Square) * scene->n_squares, sizeof(Square) * (scene->n_squares + 2));
    center = ft_coordinate(data[1]);
    normal = ft_normalizate(data[2]);
    side = side_square(data[3]);
    color = ft_color(data[4]);

    scene->squares->center = center;
    scene->squares->normal = normal;
    scene->squares->side = side;
    scene->squares->mater_prop.vColor = rgb_to_color((int)color.r, (int)color.g, (int)color.b);
    scene->squares[scene->n_squares].mater_prop.absorption[R] = 1 - scene->squares[scene->n_squares].mater_prop.vColor->r;
	scene->squares[scene->n_squares].mater_prop.absorption[G] = 1 - scene->squares[scene->n_squares].mater_prop.vColor->g;
	scene->squares[scene->n_squares].mater_prop.absorption[B] = 1 - scene->squares[scene->n_squares].mater_prop.vColor->b;
	scene->squares[scene->n_squares].mater_prop.reflect = 0;
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