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
# define MAIN_H

# include <X11/keysym.h>
# include <X11/X.h>
# include "../lib/minilibx-linux/mlx.h"
# include "../lib/libft/libft.h"
# include "../lib/minilibx_opengl/mlx_opengl.h"
# include <stdint.h>
# include <math.h>
# include <fcntl.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
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

typedef enum e_vals
{
	A,
}	t_valssss;

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vector3;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
	int		color;
}	Color;

typedef struct s_vector2
{
	double	x;
	double	y;
}	Vector2;

typedef struct s_camera
{
	t_vector3	pos;
	t_vector3	dir;
	t_vector3	horizontal;
	t_vector3	vertical;
	double	fov;
	double	aspect_ratio;
	double	plane_distance;
	double	plane_half_width;
	double	plane_half_height;
}	Camera;

typedef struct s_ray
{
	t_vector3	origin;
	t_vector3	direction;
}	Ray;

typedef struct s_img
{
	void	*img;
	char	*buffer;
	int		bitxpixel;
	int		lines;
	int		endian;
}	Img;

typedef struct s_materialProperties
{
	double	reflect;
	double	glssns;
	double	absorption[3];
	Img		texture;
	Color	vColor;
}	MaterialProperties;

typedef struct s_sphere
{
	t_vector3				center;
	double				radius;
	int					color;
	MaterialProperties	mater_prop;
}	Sphere;

typedef struct s_map_fun
{
	int		key;
	void	(*func)(void *);
}	t_map_fun;

typedef struct s_cylinder
{
	t_vector3				center;
	t_vector3				axis;
	double				diameter;
	double				height;
	MaterialProperties	mater_prop;
}	Cylinder;

typedef struct s_plane
{
	t_vector3				normal;
	t_vector3				point;
	MaterialProperties	mater_prop;
}	Plane;

typedef struct s_triangle
{
	t_vector3				vertex[3];
	int					n_vertex;
	Plane				*p_triangle;
	MaterialProperties	mater_prop;
}	Triangle;

typedef struct s_square
{
	t_vector3				center;
	t_vector3				normal;
	double				side;
	MaterialProperties	mater_prop;
}	Square;

typedef struct s_light
{
	t_vector3	point;
	double	ratio;
	Color	color;
}	Light;

typedef struct s_ambient
{
	Color	color;
	double	ratio;
}	Ambient;

typedef struct s_pos_obj
{
	int		type;
	int		idx;
	void	(*rot[10])(void *, t_vector3, int);
	void	(*pos[10])(void *, t_vector3);

}	t_pos_obj;

typedef struct s_sphere_isc_ctx
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
}	t_sphere_isc_ctx;

typedef struct s_triangle_isc_ctx
{
	t_vector3	edge1;
	t_vector3	edge2;
	t_vector3	h;
	t_vector3	s;
	t_vector3	q;
	double	a;
	double	f;
	double	u;
	double	v;
}	t_triangle_isc_ctx;

typedef struct s_isc_cyl_ctx
{
	t_vector3	ro;
	t_vector3	d;
	t_vector3	ca;
	double	a;
	double	b;
	double	c;
	Vector2	t;
	Vector2	y;
	double	th;
	double	half_h;
}	t_isc_cyl_ctx;

typedef struct s_scene
{
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
	t_pos_obj	*pos_obj;
	int			(*isc[10])(const void *, const void *, double *);
	int			(*rfc[10])(void *, Ray, int, int);
	int			(*render[10])(void *, t_vector3, int);
	int			(*parser[10])(void *, void *);
}	Scene;

typedef double	(*IntensityFunc)(t_vector3, t_vector3);
typedef double	(*AttenuationFunc)(double, double, double, double);
typedef t_vector3	(*ReflectFunc)(t_vector3, t_vector3);

typedef struct s_lighting_fun
{
	IntensityFunc	calculate_intensity;
	AttenuationFunc	calculate_attenuation;
	ReflectFunc		reflect;
}	LightingFunctions;

typedef struct s_rend_ctx
{
	Scene				*scene;
	t_vector3				hit_pt;
	t_vector3				normal;
	Ray					rayl;
	t_vector3				cam_dir;
	MaterialProperties	mater_prop;
	LightingFunctions	funcs;
}	RenderContext;

typedef struct s_light_ctx
{
	Light	*light;
	double	distance_light;
	double	attenuation;
	t_vector3	reflect_dir;
	double	diffuse_intensity;
	double	specular;
	Color	*current_color;
	double	full_phong;
}	t_light_ctx;

