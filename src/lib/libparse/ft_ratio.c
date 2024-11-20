/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ratio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:38:54 by razamora          #+#    #+#             */
/*   Updated: 2024/11/18 18:48:48 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

double ft_ratio(char *str)
{
	double	ratio;
    
	if (str == NULL)
	{
		printf("Error: %s not contain ratio\n", str);
		exit(1);
	}
	ratio = atof(str);
	return (ratio);
}