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

#include "../lib/minilibx-linux/mlx.h"
#include "../lib/minilibx_opengl/mlx_opengl.h"
#include <math.h>
#define WINX 1280
#define WINY 720
# define X 0
# define Y 1
#include <time.h>
#include <stdio.h>
#include <stdlib.h>



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
int	ft_round(double num)
{
	int	rounded;

	rounded = (int)num;
	if (num - rounded >= .5)
		rounded++;
	return (rounded);
}
int	gradient(int startcolor, int endcolor, int len, int pix)
{
	double	increment[3];
	int		new[3];
	int		newcolor;

	increment[0] = (double)((endcolor >> 16) - \
					(startcolor >> 16)) / (double)len;
	increment[1] = (double)(((endcolor >> 8) & 0xFF) - \
					((startcolor >> 8) & 0xFF)) / (double)len;
	increment[2] = (double)((endcolor & 0xFF) - (startcolor & 0xFF)) \
					/ (double)len;
	new[0] = (startcolor >> 16) + ft_round(pix * increment[0]);
	new[1] = ((startcolor >> 8) & 0xFF) + ft_round(pix * increment[1]);
	new[2] = (startcolor & 0xFF) + ft_round(pix * increment[2]);
	newcolor = (new[0] << 16) + (new[1] << 8) + new[2];
	return (newcolor);
}
int	draw_line(Vector3 start, Vector3 end, void *win, void *mlx)
{
	Vector3	delta;
	Vector3	pixel;
	int		pixels;
	int		len;
    int color;
    int init_color;
    int end_color;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	delta.z = end.z - start.z;
	pixels = sqrt((delta.x * delta.x) + (delta.y * delta.y) + (delta.z * delta.z));
	len = pixels;
	delta.x /= pixels;
	delta.y /= pixels;
	pixel.x = start.x;
	pixel.y = start.y;
	while (pixels > 0)
	{
		//color = gradient(init_color, end_color, len, len - pixels);
        mlx_pixel_put(mlx, win, pixel.x, pixel.y, 0xFFFFFF);
		pixel.x += delta.x;
		pixel.y += delta.y;
		pixels = pixels - 1;
	}
	return (1);
}
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
    Ray *ray = malloc(sizeof(Ray));
    ray->origin = camera_pos;

    // Coordenadas de la pantalla (simulación de una cámara simple)
    ray->direction.x = (x - (screen_width / 2.0)) / screen_width;
    ray->direction.y = (y - (screen_height / 2.0)) / screen_height;
    ray->direction.z = 1;  // Apunta hacia adelante en el eje Z

    // Normalizar dirección del rayo
    double length = sqrt(ray->direction.x * ray->direction.x + ray->direction.y * ray->direction.y + ray->direction.z * ray->direction.z);
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
    return fmax(0.0, normal.x * light_dir.x + normal.y * light_dir.y + normal.z * light_dir.z);
}

