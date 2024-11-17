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

# include <X11/keysym.h>
# include <X11/X.h>

int	terminate_program(void *param)
{
	Scene	*scene;

	scene = (Scene *)param;
	mlx_destroy_image(scene->mlx, scene->img->img);
	mlx_destroy_window(scene->mlx, scene->win);
	mlx_destroy_display(scene->mlx);
	//Free
	/* free(scene->vars.mlx);
	free(scene->map[0].points);
	free(scene->map); */
	exit(0);
}

/* 
*	This function handle when a key is pressed
*/
//#define XK_Left                          0xff51  /* Move left, left arrow */
//#define XK_Up                            0xff52  /* Move up, up arrow */
//#define XK_Right                         0xff53  /* Move right, right arrow */
//#define XK_Down                          0xff54  /* Move down, down arrow */
int	key_press(int key, void *param)
{
	static n_intent = 0;
	Scene	*scene;

	if (n_intent >= 1)
		return 0;
	scene = (Scene *)param;
	if (key == XK_a)
	{
		n_intent++;
		scene->cameras->dir.x -= 0.1;
		fmax(fmin(scene->cameras->dir.x, 1.0), -1.0);
		if (!scene->cameras->dir.x)
			scene->cameras->dir.x = -0.1;
		render_scene(scene, N_SAMPLING);
		n_intent--;
		printf("A Left\n");
	}
	if (key == XK_d)
	{
		n_intent++;
		scene->cameras->dir.x += 0.1;
		fmax(fmin(scene->cameras->dir.x, 1.0), -1.0);
		if (!scene->cameras->dir.x)
			scene->cameras->dir.x = +0.1;
		render_scene(scene, N_SAMPLING);
		n_intent--;
		printf("D Right\n");
	}
	if (key == XK_w)
	{
		n_intent++;
		scene->cameras->dir.y -= 0.1;
		fmax(fmin(scene->cameras->dir.y, 1.0), -1.0);
		if (!scene->cameras->dir.y)
			scene->cameras->dir.y = -0.1;
		render_scene(scene, N_SAMPLING);
		n_intent--;
		printf("W Up\n");
	}
	if (key == XK_s)
	{
		n_intent++;
		scene->cameras->dir.y += 0.1;
		fmax(fmin(scene->cameras->dir.y, 1.0), -1.0);
		if (!scene->cameras->dir.y)
			scene->cameras->dir.y = 0.1;
		render_scene(scene, N_SAMPLING);
		n_intent--;
		printf("S Down\n");
	}
	if (key == XK_Left)
	{
		n_intent++;
		scene->cameras->pos.x -= 1;
		fmax(fmin(scene->cameras->pos.x, 1.0), -1.0);
		if (!scene->cameras->pos.x)
			scene->cameras->pos.x = -0.1;
		render_scene(scene, N_SAMPLING);
		n_intent--;
		printf("Left\n");
	}
	if (key == XK_Up)
	{
		n_intent++;
		scene->cameras->pos.z -= 1.0;
		fmax(fmin(scene->cameras->pos.z, 1.0), -1.0);
		if (!scene->cameras->pos.z)
			scene->cameras->pos.z = -0.1;
		render_scene(scene, N_SAMPLING);
		n_intent--;
		printf("Up\n");
	}
	if (key == XK_Right)
	{
		n_intent++;
		scene->cameras->pos.x += 1;
		fmax(fmin(scene->cameras->pos.x, 1.0), -1.0);
		if (!scene->cameras->pos.x)
			scene->cameras->pos.x = 0.1;
		render_scene(scene, N_SAMPLING);
		n_intent--;
		printf("Right\n");
	}
	if (key == XK_Down)
	{
		n_intent++;
		scene->cameras->pos.z += 1;
		fmax(fmin(scene->cameras->pos.z, 1.0), -1.0);
		if (!scene->cameras->pos.z)
			scene->cameras->pos.z = 0.1;
		render_scene(scene, N_SAMPLING);
		n_intent--;
		printf("Down\n");
	}
	if (key == XK_Escape)
		terminate_program(param);
	return (0);
}

static void	mlx_listen_meta(Scene *scene)
{
/* 	mlx_hook(meta->vars.win, 4, 1L << 2, mouse_press, meta);
	mlx_hook(meta->vars.win, 5, 1L << 3, mouse_release, meta);
	mlx_hook(meta->vars.win, 6, 1L << 6, mouse_move, meta);
*/
	mlx_hook(scene->win, 2, 1, key_press, scene);
	mlx_hook(scene->win, 17, 1, terminate_program, scene);
	mlx_loop(scene->mlx);
}

int is_in_shadow(Scene scene, Vector3 light_pos, Vector3 hit_point) 
{
	Ray shadow_ray;
	shadow_ray.origin = hit_point;
	shadow_ray.direction = *normalize_withpoint(hit_point, light_pos); // Vector from hit_point to light

	double light_dist = distance(hit_point, light_pos);
	double t = 0;
	int i;

 
	 // Check intersection with all planes
	i = -1;
	while (++i < scene.n_planes) {
		if (intersect_plane(&shadow_ray, &scene.planes[i], &t)) {
			if (t > 0 && t < light_dist) {
				return t; // In shadow
			}
		}
	} 
   // Check intersection with the sphere
	i = -1;
	while (++i < scene.n_spheres)
	{
		if (intersect_sphere(&shadow_ray, scene.spheres, &t)) {
			if (t > 0 && t < light_dist) {
				return t; // In shadow
			}
		}
	}
   // Check intersection with the triangle
	i = -1;
	while (++i < scene.n_triangles)
	{
		if (intersect_triangle(&shadow_ray, scene.triangle, &t)) {
			if (t > 0 && t < light_dist) {
				return t; // In shadow
			}
		}
	}
   // Check intersection with the triangle
	i = -1;
	while (++i < scene.n_cylinders)
	{
		if (intersect_cylinder(&shadow_ray, scene.cylinders, &t)) {
			if (t > 0 && t < light_dist) {
				return t; // In shadow
			}
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

	
	printf("ang(dircmr, dirtr): %f\n", dot(scene->cameras->dir, scene->triangle[0].p_triangle->normal) * ( 180/ M_PI));
	//render(mlx, win, WINX, WINY, sphere, plans, camera_pos, buffer);

	
	render_scene(scene, N_SAMPLING);
	//mlx_loop(scene->mlx);
	mlx_listen_meta(scene);
}