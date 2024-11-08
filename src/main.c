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
#define EPSILON 1e-6 // Margen de tolerancia para precisión flotante

void normalize_color(Color *color) {
    color->r = fmax(0.0, fmin(1.0, color->r / 255.0));
    color->g = fmax(0.0, fmin(1.0, color->g / 255.0));
    color->b = fmax(0.0, fmin(1.0, color->b / 255.0));
}

int colornormal_to_int(Color color) {
    int r = (int)(color.r * 255.0);
    int g = (int)(color.g * 255.0);
    int b = (int)(color.b * 255.0);
    return (r << 16) | (g << 8) | b;
}
Color *int_to_color(int src) {
    Color *color = malloc(sizeof(Color));
    if (color == NULL) {
        return NULL;  // Manejo de error de asignación de memoria
    }
    color->r = ((src >> 16) & 0xFF) / 255.0;
    color->g = ((src >> 8) & 0xFF) / 255.0;
    color->b = (src & 0xFF) / 255.0;
    color->color = src;
    return color;
}

void	set_color(char *buffer, int endian, int color, int alpha)
{
	if (endian == 1)
	{
		buffer[0] = 0;
		buffer[1] = (color >> 16) & 0xFF;
		buffer[2] = (color >> 8) & 0xFF;
		buffer[3] = (color) & 0xFF;
	}
	else
	{
		buffer[0] = (color) & 0xFF;
		buffer[1] = (color >> 8) & 0xFF;
		buffer[2] = (color >> 16) & 0xFF;
		buffer[3] = 0;
	}
}

int get_color(char *buffer, int endian, int *alpha)
{
    int color = 0;

    if (endian == 1) // Big endian
    {
        color |= (buffer[1] & 0xFF) << 16;
        color |= (buffer[2] & 0xFF) << 8;
        color |= (buffer[3] & 0xFF);
    }
    else // Little endian
    {
        color |= (buffer[0] & 0xFF);
        color |= (buffer[1] & 0xFF) << 8;
        color |= (buffer[2] & 0xFF) << 16;
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
		double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
		if (t1 > 0) {
			*t = t1;
			return 1; // Valid intersection distancia mas corta
		}
	 	if (t2 > 0) {
			*t = t2;
			return 1; // Valid intersection
		}
	}
	return 0; // No valid intersection
}

int plane_solution_point(Plane plane, Vector3 point){
    // Calcula el término constante D usando el punto del plano
    double D = -(plane.normal.x * plane.point.x + 
                plane.normal.y * plane.point.y + 
                plane.normal.z * plane.point.z);

    // Calcula el valor de la ecuación del plano con el punto dado
    double result = plane.normal.x * point.x + 
                   plane.normal.y * point.y + 
                   plane.normal.z * point.z + D;

    // Verifica si el resultado está dentro del margen de tolerancia
    if (fabs(result) < EPSILON) {
        return 1; // El punto está en el plano
    } else {
        return 0; // El punto no está en el plano
    }
}

