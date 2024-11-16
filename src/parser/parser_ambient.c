/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:06:22 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 16:57:48 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	parser_ambient(Scene *scene, char **data)
{

    Color color = {0, 0, 0};
    printf("Ambient function fichero para procesar\n");
    scene->ambient = malloc(sizeof(Ambient));
    scene->ambient->ratio = ft_radio(data[1]);
    char **args = ft_split(data[2], ',');
    if (ft_sarrsize(args) != 3)
    {
        printf("Error: %s not contain color r, g, b\n", data[2]);
        exit(1);
    }
    color.r = ft_limit(0.0, 255.0, atof(args[0]));
    //Verificar si cumple con que esta en 0 255
    color.g = ft_limit(0.0, 255.0, atof(args[1]));
    color.b = ft_limit(0.0, 255.0,  atof(args[2]));


    if (color.r < 0 || color.r > 255)
    {
        printf("Error: %s not contain color r, g, b\n", data[2]);
        exit(1);
    }
    if (color.g < 0 || color.g > 255)
    {
        printf("Error: %s not contain color r, g, b\n", data[2]);
        exit(1);
    }
    if (color.b < 0 || color.b > 255)
    {
        printf("Error: %s not contain color r, g, b\n", data[2]);
        exit(1);
    }
    scene->ambient->color = rgb_to_color(color.r, color.g, color.b);
}