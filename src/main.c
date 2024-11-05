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
#include <float.h>
#include <stdint.h>

void	set_color(char *buffer, int endian, int color, int alpha)
{
	if (endian == 1)
	{
		buffer[0] = alpha;
		buffer[1] = (color >> 16) & 0xFF;
		buffer[2] = (color >> 8) & 0xFF;
		buffer[3] = (color) & 0xFF;
	}
	else
	{
		buffer[0] = (color) & 0xFF;
		buffer[1] = (color >> 8) & 0xFF;
		buffer[2] = (color >> 16) & 0xFF;
		buffer[3] = alpha;
	}
}

int get_color(const char *buffer, int endian, int *alpha) {
    int color = 0;

    if (endian == 1) {
        // Formato: ARGB
        if (alpha)
			*alpha = buffer[0]; // Valor alfa
		if (buffer[1] && buffer[2] && buffer[3])
			color = (buffer[1] << 16) | (buffer[2] << 8) | buffer[3]; // Color
    } else {
		if (alpha)
			*alpha = buffer[3]; // Valor alfa
		if (buffer[0] && buffer[1] && buffer[2])
			color = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2]; // Color
    }

    return color;
}

void normalize(Vector3 *v) {
	// Calcula la magnitud del vector
	double magnitude = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	
	// Evita la división por cero
	if (magnitude > 0) {
		v->x /= magnitude;
		v->y /= magnitude;
		v->z /= magnitude;
	}
}

