#include "../main.h"	
    
    Scene scene;
	

	scene.mlx = mlx_init();
	scene.win = mlx_new_window(scene.mlx, WINX, WINY, "miniRT!");
	Img img;
	scene.img = &img;
	scene.img->img = mlx_new_image(scene.mlx, WINX, WINY);
	scene.img->buffer = mlx_get_data_addr(scene.img->img, &(scene.img->bitxpixel), &(scene.img->lines), &(scene.img->endian));
	Plane *plans = malloc(sizeof(Plane) * 6);
	plans[0] =  (Plane){{0, 0, 1}, {0, 0, -1}};
	plans[0].mater_prop.color[0] = 0xb29674;
	plans[0].mater_prop.color[1] = 0xb29674;
	plans[0].mater_prop.color[2] = 0xFFFFFF;
	plans[0].mater_prop.vColor = int_to_color(0xcbb677);
	plans[0].mater_prop.absorption[R] = 1 - plans[0].mater_prop.vColor->r;
	plans[0].mater_prop.absorption[G] = 1 - plans[0].mater_prop.vColor->g;
	plans[0].mater_prop.absorption[B] = 1 - plans[0].mater_prop.vColor->b;
	
	printf("ABS RGB: (%.2f, %.2f, %.2f) = %06X\n", plans[0].mater_prop.absorption[R], plans[0].mater_prop.absorption[G], plans[0].mater_prop.absorption[B], plans[0].mater_prop.vColor->color);

	plans[1] =  (Plane){{1, 0, 0}, {-10, 0, 0}};
	plans[1].mater_prop.color[0] = 0xff001d;
	plans[1].mater_prop.color[1] = 0xff001d;
	plans[1].mater_prop.color[2] = 0xFFFFFF;
	plans[1].mater_prop.vColor = int_to_color(0xff001d);
	plans[1].mater_prop.absorption[R] = 1 - plans[1].mater_prop.vColor->r ;
	plans[1].mater_prop.absorption[G] = 1 -plans[1].mater_prop.vColor->g ;
	plans[1].mater_prop.absorption[B] = 1 -plans[1].mater_prop.vColor->b ;

	plans[2] =  (Plane){{-1, 0, 0}, {10, 0, 0}};
	plans[2].mater_prop.color[0] = 0x00ffb5;
	plans[2].mater_prop.color[1] = 0x00ffb5;
	plans[2].mater_prop.color[2] = 0xFFFFFF;
	plans[2].mater_prop.vColor = int_to_color(0x00ffb5);
	plans[2].mater_prop.absorption[R] =1 - plans[2].mater_prop.vColor->r ;
	plans[2].mater_prop.absorption[G] = 1 -plans[2].mater_prop.vColor->g ;
	plans[2].mater_prop.absorption[B] = 1 -plans[2].mater_prop.vColor->b ;

	plans[3] =  (Plane){{0, -1, 0}, {0, 5.5, 0}};
	plans[3].mater_prop.color[0] = 0xb29674;
	plans[3].mater_prop.color[1] = 0xb29674;
	plans[3].mater_prop.color[2] = 0xFFFFFF;
	plans[3].mater_prop.vColor = int_to_color(0xcbb677);
	plans[3].mater_prop.absorption[R] = 1 - plans[3].mater_prop.vColor->r ;
	plans[3].mater_prop.absorption[G] = 1 -plans[3].mater_prop.vColor->g ;
	plans[3].mater_prop.absorption[B] = 1 -plans[3].mater_prop.vColor->b ;

	plans[4] =  (Plane){{0, 1, 0}, {0, -5.5, 0}};
	plans[4].mater_prop.color[0] = 0xb29674;
	plans[4].mater_prop.color[1] = 0xb29674;
	plans[4].mater_prop.color[2] = 0xFFFFFF;
	plans[4].mater_prop.vColor = int_to_color(0xcbb677);
	plans[4].mater_prop.absorption[R] = 1 - plans[4].mater_prop.vColor->r ;
	plans[4].mater_prop.absorption[G] = 1 - plans[4].mater_prop.vColor->g ;
	plans[4].mater_prop.absorption[B] = 1 - plans[4].mater_prop.vColor->b ;
	plans[5] =  (Plane){{0, 0, 35}, {0, 0, 1}};
	plans[5].mater_prop.color[0] = 0xb29674;
	plans[5].mater_prop.color[1] = 0xb29674;
	plans[5].mater_prop.color[2] = 0xFFFFFF;
	plans[5].mater_prop.vColor = int_to_color(0xcbb677);
	plans[5].mater_prop.absorption[R] = 1 - plans[5].mater_prop.vColor->r;
	plans[5].mater_prop.absorption[G] = 1 - plans[5].mater_prop.vColor->g;
	plans[5].mater_prop.absorption[B] = 1 - plans[5].mater_prop.vColor->b;

	normalize(&plans[0].normal);
	normalize(&plans[1].normal);
	normalize(&plans[2].normal);
	normalize(&plans[3].normal);
	normalize(&plans[4].normal);
	normalize(&plans[5].normal);
	scene.planes = plans;
	scene.lights = malloc(sizeof(Light));
	scene.lights->color = int_to_color(0xFFFFFF);
	scene.lights->point =  (Vector3){0, -5, 3};
	scene.lights->ratio = 1;
	Sphere sphere;      // Esfera en Z = 5 con radio 1
	scene.spheres = malloc(sizeof(Sphere)*2);
	scene.spheres->center = (Vector3){0, 0, 3};
	scene.spheres->radius = 1.5;
	scene.spheres->mater_prop.vColor = int_to_color(0xc41414);
	scene.spheres->mater_prop.absorption[R] = 1 - scene.spheres->mater_prop.vColor->r ;
	scene.spheres->mater_prop.absorption[G] = 1 - scene.spheres->mater_prop.vColor->g ;
	scene.spheres->mater_prop.absorption[B] = 1 - scene.spheres->mater_prop.vColor->b ;

	scene.spheres[1].center = (Vector3){0, -5, 3};
	scene.spheres[1].radius = 0.2;
	Camera camera;
	scene.cameras = &camera;
	scene.cameras->pos = (Vector3){0, 0, 30};
	// Ajusta el tamaño del plano de proyección en función de la relación de aspecto
	scene.cameras->aspect_ratio = (double)WINX/WINY;
	double fov = 50;
	scene.cameras->plane_distance = tan((fov / 2) * (M_PI / 180));
	scene.cameras->plane_half_width = scene.cameras->aspect_ratio * scene.cameras->plane_distance; // Ajuste según el aspecto
	scene.cameras->plane_half_height = 1.0 * scene.cameras->plane_distance;         // Altura basada en la distancia
	scene.cameras->dir = (Vector3){0, 0, -1}; // Apunta hacia el -Z
	scene.cameras->horizontal = (Vector3){1, 0, 0};      // Apunta hacia la derecha
	scene.cameras->vertical = (Vector3){0, -1, 0};         // Apunta hacia arriba
	scene.n_planes = 5;
	scene.n_spheres = 1;
	scene.n_cylinders = 0;
	scene.n_lights = 0;
	ft_memset(scene.img->buffer, 0 ,((WINY - 1)* WINX * 4) + ((WINX - 1) * 4));
	//render(mlx, win, WINX, WINY, sphere, plans, camera_pos, buffer);
	printf("Original RGB: (%.2f, %.2f, %.2f) = %06X\n", plans[0].mater_prop.vColor->r, plans[0].mater_prop.vColor->g, plans[0].mater_prop.vColor->b, plans[0].mater_prop.vColor->color);
	printf("ABS RGB: (%.2f, %.2f, %.2f) = %06X\n", plans[0].mater_prop.absorption[R], plans[0].mater_prop.absorption[G], plans[0].mater_prop.absorption[B], plans[0].mater_prop.vColor->color);
	printf("Original RGB: (%.2f, %.2f, %.2f) = %06X\n", plans[1].mater_prop.vColor->r, plans[1].mater_prop.vColor->g, plans[1].mater_prop.vColor->b, plans[1].mater_prop.vColor->color);
	printf("Original RGB: (%.2f, %.2f, %.2f) = %06X\n", plans[2].mater_prop.vColor->r, plans[2].mater_prop.vColor->g, plans[2].mater_prop.vColor->b, plans[2].mater_prop.vColor->color);
	printf("Original RGB: (%.2f, %.2f, %.2f) = %06X\n", plans[3].mater_prop.vColor->r, plans[3].mater_prop.vColor->g, plans[3].mater_prop.vColor->b, plans[3].mater_prop.vColor->color);
	printf("Original RGB: (%.2f, %.2f, %.2f) = %06X\n", plans[4].mater_prop.vColor->r, plans[4].mater_prop.vColor->g, plans[4].mater_prop.vColor->b, plans[4].mater_prop.vColor->color);
	printf("Original RGB: (%.2f, %.2f, %.2f) = %06X\n", scene.lights->color->r, scene.lights->color->g, scene.lights->color->b, scene.lights->color->color);
	render_scene(scene, 4);
	//render(scene);
	free(scene.planes);
	//mlx_put_image_to_window(scene.mlx, scene.win, scene.img->img, 0, 0);
	mlx_loop(scene.mlx);