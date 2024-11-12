#include "../main.h"

int	idstr(char *alphabet[], char *str)
{
	int	i;

	i = -1;
	while (alphabet[++i])
		if (ft_strncmp(alphabet[i], str, ft_strlen(str)) == 0)
			return (i);
	return (8); //devolver el ultimo + 1 idx del alphabet
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
	scene->parser[PLANE] = parser_plane;//posicion 0
	scene->parser[SPHERE] = parser_sphere;//posicion 1
	scene->parser[CAMERA] = parser_camera;//posicion 2
	scene->parser[LIGHT] = parser_light;//posicion 3
}

/**
 * Terminar de llenar el alphabet de objetos
 */
char **init_args()
{
	char **alphabet;
	alphabet = ft_sarradd(alphabet, "pl"); //posicion 0
	alphabet = ft_sarradd(alphabet, "sp");//posicion 1
	alphabet = ft_sarradd(alphabet, "l");//posicion 2
	alphabet = ft_sarradd(alphabet, "cm");//posicion 3
	return alphabet;
}

/**
 * Aqui va el codigo de automata para resolver 
 * el parseo
 */
int parser_obj(Scene *scene, int fd)
{
	init_parser(scene);
	char **data;
	char **alphabet = init_args();
	//Abrir el archivo
	//Leerlo
	//Reconoce patrones los typos
	//en caso de que encuetres un 'pl'en el argumento 0 del split vas a llamar
	//para vos data es un split de los valores de la linea
	while (1)
	{
		char *line = get_next_line(fd);
		if (!line)
			return NULL;
		data = split(line, ' '); //Esto te debe devolver data[0]->"pl" data[1]->"0.0,0.0,-10.0" data[2]->"0.0,1.0,0.0" data[3]->"0,0,225"
		int state = idstr(alphabet, data[0]); //data[0]->"pl" entonces idstr debe devolver 0
		//if (state == 8) entonces tienes que dar error.
		if (scene->parser[state]) //por tanto state es 0.
			scene->parser[state](scene, data); //ejecuto la funciond e la posicion 0, que en este caso seria parser_plane
	}
	//vas a splitear la linea
}