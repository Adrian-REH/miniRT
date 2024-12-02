/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sarradd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:24:38 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:24:39 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

char	**ft_sarradd(char **arr, char *string)
{
	int		size;
	char	**new_arr;

	if (!string)
		return (arr);
	size = ft_sarrsize(arr) + 2;
	new_arr = malloc(sizeof(char *) * (size));
	if (!new_arr)
		return (NULL);
	size = 0;
	if (arr)
	{
		while (arr[size])
		{
			new_arr[size] = ft_strdup(arr[size]);
			if (!new_arr[size++])
				return (ft_free_p2(new_arr), NULL);
		}
		ft_free_p2(arr);
	}
	new_arr[size++] = ft_strdup(string);
	if (!new_arr[size - 1])
		return (ft_free_p2(new_arr), NULL);
	new_arr[size] = NULL;
	return (new_arr);
}
