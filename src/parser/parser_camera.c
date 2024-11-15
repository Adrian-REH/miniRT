#include "../main.h"

int	parser_camera(Scene *scene, char **data)
{

	
	//printf ("Camera realizar funcion\n");
	(void)data;

	Camera camera;

	char **args = ft_split(data[0], ',');
	
	// printf("camera----> %s %s %s\n", args[0], args[1], args[2]);
	// // if (ft_sarrsize(args) != 3)
	// // {
	// // 	printf("Error: %s no es un typo valido\n", data[0]);
	// // 	exit(1);
	// // }

	// // exit(1);

	// scene->cameras = malloc(sizeof(Camera));
	// scene->cameras->pos = (Vector3){0, 0, 30};
	// // Ajusta el tamaño del plano de proyección en función de la relación de aspecto
	// scene->cameras->aspect_ratio = (double)WINX/WINY;
	// double fov = 50;
	// scene->cameras->plane_distance = tan((fov / 2) * (M_PI / 180));
	// scene->cameras->plane_half_width = scene->cameras->aspect_ratio * scene->cameras->plane_distance; // Ajuste según el aspecto
	// scene->cameras->plane_half_height = 1.0 * scene->cameras->plane_distance;         // Altura basada en la distancia
	// scene->cameras->dir = (Vector3){0, 0, -1}; // Apunta hacia el -Z
	// scene->cameras->horizontal = (Vector3){1, 0, 0};      // Apunta hacia la derecha
	// scene->cameras->vertical = (Vector3){0, -1, 0};         // Apunta hacia arriba
}