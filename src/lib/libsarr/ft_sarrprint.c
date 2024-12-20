/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sarrprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:24:36 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:24:38 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	ft_sarrprint(char **arr)
{
	int	i;

	if (!arr || !arr[0])
		return (0);
	i = -1;
	while (arr[++i])
	{
		ft_putstr_fd(arr[i], 1);
		ft_putstr_fd("\n", 1);
	}
	return (i);
}
