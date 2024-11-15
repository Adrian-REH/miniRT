#include "../main.h"

int	parser_resolution(Scene *scene, char **data)
{
	scene->width = ft_atoi(data[1]);
	scene->height = ft_atoi(data[2]);
	return (0);
}
