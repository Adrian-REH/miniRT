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

double random_float()
{
    return rand() / (double)RAND_MAX;
}

void render(Scene scene)
{
   // normalize(&light);
	time_t start, end;
	double min_dist;
	int alpha = 0;
	start = clock();
	/* 
	for (int y = 0; y < WINY; ++y) { //Esta es la coordenada de la pantalla
		for (int x = 0; x < WINX ; ++x) {
			//  Este es el haz que se lanza desde camara_pos hasta el punto de la
			Ray ray = *generate_ray(x, y, WINX, WINY, *scene.cameras); 
			double t = 0;
			int id = 0;
			int type = 0;

			type = find_nearest_obj(scene, &ray, &t, &id);
			if (type == PLANE){
				Vector3 *hit_pt = hit_point(ray, t);
				int current_color = render_point_plane(scene, *hit_pt, id);
				set_color(&scene.img->buffer[idxpixel(x, y)], 0, current_color, 0);
				free(hit_pt);
			}
		
			if (type == SPHERE)
			{
				Vector3 *hit_pt = hit_point(ray, t);
				int current_color = render_point_sphere(scene, *hit_pt, id);
				set_color(&scene.img->buffer[idxpixel(x, y)], 0, current_color, 0);
				//set_color(&scene.img->buffer[mypixel], 0, current_color, 0);
				//Reflejo la bola y si intersecta, entonces verifico si la camara_dir respecto a su angulo es 0 para poder reflejarlo
				free(hit_pt);
			}
			
			if (intersect_sphere(&ray, &scene.spheres[1], &t)) //para la esfera de luz
			{
				Vector3 *hit_pt = hit_point(ray, t);
				int current_color = 0xFFFFFF;
				int mypixel = (y * WINX * 4) + (x * 4);
				set_color(&scene.img->buffer[mypixel], 0, current_color, 0);
				//Reflejo la bola y si intersecta, entonces verifico si la camara_dir respecto a su angulo es 0 para poder reflejarlo
				free(hit_pt);
			}
		}
	}
  */

	char *tmp_bfr;
	Img *img = malloc(sizeof(Img));
	img->img = mlx_new_image(scene.mlx, WINX, WINY);
	img->buffer = mlx_get_data_addr(img->img, &(img->bitxpixel), &(img->lines), &(img->endian));
	//mlx_put_image_to_window(scene.mlx, scene.win, scene.img->img, 0, 0);
	

 	for (int y = 0 ; y < WINY ; ++y) {
		for (int x = 0; x < WINX ; ++x) {
			Ray ray = *generate_ray(x, y, WINX, WINY, *scene.cameras); 
			double t = 0;
			double d = 0;
			min_dist = 90000000;
			int i = -1;
			int type;
			int id;
			
			type = find_nearest_obj(scene, &ray, &t, &id);
			i = id;
			if (type == PLANE){
				double md= 900000;
				int hit_color = 0;
				Vector3 *hit_pt = hit_point(ray, t);
				Vector3 *hit_rfc;
				Vector3 *dir_pt = normalize_withpoint(scene.cameras->pos , *hit_pt);
				Vector3 *rfc = reflect(*dir_pt, scene.planes[i].normal);
				if (dot(scene.planes[i].normal, *rfc) < 0)
					invnormal(rfc);
				Ray rayrfc = {*hit_pt , *rfc};
				int j = -1;

				//Si hay reflexion entonces pasa esto
				while (++j < scene.n_planes){

					if (intersect_plane(&rayrfc, &scene.planes[j], &t) && (t < md))
					{
						hit_rfc = hit_point(rayrfc, t);
						//El plano que emitio el rayo no deberia ser solucion para la reflexion
						if (!plane_solution_point(scene.planes[i], *hit_rfc))
						{
							md = t;
							int current_pixel = render_point_plane(scene, *hit_pt, i);
							hit_color = render_point_plane(scene, *hit_rfc, j);
							current_pixel = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.5, 0.9, 0, scene.planes[i].mater_prop)->color;
							set_color(&img->buffer[idxpixel(x, y)], 0, current_pixel, alpha);
						}
						free(hit_rfc);
					}
				}
				j = -1;
				while (++j < scene.n_spheres)
				{
					if (intersect_sphere(&rayrfc, &scene.spheres[j], &t) && (t < md)){
						hit_rfc = hit_point(rayrfc, t);
						if (!plane_solution_point(scene.planes[i], *hit_rfc)){
							md = t;
							hit_color = render_point_sphere(scene, *hit_rfc, j);
							int current_pixel = render_point_plane(scene, *hit_pt, i);
							current_pixel = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene.planes[i].mater_prop)->color;
							set_color(&img->buffer[idxpixel(x, y)], 0, current_pixel, alpha);
						}
						free(hit_rfc);
					}
				}
				
				free(hit_pt);
				free(rfc);
			}
			
			if (type == SPHERE){
				double md= 900000;
				int hit_color = 0;
				Vector3 *hit_pt = hit_point(ray, t);
				Vector3 *hit_rfc;
				Vector3 *dir_pt = normalize_withpoint(scene.cameras->pos , *hit_pt);
				Vector3 *n_sphere = normal_sphere(*hit_pt, scene.spheres[i]);
				Vector3 *rfc = reflect(*dir_pt, *n_sphere);
				if (dot(*n_sphere, *rfc) < 0)
					invnormal(rfc);
				Ray rayrfc = {*hit_pt , *rfc};
				int j = -1;
				//Verificador de planos o objetos mas cercanos para optimizar
				while (++j < scene.n_planes)
				{
					if (intersect_plane(&rayrfc, &scene.planes[j], &t) && (t < md))
					{
						hit_rfc = hit_point(rayrfc, t);
						//El plano que emitio el rayo no deberia ser solucion para la reflexion
						if (!sphere_solution_point(scene.spheres[i], *hit_rfc))
						{
							md = t;
							//Vector2 px_rfc;
							//point3D_to_pixel(*hit_rfc, *scene.cameras, WINX, WINY, &px_rfc);
							int current_pixel = render_point_sphere(scene, *hit_pt, i);
							hit_color = render_point_plane(scene, *hit_rfc, j);
							current_pixel = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 1, 1, 0, scene.spheres[i].mater_prop)->color;
							set_color(&img->buffer[idxpixel(x, y)], 0, hit_color, alpha);
						}
						free(hit_rfc);
					}
				}
				j = -1;
				while (++j < scene.n_spheres)
				{
					if (intersect_sphere(&rayrfc, &scene.spheres[j], &t) && (t < md))
					{
						hit_rfc = hit_point(rayrfc, t);
						//El plano que emitio el rayo no deberia ser solucion para la reflexion
						if (!sphere_solution_point(scene.spheres[i], *hit_rfc))
						{
							md = t;
							int current_pixel = render_point_sphere(scene, *hit_pt, i);
							hit_color = render_point_sphere(scene, *hit_rfc, j);
							current_pixel = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.1, 0.1, 0, scene.spheres[i].mater_prop)->color;
							set_color(&img->buffer[idxpixel(x, y)], 0, hit_color, alpha);
						}
						free(hit_rfc);
					}
				}
			}
				
			if (intersect_sphere(&ray, &scene.spheres[1], &t)) //para la esfera de luz
			{
				Vector3 *hit_pt = hit_point(ray, t);
				set_color(&img->buffer[idxpixel(x,y)], 0, 0xFFFFFF, 0);
				//Reflejo la bola y si intersecta, entonces verifico si la camara_dir respecto a su angulo es 0 para poder reflejarlo
				free(hit_pt);
			}
		
		
		}
	}

