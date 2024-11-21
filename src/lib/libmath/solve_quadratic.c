/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:06:54 by razamora          #+#    #+#             */
/*   Updated: 2024/11/21 21:08:34 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	solve_quadratic(double a, double b, double c, double* t0, double* t1)
{
	double	discriminant;
	double	q;
	double	temp;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);

	q = (b > 0) ? -0.5 * (b + sqrt(discriminant)) : -0.5 * \
	(b - sqrt(discriminant));
	*t0 = q / a;
	*t1 = c / q;
	if (*t0 > *t1)
	{
		temp = *t0;
		*t0 = *t1;
		*t1 = temp;
	}
	return (1);
}
