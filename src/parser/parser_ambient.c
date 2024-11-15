#include "../main.h"

int	parser_ambient(Scene *scene, char **data)
{

    Color color = {0, 0, 0};
    printf("Ambient function fichero para procesar\n");

    scene->ambient = malloc(sizeof(Ambient));

   scene->ambient->ratio = atof(data[1]);

char **args = ft_split(data[2], ',');
if (ft_sarrsize(args) != 3)
{
    printf("Error: %s not contain color r, g, b\n", data[2]);
    exit(1);
}
color.r = atof(args[0]);
color.g = atof(args[1]);
color.b = atof(args[2]);


if (color.r < 0 || color.r > 255)
{
    printf("Error: %s not contain color r, g, b\n", data[2]);
    exit(1);
}
if (color.g < 0 || color.g > 255)
{
    printf("Error: %s not contain color r, g, b\n", data[2]);
    exit(1);
}
if (color.b < 0 || color.b > 255)
{
    printf("Error: %s not contain color r, g, b\n", data[2]);
    exit(1);
}






}