typedef struct s_nearest_ctx
{
	double	dist;
	int		id_o;
	int		type;
}	t_nearest_ctx;

//------FSM-------
void			init_intersect_fun(Scene *scene);
char			**init_args(void);
void			init_parser_fun(Scene *scene);
void			init_render_fun(Scene *scene);
void			init_rfc_render_fun(Scene *scene);
//------MATH-------
int				solve_quadratic(t_vector3 val, double *t0, double *t1);
int				terminate_program(void *param);
t_vector3			rotate_x(t_vector3 v, double angle);
t_vector3			rotate_z(t_vector3 v, double angle);
t_vector3			rotate_y(t_vector3 v, double angle);
//CONTROL
int				key_press(int key, Scene *param);
int				mouse_press(int button, int x, int y, void *param);
Color			darken_surface(Color *surface_color, double darkness_intensity);
//-----RENDER APPLY-----
Color			apply_lighting(const RenderContext *ctx, \
	t_vector3 *light_dir, t_vector3 *cam_dir);
Color			apply_shadow(const RenderContext *ctx, \
	t_vector3 *light_dir, t_vector3 *cam_dir, t_vector3 *opac_pt);
Color			apply_ambient(const RenderContext *ctx);
RenderContext	build_render_ctx(Scene *scene, MaterialProperties mater_prop, \
	t_vector3 normal, t_vector3 hit_pt);
//------libsarr----
int				ft_sarrprint(char **arr);
char			**ft_sarradd(char **arr, char *string);
int				ft_sarrsize(char **arr);
//-----libcolor/------
double			mix(double a, double b, double t);
t_vector3			reflect(t_vector3 L, t_vector3 N);
double			calculate_attenuation(double distance, double k_c, double k_l, \
double k_q);
int				colornormal_to_int(Color color);
void			addint_to_color(Color *color, int src);
void			fillcolor_by_int(Color *color, int src);
Color			int_to_color(int src);
void			normalize_color(Color *color);
Color			rgb_to_color(int r, int g, int b);
void			set_color(char *buffer, int endian, int color, int alpha);
int				get_color(char *buffer, int endian, int *alpha);
Color			illuminate_surface(Color surface_color, Color light_color, \
	double intensity, MaterialProperties prop);
double			calculate_attenuation(double distance, double k_c, double k_l, \
	double k_q);
//------libvector3/------
t_vector3			resolve_hit_point(Ray ray, double t);
t_vector3			*hit_point(Ray ray, double t);
t_vector3			scalev3(t_vector3 v, float scalar);
double			sin_v3(t_vector3 v1, t_vector3 v2);
t_vector3			cross_v3(t_vector3 v1, t_vector3 v2);
t_vector3			rotate_v3(t_vector3 v, t_vector3 axis, double angle);
t_vector3			add_scalar_to_vector3(t_vector3 init, double scale);
t_vector3			add_vector3_to_vector3(t_vector3 init, t_vector3 end);
t_vector3			multiplyv3(t_vector3 v, t_vector3 u);
t_vector3			norm_subtract(t_vector3 init, t_vector3 end);
t_vector3			subtract(t_vector3 init, t_vector3 end);
double			calculate_intensity(t_vector3 normal, t_vector3 light_dir);
double			distance(t_vector3 init, t_vector3 end);
int				line_solution_point(Ray ray, t_vector3 point);
double			mod(t_vector3 v);
//------lib/libbrdf/------
double			dot(t_vector3 a, t_vector3 b);
void			normalize(t_vector3 *v);
t_vector3			*invnormal(t_vector3 *normal);
double			specular_intensity(t_vector3 reflection, t_vector3 view_dir, \
	double shininess, double ks);
double			ft_atof(const char *str);
int				idxpixel(int width, int x, int y);
//------lib/libparse------
double			ft_limit(double min, double max, double val);
//------lib/libproject------
Ray				*generate_ray(Vector2 px, int screen_width, \
	int screen_height, Camera camera);
Ray				generate_reflect_ray(Scene *scene, t_vector3 hit_pt, \
	t_vector3 normal);
