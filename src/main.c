
#include "main.h"

int	terminate_program(void *param)
{
	Scene	*scene;

	scene = (Scene *)param;
	mlx_destroy_image(scene->mlx, scene->img->img);
	mlx_destroy_window(scene->mlx, scene->win);
	mlx_destroy_display(scene->mlx);
	//Free
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
	/*
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
void init_pos_obj_fun(Scene *scene)
{
	scene->pos_obj->type = CAMERA;
	scene->pos_obj->idx = 0;
	scene->pos_obj->pos[PLANE] = (void (*)(void *, Vector3))pos_plane;
	scene->pos_obj->pos[SPHERE] = (void (*)(void *, Vector3))pos_sphere;
	scene->pos_obj->pos[TRIANGLE] = (void (*)(void *, Vector3))pos_triangle;
	scene->pos_obj->pos[CYLINDER] = (void (*)(void *, Vector3))pos_cylinder;
	scene->pos_obj->pos[CAMERA] = (void (*)(void *, Vector3))pos_camera;
	scene->pos_obj->rot[PLANE] = (void (*)(void *, Vector3, int))rot_plane;
	scene->pos_obj->rot[SPHERE] = NULL;
	scene->pos_obj->rot[TRIANGLE] = (void (*)(void *, Vector3, int))rot_triangle;
	scene->pos_obj->rot[CYLINDER] = (void (*)(void *, Vector3, int))rot_cylinder;
	scene->pos_obj->rot[CAMERA] = (void (*)(void *, Vector3, int))rot_camera;
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
	scene->pos_obj = malloc(sizeof(s_pos_obj));
	ft_bzero(scene->pos_obj, sizeof(s_pos_obj));
	init_pos_obj_fun(scene);
	init_intersect_fun(scene);
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, scene->width, scene->height, "miniRT!");
	scene->img = &img;
	scene->img->img = mlx_new_image(scene->mlx, scene->width, scene->height);
	scene->img->buffer = mlx_get_data_addr(scene->img->img, &(scene->img->bitxpixel), &(scene->img->lines), &(scene->img->endian));
	render_scene(scene, N_SAMPLING);
	mlx_listen_meta(scene);
}
