/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:12:23 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/02 01:41:09 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minilibx-linux/mlx.h"
#include <math.h>
#define WINX 1280
#define WINY 720

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

int intersect_sphere(const Ray *ray, const Sphere *sphere, double *t) {
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

void render_sphere(void *mlx, void *win, int screen_width, int screen_height, Sphere sphere, Vector3 camera_pos) {
    Vector3 light = {0, 1, 6};   // luz
    for (int y = 0; y < screen_height; ++y) {
        for (int x = 0; x < screen_width; ++x) {
            Ray ray = generate_ray(x, y, screen_width, screen_height, camera_pos);
            Ray rayslight = generate_ray(x, y, screen_width, screen_height, light);
            double t;
            if (intersect_sphere(&ray, &sphere, &t)) {
				if (intersect_sphere(&rayslight, &sphere, &t)){
					mlx_pixel_put(mlx, win, x, y, 0x33cc55);  // Color negro si no hay intersección
				}else{
					mlx_pixel_put(mlx, win, x, y, 0xFFFFFF);  // Color blanco si hay intersección
				}
            }
        }
    }
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
    Sphere sphere = {{0, 0, 5}, 1};      // Esfera en Z = 5 con radio 1
    Vector3 camera_pos = {0, 0, 0};      // Cámara en el origen

    render_sphere(mlx, win, WINX, WINY, sphere, camera_pos);

	//peint_plane(buffer, endian, lines,  color);
	//mlx_put_image_to_window(mlx, win, 0, 1);
	mlx_loop(mlx);
}