//------lib/libmapfun------
t_map_fun		map_fun_get(const t_map_fun *map_fun, int key);
//------control_camera/----
void			control_a(Scene *scene);
void			control_s(Scene *scene);
void			control_d(Scene *scene);
void			control_w(Scene *scene);
void			control_left(Scene *scene);
void			control_right(Scene *scene);
void			control_down(Scene *scene);
void			control_up(Scene *scene);
void			mlx_listen_meta(Scene *scene);
//------CONTROL_QUITE----
void			control_escape(Scene *scene);
//------RANDOM------
double			random_double(void);
int				idxfind_min(double *arr, int size);
//------scene.c------
int				obj_solution_point(Scene scene, t_vector3 point, int type, \
	int id);
int				find_nearest_obj(Scene scene, Ray *ray, \
	t_nearest_ctx *nrst_ctx);
//------cylinder.c----
int				find_nearest_cylinder(Scene scene, Ray *ray, \
	t_nearest_ctx *nrst_ctx);
int				intersect_cylinder(const Ray *ray, const Cylinder *cylinder, \
	double *t);
int				cylinder_solution_point(Cylinder cylinder, t_vector3 point);
t_vector3			normal_cylinder(t_vector3 hit_point, Cylinder cylinder);
void			rot_cylinder(Scene *scene, t_vector3 dir, int ang);
void			pos_cylinder(Scene *scene, t_vector3 dir);
//------sphere.c----
int				find_nearest_sphere(Scene scene, Ray *ray, \
	t_nearest_ctx *nrst_ctx);
int				intersect_sphere(const Ray *ray, const Sphere *sphere, \
	double *t);
int				sphere_solution_point(Sphere sphere, t_vector3 point);
void			pos_sphere(Scene *scene, t_vector3 dir);
//------triangle.c----
int				find_nearest_triangle(Scene scene, Ray *ray, \
	t_nearest_ctx *nrst_ctx);
int				intersect_triangle(const Ray *ray, const Triangle *triangle, \
	double *t);
void			rot_triangle(Scene *scene, t_vector3 dir, int ang);
void			pos_triangle(Scene *scene, t_vector3 dir);
//------plane.c----
int				find_nearest_plane(Scene scene, Ray *ray, \
	t_nearest_ctx *nrst_ctx);
int				intersect_plane(const Ray *ray, const Plane *plane, double *t);
int				plane_solution_point(Plane plane, t_vector3 point);
void			rot_plane(Scene *scene, t_vector3 dir, int ang);
void			pos_plane(Scene *scene, t_vector3 dir);
//------camera.c----
void			rot_camera(Scene *scene, t_vector3 dir, int ang);
void			pos_camera(Scene *scene, t_vector3 dir);
//------PARSER------
int				parser_cylinder(Scene *scene, char **data);
int				parser_triangle(Scene *scene, char **data);
int				parser_obj(Scene *scene, int fd);
int				parser_camera(Scene *scene, char **data);
int				parser_plane(Scene *scene, char **data);
int				parser_light(Scene *scene, char **data);
int				parser_sphere(Scene *scene, char **data);
int				parser_resolution(Scene *scene, char **data);
int				parser_ambient(Scene *scene, char **data);
int				parser_square(Scene *scene, char **data);
//------render/------
int				render_light(Scene scn, RenderContext ctx, void *obj, int tp);
int				render_reflect_cylinder(Scene *scn, Ray rayrfc, int id, int tp);
int				render_cylinder(Scene *scene, t_vector3 hit_pt, int id);
int				render_triangle(Scene *scene, t_vector3 hit_pt, int id);
int				render_plane(Scene *scene, t_vector3 hit_pt, int id);
int				render_sphere(Scene *scene, t_vector3 hit_pt, int id);
int				sampling(int x, int y, Scene *scene, int samples_per_pixel);
int				render_point_sphere(Scene scene, t_vector3 hit_pt, int nb_sphere);
int				render_point_plane(Scene scene, t_vector3 hit_pt, int n_plane);
void			render_scene(Scene *scene, int samples_per_pixel);
int				render_reflect_sphere(Scene *scene, Ray rayrfc, int id, int tp);
int				render_reflect_plane(Scene *scene, Ray rayrfc, int id, int tp);
int				render_reflect_triangle(Scene *scn, Ray rayrfc, int id, int tp);
// UTILS
void			ft_free_p2(char **dst);
void			*ft_realloc(void *ptr, size_t size_old, size_t size);
t_vector3			ft_coordinate(char *argv);
double			ft_ratio(char *str);
Color			ft_color(char *str);
t_vector3			stonorm(char *argv);
t_vector3			substract(t_vector3 init, t_vector3 end);
int				init_file(char *file);
int				is_in_shadow(Scene scene, t_vector3 light_pos, t_vector3 hit_point);

#endif