void render_sphere(void *mlx, void *win, int screen_width, int screen_height, Sphere sphere, Plane *plans, Vector3 camera_pos) {
    Vector3 light = {10, 10, -10}; // luz
   // normalize(&light);
    time_t start, end;
	int color = 0x33cc55;
    start = clock();
	double max_x = 0;
	double max_y = 0;
	double min_x = 902;
	double min_y = 0;
    for (int y = 0; y < screen_height; ++y) {
        for (int x = 0; x < screen_width; ++x) {
            Ray ray = *generate_ray(x, y, WINX, WINY, camera_pos);
           	Ray rayslight = *generate_ray(x, y, WINX, WINY, light);
            double t = 0;
	 		 if (intersect_plane(&ray, &plans[0], &t))
			{
				Vector3 *hit_pt = hit_point(ray, t);
				Vector3 *cam_dir = camera_dir(camera_pos, *hit_pt);
				double intensity = calculate_intensity(plans[0].normal, *cam_dir);
				int current_color = mix_colors(0xD89A0B, 0xD89A0B, intensity);
                intersect_plane(&rayslight, &plans[0], &t);
				hit_pt = hit_point(rayslight, t);
				Vector3 *l_dir = light_dir(plans[0].normal, light, *hit_pt);
				intensity = calculate_intensity(plans[0].normal, *l_dir);
				int new_color = mix_colors(0x33cc55, current_color, intensity);
				mlx_pixel_put(mlx, win, x, y, new_color);
			}
  /* 			 if ( (x > (screen_width / 2)) && intersect_plane(&ray, &plans[2], &t))
			{
				Vector3 *hit_pt = hit_point(ray, t);
				Vector3 *cam_dir = camera_dir(camera_pos, *hit_pt);
				double intensity = calculate_intensity(plans[2].normal, *cam_dir);
				int current_color = mix_colors(0x19b191, 0x19b191, intensity);
                intersect_plane(&rayslight, &plans[2], &t);
				hit_pt = hit_point(rayslight, t);
				Vector3 *l_dir = light_dir(plans[2].normal, light, *hit_pt);
				intensity = calculate_intensity(plans[2].normal, *l_dir);
				int new_color = mix_colors(0x33cc55, current_color, intensity);
				mlx_pixel_put(mlx, win, x, y, new_color);
			}
	 		else if ((x < (screen_width / 2)) && intersect_plane(&ray, &plans[1], &t))
			{
				Vector3 *hit_pt = hit_point(ray, t);
				Vector3 *cam_dir = camera_dir(camera_pos, *hit_pt);
				double intensity = calculate_intensity(plans[1].normal, *cam_dir);
				int current_color = mix_colors(0xF05A7E, 0xF05A7E, intensity);
                intersect_plane(&rayslight, &plans[1], &t);
				hit_pt = hit_point(rayslight, t);
				Vector3 *l_dir = light_dir(plans[1].normal, light, *hit_pt);
				intensity = calculate_intensity(plans[1].normal, *l_dir);
				int new_color = mix_colors(0x33cc55, current_color, intensity);
				mlx_pixel_put(mlx, win, x, y, new_color);
			} */
			if (intersect_sphere(&ray, &sphere, &t))
			{
				Vector3 *hit_pt = hit_point(ray, t);
				Vector3 *n_sphere = normal_sphere(*hit_pt, sphere);
				Vector3 *cam_dir = camera_dir(camera_pos, *hit_pt);
				double intensity = calculate_intensity(*n_sphere, *cam_dir);
				int current_color = mix_colors(0x1864AA, 0, intensity);
				Vector3 *l_dir = light_dir(*n_sphere, light, *hit_pt);
                intersect_sphere(&rayslight, &sphere, &t);
				hit_pt = hit_point(rayslight, t);
				n_sphere = normal_sphere(*hit_pt, sphere);
				intensity = calculate_intensity(*n_sphere, *l_dir);
				int new_color = mix_colors(0x33cc55, current_color, intensity);
				mlx_pixel_put(mlx, win, x, y, new_color);
               // draw_line(camera_pos, (Vector3){x, y, 10}, win, mlx);
			}
          //  draw_line(ray.origin,ray.direction, win, mlx);
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
    Plane *plans = malloc(sizeof(Plane) * 5);
    plans[0] =  (Plane){{1, 0, 0}, {0, 0, 0}};
    plans[1] =  (Plane){{1, 1, 0}, {-2, 0, 0}};
    plans[2] =  (Plane){{-1, 1, 0}, {2, 0, 0}};
    plans[3] =  (Plane){{0, 0, 1}, {0, 0, 0}};
    plans[4] =  (Plane){{0, 1, 0}, {0, 0, 0}};
    normalize(&plans[0].normal);
    normalize(&plans[1].normal);
    normalize(&plans[2].normal);
    normalize(&plans[3].normal);
    normalize(&plans[4].normal);
    render_sphere(mlx, win, WINX, WINY, sphere, plans, camera_pos);

	mlx_loop(mlx);
}