/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:12:23 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/02 20:22:59 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minilibx-linux/mlx.h"
#include "../lib/minilibx_opengl/mlx_opengl.h"
#include <math.h>
#define WINX 1280
#define WINY 720
#include <time.h>
#include <stdio.h>


typedef struct {
    double x, y, z;
} Vector3;

typedef struct {
    Vector3 origin;
    Vector3 direction;
} Ray;

typedef struct {
    Vector3 center;
    double radius;
} Sphere;
typedef struct {
    Vector3 normal;
    Vector3 point;
} Plane;

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

    if (discriminant < 0) {
        return 0; // No hay intersección
    } else {
        *t = (-b - sqrt(discriminant)) / (2.0 * a);
        return 1; // Hay intersección
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

    return (*t >= 0); // Si t es positivo, hay intersección en dirección del rayo
}

Ray generate_ray(int x, int y, int screen_width, int screen_height, Vector3 camera_pos) {
    Ray ray;
    ray.origin = camera_pos;

    // Coordenadas de la pantalla (simulación de una cámara simple)
    ray.direction.x = (x - screen_width / 2.0) / screen_width;
    ray.direction.y = (y - screen_height / 2.0) / screen_height;
    ray.direction.z = 1.0;  // Apunta hacia adelante en el eje Z

    // Normalizar dirección del rayo
    double length = sqrt(ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z);
    ray.direction.x /= length;
    ray.direction.y /= length;
    ray.direction.z /= length;

    return ray;
}

Vector3 *hit_point(Ray ray, double t){
	Vector3 *hit_point = malloc(sizeof(Vector3));
	 hit_point->x = ray.origin.x + t * ray.direction.x;
	hit_point->y = ray.origin.y + t * ray.direction.y;
	hit_point->z = ray.origin.z + t * ray.direction.z;
	return hit_point;
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

double calculate_intensity(Vector3 normal, Vector3 light_dir) {
    return fmax(0.0, normal.x * light_dir.x + normal.y * light_dir.y + normal.z * light_dir.z);
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


void render_sphere(void *mlx, void *win, int screen_width, int screen_height, Sphere sphere, Plane plane, Vector3 camera_pos) {
    Vector3 light = {0, -1, 0};   // luz
    time_t start, end;
	int color = 0x33cc55;
    start = clock();
	double max_x = 0;
	double max_y = 0;
	double min_x = 902;
	double min_y = 0;
    for (int y = 0; y < screen_height; ++y) {
        for (int x = 0; x < screen_width; ++x) {
            Ray ray = generate_ray(x, y, screen_width, screen_height, camera_pos);
           	Ray rayslight = generate_ray(x, y, screen_width, screen_height, light);
            double t;
			if (intersect_sphere(&ray, &sphere, &t)) {
				Vector3 *hit_pt = hit_point(ray, t);
				Vector3 *n_sphere = normal_sphere(*hit_pt, sphere);
				Vector3 *l_dir = light_dir(*n_sphere, light, *hit_pt);
				Vector3 *cam_dir = camera_dir(camera_pos, *hit_pt);
				double intensity = calculate_intensity(*n_sphere, *l_dir);
				int current_color = mix_colors(0x1864AA, 0, intensity);
				hit_pt = hit_point(rayslight, t);
				n_sphere = normal_sphere(*hit_pt, sphere);
				l_dir = light_dir(*n_sphere, light, *hit_pt);
				cam_dir = camera_dir(camera_pos, *hit_pt);
				intensity = calculate_intensity(*n_sphere, *l_dir);
				int new_color = mix_colors(0x33cc55, current_color, intensity);
				mlx_pixel_put(mlx, win, x, y, new_color);
			}
			else if (intersect_plane(&ray, &plane, &t)) {
				mlx_pixel_put(mlx, win, x, y, 0x33DD55);

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
	win = mlx_new_window(mlx, WINX, WINY, "Draw line!");
	img = mlx_new_image(mlx, WINX, WINY);
	color = mlx_get_color_value(mlx, color);
	mlx_pixel_put(mlx, win, WINX ,WINY, color);
	buffer = mlx_get_data_addr(img, &bitxpixel, &lines, &endian);
    Vector3 camera_pos = {0, 0, 0};      // Cámara en el origen
    Sphere sphere = {{0, 0, 5}, 1};      // Esfera en Z = 5 con radio 1
    Plane plane = {{1, 1, 0}, {1, 1, 1}};  // Esfera en Z = 5 con radio 1

    render_sphere(mlx, win, WINX, WINY, sphere, plane, camera_pos);

	//peint_plane(buffer, endian, lines,  color);
	//mlx_put_image_to_window(mlx, win, 0, 1);
	mlx_loop(mlx);
}