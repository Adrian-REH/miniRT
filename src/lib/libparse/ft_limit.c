/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_limit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:40:02 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 22:08:45 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

double	ft_limit(double min, double max, double val)
{
	if ( max < val || val > min)
		return val;
	printf("Error el valor no se encuentre entre los limites [%f, %f]", min, max);
	//llamar a una funcion que libere
	exit(1);
}