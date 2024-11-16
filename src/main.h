/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathmatrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:06:31 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/17 11:27:48 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#include "../lib/minilibx-linux/mlx.h"
#include "../lib/libft/libft.h"
#include "../lib/minilibx_opengl/mlx_opengl.h"
#include <float.h>
#include <stdint.h>
#include <math.h>
#define EPSILON 1e-8 // Margen de tolerancia para precisión flotante

#define WINX 1280 
#define WINY 720
# define N_SAMPLING 1
# define X 0
# define Y 1
# define Z 2
#define SHININESS 30
#define KS 0.8
#define AMBIENT_INTENSITY 0.1 // Ajusta este valor según lo necesites

# define L_A_S_KC 1.0
# define L_A_S_KL 0.07
# define L_A_S_KQ 0.001

# define L_P_KC 1.0
# define L_P_KL 0
# define L_P_KQ 0.01

# define L_D_KC 1.0
# define L_D_KL 0.0
# define L_D_KQ 0.0

# define MAX_TEXTURE_SIZE 5
# define N_TYPE 5
# define MAX_COLOR_SIZE 5
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define MATTE_REFLECTION 0.1
#define MATTE_ABSORPTION 0.7
#define MATTE_TRANSMISSION 0.0
#define MATTE_GLOSSINESS 0.0
#define MATTE_DIFFUSION 0.9
#define MATTE_ROUGHNESS 0.8
#define MATTE_IRIDESCENCE 0.0
#define MATTE_EMISSION 0.0
#define MATTE_SSS 0.1
#define MATTE_TEXTURE "default_matte_texture"
#define MATTE_REFRACTION_INDEX 1.0 // Similar al aire
#define MATTE_COLOR "gray"

#define METAL_POLISHED_REFLECTION 0.9
#define METAL_POLISHED_ABSORPTION 0.1
#define METAL_POLISHED_TRANSMISSION 0.0
#define METAL_POLISHED_GLOSSINESS 1.0
#define METAL_POLISHED_DIFFUSION 0.1
#define METAL_POLISHED_ROUGHNESS 0.05
#define METAL_POLISHED_IRIDESCENCE 0.1
#define METAL_POLISHED_EMISSION 0.0
#define METAL_POLISHED_SSS 0.0
#define METAL_POLISHED_TEXTURE "default_metal_texture"
#define METAL_POLISHED_REFRACTION_INDEX 2.5 // Dependiendo del metal
#define METAL_POLISHED_COLOR "silver"

#define ABS_R 0.01
#define ABS_B 0.03
#define ABS_G 0.02
#define COL_T 5000 //Luz ligeramente calida
#define INTSITY 0.8 // Material muy reflectante pero no perfecto
#define REFLECT 0.95 // Intensidad de la luz


typedef enum
{
	PLANE,
	SPHERE,
	CYLINDER,
	TRIANGLE,
} e_obj;

typedef enum
{
	R,
	G,
	B
} e_col;
typedef struct
{
	double	x;
	double	y;
	double	z;
	int	color;
} Vector3;

typedef struct
{
	double	r;
	double	g;
	double	b;
	int		color;
} Color;
typedef struct
{
	double	x;
	double	y;
} Vector2;

typedef struct {
	Vector3	pos;
	Vector3	dir;
	Vector3	horizontal;
	Vector3	vertical;
	double	fov;
	double	aspect_ratio;
	double	plane_distance;
	double	plane_half_width;
	double	plane_half_height;
} Camera;

typedef struct
{
	Vector3	origin;
	Vector3	direction;
} Ray;

typedef struct t_materialProperties
{
    double reflect;                    // Reflexión
    double absorption[3];              // Absorción
    double transmission;               // Transmisión
    double glossiness;                 // Brillo
    double diffusion;                  // Difusión
    double iridescence;                // Iridescencia
    double emission;                   // Emisión
    double subsurface_scattering;      // SSS
    char texture[MAX_TEXTURE_SIZE];    // Textura
    double refraction_index;           // Índice de refracción
    int color[MAX_COLOR_SIZE];        // Color
	Color *vColor;
} MaterialProperties;


typedef struct
{
	Vector3				center;
	double				radius;
	int					color;
	MaterialProperties	mater_prop;
} Sphere;

typedef struct
{
	Vector3	center;
	Vector3	axis;
	double	diameter;
	double	height;
	MaterialProperties	mater_prop;
} Cylinder;

typedef struct
{
	Vector3				normal;
	Vector3				point;
	MaterialProperties	mater_prop;
} Plane;

typedef struct
{
	Vector3	vertex[3];
	Vector3	*dir[3];
	int		n_vertex;
	Plane	*p_triangle;
	MaterialProperties	mater_prop;
} Triangle;

typedef struct
{
	Vector3	point;
	double	ratio;
	Color	*color;
} Light;

typedef struct {
	Color	*color;
	double	ratio;
} Ambient;

