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

int	idstr(char *alphabet[], char *str)
{
	int	i;

	i = -1;
	while (alphabet[++i])
		if (ft_strncmp(alphabet[i], str, ft_strlen(str)) == 0)
			return (i);
	return (9); //devolver el ultimo + 1 idx del alphabet
}

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

/**
 * Terminar de
 */
void init_parser(Scene *scene)
{
	scene->parser[0] = parser_resolution;//posicion 0
	scene->parser[1] = parser_ambient;//posicion 1
	scene->parser[2] = parser_camera;//posicion 2
	scene->parser[3] = parser_light;//posicion 3
	scene->parser[4] = parser_plane;//posicion 4
	scene->parser[5] = parser_sphere;//posicion 5
	scene->parser[6] = parser_square;//posicion 6
	scene->parser[7] = parser_cylinder;//posicion 7
	scene->parser[8] = parser_triangle;//posicion 8
	scene->parser[9] = NULL; // NULL 

}

/**
 * Terminar de llenar el alphabet de objetos
 */
char **init_args()
{
	char **alphabet;
	alphabet = ft_sarradd(alphabet, "R"); //posicion 0 Resolution
	alphabet = ft_sarradd(alphabet, "A");//posicion 1 Ambient
	alphabet = ft_sarradd(alphabet, "c");//posicion 2	camara
	alphabet = ft_sarradd(alphabet, "l");//posicion 2	Light
	alphabet = ft_sarradd(alphabet, "pl");//posicion 4 Plane
	alphabet = ft_sarradd(alphabet, "sp"); //posicion 5 Sphere
	alphabet = ft_sarradd(alphabet, "sq");//posicion 6 Square
	alphabet = ft_sarradd(alphabet, "cy");//posicion 7 Cylinder
	alphabet = ft_sarradd(alphabet, "tr");//posicion 8 Triangle
	return (alphabet);
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
	init_parser(scene);
	char **data;
	int i=0;
	char **alphabet = init_args();

	//int i = 0;
	//Abrir el archivo
	//Leerlo
	//Reconoce patrones los typos
	//en caso de que encuetres un 'pl'en el argumento 0 del split vas a llamar
	//para vos data es un split de los valores de la linea
	char *line = get_next_line(fd);
	while (line)//No olvidarse de poner una comprobacion o hacer brake
	{
		data = ft_split(line, ' '); //Esto te debe devolver data[0]->"pl" data[1]->"0.0,0.0,-10.0" data[2]->"0.0,1.0,0.0" data[3]->"0,0,225"
		if (data == NULL || *data == NULL)
			continue ;

		int state = idstr(alphabet, data[0]); //data[0]->"pl" entonces idstr debe devolver 0
		printf("state: %d\n", state);
		if (state == 11)
		{
			printf("Error: %s no es un typo valido\n", data[0]);
			exit(1);
		}
		//if (state == 8) entonces tienes que dar error.
		if (scene->parser[state]) //por tanto state es 0.
			scene->parser[state](scene, data); //ejecuto la funciond e la posicion 0, que en este caso seria parser_plane
		ft_sarrprint(data);
		free(line);
		ft_free_p2(data);
		line = get_next_line(fd);
	}
	printf("resolution: %d %d\n", scene->width, scene->height);

	printf("ambient: %d\n", scene->ambient->ratio);
	//printf("color (%f, %f, %f)\n", scene->ambient->color.r, scene->ambient->color.g, scene->ambient->color.b);
	printf("n_planes: %d\n", scene->n_planes);
	printf(" norme (%f, %f, %f)\n", scene->planes[0].normal.x,scene->planes[0].normal.y,scene->planes[0].normal.z);
	printf(" axis (%f, %f, %f)\n", scene->planes[0].point.x,scene->planes[0].point.y,scene->planes[0].point.z);
	printf(" vCOlor (%f, %f, %f)\n", scene->planes[0].mater_prop.vColor->r, scene->planes[0].mater_prop.vColor->g, scene->planes[0].mater_prop.vColor->b);
	

	printf("CAMERA: \n");
	printf(" pos (%f, %f, %f)\n", scene->cameras[0].pos.x,scene->cameras[0].pos.y,scene->cameras[0].pos.z);
	printf(" dir (%f, %f, %f)\n", scene->cameras[0].dir.x,scene->cameras[0].dir.y,scene->cameras[0].dir.z);
	printf(" fov (%f )\n", scene->cameras[0].fov);
	

	printf("SPHERE: %d\n", scene->n_planes);
	printf(" norme (%f, %f, %f)\n", scene->spheres[0].center.x,scene->spheres[0].center.y,scene->spheres[0].center.z);
	printf(" Radous (%f )\n", scene->spheres[0].radius);
	printf(" vCOlor (%f, %f, %f)\n", scene->spheres[0].mater_prop.vColor->r, scene->spheres[0].mater_prop.vColor->g, scene->spheres[0].mater_prop.vColor->b);


	printf("SQUERE: \n");
	printf(" center (%f, %f, %f)\n", scene->squares[0].center.x,scene->squares[0].center.y,scene->squares[0].center.z);
	printf(" normal (%f, %f, %f)\n", scene->squares[0].normal.x,scene->squares[0].normal.y,scene->squares[0].normal.z);
	printf(" side (%f )\n", scene->squares[0].side);
	//printf(" vColor (%f, %f, %f)\n", scene->squares[0].mater_prop.vColor->r, scene->squares[0].mater_prop.vColor->g, scene->squares[0].mater_prop.vColor->b);

	printf("CYLINDER: %d\n", scene->n_cylinders);
	printf(" center (%f, %f, %f)\n", scene->cylinders[0].center.x,scene->cylinders[0].center.y,scene->cylinders[0].center.z);
	printf(" axis (%f, %f, %f)\n", scene->cylinders[0].axis.x,scene->cylinders[0].axis.y,scene->cylinders[0].axis.z);
	printf(" diameter (%f )\n", scene->cylinders[0].diameter);
	printf(" height (%f )\n", scene->cylinders[0].height);
	//printf(" vColor (%f, %f, %f)\n", scene->cylinders[0].color.r, scene->cylinders[0].mater_prop.vColor->g, scene->cylinders[0].mater_prop.vColor->b);
	//vas a splitear la linea
}
