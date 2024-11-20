/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:12:23 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/18 18:42:43 by razamora         ###   ########.fr       */
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

int	key_press(int key, void *param)
{
	static n_intent = 0;
	t_map_fun map_fun;
	const t_map_fun controls[10] = {
		{XK_a, control_a},
		{XK_d, control_d},
		{XK_w, control_w},
		{XK_s, control_s},
		{XK_Left, control_left},
		{XK_Up, control_up},
		{XK_Right, control_right},
		{XK_Down, control_down},
		{XK_Escape, control_escape},
		{0, NULL}
	};

	if (n_intent >= 1)
		return 0;
	map_fun = map_fun_get(controls, key);
	if (map_fun.func)
	{
		n_intent++;
		map_fun.func(param);
		n_intent--;
	}
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
		if (intersect_sphere(&shadow_ray, &scene.spheres[i], &t)) {
			if (t > 0 && t < light_dist) {
				return t; // In shadow
			}
		}
	}
   // Check intersection with the triangle
	i = -1;
	while (++i < scene.n_triangles)
	{
		if (intersect_triangle(&shadow_ray, &scene.triangles[i], &t)) {
			if (t > 0 && t < light_dist) {
				return t; // In shadow
			}
		}
	}
   // Check intersection with the triangle
	i = -1;
	while (++i < scene.n_cylinders)
	{
		if (intersect_cylinder(&shadow_ray, &scene.cylinders[i], &t)) {
			if (t > 0 && t < light_dist) {
				return t;
			}
		}
	}
	return 0;
}

int init_file(char *file)
{
	int fd;
	int len_file;
	
	len_file = ft_strlen(file);
	if (file[len_file - 1] != 't' && file[len_file - 2] != 'r' && file[len_file - 3] != '.')
		(printf("Error: El archivo no es un archivo .rt\n"), exit(1));
	fd = open(file, 0);
	if (fd < 0)
		(printf("Error al abrir el archivo\n"), exit(1));
	return (fd);
}

static void review_scene(Scene *scene)
{
	if (!scene->width || !scene->height)
	{
		scene->width = WINX;
		scene->height = WINY;
	}
	if (scene->n_lights <= 0)
	{
		printf("Error: No hay Luz en la escena\n");
		exit(1);
	}
	if (!scene->cameras)
	{
		printf("Error: No hay camaras en la escena\n");
		exit(1);
	}
	if (!scene->ambient)
	{
		printf("Error: No hay Ambiente en la escena\n");
		exit(1);
	}

}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error: Argumentos invalidos\n");
		exit(1);
	}
	Scene *scene = malloc(sizeof(Scene));
	Img img;
	ft_bzero(scene, sizeof(Scene));
	parser_obj(scene, init_file(argv[1]));
	review_scene(scene);
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, scene->width, scene->height, "miniRT!");
	scene->img = &img;
	scene->img->img = mlx_new_image(scene->mlx, scene->width, scene->height);
	scene->img->buffer = mlx_get_data_addr(scene->img->img, &(scene->img->bitxpixel), &(scene->img->lines), &(scene->img->endian));

	render_scene(scene, N_SAMPLING);

	mlx_listen_meta(scene);
}