typedef struct
{
	char	*buffer;
	int		bitxpixel;
	void	*img;
	int		lines;
	int		endian;
} Img;

typedef struct {
	void		*mlx;
	void		*win;
	Img			*img;
	Triangle	*triangle;
	Camera		*cameras;
	Sphere		*spheres;
	Cylinder	*cylinders;
	Plane		*planes;
	Light		*lights;
	int			n_lights;
	int			n_planes;
	int			n_cylinders;
	int			n_spheres;
	int			n_triangles;
	int			(*parser[10])(void *, void *);
} Scene;
int intersect_cylinder(const Ray *ray, const Cylinder *cylinder, double *t);
int find_nearest_cylinder(Scene scene, Ray *ray, double *t, int id, int type);
int line_solution_point(Ray ray, Vector3 point);
int triangle_solution_point(Triangle triangle, Vector3 hit_pt);
double	mod(Vector3 v);
double		sin_v3(Vector3 v1, Vector3 v2);
Vector3		cross_v3(Vector3 v1, Vector3 v2);
Vector3		*reflect(Vector3 L, Vector3 N);
Vector3 subtract(Vector3 init, Vector3 end);
int		is_in_shadow(Scene scene, Vector3 light_pos, Vector3 hit_point) ;
double	calculate_attenuation(double distance, double k_c, double k_l, double k_q);
int		colornormal_to_int(Color color);
void	addint_to_color(Color *color, int src);
void	fillcolor_by_int(Color *color, int src);
Color	*int_to_color(int src);
int		mix_colors(int base_color, int current_color, double intensity);
void	normalize_color(Color *color);
Color	*rgb_to_color(int r, int g, int b);
void	set_color(char *buffer, int endian, int color, int alpha);
int		get_color(char *buffer, int endian, int *alpha);
Color *illuminate_surface(Color *surface_color, Color *light_color, double intensity, double reflectivity, double glossiness, MaterialProperties prop);
Vector3	cross_v3(Vector3 v1, Vector3 v2);
double calculate_intensity(Vector3 normal, Vector3 light_dir);
double distance(Vector3 init, Vector3 end);
double dot(Vector3 a, Vector3 b);
void normalize(Vector3 *v);
Vector3 *invnormal(Vector3 *normal);
Vector3 *normalize_withpoint(Vector3 init, Vector3 end);
double specular_intensity(Vector3 reflection, Vector3 view_dir, double shininess, double ks);
int solve_quadratic(double a, double b, double c, double* t0, double* t1);
Vector3 *dir_withpoint(Vector3 init, Vector3 end);
int idxpixel(int x, int y);
void point3D_to_pixel(Vector3 point, Camera camera, int screen_width, int screen_height, Vector2 *pxl);
Ray *generate_ray(double x, double y, int screen_width, int screen_height, Camera camera);
Vector3 *hit_point(Ray ray, double t);
double mix(double a, double b, double t);
Ray *generate_reflect_ray(Scene *scene, Vector3 hit_pt, Vector3 normal);
//------RANDOM------
double random_double();
//------OBJECT------
int obj_solution_point(Scene scene, Vector3 point, int type, int id);
int idxfind_min(double *arr, int size);
int find_nearest_sphere(Scene scene, Ray *ray, double *t, int id, int type);
int	find_nearest_obj(Scene scene, Ray *ray, double *t, int *id, int type);
int intersect_sphere(const Ray *ray, const Sphere *sphere,  double *t);
Vector3 *normal_sphere(Vector3 hit_point, Sphere sphere);
int sphere_solution_point(Sphere sphere, Vector3 point);
int plane_solution_point(Plane plane, Vector3 point);
int intersect_plane(const Ray *ray, const Plane *plane, double *t);
//------PARSER------
int	parser_cylinder(Scene *scene, char **data);
int	parser_triangle(Scene *scene, char **data);
int	parser_camera(Scene *scene, char **data);
int	parser_plane(Scene *scene, char **data);
int	parser_light(Scene *scene, char **data);
int	parser_sphere(Scene *scene, char **data);
//------RENDER------
int find_nearest_triangle(Scene scene, Ray *ray, double *t, int id, int type);
int	render_triangle(Scene *scene, Vector3 hit_pt, int id);
int intersect_triangle(const Ray *ray, const Triangle *triangle, double *t);
int	render_plane(Scene *scene,Vector3 hit_pt, int id);
int	render_sphere(Scene *scene, Vector3 hit_pt, int id);
int render_sampling(int x, int y, Scene *scene, int samples_per_pixel);
int render_point_sphere(Scene scene, Vector3 hit_pt, int nb_sphere);
int render_point_plane(Scene scene, Vector3 hit_pt, int n_plane);
int find_nearest_plane(Scene scene, Ray *ray, double *t, int id, int type);
void render_scene(Scene *scene, int samples_per_pixel);
int	render_reflect_sphere(Scene *scene, Ray rayrfc, int id, int type);
int	render_reflect_plane(Scene *scene, Ray rayrfc, int id, int type);

#endif