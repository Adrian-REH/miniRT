/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:12:23 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/13 23:38:53 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//----------------------------COLOR----------------------------

//OBJECT----------------------------------------------

int is_in_shadow(Scene scene, int plane_count, Vector3 light_pos, Vector3 hit_point) 
{
	Ray shadow_ray;
	shadow_ray.origin = hit_point;
	shadow_ray.direction = *normalize_withpoint(hit_point, light_pos); // Vector from hit_point to light

	double light_dist = distance(hit_point, light_pos);
	double t = 0;

 
	 // Check intersection with all planes
	for (int i = 0; i < plane_count; ++i) {
		if (intersect_plane(&shadow_ray, &scene.planes[i], &t)) {
			if (t > 0 && t < light_dist) {
				return t; // In shadow
			}
		}
	} 
   // Check intersection with the sphere
	if (intersect_sphere(&shadow_ray, scene.spheres, &t)) {
		if (t > 0 && t < light_dist) {
			return t; // In shadow
		}
	}
 
	return 0; // Not in shadow
}

int init_file(char *file)
{
	int fd;
	int len_file = ft_strlen(file);
	if (file[len_file - 1] != 't' && file[len_file - 2] != 'r' && file[len_file - 3] != '.')
	{
		printf("Error: El archivo no es un archivo .rt\n");
		exit(1);
	}
	fd = open(file, 0);	
	if (fd < 0)
	{
		printf("Error al abrir el archivo\n");
		exit(1);
	}
	return (fd);
}

int main()
{
	Scene *scene = malloc(sizeof(Scene));
	ft_bzero(scene, sizeof(Scene));
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, WINX, WINY, "miniRT!");
	Img img;
	scene->img = &img;
	scene->img->img = mlx_new_image(scene->mlx, WINX, WINY);
	scene->img->buffer = mlx_get_data_addr(scene->img->img, &(scene->img->bitxpixel), &(scene->img->lines), &(scene->img->endian));

	//PARSER----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	parser_obj(scene, init_file("mandatory.rt"));
	parser_plane(scene, NULL);
	parser_light(scene, NULL);
	parser_sphere(scene, NULL);
	parser_camera(scene, NULL);
	
	//render(mlx, win, WINX, WINY, sphere, plans, camera_pos, buffer);
	printf("Original RGB: (%.2f, %.2f, %.2f) = %06X\n", scene->planes[0].mater_prop.vColor->r, scene->planes[0].mater_prop.vColor->g, scene->planes[0].mater_prop.vColor->b, scene->planes[0].mater_prop.vColor->color);
	printf("ABS RGB: (%.2f, %.2f, %.2f) = %06X\n", scene->planes[0].mater_prop.absorption[R], scene->planes[0].mater_prop.absorption[G], scene->planes[0].mater_prop.absorption[B], scene->planes[0].mater_prop.vColor->color);
	printf("Original RGB: (%.2f, %.2f, %.2f) = %06X\n", scene->planes[1].mater_prop.vColor->r, scene->planes[1].mater_prop.vColor->g, scene->planes[1].mater_prop.vColor->b, scene->planes[1].mater_prop.vColor->color);
	printf("Original RGB: (%.2f, %.2f, %.2f) = %06X\n", scene->planes[2].mater_prop.vColor->r, scene->planes[2].mater_prop.vColor->g, scene->planes[2].mater_prop.vColor->b, scene->planes[2].mater_prop.vColor->color);
	printf("Original RGB: (%.2f, %.2f, %.2f) = %06X\n", scene->planes[3].mater_prop.vColor->r, scene->planes[3].mater_prop.vColor->g, scene->planes[3].mater_prop.vColor->b, scene->planes[3].mater_prop.vColor->color);
	printf("Original RGB: (%.2f, %.2f, %.2f) = %06X\n", scene->planes[4].mater_prop.vColor->r, scene->planes[4].mater_prop.vColor->g, scene->planes[4].mater_prop.vColor->b, scene->planes[4].mater_prop.vColor->color);
	printf("Original RGB: (%.2f, %.2f, %.2f) = %06X\n", scene->lights->color->r, scene->lights->color->g, scene->lights->color->b, scene->lights->color->color);
	//RENDER----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//ft_memset(scene->img->buffer, 0 ,((WINY - 1)* WINX * 4) + ((WINX - 1) * 4));
	render_scene(scene, 1);
	free(scene->planes);
	mlx_loop(scene->mlx);
}