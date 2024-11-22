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

int	solve_quadratic(Vector3 val, double *t0, double *t1)
{
	double	discriminant;
	double	q;
	double	temp;

	discriminant = val.y * val.y - 4 * val.x * val.z;
	if (discriminant < 0)
		return (0);
	if (val.y > 0)
		q = -0.5 * (val.y + sqrt(discriminant));
	else
		q = -0.5 * (val.y - sqrt(discriminant));
	*t0 = q / val.x;
	*t1 = val.z / q;
	if (*t0 > *t1)
	{
		temp = *t0;
		*t0 = *t1;
		*t1 = temp;
	}
	return (1);
}
