/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:03:46 by razamora          #+#    #+#             */
/*   Updated: 2024/11/21 21:06:06 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static int	ft_iterative_power(int nb, int power)
{
	int	result;

	result = 1;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (power > 0)
	{
		result *= nb;
		power--;
	}
	return (result);
}

double	ft_atof(const char *str)
{
	int		sign;
	double	result;
	double	decimal;
	int		i;
	int		j;

	j = 0;
	i = 0;
	sign = 1;
	result = 0;
	decimal = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
		if (str[i++] == 45)
			sign *= -1;
	while (str[i] >= 48 && str[i] <= 57 && str[i] != '.')
		result = result * 10 + (str[i++] - 48);
	i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		decimal = decimal * 10 + (str[i++] - 48);
		j++;
	}
	return ((result + decimal / ft_iterative_power(10, j)) * sign);
}
