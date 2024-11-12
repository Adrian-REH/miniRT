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

double random_float() {
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

int calculate_pixel_color(int x, int y, Scene *scene, int samples_per_pixel) {
    Color final_color = {0, 0, 0};  // Color acumulado (R, G, B)
    Color sample_color = {0, 0, 0};  // Color acumulado (R, G, B)
    float inv_samples = 1.0f / samples_per_pixel;

    for (int s = 0; s < samples_per_pixel; s++) {
        // Calcular pequeñas desviaciones aleatorias dentro del píxel (jittering)
        double u = (x + random_float()) / (double)WINX;
        double v = (y + random_float()) / (double)WINY;

        // Generar rayo para la posición u, v dentro del píxel
		Ray ray = *generate_ray(x + u, y + v, WINX, WINY, *scene->cameras); 
		double t = 0;
		double min_dist = 90000000;
		int type;
		int id;
		type = find_nearest_obj(*scene, &ray, &t, &id);
		if (type == PLANE){
			double md= 900000;
			int hit_color = 0;
			Vector3 *hit_pt = hit_point(ray, t);
			Vector3 *hit_rfc;
			Vector3 *dir_pt = normalize_withpoint(scene->cameras->pos , *hit_pt);
			Vector3 *rfc = reflect(*dir_pt, scene->planes[id].normal);
			if (dot(scene->planes[id].normal, *rfc) < 0)
				invnormal(rfc);
			Ray rayrfc = {*hit_pt , *rfc};
			int j = -1;

			//Si hay reflexion entonces pasa esto
			while (++j < scene->n_planes){

				if (intersect_plane(&rayrfc, &scene->planes[j], &t) && (t < md))
				{
					hit_rfc = hit_point(rayrfc, t);
					//El plano que emitio el rayo no deberia ser solucion para la reflexion
					if (!plane_solution_point(scene->planes[id], *hit_rfc))
					{
						md = t;
						hit_color = render_point_plane(*scene, *hit_rfc, j);
						int current_pixel = render_point_plane(*scene, *hit_pt, id);
						current_pixel = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene->planes[id].mater_prop)->color;
						set_color(&scene->img->buffer[idxpixel(x, y)], 0, current_pixel, 0);
						addint_to_color(&sample_color, current_pixel);
					}
					free(hit_rfc);
				}
			}
			j = -1;
			while (++j < scene->n_spheres)
			{
				if (intersect_sphere(&rayrfc, &scene->spheres[j], &t) && (t < md)){
					hit_rfc = hit_point(rayrfc, t);
					if (!plane_solution_point(scene->planes[id], *hit_rfc)){
						md = t;
						hit_color = render_point_sphere(*scene, *hit_rfc, j);
						
						int current_pixel = render_point_plane(*scene, *hit_pt, id);
						current_pixel = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene->planes[id].mater_prop)->color;
						set_color(&scene->img->buffer[idxpixel(x, y)], 0, current_pixel, 0);
						addint_to_color(&sample_color, current_pixel);
					}
					free(hit_rfc);
				}
			}
			
			free(hit_pt);
			free(dir_pt);
			free(rfc);
		}
		
		if (type == SPHERE)
		{
			double md= 900000;
			int hit_color = 0;
			Vector3 *hit_pt = hit_point(ray, t);
			Vector3 *hit_rfc;
			Vector3 *dir_pt = normalize_withpoint(scene->cameras->pos , *hit_pt);
			Vector3 *n_sphere = normal_sphere(*hit_pt, scene->spheres[id]);
			Vector3 *rfc = reflect(*dir_pt, *n_sphere);
			if (dot(*n_sphere, *rfc) < 0)
				invnormal(rfc);
			Ray rayrfc = {*hit_pt , *rfc};
			int j = -1;
			//Verificador de planos o objetos mas cercanos para optimizar
			while (++j < scene->n_planes)
			{
				if (intersect_plane(&rayrfc, &scene->planes[j], &t) && (t < md))
				{
					hit_rfc = hit_point(rayrfc, t);
					//El plano que emitio el rayo no deberia ser solucion para la reflexion
					if (!sphere_solution_point(scene->spheres[id], *hit_rfc))
					{
						md = t;
						hit_color = render_point_plane(*scene, *hit_rfc, j);
						int current_pixel = render_point_sphere(*scene, *hit_pt, id);
						current_pixel = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.5, 0.9, 0, scene->spheres[id].mater_prop)->color;
						set_color(&scene->img->buffer[idxpixel(x, y)], 0, hit_color, 0);
						addint_to_color(&sample_color, hit_color);
					}
					free(hit_rfc);
				}
			}
			j = -1;
			while (++j < scene->n_spheres)
			{
				if (intersect_sphere(&rayrfc, &scene->spheres[j], &t) && (t < md))
				{
					hit_rfc = hit_point(rayrfc, t);
					//El plano que emitio el rayo no deberia ser solucion para la reflexion
					if (!sphere_solution_point(scene->spheres[id], *hit_rfc))
					{
						md = t;
						hit_color = render_point_sphere(*scene, *hit_rfc, j);
						int current_pixel = render_point_sphere(*scene, *hit_pt, id);
						current_pixel = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.5, 0.9, 0, scene->spheres[id].mater_prop)->color;
						set_color(&scene->img->buffer[idxpixel(x, y)], 0, hit_color, 0);
						addint_to_color(&sample_color, hit_color);
					}
					free(hit_rfc);
				}
			}

			free(hit_pt);
			free(dir_pt);
			free(n_sphere);
			free(rfc);
		}
			
		if (intersect_sphere(&ray, &scene->spheres[1], &t)) //para la esfera de luz
		{
			Vector3 *hit_pt = hit_point(ray, t);
			addint_to_color(&sample_color, 0xFFFFFF);
			free(hit_pt);
		}
        // Acumular el color de esta muestra
        final_color.r += sample_color.r;
        final_color.g += sample_color.g;
        final_color.b += sample_color.b;
    }
    // Promediar el color acumulado dividiendo por el número de muestras
	final_color.r *= inv_samples;
	final_color.g *= inv_samples;
	final_color.b *= inv_samples;

	return colornormal_to_int(final_color);
}

int main()
{
	Scene scene;
	
	scene.mlx = mlx_init();
	scene.win = mlx_new_window(scene.mlx, WINX, WINY, "miniRT!");
	Img img;
	scene.img = &img;
	scene.img->img = mlx_new_image(scene.mlx, WINX, WINY);
	scene.img->buffer = mlx_get_data_addr(scene.img->img, &(scene.img->bitxpixel), &(scene.img->lines), &(scene.img->endian));

	//PARSER----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
	//RENDER----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	render_scene(scene, 1);
	free(scene.planes);
	mlx_loop(scene.mlx);
}