
#include "../main.h"

void	*ft_realloc(void *ptr, size_t size_old, size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new, ptr, size_old);
		free(ptr);
	}
	if (size > size_old)
		ft_bzero(new + size_old, size - size_old);
	return (new);
}

/**
 * Re alocar la memoria de scene->planes para guardar los datos del nuevo plano.
 */
int	parser_plane(Scene *scene, char **data)
{
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
	//scene->planes[scene->n_planes].normal = (Vector3)str_to_Vecotr3(data[1]); 
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







	scene->planes =  malloc(sizeof(Plane) * 6);
	scene->n_planes = 0;
	scene->planes[scene->n_planes] =  (Plane){{0, 0, 1}, {0, 0, -1}};
	scene->planes[scene->n_planes].mater_prop.color[0] = 0xb29674;
	scene->planes[scene->n_planes].mater_prop.color[1] = 0xb29674;
	scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0xcbb677);
	scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->g;
	scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->b;
	scene->n_planes++;
	scene->planes[scene->n_planes] =  (Plane){{1, 0, 0}, {-10, 0, 0}};
	scene->planes[scene->n_planes].mater_prop.color[0] = 0xff001d;
	scene->planes[scene->n_planes].mater_prop.color[1] = 0xff001d;
	scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0xff001d);
	scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->g;
	scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->b;
	scene->n_planes++;
	scene->planes[scene->n_planes] =  (Plane){{-1, 0, 0}, {10, 0, 0}};
	scene->planes[scene->n_planes].mater_prop.color[0] = 0x00ffb5;
	scene->planes[scene->n_planes].mater_prop.color[1] = 0x00ffb5;
	scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0x00ffb5);
	scene->planes[scene->n_planes].mater_prop.absorption[R] =1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->g;
	scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->b;
	scene->n_planes++;
	scene->planes[scene->n_planes] =  (Plane){{0, -1, 0}, {0, 5.5, 0}};
	scene->planes[scene->n_planes].mater_prop.color[0] = 0xb29674;
	scene->planes[scene->n_planes].mater_prop.color[1] = 0xb29674;
	scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0xcbb677);
	scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->g;
	scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 -scene->planes[scene->n_planes].mater_prop.vColor->b;
	scene->n_planes++;
	scene->planes[scene->n_planes] =  (Plane){{0, 1, 0}, {0, -5.5, 0}};
	scene->planes[scene->n_planes].mater_prop.color[0] = 0xb29674;
	scene->planes[scene->n_planes].mater_prop.color[1] = 0xb29674;
	scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0xcbb677);
	scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->g;
	scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->b;
	scene->n_planes++;
	scene->planes[scene->n_planes] =  (Plane){{0, 0, 35}, {0, 0, 1}};
	scene->planes[scene->n_planes].mater_prop.color[0] = 0xb29674;
	scene->planes[scene->n_planes].mater_prop.color[1] = 0xb29674;
	scene->planes[scene->n_planes].mater_prop.color[2] = 0xFFFFFF;
	scene->planes[scene->n_planes].mater_prop.vColor = int_to_color(0xcbb677);
	scene->planes[scene->n_planes].mater_prop.absorption[R] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->r;
	scene->planes[scene->n_planes].mater_prop.absorption[G] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->g;
	scene->planes[scene->n_planes].mater_prop.absorption[B] = 1 - scene->planes[scene->n_planes].mater_prop.vColor->b;
	normalize(&scene->planes[0].normal);
	normalize(&scene->planes[1].normal);
	normalize(&scene->planes[2].normal);
	normalize(&scene->planes[3].normal);
	normalize(&scene->planes[4].normal);
	normalize(&scene->planes[5].normal);

}