int sphere_solution_point(Sphere sphere, Vector3 point) {
    // Calculamos la distancia entre el punto y el centro de la esfera
    double dx = point.x - sphere.center.x;
    double dy = point.y - sphere.center.y;
    double dz = point.z - sphere.center.z;

    // Calculamos el cuadrado de la distancia entre el punto y el centro
    double distance_squared = dx * dx + dy * dy + dz * dz;

    // Comparamos la distancia al cuadrado con el radio al cuadrado
    double radius_squared = sphere.radius * sphere.radius;

    // Verificamos si la diferencia es pequeña (con un margen de error)
    if (fabs(distance_squared - radius_squared) < EPSILON) {
        return 1; // El punto está en la superficie de la esfera
    } else {
        return 0; // El punto no está en la superficie de la esfera
    }
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

int add_color(int base_color, int current_color) {

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
	int mixed_red = (int)(base_red  + crr_red );
	int mixed_green = (int)(base_green  + crr_green );
	int mixed_blue = (int)(base_blue  + crr_blue );

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

void project_to_pixel(Vector3 hit_pt, Camera camera, int *x, int *y){

	*x = (hit_pt.x * (WINX - 0.5) / 2 * camera.plane_half_width) - 0.5;
	//hit_pt.y = ((*y + 0.5) / WINY - 0.5) * 2.0 * camera.plane_half_height;

}

Vector2 *convert_to_pixel(Vector3 point_on_plane, Camera camera) {
    Vector2 *pixel = malloc(sizeof(Vector2));

    // Proyección de las coordenadas del punto en el plano de proyección
    // Asegúrate de que el punto esté en el mismo plano de proyección que el que defines
	double screen_x = (point_on_plane.x / camera.plane_half_width) + 0.5;
	double screen_y = (point_on_plane.y / camera.plane_half_height) + 0.5;
	// Asegurarse de que las coordenadas están dentro de [0, 1]
	screen_x = fmin(fmax(screen_x, 0.0), 1.0);
	screen_y = fmin(fmax(screen_y, 0.0), 1.0);
    // Convertir las coordenadas de pantalla a coordenadas de píxel
    pixel->x = (1.012 - screen_x) * WINX;
    pixel->y = (1.0423 - screen_y) * WINY;
	pixel->x = fmin(fmax(pixel->x, 0), WINX - 1);
	pixel->y = fmin(fmax(pixel->y, 0), WINY - 1);

    // Asegúrate de que las coordenadas de píxel estén dentro de los límites de la pantalla
// Asegúrate de que las coordenadas de píxel estén dentro de los límites de la pantalla
	if (pixel->x < 0) pixel->x = 0;
	if (pixel->x >= WINX) pixel->x = WINX;
	if (pixel->y < 0) pixel->y = 0;
	if (pixel->y >= WINY) pixel->y = WINY - 1;

    return pixel;
}

void point3D_to_pixel(Vector3 point, Camera camera, int screen_width, int screen_height, Vector2 *pxl) {
    // Vector desde la cámara al punto
    Vector3 to_point = {
        point.x - camera.pos.x,
        point.y - camera.pos.y,
        point.z - camera.pos.z
    };

    // Calculamos el factor de escala para la proyección
    double t = camera.dir.z / to_point.z;

    // Proyectamos el punto en el plano de la cámara
    Vector3 projected_point = {
        to_point.x * t,
        to_point.y * t,
        camera.plane_distance
    };

    // Calculamos las coordenadas en el plano de proyección
    double px = projected_point.x / camera.plane_half_width;
    double py = projected_point.y / camera.plane_half_height;

    // Convertimos las coordenadas del plano a coordenadas de píxel
    pxl->x = (int)((px + 1.0) * 0.5 * screen_width );
    pxl->y = (int)(((py + 1.0) * 0.5) * screen_height);
	//*x = ((int)((1 - point.x) * WINX) + WINX / 2) % WINX;
	//*y = (int)((1 - point.y) * WINY);

    // Ajustamos para el centro del píxel
     pxl->x  = ( pxl->x < screen_width && pxl->x > 0) ? pxl->x : screen_width - 1;
     pxl->y = ( pxl->y < screen_height && pxl->y > 0) ? pxl->y : screen_height - 1;
}

Ray *generate_ray(int x, int y, int screen_width, int screen_height, Camera camera) {

	// Inicializa el rayo y su origen
	Ray *ray = malloc(sizeof(Ray));
	ray->origin = camera.pos;

	// Calcula las coordenadas del punto en el plano de proyección
    float px = (2 * (x + 0.5) / (float) WINX - 1) * camera.aspect_ratio * camera.plane_distance;
    float py = (1 - 2 * (y + 0.5) / (float) WINY) * camera.plane_distance;

	// Calcula el punto en el plano de proyección usando los vectores de la cámara
	Vector3 point_on_plane = {
		camera.dir.x  + camera.horizontal.x * px + camera.vertical.x * py,
		camera.dir.y  + camera.horizontal.y * px + camera.vertical.y * py,
		camera.dir.z  + camera.horizontal.z * px + camera.vertical.z * py
	};
	// Calcula la dirección del rayo desde la cámara al punto en el plano de proyección
	ray->direction.x = point_on_plane.x ;
	ray->direction.y = point_on_plane.y;
	ray->direction.z = point_on_plane.z ;
//para 8 es 2.5
//para 10 es 2
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

int is_in_shadow(Scene scene, int plane_count, Vector3 light_pos, Vector3 hit_point) {
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

double find_intersect(Scene scene, int plane_count, Ray ray, double *t, Vector3 *normal, Vector3 *hit_pt){
	double min_dist = 9000000;
	double d;
	 // Check intersection with all planes
	for (int i = 0; i < plane_count; ++i) {
		if (intersect_plane(&ray, &scene.planes[i], &d)) {
			if ((d > 0) && (d < min_dist)) {
				min_dist = d;
				hit_pt = hit_point(ray, d);
				*normal = scene.planes[i].normal;
			}
		}
	} 
   // Check intersection with the sphere
	if (intersect_sphere(&ray, scene.spheres, &d)) {
		if ((d > 0) && (d < min_dist)) {
			min_dist = d;
			*hit_pt = *hit_point(ray, d);
			*normal = *normal_sphere(*hit_pt, *scene.spheres);
		}
	}
	return d; // Not in shadow
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

Color *illuminate_surface(Color *surface_color, Color *light_color, double intensity, 
                         double reflectivity, double glossiness, MaterialProperties prop) {
    Color *result = malloc(sizeof(Color));
    if (!result)
		return 0;
    result->r = surface_color->r * light_color->r * (1.0 - prop.absorption[R]);
    result->g = surface_color->g * light_color->g * (1.0 - prop.absorption[G]);
    result->b = surface_color->b * light_color->b * (1.0 - prop.absorption[B]) ;
	// Ajuste para materiales metálicos
    if (glossiness > 0) {
        // Los metales tienden a reflejar el color de la luz
        result->r = mix(result->r, light_color->r, glossiness);
        result->g = mix(result->g, light_color->g, glossiness);
        result->b = mix(result->b, light_color->b, glossiness);
        
        // Aumentar la reflectividad para metales
        reflectivity = mix(reflectivity, 1.0, glossiness);
    }

    // Calculamos la mezcla de colores
  	result->r = light_color->r + (result->r - light_color->r) * intensity * reflectivity;
    result->g = light_color->g + (result->g - light_color->g) * intensity * reflectivity;
    result->b = light_color->b + (result->b - light_color->b) * intensity * reflectivity;

	//result->r *= red_shift;
	//result->b *= blue_shift;

	// Asegurar que los valores estén en el rango [0, 1]
	result->r = fmin(1.0, fmax(0.0, result->r)) * 255;
	result->g = fmin(1.0, fmax(0.0, result->g)) * 255;
	result->b = fmin(1.0, fmax(0.0, result->b)) * 255;
	result->color = (((int)result->r << 16) | ((int)result->g << 8) | (int)result->b);

    return result;
}

int render_point_plane(Scene scene, Vector3 hit_pt, int n_plane)
{
	double d;
	int current_color = scene.planes[n_plane].mater_prop.color[0];//scene.planes[n_plane].mater_prop.color[0];
	Color *vCurrentColor = scene.planes[n_plane].mater_prop.vColor;
	MaterialProperties prop = scene.planes[n_plane].mater_prop;
	int ambient_color = 0; // Color gris para la luz ambiental
	// Calcula la dirección de la cámara hacia el punto de impacto
	Vector3 *cam_dir = normalize_withpoint(scene.cameras->pos, hit_pt);
	// Calcula la intensidad de la luz con respecto a la cámara
	double intensity = calculate_intensity(scene.planes[n_plane].normal, *cam_dir);
	// Mezcla el color base con la intensidad calculada para la dirección de la cámara

	current_color = vCurrentColor->color;
	Vector3 *light_dir = normalize_withpoint(scene.lights->point, hit_pt);
	Ray rayslight = {scene.lights->point, *light_dir};
	// Calcula la intersección del plano con el rayo de luz
	if (intersect_plane(&rayslight, &scene.planes[n_plane], &d))
	{
		// Calcula el punto de impacto con el rayo de luz
		double t = is_in_shadow(scene, 5, scene.lights->point, hit_pt);
		if (!t)
		{	// Calcula la dirección de la luz hacia el punto de impacto
				double distance_light = distance(rayslight.origin, hit_pt);
				double attenuation = calculate_attenuation(distance_light, L_P_KC, L_P_KL, L_P_KQ);
				double diffuse_intensity = calculate_intensity(scene.planes[n_plane].normal, rayslight.direction);
				diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1.0);
				Vector3 *reflect_dir = reflect(rayslight.direction, scene.planes[n_plane].normal);

				double specular = specular_intensity(*reflect_dir, *cam_dir, SHININESS, KS);
				specular = fmin(fmax(specular, 0.0), 1.0);
				
				//La cantidad de color del material sobre
				//La cantidad de luz que aplico sobre el color del material
				vCurrentColor = illuminate_surface(vCurrentColor, scene.lights->color, fmin(0.8, fmax(0.0, ( 1 - (diffuse_intensity * attenuation )))) , 0.95, 0, prop);
				normalize_color(vCurrentColor);
				
				//current_color = mix_colors(scene.planes[n_plane].mater_prop.color[1], current_color, diffuse_intensity * attenuation);
				vCurrentColor = illuminate_surface(vCurrentColor, scene.lights->color, fmin(1, fmax(0.0, ( 1- (specular * attenuation * diffuse_intensity)))) , 0.95, 0, prop);
				normalize_color(vCurrentColor);
				
				vCurrentColor = illuminate_surface(int_to_color(ambient_color), vCurrentColor, fmin(1, fmax(0.0, ( 1 - ( attenuation * diffuse_intensity)))) , 0.9, 0, prop);
				normalize_color(vCurrentColor);

				current_color = vCurrentColor->color;
		}else
		{
			Vector3 *hit_shadow = hit_point(rayslight, t);
			double distance_light = distance(rayslight.origin, *hit_shadow);
			double attenuation = calculate_attenuation(distance_light, L_P_KC, L_P_KL, L_P_KQ);
			double diffuse_intensity = calculate_intensity(scene.planes[n_plane].normal, rayslight.direction);
			diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1.0);
			Vector3 *reflect_dir = reflect(rayslight.direction, scene.planes[n_plane].normal);
			double specular = specular_intensity(*reflect_dir, *cam_dir, SHININESS, KS);
			specular = fmin(fmax(specular, 0.0), 1.0);

			vCurrentColor = illuminate_surface(int_to_color(ambient_color), vCurrentColor, fmin(1, fmax(0.0, ( attenuation ))) , 0.95, 0, prop);
			normalize_color(vCurrentColor);
			current_color = vCurrentColor->color;
		}
	}
	free(cam_dir);
	free(light_dir);
	return current_color;
}

int render_point_sphere(Scene scene, Vector3 hit_pt){
	double d;
	int current_color = 0; // Color base de la esfera
	int ambient_color = 0; // Color gris para la luz ambiental

	Vector3 *n_sphere = normalize_withpoint( scene.spheres->center, hit_pt);
	Vector3 *cam_dir = normalize_withpoint(scene.cameras->pos, hit_pt );
	current_color = mix_colors(ambient_color, current_color, AMBIENT_INTENSITY);
	Ray rayslight = {scene.lights->point, *normalize_withpoint(scene.lights->point, hit_pt)};
	// Calcula la intersección del plano con el rayo de luz
	if (intersect_sphere(&rayslight, scene.spheres, &d)) // Agrega esta verificación
	{
		//Tengo que hacer reflejo y acumular el color.
		if (!is_in_shadow(scene, 5, scene.lights->point, hit_pt)) {
			// Cálculo de la luz difusa
			double distance_light = distance(rayslight.origin, hit_pt);
			double attenuation = calculate_attenuation(distance_light, 1, 0.01, 0.03);
			double diffuse_intensity = calculate_intensity(*n_sphere, rayslight.direction);
			diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1);
			current_color = mix_colors(0xc61200, current_color, diffuse_intensity * attenuation);
			Vector3 *reflect_dir = reflect(rayslight.direction, *n_sphere);
			// Cálculo de la luz especular
			double specular = specular_intensity(*reflect_dir, *cam_dir, SHININESS, KS);
			//	attenuation = calculate_attenuation(distance_light, 1.0, 0.1, 0.01);
			//specular = fmin(fmax(specular, 0.0), 1.0);
			current_color = mix_colors(0xFFFFFF, current_color, specular * attenuation);
			free(reflect_dir);
		}
	}
	free(cam_dir);
	return current_color;
}

double random_double() {
    return (double)rand() / RAND_MAX * 2.0 - 1.0;
}

// Genera un vector aleatorio dentro de una esfera unitaria
Vector3 *random_in_unit_sphere() {
    Vector3 *p = malloc(sizeof(Vector3));
    do {
        *p = (Vector3){ random_double(), random_double(), random_double() };
    } while ((p->x * p->x + p->y * p->y + p->z * p->z) >= 1.0);
    return p;
}

Vector3 *random_in_hemisphere(Vector3 normal) {
    Vector3 *in_unit_sphere = random_in_unit_sphere();
    
    // Si el vector está en la misma dirección que la normal, úsalo; de lo contrario, invierte el vector
    if ((in_unit_sphere->x * normal.x + in_unit_sphere->y * normal.y + in_unit_sphere->z * normal.z) > 0.0) {
        return in_unit_sphere;
    } else {
		in_unit_sphere->x = -in_unit_sphere->x;
		in_unit_sphere->y = -in_unit_sphere->y;
		in_unit_sphere->z = -in_unit_sphere->z;
        return in_unit_sphere;
    }
}


int color_scale(int color, double scale) {

	// Extraemos los componentes RGB del color base
	int base_red = (color >> 16) & 0xFF;
	int base_green = (color >> 8) & 0xFF;
	int base_blue = color & 0xFF;

	// y cuando intensity sea 1, el resultado sea base_color.
	int mixed_red = (int)(base_red * scale);
	int mixed_green = (int)(base_green * scale);
	int mixed_blue = (int)(base_blue * scale);

	// Nos aseguramos de que los valores estén en el rango [0, 255]
	mixed_red = mixed_red > 255 ? 255 : mixed_red;
	mixed_green = mixed_green > 255 ? 255 : mixed_green;
	mixed_blue = mixed_blue > 255 ? 255 : mixed_blue;

	// Combinamos los componentes mezclados en un solo color hexadecimal
	return (mixed_red << 16) | (mixed_green << 8) | mixed_blue;
}

int idxpixel(int x, int y){
	return (y * WINX * 4) + (x * 4);
}

int find_reflect(Scene scene, Ray ray, int color) {
	double t = 0;
	double min_dist = 90000000;
	int hit_color = color;
	Vector3 normal;
	//for (int i = 1; i < 5; i++){
		if (intersect_plane(&ray, &scene.planes[1], &t)) {
			min_dist = t;
			Vector3 *hit_pt = hit_point(ray, t);
			Vector3 *rfc = reflect(ray.direction, scene.planes[2].normal);
			Ray rayrfc = {*hit_pt , *rfc};
			if (intersect_plane(&rayrfc, &scene.planes[0], &t) && t > 0) {//Busco quien intersecta con el vector de reflexion
				Vector3 *hit_rfc = hit_point(rayrfc, t);
				//if (!is_in_shadow(scene, 5, *hit_pt, *hit_rfc))
				//{
					Vector2 px_rfc;
					Vector2 px;
					point3D_to_pixel(*hit_rfc, *scene.cameras, WINX, WINY, &px_rfc);
					point3D_to_pixel(*hit_pt, *scene.cameras, WINX, WINY, &px);
					set_color(&scene.img->buffer[idxpixel(px_rfc.x, px_rfc.y)],0 , 0xFFFFFF, 0);
					set_color(&scene.img->buffer[idxpixel(px.x, px.y)],0 , 0x555555, 0);
					hit_color = get_color(&scene.img->buffer[idxpixel(px_rfc.x, px_rfc.y)], 0, NULL);
					return hit_color;
				//}

			}
			free(rfc);
			free(hit_pt);
		}
	//}
	min_dist = 90000000;
	for (int i = 0; i < 1; i++){
		if (intersect_sphere(&ray, &scene.spheres[i], &t)){
			min_dist = t;
			Vector3 *hit_pt = hit_point(ray, t);
			Vector3 *n_sphere =  normal_sphere(*hit_pt, scene.spheres[i]);
			Vector3 *rfc = reflect( *n_sphere, ray.direction);
			Ray rayrfc = {*hit_pt , *rfc};
			if (intersect_plane(&rayrfc, &scene.planes[0], &t) && t > 0) {//Busco quien intersecta con el vector de reflexion
				Vector3 *hit_rfc = hit_point(rayrfc, t);
				if (!is_in_shadow(scene, 5, *hit_pt, *hit_rfc))
				{
					Vector2 px_rfc;
					point3D_to_pixel(*hit_rfc, *scene.cameras, WINX, WINY, &px_rfc);
					hit_color = get_color(&scene.img->buffer[idxpixel(px_rfc.x, px_rfc.y)], 0, NULL);
					return hit_color;
				}
			}
			free(n_sphere);
			free(rfc);
			free(hit_pt);
		}
	}
	return hit_color;
}

Vector3 *invnormal(Vector3 *normal){
	normal->x = -normal->x;
	normal->y = -normal->y;
	normal->z = -normal->z;
	return normal;
}

int find_nearest_plane(Scene scene, Ray *ray, double *t){
	int i;
	int j;
	double min_dist = INT32_MAX;

	i = -1;
	j = -1;
	while (++i < scene.n_planes)
	{
		if (intersect_plane(ray, &scene.planes[i], t) && (*t < min_dist))
		{
			min_dist = *t;
			j = i;
		}
	}
	*t = min_dist;
	return j;
}

int find_nearest_sphere(Scene scene, Ray *ray, double *t){
	int i;
	int j;
	double min_dist = INT32_MAX;

	i = -1;
	j = -1;
	while (++i < scene.n_spheres)
	{
		if (intersect_sphere(ray, &scene.spheres[i], t) && (*t < min_dist))
		{
			min_dist = *t;
			j = i;
		}
	}
	*t = min_dist;
	return j;
}

int idxfind_min(double *arr, int size) {
	int i;
	int idx;
	double min;

    if (size <= 0)
        return 0;
	i = 0;
	idx = 0;
    min = arr[i];  // Inicializamos el valor mínimo con el primer elemento
    while (++i < size) {
        if (arr[i] < min) {
            min = arr[i];  // Actualizamos el valor mínimo si encontramos uno menor
			idx = i;
        }
    }
    return idx;  // Retorna el valor mínimo encontrado
}

int	find_nearest_obj(Scene scene, Ray *ray, double *t, int *id){
	double distance[10];
	double idx[10];
	int type;

	idx[PLANE] = find_nearest_plane(scene, ray, t);
	distance[0] = *t;
	idx[SPHERE] = find_nearest_sphere(scene, ray, t);
	distance[1] = *t;
	idx[2] = 0;
	//idx[2] = find_nearest_cylinder(scene, ray, &satate[1]);
	//idx[3] = find_nearest_polygon(scene, ray, &satate[1]);
	//idx[4] = 0;
	type = idxfind_min(distance, 2);
	*id = idx[type];
	*t = distance[type];
	return type;
}

void render(Scene scene)
{
   // normalize(&light);
	time_t start, end;
	double min_dist;
	int alpha = 0;
	start = clock();
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
				int current_color = render_point_sphere(scene, *hit_pt);
				set_color(&scene.img->buffer[idxpixel(x, y)], 0, current_color, 0);
				//set_color(&scene.img->buffer[mypixel], 0, current_color, 0);
				//Reflejo la bola y si intersecta, entonces verifico si la camara_dir respecto a su angulo es 0 para poder reflejarlo
				free(hit_pt);
			}
			
			if (intersect_sphere(&ray, &scene.spheres[1], &t)) //para la esfera de luz
			{
				Vector3 *hit_pt = hit_point(ray, t);
				int current_color = 0xFFFFFF;//render_point_sphere(scene, *hit_pt, y, x);
				int mypixel = (y * WINX * 4) + (x * 4);
				set_color(&scene.img->buffer[mypixel], 0, current_color, 0);
				//Reflejo la bola y si intersecta, entonces verifico si la camara_dir respecto a su angulo es 0 para poder reflejarlo
				free(hit_pt);
			}
		}
	}
 
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
				while (++j < scene.n_planes){

					if (intersect_plane(&rayrfc, &scene.planes[j], &t) && (t < md))
					{
						hit_rfc = hit_point(rayrfc, t);
						//El plano que emitio el rayo no deberia ser solucion para la reflexion
						if (!plane_solution_point(scene.planes[i], *hit_rfc))
						{
							md = t;
							//Vector2 px_rfc;
							//point3D_to_pixel(*hit_rfc, *scene.cameras, WINX, WINY, &px_rfc);
							int current_pixel = render_point_plane(scene, *hit_pt, i);
							hit_color = render_point_plane(scene, *hit_rfc, j);
							current_pixel = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene.planes[i].mater_prop)->color;
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
							hit_color = render_point_sphere(scene, *hit_rfc);
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
						if (!plane_solution_point(scene.planes[i], *hit_rfc))
						{
							md = t;
							//Vector2 px_rfc;
							//point3D_to_pixel(*hit_rfc, *scene.cameras, WINX, WINY, &px_rfc);
							int current_pixel = render_point_sphere(scene, *hit_pt);
							hit_color = render_point_plane(scene, *hit_rfc, j);
							current_pixel = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene.spheres[i].mater_prop)->color;
							set_color(&img->buffer[idxpixel(x, y)], 0, current_pixel, alpha);
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
							int current_pixel = render_point_sphere(scene, *hit_pt);
							hit_color = render_point_sphere(scene, *hit_rfc);
							current_pixel = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene.spheres[i].mater_prop)->color;
							set_color(&img->buffer[idxpixel(x, y)], 0, current_pixel, alpha);
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
	Scene scene;
	

	scene.mlx = mlx_init();
	scene.win = mlx_new_window(scene.mlx, WINX, WINY, "miniRT!");
	Img img;
	scene.img = &img;
	scene.img->img = mlx_new_image(scene.mlx, WINX, WINY);
	scene.img->buffer = mlx_get_data_addr(scene.img->img, &(scene.img->bitxpixel), &(scene.img->lines), &(scene.img->endian));
	Plane *plans = malloc(sizeof(Plane) * 5);
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
	normalize(&plans[0].normal);
	normalize(&plans[1].normal);
	normalize(&plans[2].normal);
	normalize(&plans[3].normal);
	normalize(&plans[4].normal);
	scene.planes = plans;
	scene.lights = malloc(sizeof(Light));
	scene.lights->color = int_to_color(0xFFFFFF);
	scene.lights->point =  (Vector3){0, -5, 3};
	scene.lights->ratio = 1;
	Sphere sphere;      // Esfera en Z = 5 con radio 1
	scene.spheres = malloc(sizeof(Sphere)*2);
	scene.spheres->center = (Vector3){0, 0, 2};
	scene.spheres->radius = 1;
	scene.spheres->mater_prop.vColor = int_to_color(0xcbb677);
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
	render(scene);
	free(scene.planes);
	//mlx_put_image_to_window(scene.mlx, scene.win, scene.img->img, 0, 0);
	mlx_loop(scene.mlx);
}