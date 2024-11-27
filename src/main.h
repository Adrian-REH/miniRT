/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:06:31 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 19:25:23 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H
#include <X11/keysym.h>
#include <X11/X.h>
#include "../lib/minilibx-linux/mlx.h"
#include "../lib/libft/libft.h"
#include "../lib/minilibx_opengl/mlx_opengl.h"
#include <float.h>
#include <stdint.h>
#include <math.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
# define EPSILON 1e-8 // Margen de tolerancia para precisión flotante
# define WINX 1280 
# define WINY 720
# define N_SAMPLING 1
# define X 0
# define Y 1
# define Z 2
# define SHININESS 30
# define KS 0.8
# define AMBIENT_INTENSITY 0.1 // Ajusta este valor según lo necesites
# define L_P_KC 1.0
# define L_P_KL 0
# define L_P_KQ 0.01
# define MAX_TEXTURE_SIZE 5
# define N_TYPE 5
# define MAX_COLOR_SIZE 5
# define PI 3.1415
# define PLANE 0
# define SPHERE 1
# define TRIANGLE 2
# define CYLINDER 3
# define CAMERA 4
# define LIGHT 5
# define R 0
# define G 1
# define B 2

typedef enum {
	A,
}t_valssss;

typedef struct t_vector3 {
	double	x;
	double	y;
	double	z;
} Vector3;

typedef struct {
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

typedef struct
{
	void	*img;
	char	*buffer;
	int		bitxpixel;
	int		lines;
	int		endian;
} Img;

typedef struct t_materialProperties
{
	double	reflect;
	double	glssns;
	double	absorption[3];
	Img		texture;
	Color	vColor;
}	MaterialProperties;




typedef struct
{
	Vector3				center;
	double				radius;
	int					color;
	MaterialProperties	mater_prop;
} Sphere;


typedef struct
{
	int key;
	void (*func)(void *);
}	t_map_fun;


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
	int		n_vertex;
	Plane	*p_triangle;
	MaterialProperties	mater_prop;
} Triangle;

typedef struct
{
	Vector3	center;
	Vector3	normal;
	double	side;
	MaterialProperties	mater_prop;
} Square;

typedef struct
{
	Vector3	point;
	double	ratio;
	Color	color;
}	Light;

typedef struct {
	Color	color;
	double	ratio;
} Ambient;


typedef struct {
	int type;
	int idx;
	void (*rot[10])(void *, Vector3, int);
	void (*pos[10])(void *, Vector3);

} s_pos_obj;

typedef struct t_sphere_isc_ctx {
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
}	s_sphere_isc_ctx;

typedef struct t_triangle_isc_ctx {
	Vector3	edge1;
	Vector3	edge2;
	Vector3	h;
	Vector3	s;
	Vector3	q;
	double	a;
	double	f;
	double	u;
	double	v;
}	s_triangle_isc_ctx;

typedef struct t_isc_cyl_ctx{
	Vector3	ro;
	Vector3	d;
	Vector3	ca;
	double	a;
	double	b;
	double	c;
	Vector2	t;
	Vector2	y;
	double	th;
	double	half_h;
} s_isc_cyl_ctx;

typedef struct {
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	Img			*img;
	Camera		*cameras;
	Ambient		*ambient;
	Sphere		*spheres;
	Square		*squares;
	Triangle	*triangles;
	Cylinder	*cylinders;
	Plane		*planes;
	Light		*lights;
	int			n_lights;
	int			n_planes;
	int			n_cylinders;
	int			n_spheres;
	int			n_squares;
	int			n_triangles;
	int			n_interaction;
	s_pos_obj	*pos_obj;
	int			(*isc[10])(const void *, const void *, double *);
	int			(*rfc[10])(void *, Ray, int, int);
	int			(*render[10])(void *, Vector3, int);
	int			(*parser[10])(void *, void *);
} Scene;
typedef double (*IntensityFunc)(Vector3, Vector3);
typedef double (*AttenuationFunc)(double, double, double, double);
typedef Vector3 (*ReflectFunc)(Vector3, Vector3);

typedef struct {
	IntensityFunc calculate_intensity;
	AttenuationFunc calculate_attenuation;
	ReflectFunc reflect;
} LightingFunctions;

typedef struct {
	Scene *scene;
	Vector3 hit_pt;
	Vector3 normal;
	Ray rayl;
	Vector3 cam_dir;
	MaterialProperties mater_prop;
	LightingFunctions funcs;
} RenderContext;


