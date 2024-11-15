
#include "../main.h"



/**
 * Re alocar la memoria de scene->planes para guardar los datos del nuevo plano.
 */
int	parser_plane(Scene *scene, char **data)
{
	// printf("Plane\n");
	// return 0;
	(void)data;
	// data[0] -> typo 
	// data[1] -> Point inside of plane 
	// data[2] -> Normal 
	// data[3] -> Color RGB

	Plane	plane_null;
	//sizeof(Plane) * scene->n_planes : el size de la memoria que existe
	//sizeof(Plane) * (scene->n_planes + 2) : el size de la memoria que existe mas la que queremos agregar mas el plane_null
	scene->planes = ft_realloc(scene->planes, sizeof(Plane) * scene->n_planes, sizeof(Plane) * (scene->n_planes + 2));
	//Agregar los datos necesarios para el plano en la posicion scene->n_planes
	// "0.0,0.0,0.0" -> Vector3 normal = {0.0, 0.0 ,0.0}
	int i = -1;
	Vector3 normal = {0.0, 0.0, 0.0};
	Vector3  point = {0.0, 0.0, 0.0};
	Color color = {0, 0, 0};
	char **args = ft_split(data[2], ',');



	// PARSE NORMALIZE
	if (ft_sarrsize(args) != 3)
	{
		printf("Error: %s no es un typo valido\n", data[2]);
		exit(1);
	}
	//printf("---->%d: ", ft_sarrsize(args));
	normal.x = atof(args[++i]);
	if (normal.x < -1 || normal.x > 1)
	{
		printf("Error: %s no es un typo valido\n", data[2]);
		exit(1);
	}
	normal.y = atof(args[++i]);
		printf("----> %s\n", args[1]);
		printf("----> %f\n", normal.y);

	if (normal.y < -1 || normal.y > 1)
	{
		printf("Error: %s no es un typo valido\n", data[2]);
		exit(1);
	}
	normal.z = atof(args[++i]);
	if (normal.z < -1 || normal.z > 1)
	{
		printf("Error: %s no es un typo valido\n", data[2]);
		exit(1);
	}
	printf("----> norme: (%f, %f, %f)\n", normal.x, normal.y, normal.z);
	ft_free_p2(args);


	//PARSE POINT COORDINATES
	args = ft_split(data[1], ',');
	if (ft_sarrsize(args) != 3)
	{
		printf("Error: %s eb las coordenadas\n", data[1]);
		exit(1);
	}
	i = -1;
	printf("----> Point: (%f, %f, %f)\n", point.x, point.y, point.z);
	//exit(1);
	point.x = atof(args[++i]);
	point.y = atof(args[++i]);
	point.z = atof(args[++i]);

	ft_free_p2(args);
	args = NULL;
	args = ft_split(data[3], ',');

		//COlOR

	 if (ft_sarrsize(args) != 3)
	 {
		 printf("Error: %s no es un typo valido\n", data[3]);
		 exit(1);
	 }
	 	printf("---->  color (%s %s %s) \n", args[0], args[1], args[2]);
		printf("---->  colorC( %0.f %0.f %0.f)\n", color.r, color.g, color.b);
		
		color.r = atof(args[0]);
		color.g = atof(args[1]);
		color.b = atof(args[2]);
		printf("---->  color %0.f %0.f %0.f\n", color.r, color.g, color.b);
		//exit (1);


	
	 if (color.r < 0 || color.r > 255)
	 {
		 printf("Error: %s no es un typo valido\n", data[3]);
		 exit(1);
	 }
	 if (color.g < 0 || color.g > 255)
	 {
		 printf("Error: %s no es un typo valido\n", data[3]);
		 exit(1);
	 }
	if (color.b < 0 || color.b > 255)
	 {
		 printf("Error: %s no es un typo valido\n", data[3]);
		 exit(1);
	 }
	
	scene->planes[scene->n_planes].mater_prop.vColor = rgb_to_color((int)color.r, (int)color.g, (int)color.b);
	scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->g;
	scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->b;
	scene->planes[scene->n_planes].normal = normal;
	scene->planes[scene->n_planes].point = point;


	// "0.0,0.0,0.0" -> Vector3 point = {0.0, 0.0 ,0.0}
	//scene->planes[scene->n_planes].point = (Vector3)str_to_Vecotr3(data[2]); 
	// "255,0,255" -> int r= 255; int g = 0; int b = 255;
	//scene->planes[scene->n_planes].mater_prop.vColor = (Color)rgb_to_color(r, g, b);
	//scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor.r;
	//scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 - scene->planes[scene->n_planes].mater_prop.vColor.g;
	//scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 - scene->planes[scene->n_planes].mater_prop.vColor.b;
	//Es importante iterar a uno mas para asigar el null.
	scene->n_planes++;
	ft_bzero(&plane_null, sizeof(Plane));
	scene->planes[scene->n_planes] = plane_null;
	//Re alocas el conjunto de planos







	// scene->planes =  malloc(sizeof(Plane) * 6);
	// scene->n_planes = 0;
	// scene->planes[scene->n_planes] =  (Plane){{0, 0, 1}, {0, 0, -1}};
	// scene->planes[scene->n_planes].mater_prop.color[0] = 0xb29674;
	// scene->planes[scene->n_planes].mater_prop.color[1] = 0xb29674;
	// scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	// scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0xcbb677);
	// scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	// scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->g;
	// scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->b;
	// scene->n_planes++;
	// scene->planes[scene->n_planes] =  (Plane){{1, 0, 0}, {-10, 0, 0}};
	// scene->planes[scene->n_planes].mater_prop.color[0] = 0xff001d;
	// scene->planes[scene->n_planes].mater_prop.color[1] = 0xff001d;
	// scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	// scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0xff001d);
	// scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	// scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->g;
	// scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->b;
	// scene->n_planes++;
	// scene->planes[scene->n_planes] =  (Plane){{-1, 0, 0}, {10, 0, 0}};
	// scene->planes[scene->n_planes].mater_prop.color[0] = 0x00ffb5;
	// scene->planes[scene->n_planes].mater_prop.color[1] = 0x00ffb5;
	// scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	// scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0x00ffb5);
	// scene->planes[scene->n_planes].mater_prop.absorption[R] =1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	// scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->g;
	// scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->b;
	// scene->n_planes++;
	// scene->planes[scene->n_planes] =  (Plane){{0, -1, 0}, {0, 5.5, 0}};
	// scene->planes[scene->n_planes].mater_prop.color[0] = 0xb29674;
	// scene->planes[scene->n_planes].mater_prop.color[1] = 0xb29674;
	// scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	// scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0xcbb677);
	// scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	// scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->g;
	// scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->b;
	// scene->n_planes++;
	// scene->planes[scene->n_planes] =  (Plane){{0, 1, 0}, {0, -5.5, 0}};
	// scene->planes[scene->n_planes].mater_prop.color[0] = 0xb29674;
	// scene->planes[scene->n_planes].mater_prop.color[1] = 0xb29674;
	// scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	// scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0xcbb677);
	// scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	// scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->g;
	// scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->b;
	// scene->n_planes++;
	// scene->planes[scene->n_planes] =  (Plane){{0, 0, 35}, {0, 0, 1}};
	// scene->planes[scene->n_planes].mater_prop.color[0] = 0xb29674;
	// scene->planes[scene->n_planes].mater_prop.color[1] = 0xb29674;
	// scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	// scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0xcbb677);
	// scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	// scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->g;
	// scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->b;
	// normalize(&scene->planes[0].normal);
	// normalize(&scene->planes[1].normal);
	// normalize(&scene->planes[2].normal);
	// normalize(&scene->planes[3].normal);
	// normalize(&scene->planes[4].normal);
	// normalize(&scene->planes[5].normal);

}