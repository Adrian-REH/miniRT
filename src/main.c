/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:30:51 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:49:54 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	terminate_program(void *param)
{
	Scene	*scene;

	scene = (Scene *)param;
	mlx_destroy_image(scene->mlx, scene->img->img);
	mlx_destroy_window(scene->mlx, scene->win);
	mlx_destroy_display(scene->mlx);
	if (scene->n_cylinders)
		free(scene->cylinders);
	if (scene->n_triangles)
		free(scene->triangles);
	if (scene->n_planes)
		free(scene->planes);
	if (scene->n_spheres)
		free(scene->spheres);
	if (scene->n_squares)
		free(scene->squares);
	if (scene->n_lights)
		free(scene->lights);
	free(scene->cameras);
	free(scene->ambient);
	exit(0);
}

static void	mlx_listen_meta(Scene *scene)
{
	mlx_hook(scene->win, 4, 1L << 2, mouse_press, scene);
	mlx_hook(scene->win, 2, 1, key_press, scene);
	mlx_hook(scene->win, 17, 1, terminate_program, scene);
	mlx_loop(scene->mlx);
}

int	is_in_shadow(Scene scene, Vector3 light_pos, Vector3 hit_point)
{
	Ray				shadow_ray;
	double			t;
	int				i;
	int				j;
	const double	n_objs[5] = {
		scene.n_planes,
		scene.n_spheres,
		scene.n_triangles,
		scene.n_cylinders,
		distance(hit_point, light_pos)
	};

	shadow_ray.origin = hit_point;
	shadow_ray.direction = norm_subtract(hit_point, light_pos);
	i = ((t = ((j = -1), 0)), -1);
	while (++j < 4)
	{
		while (++i < n_objs[j])
		{
			if (scene.isc[i] && scene.isc[i](&shadow_ray, &scene.planes[i], &t))
				if (t > 0 && t < n_objs[4])
					return (t);
		}
	}
	return (0);
}

int	init_file(char *file)
{
	int	fd;
	int	len_file;

	len_file = ft_strlen(file);
	if (file[len_file - 1] != 't' || file[len_file - 2] != 'r' || \
		file[len_file - 3] != '.')
		(printf("Error: El archivo no es un archivo .rt\n"), exit(1));
	fd = open(file, 0);
	if (fd < 0)
		(printf("Error al abrir el archivo\n"), exit(1));
	return (fd);
}

static void	review_scene(Scene *scene)
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

void	init_pos_obj_fun(Scene *scene)
{
	scene->pos_obj->type = CAMERA;
	scene->pos_obj->idx = 0;
	scene->pos_obj->pos[PLANE] = (void (*)(void *, Vector3))pos_plane;
	scene->pos_obj->pos[SPHERE] = (void (*)(void *, Vector3))pos_sphere;
	scene->pos_obj->pos[TRIANGLE] = (void (*)(void *, Vector3))pos_triangle;
	scene->pos_obj->pos[CYLINDER] = (void (*)(void *, Vector3))pos_cylinder;
	scene->pos_obj->pos[CAMERA] = (void (*)(void *, Vector3))pos_camera;
	scene->pos_obj->rot[PLANE] = (void (*)(void *, Vector3, int))rot_plane;
	scene->pos_obj->rot[SPHERE] = (void (*)(void *, Vector3, int))0;
	scene->pos_obj->rot[TRIANGLE] = \
		(void (*)(void *, Vector3, int))rot_triangle;
	scene->pos_obj->rot[CYLINDER] = \
		(void (*)(void *, Vector3, int))rot_cylinder;
	scene->pos_obj->rot[CAMERA] = (void (*)(void *, Vector3, int))rot_camera;
}

int	main(int argc, char **argv)
{
	Scene	*scene;
	Img		img;

	if (argc != 2)
	{
		printf("Error: Argumentos invalidos\n");
		exit(1);
	}
	scene = malloc(sizeof(Scene));
	ft_bzero(scene, sizeof(Scene));
	parser_obj(scene, init_file(argv[1]));
	review_scene(scene);
	scene->pos_obj = malloc(sizeof(s_pos_obj));
	ft_bzero(scene->pos_obj, sizeof(s_pos_obj));
	init_pos_obj_fun(scene);
	init_intersect_fun(scene);
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, \
		scene->width, scene->height, "miniRT!");
	scene->img = &img;
	scene->img->img = mlx_new_image(scene->mlx, scene->width, scene->height);
	scene->img->buffer = mlx_get_data_addr(scene->img->img, \
		&(scene->img->bitxpixel), &(scene->img->lines), &(scene->img->endian));
	render_scene(scene, N_SAMPLING);
	mlx_listen_meta(scene);
}
