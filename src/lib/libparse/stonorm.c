/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stonorm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:37:04 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 23:03:38 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

t_vector3	stonorm(char *argv)
{
	t_vector3	norm;
	char		**args;

	args = ft_split(argv, ',');
	if (ft_sarrsize(args) != 3)
	{
		printf("Error: Not contain norme x, x ,y\n");
		exit(1);
	}
	norm.x = ft_limit(-1, 1, atof(args[0]));
	norm.y = ft_limit(-1, 1, atof(args[1]));
	norm.z = ft_limit(-1, 1, atof(args[2]));
	ft_free_p2(args);
	return (norm);
}
