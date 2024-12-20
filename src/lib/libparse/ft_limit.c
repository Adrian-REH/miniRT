/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_limit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:40:02 by razamora          #+#    #+#             */
/*   Updated: 2024/12/01 18:10:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

double	ft_limit(double min, double max, double val)
{
	if (val < min || val > max)
	{
		printf(" max %f < val %f || val %f > min %f\n", max, val, val, min);
		printf("Error el valor no se encuentra entre los limites [%f, %f]", \
			min, max);
		exit(1);
	}
	return (val);
}
