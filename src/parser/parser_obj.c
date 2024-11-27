/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:06:04 by razamora          #+#    #+#             */
/*   Updated: 2024/11/26 19:23:08 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	idstr(char *alphabet[], char *str)
{
	int	i;

	i = -1;
	if (ft_strlen(str) == 1)
		str = ft_memmap(str, ft_strlen(str), ft_toupper);
	else
		str = ft_memmap(str, ft_strlen(str), ft_tolower);
	while (alphabet[++i])
		if (ft_strncmp(alphabet[i], str, 2) == 0)
			return (i);
	return (9);
}

/**
 * Aqui va el codigo de automata para resolver 
 * el parseo
 */
int	ft_countword(const char *s, int c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c && (s[1] == c || s[1] == 0))
			count++;
		s++;
	}
	return (count);
}

int	parser_obj(t_scene *scene, int fd)
{
	char	**data;
	char	**alphabet;
	char	*line;
	int		state;

	init_parser_fun(scene);
	alphabet = init_args();
	line = get_next_line(fd);
	while (line)
	{
		data = ft_split_space(line);
		if (data == NULL || *data == NULL)
		{
			line = (free(line), ft_free_p2(data), get_next_line(fd));
			continue ;
		}
		state = idstr(alphabet, data[0]);
		if (scene->parser[state])
			scene->parser[state](scene, data);
		else
			printf("The argument is not recognized: %s\n", data[0]);
		(free(line), ft_free_p2(data));
		line = get_next_line(fd);
	}
	return (0);
}
