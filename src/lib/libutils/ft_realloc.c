/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 21:12:06 by razamora          #+#    #+#             */
/*   Updated: 2024/11/21 21:24:10 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	*ft_realloc(void *ptr, size_t size_old, size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new, ptr, size_old);
		free(ptr);
	}
	if (size > size_old)
		ft_bzero(new + size_old, size - size_old);
	return (new);
}
