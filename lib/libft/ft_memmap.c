/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 23:12:29 by adherrer          #+#    #+#             */
/*   Updated: 2024/03/25 00:13:46 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmap(void *src, size_t len, int (*f)(int))
{
	char	*var;

	if (!src)
		return (src);
	var = (char *)src;
	while (len-- > 0)
		*(var + len) = f((int)var[len]);
	return (var);
}
