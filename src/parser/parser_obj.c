/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:06:04 by razamora          #+#    #+#             */
/*   Updated: 2024/11/16 16:09:16 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"


int	idstr(char *alphabet[], char *str)
{
	int	i;

	i = -1;
	while (alphabet[++i])
		if (ft_strncmp(alphabet[i], str, ft_strlen(str)) == 0)
			return (i);
	return (9); //devolver el ultimo + 1 idx del alphabet
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

int parser_obj(Scene *scene, int fd)
{
	init_parser_fun(scene);
	char **data;
	int i=0;
	char **alphabet = init_args();
	char *line = get_next_line(fd);

	while (line)//No olvidarse de poner una comprobacion o hacer brake
	{
		data = ft_split_space(line); //Esto te debe devolver data[0]->"pl" data[1]->"0.0,0.0,-10.0" data[2]->"0.0,1.0,0.0" data[3]->"0,0,225"
		if (data == NULL || *data == NULL)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		int state = idstr(alphabet, data[0]); //data[0]->"pl" entonces idstr debe devolver 0
		if (state == 11)
		{
			printf("Error: %s no es un typo valido\n", data[0]);
			exit(1);
		}
		if (scene->parser[state]){
			printf("%s\n", data[0]);
			scene->parser[state](scene, data);}
		free(line);
		ft_free_p2(data);
		line = get_next_line(fd);
	}
	printf("n_l: %d\n", scene->n_lights);
	printf("n_cy: %d\n", scene->n_cylinders);
	printf("n_tr: %d\n", scene->n_triangles);
	printf("n_pl: %d\n", scene->n_planes);
	printf("n_sp: %d\n", scene->n_spheres);
	printf("n_sq: %d\n", scene->n_squares);

}
