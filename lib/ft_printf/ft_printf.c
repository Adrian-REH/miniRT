/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 04:19:20 by adherrer          #+#    #+#             */
/*   Updated: 2024/03/31 00:58:17 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_e(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		if (write(fd, &s[i++], 1) < 0)
			return (-1);
	return (i);
}

size_t	puts_str(char *str)
{
	if (!str)
		return (ft_putstr_e("(null)", 1));
	return (ft_putstr_e(str, 1));
}

static void	puts_nbr(char const *format, va_list args, size_t *printed)
{
	int		result;
	long	sign;

	result = 0;
	sign = 0;
	if (*format == 'p')
		result = (ft_putstr_fd("0x", 1), 2)
			+ ft_strnbr_base(((size_t)va_arg(args, void *)), HEX_LOW, 1, 1);
	else if (*format == 'd' || *format == 'i')
	{
		sign = va_arg(args, int);
		if (sign < 0)
			result = ft_strnbr_base((size_t)(sign) * -1, DEC_DEF, 1, -1);
		else
			result = ft_strnbr_base((size_t)sign, DEC_DEF, 1, 1);
	}
	else if (*format == 'u')
		result = ft_strnbr_base(va_arg(args, unsigned int), DEC_DEF, 1, 1);
	else if (*format == 'x')
		result = ft_strnbr_base(va_arg(args, unsigned int), HEX_LOW, 1, 1);
	else if (*format == 'X')
		result = ft_strnbr_base(va_arg(args, unsigned int), HEX_UPP, 1, 1);
	*printed += result;
}

static int	process_format_specifier(const char *str,
	va_list args, size_t *printed)
{
	int	value;

	if (*str == 's')
		*printed += puts_str(va_arg(args, char *));
	else if (*str == 'c' && ++(*printed))
	{
		value = va_arg(args, int);
		if (write(1, &value, 1) < 0)
			return (-1);
	}
	else if (*str == 'p' || *str == 'd' || *str == 'i' || *str == 'u'
		|| *str == 'x' || *str == 'X')
	{
		puts_nbr(str, args, printed);
	}
	else if (*str == '%' && ++(*printed))
	{
		if (write(1, "%", 1) < 0)
			return (-1);
	}
	else
		if (write(1, (str - 1), 1) < 0)
			return (-1);
	return (0);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	size_t	printed;

	va_start(args, str);
	printed = 0;
	while (*str && str)
	{
		if (*str == '%')
		{
			str++;
			if (process_format_specifier(str, args, &printed) < 0)
				return (-1);
		}
		else
		{
			if (write (1, str, 1) < 0)
				return (-1);
			printed++;
		}
		str++;
	}
	va_end(args);
	return (printed);
}

/* 
#include "limits.h"

 int main()
{
	char *str = "HOLA";
	int n = INT_MIN;
	char z = 'z';
	char *mask = "%c %sss %% dd%%dd d@@@%% %% %d %X----%x %p.%%%i %u...\n";
	int res =     printf(mask, z, str, n, n, n, 2,2, &n);
	int res2 = ft_printf(mask, z, str, n, n, n, 2,2, &n);
	printf("%d vs %d\n", res, res2);

} */