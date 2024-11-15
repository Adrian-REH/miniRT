#include "../main.h"




int	parser_cylinder(Scene *scene, char **data)
{

	/*
	cy
	50.0,0.0,20.6
	0,0,1.0
	14.2
	21.42
	10, 0,255
		Vector3	center;
	Vector3	axis;
	double	diameter;
	double	height;
	int		color;
	*/

	Vector3		center =  {0.0, 0.0, 0.0};
	Vector3		axis = {0.0, 0.0, 0.0};
	double	diameter;
	double	height;
	Color color = {0, 0, 0};

	Cylinder cylinder_null;
	scene->cylinders = ft_realloc(scene->cylinders, sizeof(Cylinder) * scene->n_cylinders, sizeof(Cylinder) * (scene->n_cylinders + 2));

	char **args = ft_split(data[1], ',');
	if (ft_sarrsize(args) != 3)
	{
		printf("Error: %s not contain coor x, x ,y\n", data[1]);
		exit(1);
	}
	center.x = atof(args[0]);
	center.y = atof(args[1]);
	center.z = atof(args[2]);

	ft_free_p2(args);

	args = ft_split(data[2], ',');

	if (ft_sarrsize(args) != 3)
	{
		printf("Error: %s not contain coor x, x ,y\n", data[2]);
		exit(1);
	}
	axis.x = atof(args[0]);
	axis.y = atof(args[1]);
	axis.z = atof(args[2]);
	if (axis.x < -1 || axis.x > 1)
	{
		printf("Error: %s Axis x not valide\n", data[2]);
		exit(1);
	}
	if (axis.y < -1 || axis.y > 1)
	{
		printf("Error: %s Axis x not valide\n", data[2]);
		exit(1);
	}
	if (axis.z < -1 || axis.z > 1)
	{
		printf("Error: %s Axis x not valide\n", data[2]);
		exit(1);
	}
	printf("----> axis (%f %f %f) \n", axis.x, axis.y, axis.z);
	ft_free_p2(args);

	if (data[3] == NULL)
	{
		printf("Error: %s not contain diameter\n", data[3]);
		exit(1);
	}
	diameter = atof(data[3]);

	if (data[4] == NULL)
	{
		printf("Error: %s not contain height\n", data[4]);
		exit(1);
	}	
	height = atof(data[4]);

	args = ft_split(data[5], ',');
	if (ft_sarrsize(args) != 3)
	{
		printf("Error: %s not contain color r, g, b\n", data[5]);
		exit(1);
	}	
	color.r = atof(args[0]);
	color.g = atof(args[1]);
	color.b = atof(args[2]);
	if (color.r < 0 || color.r > 255)
	{
		printf("Error: %s  r outside color range\n", data[5]);
		exit(1);
	}
	if (color.g < 0 || color.g > 255)
	{
		printf("Error: %s g outside color range\n", data[5]);
		exit(1);
	}
	if (color.b < 0 || color.b > 255)
	{
		printf("Error: %s b outside color range\n", data[5]);
		exit(1);
	}

	scene->cylinders[scene->n_cylinders].center = center;
	scene->cylinders[scene->n_cylinders].axis = axis;
	scene->cylinders[scene->n_cylinders].diameter = diameter;
	scene->cylinders[scene->n_cylinders].height = height;
	scene->cylinders[scene->n_cylinders].color = rgb_to_color((int)color.r, (int)color.g, (int)color.b);


	


	


}