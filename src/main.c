/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:12:23 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/03 03:08:42 by adherrer         ###   ########.fr       */
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

 
	 // Check intersection with all planes
	for (int i = 0; i < scene.n_planes; ++i) {
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
   // Check intersection with the triangle
	if (intersect_triangle(&shadow_ray, scene.triangle, &t)) {
		if (t > 0 && t < light_dist) {
			return t; // In shadow
		}
	}
 
	return 0; // Not in shadow
}


int main()
{
	Scene *scene = malloc(sizeof(Scene));
	
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, WINX, WINY, "miniRT!");
	Img img;
	scene->img = &img;
	scene->img->img = mlx_new_image(scene->mlx, WINX, WINY);
	scene->img->buffer = mlx_get_data_addr(scene->img->img, &(scene->img->bitxpixel), &(scene->img->lines), &(scene->img->endian));

	//PARSER----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	parser_plane(scene, NULL);
	parser_light(scene, NULL);
	parser_sphere(scene, NULL);
	parser_camera(scene, NULL);
	parser_triangle(scene, NULL);
	
	//render(mlx, win, WINX, WINY, sphere, plans, camera_pos, buffer);
	printf("Original RGB: (%.2f, %.2f, %.2f) = %06X\n", scene->planes[0].mater_prop.vColor->r, scene->planes[0].mater_prop.vColor->g, scene->planes[0].mater_prop.vColor->b, scene->planes[0].mater_prop.vColor->color);
	printf("ABS RGB: (%.2f, %.2f, %.2f) = %06X\n", scene->planes[0].mater_prop.absorption[R], scene->planes[0].mater_prop.absorption[G], scene->planes[0].mater_prop.absorption[B], scene->planes[0].mater_prop.vColor->color);
	printf("planes[0] RGB: (%.2f, %.2f, %.2f) = %06X\n", scene->planes[1].mater_prop.vColor->r, scene->planes[1].mater_prop.vColor->g, scene->planes[1].mater_prop.vColor->b, scene->planes[1].mater_prop.vColor->color);
	printf("planes[1] RGB: (%.2f, %.2f, %.2f) = %06X\n", scene->planes[2].mater_prop.vColor->r, scene->planes[2].mater_prop.vColor->g, scene->planes[2].mater_prop.vColor->b, scene->planes[2].mater_prop.vColor->color);
	printf("planes[2] RGB: (%.2f, %.2f, %.2f) = %06X\n", scene->planes[3].mater_prop.vColor->r, scene->planes[3].mater_prop.vColor->g, scene->planes[3].mater_prop.vColor->b, scene->planes[3].mater_prop.vColor->color);
	printf("planes[3] RGB: (%.2f, %.2f, %.2f) = %06X\n", scene->planes[4].mater_prop.vColor->r, scene->planes[4].mater_prop.vColor->g, scene->planes[4].mater_prop.vColor->b, scene->planes[4].mater_prop.vColor->color);
	printf("lights RGB: (%.2f, %.2f, %.2f) = %06X\n", scene->lights->color->r, scene->lights->color->g, scene->lights->color->b, scene->lights->color->color);
	printf("triangle[4] RGB: (%.2f, %.2f, %.2f) = %06X\n", scene->triangle[0].mater_prop.vColor->r, scene->triangle[0].mater_prop.vColor->g, scene->triangle[0].mater_prop.vColor->b, scene->triangle[0].mater_prop.vColor->color);
	printf("triangle[0] Norm: (%.2f, %.2f, %.2f)\n", scene->triangle[0].p_triangle->normal.x, scene->triangle[0].p_triangle->normal.y, scene->triangle[0].p_triangle->normal.z);
	printf("plane[0] Norm: (%.2f, %.2f, %.2f)\n", scene->planes[0].normal.x, scene->planes[0].normal.y, scene->planes[0].normal.z);
	//RENDER----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//ft_memset(scene->img->buffer, 0 ,((WINY - 1)* WINX * 4) + ((WINX - 1) * 4));
	render_scene(scene, N_SAMPLING);
	//mlx_loop(scene->mlx);
	mlx_listen_meta(scene);
}