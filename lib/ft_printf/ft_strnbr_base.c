/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:02:57 by adherrer          #+#    #+#             */
/*   Updated: 2024/03/30 23:41:57 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	sizenbr(size_t nbr, int base_nbr)
{
	int	count;

	count = 0;
	while (nbr >= 1)
	{
		count++;
		nbr /= base_nbr;
	}
	return (count);
}

static int	ft_savestr(char *str, char *base, int base_nbr, size_t nbr)
{
	int	mod;
	int	n;

	mod = 0;
	n = 0;
	while (nbr >= 1)
	{
		mod = nbr % base_nbr;
		str[n++] = base[mod];
		nbr /= base_nbr;
	}
	return (n);
}

int	ft_strnbr_base(size_t nbr, char *base, int fd, int sign)
{
	int		base_nbr;
	char	*str;
	int		n;

	n = 0;
	if (sign < 0)
		write(fd, "-", 1);
	if (nbr == 0)
		return (write(fd, &base[0], 1), 1);
	base_nbr = ft_strlen(base);
	str = ft_calloc((sizenbr(nbr, base_nbr) + 1), sizeof(char));
	if (!str)
		return (0);
	n = ft_savestr(str, base, base_nbr, nbr);
	while (n > 0)
		if (write(fd, &str[--n], 1) < 0)
			return (free(str), -1);
	base_nbr = ft_strlen(str);
	if (sign < 0)
		base_nbr++;
	return (free(str), base_nbr);
}