double dot(Vector3 a, Vector3 b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

double specular_intensity(Vector3 reflection, Vector3 view_dir, double shininess, double ks) {
    double dot_product = dot(reflection, view_dir);
    double intensity = pow(fmax(dot_product, 0.0), shininess) * ks;
    return intensity;
}

int intersect_sphere(const Ray *ray, const Sphere *sphere,  double *t) {
	Vector3 oc = {ray->origin.x - sphere->center.x,
				ray->origin.y - sphere->center.y,
				ray->origin.z - sphere->center.z};

	double a = ray->direction.x * ray->direction.x +
				ray->direction.y * ray->direction.y +
				ray->direction.z * ray->direction.z;

	double b = 2.0 * (oc.x * ray->direction.x +
					  oc.y * ray->direction.y +
					  oc.z * ray->direction.z);
	double c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - sphere->radius * sphere->radius;
	double discriminant = b * b - 4 * a * c;
	if (discriminant >= 0) {
		double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
		//double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
		if (t1 > 0) {
			*t = t1;
			return 1; // Valid intersection distancia mas corta
		}
	/* 	if (t2 > 0) {
			*t = t2;
			return 1; // Valid intersection
		} */
	}
	return 0; // No valid intersection
}

int intersect_plane(const Ray *ray, const Plane *plane, double *t) {
	double denom = plane->normal.x * ray->direction.x +
				   plane->normal.y * ray->direction.y +
				   plane->normal.z * ray->direction.z;

	if (fabs(denom) < 1e-6) {
		return 0;
	}

	Vector3 p0l0 = {
		plane->point.x - ray->origin.x,
		plane->point.y - ray->origin.y,
		plane->point.z - ray->origin.z
	};

	*t = (plane->normal.x * p0l0.x +
		  plane->normal.y * p0l0.y +
		  plane->normal.z * p0l0.z) / denom;

	return (*t > 0); // Si t es positivo, hay intersección en dirección del rayo
}


double calculate_specular(Vector3 view_dir, Vector3 light_dir, Vector3 normal) {
	Vector3 reflect_dir = {
		-light_dir.x + 2 * normal.x * (normal.x * light_dir.x + normal.y * light_dir.y + normal.z * light_dir.z),
		-light_dir.y + 2 * normal.y * (normal.x * light_dir.x + normal.y * light_dir.y + normal.z * light_dir.z),
		-light_dir.z + 2 * normal.z * (normal.x * light_dir.x + normal.y * light_dir.y + normal.z * light_dir.z)
	};
	double spec = pow(fmax(0.0, reflect_dir.x * view_dir.x + reflect_dir.y * view_dir.y + reflect_dir.z * view_dir.z), 20);
	return spec;
}

int mix_colors(int base_color, int current_color, double intensity) {
	    intensity = fmax(0.0, fmin(1.0, intensity));

	// Extraemos los componentes RGB del color base
	int base_red = (base_color >> 16) & 0xFF;
	int base_green = (base_color >> 8) & 0xFF;
	int base_blue = base_color & 0xFF;

	// Extraemos los componentes RGB del color actual
	int crr_red = (current_color >> 16) & 0xFF;
	int crr_green = (current_color >> 8) & 0xFF;
	int crr_blue = current_color & 0xFF;

	// Ajustamos la mezcla para que cuando intensity sea 0, el resultado sea current_color,
	// y cuando intensity sea 1, el resultado sea base_color.
	int mixed_red = (int)(base_red * intensity + crr_red * (1 - intensity));
	int mixed_green = (int)(base_green * intensity + crr_green * (1 - intensity));
	int mixed_blue = (int)(base_blue * intensity + crr_blue * (1 - intensity));

	// Nos aseguramos de que los valores estén en el rango [0, 255]
	mixed_red = mixed_red > 255 ? 255 : mixed_red;
	mixed_green = mixed_green > 255 ? 255 : mixed_green;
	mixed_blue = mixed_blue > 255 ? 255 : mixed_blue;

	// Combinamos los componentes mezclados en un solo color hexadecimal
	return (mixed_red << 16) | (mixed_green << 8) | mixed_blue;
}

// Función que calcula la diferencia de color
double color_difference(int color1, int color2) {
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;

	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;

	return sqrt(pow(r2 - r1, 2) + pow(g2 - g1, 2) + pow(b2 - b1, 2));
}

int adjust_color(int base_color, double intensity) {
	// Extraemos los componentes RGB del color base
	int red = (base_color >> 16) & 0xFF;
	int green = (base_color >> 8) & 0xFF;
	int blue = base_color & 0xFF;

	// Ajustamos cada componente multiplicando por la intensidad
	red = (int)(red * intensity);
	green = (int)(green * intensity);
	blue = (int)(blue * intensity);

	// Nos aseguramos de que los valores estén en el rango [0, 255]
	red = red > 255 ? 255 : red;
	green = green > 255 ? 255 : green;
	blue = blue > 255 ? 255 : blue;

	// Combinamos los componentes ajustados en un solo color hexadecimal
	return (red << 16) | (green << 8) | blue;
}


int adjust_gradient_color(int base_color, int background_color, double intensity, double alpha) {
	// Extraemos los componentes RGB del color base
	int base_red = (base_color >> 16) & 0xFF;
	int base_green = (base_color >> 8) & 0xFF;
	int base_blue = base_color & 0xFF;

	// Extraemos los componentes RGB del color de fondo
	int bg_red = (background_color >> 16) & 0xFF;
	int bg_green = (background_color >> 8) & 0xFF;
	int bg_blue = background_color & 0xFF;

	// Ajustamos cada componente multiplicando por la intensidad
	base_red = (int)(base_red * intensity);
	base_green = (int)(base_green * intensity);
	base_blue = (int)(base_blue * intensity);

	// Nos aseguramos de que los valores estén en el rango [0, 255]
	base_red = base_red > 255 ? 255 : base_red;
	base_green = base_green > 255 ? 255 : base_green;
	base_blue = base_blue > 255 ? 255 : base_blue;

	// Mezclamos el color base con el color de fondo usando el alfa
	int mixed_red = (int)((base_red * alpha) + (bg_red * (1 - alpha)));
	int mixed_green = (int)((base_green * alpha) + (bg_green * (1 - alpha)));
	int mixed_blue = (int)((base_blue * alpha) + (bg_blue * (1 - alpha)));

	// Combinamos los componentes ajustados en un solo color hexadecimal
	return (mixed_red << 16) | (mixed_green << 8) | mixed_blue;
}

Ray *generate_ray(int x, int y, int screen_width, int screen_height, Vector3 camera_pos) {
    // Define los vectores de orientación de la cámara
    Vector3 camera_direction = {0, 0, -1}; // Apunta hacia el -Z
    Vector3 camera_right = {1, 0, 0};      // Apunta hacia la derecha
    Vector3 camera_up = {0, -1, 0};         // Apunta hacia arriba

    // Inicializa el rayo y su origen
    Ray *ray = malloc(sizeof(Ray));
    ray->origin = camera_pos;

    // Ajusta el tamaño del plano de proyección en función de la relación de aspecto
    double aspect_ratio = (double)screen_width / screen_height;
    double plane_distance = 20.0;           // Distancia desde la cámara al plano de proyección
    double plane_half_width = aspect_ratio * plane_distance; // Ajuste según el aspecto
    double plane_half_height = 1.0 * plane_distance;         // Altura basada en la distancia

    // Calcula las coordenadas del punto en el plano de proyección
    double px = ((x + 0.5) / screen_width - 0.5) * 2.0 * plane_half_width;
    double py = ((y + 0.5) / screen_height - 0.5) * 2.0 * plane_half_height;

    // Calcula el punto en el plano de proyección usando los vectores de la cámara
    Vector3 point_on_plane = {
        camera_pos.x + camera_direction.x * plane_distance + camera_right.x * px + camera_up.x * py,
        camera_pos.y + camera_direction.y * plane_distance + camera_right.y * px + camera_up.y * py,
        camera_pos.z + camera_direction.z * plane_distance + camera_right.z * px + camera_up.z * py
    };
    // Calcula la dirección del rayo desde la cámara al punto en el plano de proyección
    ray->direction.x = point_on_plane.x ;
    ray->direction.y = point_on_plane.y ;
    ray->direction.z = point_on_plane.z ;

    // Normaliza la dirección del rayo para obtener un vector unitario
    double length = sqrt(ray->direction.x * ray->direction.x +
                         ray->direction.y * ray->direction.y +
                         ray->direction.z * ray->direction.z);
    ray->direction.x /= length;
    ray->direction.y /= length;
    ray->direction.z /= length;

    return ray;
}

Vector3 *normal_sphere(Vector3 hit_point, Sphere sphere) {
	Vector3 *normal = malloc(sizeof(Vector3));
	normal->x = hit_point.x - sphere.center.x;
	normal->y = hit_point.y - sphere.center.y;
	normal->z = hit_point.z - sphere.center.z;
	
	// Normaliza la normal
	double length = sqrt(normal->x * normal->x + normal->y * normal->y + normal->z * normal->z);
	if (length > 0) { // Evita división por cero
		normal->x /= length;
		normal->y /= length;
		normal->z /= length;
	}
	
	return normal;
}

Vector3 *hit_point(Ray ray, double t){
	Vector3 *hit_point = malloc(sizeof(Vector3));
	 hit_point->x = ray.origin.x + t * ray.direction.x;
	hit_point->y = ray.origin.y + t * ray.direction.y;
	hit_point->z = ray.origin.z + t * ray.direction.z;
	return hit_point;
}

Vector3 *light_dir(Vector3 normal, Vector3 light, Vector3 hit_point) {
	Vector3 *light_dir = malloc(sizeof(Vector3));
	light_dir->x = light.x - hit_point.x;
	light_dir->y = light.y - hit_point.y;
	light_dir->z = light.z - hit_point.z;
	
	// Normaliza la dirección de la luz
	double length = sqrt(light_dir->x * light_dir->x + light_dir->y * light_dir->y + light_dir->z * light_dir->z);
	if (length > 0) { // Evita división por cero
		light_dir->x /= length;
		light_dir->y /= length;
		light_dir->z /= length;
	}
	
	return light_dir;
}

Vector3 *camera_dir(Vector3 camera_pos, Vector3 hit_pt){
	Vector3 *view_dir = malloc(sizeof(Vector3));
	view_dir->x = camera_pos.x - hit_pt.x;
	view_dir->y = camera_pos.y - hit_pt.y;
	view_dir->z = camera_pos.z - hit_pt.z;
	double view_length = sqrt(view_dir->x * view_dir->x + view_dir->y * view_dir->y + view_dir->z * view_dir->z);
	view_dir->x /= view_length; // Normalizar
	view_dir->y /= view_length;
	view_dir->z /= view_length;
	return view_dir;
}

double calculate_intensity(Vector3 normal, Vector3 light_dir) {
//	double val = -(normal.x * light_dir.x + normal.y * light_dir.y + normal.z * light_dir.z);
	double val = -dot(normal, light_dir);

	return fmax(0, val);
}

Vector3 *normalize_withpoint(Vector3 init, Vector3 end) {
    Vector3 *direction = malloc(sizeof(Vector3));

    // Calcula el vector de dirección restando los puntos
    direction->x = end.x - init.x;
    direction->y = end.y - init.y;
    direction->z = end.z - init.z;

    // Calcula la longitud del vector de dirección
    double length = sqrt(direction->x * direction->x + direction->y * direction->y + direction->z * direction->z);
    // Normaliza el vector de dirección si la longitud es mayor que 0
    if (length > 0) {
        direction->x /= length;
        direction->y /= length;
        direction->z /= length;
    } else {
        direction->x = 0;
        direction->y = 0;
        direction->z = 0;
	}

    return direction;
}

double distance(Vector3 init, Vector3 end){
	return sqrt(pow(end.x - init.x, 2) + pow(end.y - init.y, 2) + pow(end.z - init.z, 2));
}

int hasintersected(Sphere sphere, Plane *plans, Ray ray, double *t, Vector3 origin) {
    double origin_dist = distance(origin, ray.origin);
    double uniq_min = DBL_MAX; // Use DBL_MAX from float.h for better range
    int intersect = 1;
	double d= *t;
    // Check intersection with all planes
    for (int i = 0; i < 5; ++i) {
        if (intersect_plane(&ray, &plans[i], t)) {
            Vector3 ht_point = *hit_point(ray, *t);
            double hit_distance = distance(origin, ht_point);
            intersect = 0;
        }
    }

    // Check intersection with the sphere
    if (intersect_sphere(&ray, &sphere, t)) {
        Vector3 ht_point = *hit_point(ray, *t);
        double hit_distance = distance(origin, ht_point);
        intersect = 0;
    }

    // If the closest hit distance is less than the origin to the light source, it is in shadow
        return intersect; // In shadow
}

int is_light_in_front(Vector3 normal, Vector3 light_dir) {
    // Calcula el producto escalar
    double dot_product = normal.x * light_dir.x + normal.y * light_dir.y + normal.z * light_dir.z;

    // Si el producto escalar es mayor a cero, la luz está en frente
    return dot_product > 0;
}

int is_in_shadow(Sphere sphere, Plane *planes, int plane_count, Vector3 light_pos, Vector3 hit_point) {
    Ray shadow_ray;
    shadow_ray.origin = hit_point;
    shadow_ray.direction = *normalize_withpoint(hit_point, light_pos); // Vector from hit_point to light

    double light_dist = distance(hit_point, light_pos);
    double t = 0;

 
     // Check intersection with all planes
    for (int i = 0; i < plane_count; ++i) {
        if (intersect_plane(&shadow_ray, &planes[i], &t)) {
            if (t > 0 && t < light_dist) {
                return t; // In shadow
            }
        }
    } 
   // Check intersection with the sphere
    if (intersect_sphere(&shadow_ray, &sphere, &t)) {
        if (t > 0 && t < light_dist) {
            return t; // In shadow
        }
    }
 
    return 0; // Not in shadow
}

double find_intersect(Sphere sphere, Plane *planes, int plane_count, Ray ray, double *t){

 
     // Check intersection with all planes
    for (int i = 0; i < plane_count; ++i) {
        if (intersect_plane(&ray, &planes[i], t)) {
            if (t > 0) {
                return *t; // Intersect
            }
        }
    } 
   // Check intersection with the sphere
    if (intersect_sphere(&ray, &sphere, t)) {
        if (t > 0) {
            return *t; // Intersect
        }
    }
 
    return 0; // Not Intersect
}


Vector3 *reflect(Vector3 L, Vector3 N) {
    double dot_product = dot(N, L); // N dot L
    Vector3 *reflection = malloc(sizeof(Vector3));
	*reflection =  (Vector3) {
        2 * dot_product * N.x - L.x,
        2 * dot_product * N.y - L.y,
        2 * dot_product * N.z - L.z
    };
     normalize(reflection); // Normalize the reflected vector
	return reflection;
}

double calculate_attenuation(double distance, double k_c, double k_l, double k_q) {
    return 1.0 / (k_c + k_l * distance + k_q * distance * distance);
}
int  russian_roulette(double probability) {
    double random_value = (double)rand() / RAND_MAX; // Número aleatorio entre 0 y 1
    return random_value < probability;
}

int render_plane(Sphere sphere, Plane *plans, Vector3 camera_pos, Vector3 hit_pt, Vector3 light, int n_plane, char *buffer, int x, int y)
{
	double d;
	int current_color = 0; // Color base de la esfera
    int ambient_color = 0x555555; // Color gris para la luz ambiental
	// Calcula la dirección de la cámara hacia el punto de impacto
	Vector3 *cam_dir = normalize_withpoint(camera_pos, hit_pt);
	// Calcula la intensidad de la luz con respecto a la cámara
	double intensity = calculate_intensity(plans[n_plane].normal, *cam_dir);
	// Mezcla el color base con la intensidad calculada para la dirección de la cámara
	current_color = mix_colors(ambient_color, current_color, AMBIENT_INTENSITY);
	Ray rayslight = {light, *normalize_withpoint(light, hit_pt)};
	// Calcula la intersección del plano con el rayo de luz
	if (intersect_plane(&rayslight, &plans[n_plane], &d)) // Agrega esta verificación
	{
		// Calcula el punto de impacto con el rayo de luz
		if (!is_in_shadow(sphere, plans, 5, light, hit_pt))
		{	// Calcula la dirección de la luz hacia el punto de impacto
				double distance_light = distance(rayslight.origin, hit_pt);
				double attenuation = calculate_attenuation(distance_light, L_P_KC, L_P_KL, L_P_KQ);
				double diffuse_intensity = calculate_intensity(plans[n_plane].normal, rayslight.direction);
				diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1.0);
				current_color = mix_colors(plans[n_plane].mater_prop.color[1], current_color, diffuse_intensity* attenuation);
				// Calcula la intensidad de la luz con respecto a la dirección de la luz
				//attenuation = calculate_attenuation(distance_light, 1.0, 0.2, 0.05); // Aumentando k_q
				Vector3 *reflect_dir = reflect(rayslight.direction, plans[n_plane].normal);
				double specular = specular_intensity(*reflect_dir, *cam_dir, SHININESS, KS);
				current_color = mix_colors(0xFFFFFF, current_color, specular * attenuation);
		}
	}  // Libera memoria de hit_pt y cam_dir
	free(cam_dir);
	return current_color;
}
int render_sphere(Sphere sphere, Plane *plans, Vector3 camera_pos, Vector3 hit_pt, Vector3 light, char * buffer, int y, int x){
	double d;
	int current_color = 0; // Color base de la esfera
    int ambient_color = 0x555555; // Color gris para la luz ambiental

	Vector3 *n_sphere = normalize_withpoint( sphere.center, hit_pt);
	Vector3 *cam_dir = normalize_withpoint(camera_pos, hit_pt );
	double intensity = calculate_intensity(*n_sphere, *cam_dir);
	double dist_camera = distance(camera_pos, hit_pt);
	double attenuation = calculate_attenuation(dist_camera, L_P_KC, L_P_KL, L_P_KQ);
    current_color = mix_colors(ambient_color, current_color, AMBIENT_INTENSITY);

	Ray rayslight = {light, *normalize_withpoint(light, hit_pt)};
	// Calcula la intersección del plano con el rayo de luz
	if (intersect_sphere(&rayslight, &sphere, &d)) // Agrega esta verificación
	{
       if (!is_in_shadow(sphere, plans, 5, light, hit_pt)) {
            // Cálculo de la luz difusa
			double distance_light = distance(rayslight.origin, hit_pt);
			attenuation = calculate_attenuation(distance_light, 1, 0.01, 0.03);
            double diffuse_intensity = calculate_intensity(*n_sphere, rayslight.direction);
            diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1);
            current_color = mix_colors(0xc61200, current_color, diffuse_intensity * attenuation);

			Vector3 *reflect_dir = reflect(rayslight.direction, *n_sphere);

            // Cálculo de la luz especular
            double specular = specular_intensity(*reflect_dir, *cam_dir, SHININESS, KS);
			//	attenuation = calculate_attenuation(distance_light, 1.0, 0.1, 0.01);
            //specular = fmin(fmax(specular, 0.0), 1.0);
            current_color = mix_colors(0xFFFFFF, current_color, specular * attenuation);
        }
	
	}  // Libera memoria de hit_pt y cam_dir
	free(cam_dir);
	return current_color;
}