typedef struct t_light_ctx {
	Light	*light;
	double	distance_light;
	double	attenuation;
	Vector3	reflect_dir;
	double	diffuse_intensity;
	double	specular;
	Color	*current_color;
	double	full_phong;
} s_light_ctx;

typedef struct t_nearest_ctx {
	double	dist;
	int		id_o;
	int		type;
} s_nearest_ctx;
//------FSM-------
void	init_intersect_fun(Scene *scene);
char	**init_args();
void	init_parser_fun(Scene *scene);
void	init_render_fun(Scene *scene);
void	init_rfc_render_fun(Scene *scene);
//------MATH-------
int		solve_quadratic(Vector3 val, double* t0, double* t1);
int		terminate_program(void *param);
Vector3	rotate_x(Vector3 v, double angle);
Vector3	rotate_z(Vector3 v, double angle);
Vector3	rotate_y(Vector3 v, double angle);
//CONTROL
int		key_press(int key, Scene *param);
int		mouse_press(int button, int x, int y, void *param);
Color	darken_surface(Color *surface_color, double darkness_intensity);
//-----RENDER APPLY-----
Color	apply_lighting(const RenderContext *ctx, Vector3 *light_dir, Vector3 *cam_dir);
Color	apply_shadow(const RenderContext *ctx, Vector3 *light_dir, Vector3 *cam_dir, Vector3 *opac_pt);
Color	apply_ambient(const RenderContext *ctx);
RenderContext	build_render_ctx(Scene *scene, MaterialProperties mater_prop, Vector3 normal, Vector3 hit_pt);
RenderContext	build_render_ctxv2(Scene *scene, MaterialProperties mater_prop, Vector3 normal, Vector3 hit_pt, Vector3 cam_dir);
//------libsarr----
int		ft_sarrprint(char **arr);
char	**ft_sarradd(char **arr, char *string);
int		ft_sarrsize(char **arr);
//-----libcolor/------
double	mix(double a, double b, double t);
Vector3	reflect(Vector3 L, Vector3 N);
double	calculate_attenuation(double distance, double k_c, double k_l, double k_q);
int		colornormal_to_int(Color color);
void	addint_to_color(Color *color, int src);
void	fillcolor_by_int(Color *color, int src);
Color	int_to_color(int src);
void	normalize_color(Color *color);
Color	rgb_to_color(int r, int g, int b);
void	set_color(char *buffer, int endian, int color, int alpha);
int		get_color(char *buffer, int endian, int *alpha);
Color	illuminate_surface(Color surface_color, Color light_color, double intensity, MaterialProperties prop);
double	calculate_attenuation(double distance, double k_c, double k_l, double k_q);
//------libvector3/------
Vector3	resolve_hit_point(Ray ray, double t);
Vector3	*hit_point(Ray ray, double t);
Vector3	scalev3(Vector3 v, float scalar);
double	sin_v3(Vector3 v1, Vector3 v2);
Vector3	cross_v3(Vector3 v1, Vector3 v2);
Vector3	rotate_v3(Vector3 v, Vector3 axis, double angle);
Vector3	add_scalar_to_vector3(Vector3 init, double scale);
Vector3	add_vector3_to_vector3(Vector3 init, Vector3 end);
Vector3	multiplyv3(Vector3 v, Vector3 u);
Vector3	norm_subtract(Vector3 init, Vector3 end);
Vector3	subtract(Vector3 init, Vector3 end);
double	calculate_intensity(Vector3 normal, Vector3 light_dir);
double	distance(Vector3 init, Vector3 end);
int		line_solution_point(Ray ray, Vector3 point);
double	mod(Vector3 v);
//------lib/libbrdf/------
double	dot(Vector3 a, Vector3 b);
void	normalize(Vector3 *v);
Vector3	*invnormal(Vector3 *normal);
double	specular_intensity(Vector3 reflection, Vector3 view_dir, double shininess, double ks);
double	ft_atof(const char *str);
int		idxpixel(int width, int x, int y);
//------lib/libparse------
double	ft_limit(double min, double max, double val);
//------lib/libproject------
void	point3D_to_pixel(Vector3 point, Camera camera);
Ray		*generate_ray(Vector2 px, int screen_width, int screen_height, Camera camera);
Ray		generate_reflect_ray(Scene *scene, Vector3 hit_pt, Vector3 normal);
//------lib/libmapfun------
t_map_fun map_fun_get(const t_map_fun *map_fun, int key);
//------control_camera/----
void	control_a(Scene *scene);
void	control_s(Scene *scene);
void	control_d(Scene *scene);
void	control_w(Scene *scene);
void	control_left(Scene *scene);
void	control_right(Scene *scene);
void	control_down(Scene *scene);
void	control_up(Scene *scene);
void	mlx_listen_meta(Scene *scene);
//------CONTROL_QUITE----
void	control_escape(Scene *scene);
//------RANDOM------
double random_double();
int		idxfind_min(double *arr, int size);
//------scene.c------
int		obj_solution_point(Scene scene, Vector3 point, int type, int id);
int		find_nearest_obj(Scene scene, Ray *ray, s_nearest_ctx *nrst_ctx);
//------cylinder.c----
int		find_nearest_cylinder(Scene scene, Ray *ray, s_nearest_ctx *nrst_ctx);
int		intersect_cylinder(const Ray *ray, const Cylinder *cylinder, double *t);
int		cylinder_solution_point(Cylinder cylinder, Vector3 point);
Vector3	normal_cylinder(Vector3 hit_point, Cylinder cylinder);
void	rot_cylinder(Scene *scene, Vector3 dir, int ang);
void	pos_cylinder(Scene *scene, Vector3 dir);
//------sphere.c----
int		find_nearest_sphere(Scene scene, Ray *ray, s_nearest_ctx *nrst_ctx);
int		intersect_sphere(const Ray *ray, const Sphere *sphere,  double *t);
Vector3	*normal_sphere(Vector3 hit_point, Sphere sphere);
int		sphere_solution_point(Sphere sphere, Vector3 point);
void	pos_sphere(Scene *scene, Vector3 dir);
//------triangle.c----
int		find_nearest_triangle(Scene scene, Ray *ray, s_nearest_ctx *nrst_ctx);
int		intersect_triangle(const Ray *ray, const Triangle *triangle, double *t);
void	rot_triangle(Scene *scene, Vector3 dir, int ang);
void	pos_triangle(Scene *scene, Vector3 dir);
//------plane.c----
int		find_nearest_plane(Scene scene, Ray *ray, s_nearest_ctx *nrst_ctx);
int		intersect_plane(const Ray *ray, const Plane *plane, double *t);
int		plane_solution_point(Plane plane, Vector3 point);
void	rot_plane(Scene *scene, Vector3 dir, int ang);
void	pos_plane(Scene *scene, Vector3 dir);
//------camera.c----
void	rot_camera(Scene *scene, Vector3 dir, int ang);
void	pos_camera(Scene *scene, Vector3 dir);
//------PARSER------
int		parser_cylinder(Scene *scene, char **data);
int		parser_triangle(Scene *scene, char **data);
int		parser_obj(Scene *scene, int fd);
int		parser_camera(Scene *scene, char **data);
int		parser_plane(Scene *scene, char **data);
int		parser_light(Scene *scene, char **data);
int		parser_sphere(Scene *scene, char **data);
int		parser_resolution(Scene *scene, char **data);
int		parser_ambient(Scene *scene, char **data);
int		parser_square(Scene *scene, char **data);
//------render/------
int		render_light(Scene scene, RenderContext ctx, void *obj, int type);
int		render_reflect_cylinder(Scene *scene, Ray rayrfc, int id, int type);
int		render_cylinder(Scene *scene, Vector3 hit_pt, int id);
int		render_triangle(Scene *scene, Vector3 hit_pt, int id);
int		render_plane(Scene *scene,Vector3 hit_pt, int id);
int		render_sphere(Scene *scene, Vector3 hit_pt, int id);
int		sampling(int x, int y, Scene *scene, int samples_per_pixel);
int		render_point_sphere(Scene scene, Vector3 hit_pt, int nb_sphere);
int		render_point_plane(Scene scene, Vector3 hit_pt, int n_plane);
void	render_scene(Scene *scene, int samples_per_pixel);
int		render_reflect_sphere(Scene *scene, Ray rayrfc, int id, int type);
int		render_reflect_plane(Scene *scene, Ray rayrfc, int id, int type);
int		render_reflect_triangle(Scene *scene, Ray rayrfc, int id, int type);
// UTILS
void	ft_free_p2(char **dst);
void	*ft_realloc(void *ptr, size_t size_old, size_t size);
Vector3	ft_coordinate(char *argv);
double	ft_ratio(char *str);
Color	ft_color(char *str);
Vector3	stonorm(char *argv);
Vector3	substract(Vector3 init, Vector3 end);
int		init_file(char *file);


int		is_in_shadow(Scene scene, Vector3 light_pos, Vector3 hit_point) ;

#endif