/* 
 	for (int y = 0 ; y < WINY ; ++y) {
		
		for (int x = 0; x < WINX ; ++x) {
			Ray ray = *generate_ray(x, y, WINX, WINY, *scene.cameras); 
			double t = 0;
			double d = 0;
			min_dist = 90000000;
			int i = -1;
			int type;
			int id;
			
			type = find_nearest_obj(scene, &ray, &t, &id);
			i = id;
			if (type == PLANE){
					min_dist = t;
					double md= 900000;
					int hit_color = 0;
					Vector3 *hit_pt = hit_point(ray, t);
					Vector3 *hit_rfc;
					Vector3 *dir_pt = normalize_withpoint(scene.cameras->pos , *hit_pt);
					if (dot(*dir_pt, scene.planes[i].normal ) < 0) // Esto esta del reves, si dot(u, v) < 0 significa que tienen signos opuestos que es en el caso de una reflexion
						invnormal(&scene.planes[i].normal);
					Vector3 *rfc = reflect(*dir_pt, scene.planes[i].normal);
					if (dot(*dir_pt, *rfc ) < 0) // Esto esta del reves, si dot(u, v) < 0 significa que tienen signos opuestos que es en el caso de una reflexion
						invnormal(rfc);
					Ray rayrfc = {*hit_pt , *rfc};
					int j = -1;
					
					while (++j < 5)
					{
						if (intersect_plane(&rayrfc, &scene.planes[j], &t) && t < md)
						{
							hit_rfc = hit_point(rayrfc, t);
							//Verifico si no choca el rayo de reflexion con el objeto que lo emite
							if (!plane_solution_point(scene.planes[i], *hit_rfc))
							{
								//guardo la interseccion como minima distancia
								md = t;
								Vector2 px_rfc;
								//Renderizo el punto que estoy intentando reflejar
								point3D_to_pixel(*hit_rfc, *scene.cameras, WINX, WINY, &px_rfc);
								hit_color = render_point_plane(scene, *hit_rfc, j);
								hit_color = get_color(&scene.img->buffer[idxpixel(px_rfc.x, px_rfc.y)], 0, NULL);

								int mypixel = (y * WINX * 4) + (x * 4);
								int current_pixel = 0;
								//current_pixel = get_color(&scene.img->buffer[mypixel], 0, &alpha);
								
								current_pixel = scene.planes[i].mater_prop.color[0];
								//current_pixel = mix_colors(current_pixel, hit_color, 0.8);
								set_color(&img->buffer[mypixel], 0, hit_color, alpha);

								//set_color(&img->buffer[idxpixel(px_rfc.x, px_rfc.y)], 0, hit_color, 0);//pinto de donde saca
								break;
							}
							free(hit_rfc);
						}
					}
					if (intersect_sphere(&rayrfc, &scene.spheres[0], &t) && (t < md))
					{
						
						md = t;
						hit_rfc = hit_point(rayrfc, t);
						Vector2 px_rfc;
						Vector2 px;
						point3D_to_pixel(*hit_rfc, *scene.cameras, WINX, WINY, &px_rfc);
						//point3D_to_pixel(*hit_pt, *scene.cameras, WINX, WINY, &px);
						//set_color(&scene.img->buffer[idxpixel(px_rfc.x, px_rfc.y)],0 , 0xFFFFFF, 0);
						//set_color(&scene.img->buffer[idxpixel(px.x, px.y)],0 , 0x555555, 0);
						hit_color = get_color(&scene.img->buffer[idxpixel(px_rfc.x, px_rfc.y)], 0, NULL);

						int mypixel = (y * WINX * 4) + (x * 4);
						int current_pixel = 0;
						current_pixel = get_color(&scene.img->buffer[mypixel], 0, &alpha);

						current_pixel = mix_colors(hit_color, current_pixel, 1);
						set_color(&img->buffer[mypixel], 0, current_pixel, alpha);
						//break;
					}
					 
					free(hit_pt);
					free(rfc);
			}	
			i = -1;
			while(++i < (scene.n_spheres))
			{
				if (intersect_sphere(&ray, &scene.spheres[i], &t) && (t < min_dist))
				{
					min_dist = t;
					double md= 900000;
					int hit_color = 0;
					Vector3 *hit_rfc;
					Vector3 *hit_pt = hit_point(ray, t);
					Vector3 *dir_pt = normalize_withpoint(scene.cameras->pos , *hit_pt);
					Vector3 *normal = normal_sphere(*hit_pt, scene.spheres[i]);
					Vector3 *rfc = reflect(*dir_pt, *normal);
					if (dot(*dir_pt, *rfc) < 0) // Esto esta del reves, si dot(u, v) < 0 significa que tienen signos opuestos que es en el caso de una reflexion
						invnormal(rfc);
					Ray rayrfc = {*hit_pt , *rfc};
					int j = -1;
					while (++j < scene.n_planes)
					{
						if (intersect_plane(&rayrfc, &scene.planes[j], &t))
						{
							hit_rfc = hit_point(rayrfc, t);
								Vector2 px_rfc;
								point3D_to_pixel(*hit_rfc, *scene.cameras, WINX, WINY, &px_rfc);
								hit_color = get_color(&scene.img->buffer[idxpixel(px_rfc.x, px_rfc.y)], 0, NULL);

								int mypixel = (y * WINX * 4) + (x * 4);
								int current_pixel = 0;
								current_pixel = get_color(&scene.img->buffer[mypixel], 0, &alpha);

								current_pixel = mix_colors(hit_color, current_pixel, 1);
								set_color(&img->buffer[mypixel], 0, current_pixel, alpha);

								//set_color(&img->buffer[idxpixel(px_rfc.x, px_rfc.y)], 0, hit_color, 0);//pinto de donde saca
								break;
							free(hit_rfc);
						}
					}

					t = 0;
					if (intersect_sphere(&rayrfc, &scene.spheres[0], &t) ){
						
						md = t;
						hit_rfc = hit_point(rayrfc, t);
						if (!sphere_solution_point(scene.spheres[i], *hit_rfc)){
							Vector2 px_rfc;
							Vector2 px;
							point3D_to_pixel(*hit_rfc, *scene.cameras, WINX, WINY, &px_rfc);
							//point3D_to_pixel(*hit_pt, *scene.cameras, WINX, WINY, &px);
							//set_color(&scene.img->buffer[idxpixel(px_rfc.x, px_rfc.y)],0 , 0xFFFFFF, 0);
							//set_color(&scene.img->buffer[idxpixel(px.x, px.y)],0 , 0x555555, 0);
							hit_color = get_color(&scene.img->buffer[idxpixel(px_rfc.x, px_rfc.y)], 0, NULL);

							int mypixel = (y * WINX * 4) + (x * 4);
							int current_pixel = 0;
							current_pixel = get_color(&scene.img->buffer[mypixel], 0, &alpha);

							current_pixel = mix_colors(hit_color, current_pixel, 1);
							set_color(&img->buffer[mypixel], 0, current_pixel, alpha);
						}
							free(hit_rfc);
					}
					
					free(hit_pt);
					free(rfc);
				}
			}
		
		}
	}
  */
//	scene.img->buffer = tmp_bfr;
	scene.img = img;
	mlx_put_image_to_window(scene.mlx, scene.win, scene.img->img, 0, 0);
	
	end = clock();
	double elapsed = (double)(end - start) / CLOCKS_PER_SEC * 1000; // Convertido a milisegundos
	printf("Elapsed time: %.3f milliseconds\n", elapsed);
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