void render(void *mlx, void *win, int screen_width, int screen_height, Sphere sphere, Plane *plans, Vector3 camera_pos, char *buffer) {
	Vector3 light = {-8, 0, 1}; // luz
   // normalize(&light);
	time_t start, end;
	double min_dist;
	start = clock();
	for (int y = 0; y < screen_height; ++y) { //Esta es la coordenada de la pantalla
		for (int x = 0; x < screen_width ; ++x) {
			//  Este es el haz que se lanza desde camara_pos hasta el punto de la
			Ray ray = *generate_ray(x, y, WINX, WINY, camera_pos); 
			double t = 0;
			double d = 0;
			min_dist = 90000000;
			int i = -1;
			while (++i < 5)
			{
				if (intersect_plane(&ray, &plans[i], &t) && (t < min_dist))
				{
						min_dist = t;
						Vector3 *hit_pt = hit_point(ray, t);
						int current_color = render_plane(sphere, plans, camera_pos, *hit_pt, light, i, buffer, x, y);
						int mypixel = (y * WINX * 4) + (x * 4);
						set_color(&buffer[mypixel], 0, current_color, 0);
						free(hit_pt);
				}
			}
			if (intersect_sphere(&ray, &sphere, &t) && (t < min_dist))
			{
				min_dist = t;
				Vector3 *hit_pt = hit_point(ray, t);
				int current_color = render_sphere(sphere, plans, camera_pos, *hit_pt, light, buffer, y, x);
				free(hit_pt);
				int mypixel = (y * WINX * 4) + (x * 4);
				set_color(&buffer[mypixel], 0, current_color, 0);
			}
		}
	}
	
	end = clock();
	double elapsed = (double)(end - start) / CLOCKS_PER_SEC * 1000; // Convertido a milisegundos
	printf("Elapsed time: %.3f milliseconds\n", elapsed);
}

