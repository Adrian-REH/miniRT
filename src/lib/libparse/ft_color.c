/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:44:12 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 22:46:06 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

Color ft_color(char *str)
{
    Color color;
    char **args = ft_split(str, ',');

    color.r = ft_limit(0.0, 255.0, atof(args[0]));
    color.g = ft_limit(0.0, 255.0, atof(args[1]));
    color.b = ft_limit(0.0, 255.0, atof(args[2]));
    return (color);
}