int main()
{
	void *mlx;
	void *win;
	void	*img;
	char	*buffer;
	int		color;
	int		bitxpixel;
	int		lines;
	int		endian;
	

	color = 0xFFFFFF;
	mlx = mlx_init();
	win = mlx_new_window(mlx, WINX, WINY, "miniRT!");
	img = mlx_new_image(mlx, WINX, WINY);
	color = mlx_get_color_value(mlx, color);
	mlx_pixel_put(mlx, win, WINX ,WINY, color);
	buffer = mlx_get_data_addr(img, &bitxpixel, &lines, &endian);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	Vector3 camera_pos = {0, 0, 6};      // Cámara en el origen
	Sphere sphere = {{0, 0, 2}, 1};      // Esfera en Z = 5 con radio 1
	Plane *plans = malloc(sizeof(Plane) * 5);
	plans[0] =  (Plane){{0, 0, 1}, {0, 0, -1}};
	plans[0].mater_prop.color[0] = 0x010c32;
	plans[0].mater_prop.color[1] = 0x003cff;
	plans[0].mater_prop.color[2] = 0xFFFFFF;
	plans[1] =  (Plane){{1, 0, 0}, {-10, 0, 0}};
	plans[1].mater_prop.color[0] = 0x471b26;
	plans[1].mater_prop.color[1] = 0xff001d;
	plans[1].mater_prop.color[2] = 0xFFFFFF;
	plans[2] =  (Plane){{-1, 0, 0}, {10, 0, 0}};
	plans[2].mater_prop.color[0] = 0x0b3f34;
	plans[2].mater_prop.color[1] = 0x00ffb5;
	plans[2].mater_prop.color[2] = 0xFFFFFF;
	plans[3] =  (Plane){{0, -1, 0}, {0, 5.5, 0}};
	plans[3].mater_prop.color[0] = 0x4b353b;
	plans[3].mater_prop.color[1] = 0xfc3001;
	plans[3].mater_prop.color[2] = 0xFFFFFF;
	plans[4] =  (Plane){{0, 1, 0}, {0, -5.5, 0}};
	plans[4].mater_prop.color[0] = 0x472b0a;
	plans[4].mater_prop.color[1] = 0x472b0a;
	plans[4].mater_prop.color[2] = 0xFFFFFF;
	normalize(&plans[0].normal);
	normalize(&plans[1].normal);
	normalize(&plans[2].normal);
	normalize(&plans[3].normal);
	normalize(&plans[4].normal);
	ft_memset(buffer, 0 ,((WINY - 1)* WINX * 4) + ((WINX - 1) * 4));
	render(mlx, win, WINX, WINY, sphere, plans, camera_pos, buffer);
	free(plans);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_loop(mlx);
}