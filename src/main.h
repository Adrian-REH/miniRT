/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:06:31 by adherrer          #+#    #+#             */
/*   Updated: 2024/12/01 17:13:09 by razamora         ###   ########.fr       */
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
# define WINX 800 
# define WINY 800
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
}	t_color;

typedef struct s_vector2
{
	double	x;
	double	y;
}	t_vector2;

typedef struct s_camera
{
	t_vector3	pos;
	t_vector3	dir;
	t_vector3	horizontal;
	t_vector3	vertical;
	double		fov;
	double		aspect_ratio;
	double		plane_distance;
	double		plane_half_width;
	double		plane_half_height;
}	t_camera;

typedef struct s_ray
{
	t_vector3	origin;
	t_vector3	direction;
}	t_ray;

typedef struct s_img
{
	void	*img;
	char	*buffer;
	int		bitxpixel;
	int		lines;
	int		endian;
}	t_img;

typedef struct s_mater_prop
{
	double	reflect;
	double	glssns;
	double	absorption[3];
	t_img	texture;
	t_color	color;
}	t_mater_prop;

typedef struct s_sphere
{
	t_vector3			center;
	double				radius;
	int					color;
	t_mater_prop		mater_prop;
}	t_sphere;

typedef struct s_map_fun
{
	int		key;
	void	(*func)(void *);
}	t_map_fun;

typedef struct s_cylinder
{
	t_vector3			center;
	t_vector3			axis;
	double				diameter;
	double				height;
	t_mater_prop		mater_prop;
}	t_cylinder;

typedef struct s_plane
{
	t_vector3			normal;
	t_vector3			point;
	t_mater_prop		mater_prop;
}	t_plane;

typedef struct s_triangle
{
	t_vector3			vertex[3];
	int					n_vertex;
	t_plane				p_triangle;
	t_mater_prop		mater_prop;
}	t_triangle;

typedef struct s_square
{
	t_vector3			center;
	t_vector3			normal;
	double				side;
	t_mater_prop		mater_prop;
}	t_square;

typedef struct s_light
{
	t_vector3	point;
	double		ratio;
	t_color		color;
}	t_light;

typedef struct s_ambient
{
	t_color	color;
	double	ratio;
}	t_mbient;

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
	double		a;
	double		f;
	double		u;
	double		v;
}	t_triangle_isc_ctx;

typedef struct s_isc_cyl_ctx
{
	t_vector3	ro;
	t_vector3	d;
	t_vector3	ca;
	double		a;
	double		b;
	double		c;
	t_vector2	t;
	t_vector2	y;
	double		th;
	double		half_h;
}	t_isc_cyl_ctx;

typedef struct s_scene
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	t_img		*img;
	t_camera	*cameras;
	t_mbient	*ambient;
	t_sphere	*spheres;
	t_square	*squares;
	t_triangle	*triangles;
	t_cylinder	*cylinders;
	t_plane		*planes;
	t_light		*lights;
	int			n_lights;
	int			n_planes;
	int			n_cylinders;
	int			n_spheres;
	int			n_squares;
	int			n_triangles;
	int			n_interaction;
	t_pos_obj	*pos_obj;
	int			(*isc[10])(const void *, const void *, double *);
	int			(*rfc[10])(void *, t_ray, int, int);
	int			(*render[10])(void *, t_vector3, int);
	int			(*parser[10])(void *, void *);
}	t_scene;

typedef double		(*t_intensity_func)(t_vector3, t_vector3);
typedef double		(*t_attenuation_func)(double, double, double, double);
typedef t_vector3	(*t_reflect_func)(t_vector3, t_vector3);

typedef struct s_lighting_fun
{
	t_intensity_func	calculate_intensity;
	t_attenuation_func	calculate_attenuation;
	t_reflect_func		reflect;
}	t_lighting_fun;

typedef struct s_rend_ctx
{
	t_scene				*scene;
	t_vector3			hit_pt;
	t_vector3			normal;
	t_ray				rayl;
	t_vector3			cam_dir;
	t_mater_prop		mater_prop;
	t_lighting_fun		funcs;
}	t_rend_ctx;

typedef struct s_light_ctx
{
	t_light		*light;
	double		distance_light;
	double		attenuation;
	t_vector3	reflect_dir;
	double		diffuse_intensity;
	double		specular;
	t_color		*current_color;
	double		full_phong;
}	t_light_ctx;

typedef struct s_nearest_ctx
{
	double	dist;
	int		id_o;
	int		type;
}	t_nearest_ctx;

//------FSM-------
void			init_intersect_fun(t_scene *scene);
char			**init_args(void);
void			init_parser_fun(t_scene *scene);
void			init_render_fun(t_scene *scene);
void			init_rfc_render_fun(t_scene *scene);
//------MATH-------
int				solve_quadratic(t_vector3 val, double *t0, double *t1);
int				terminate_program(void *param);
t_vector3		rotate_x(t_vector3 v, double angle);
t_vector3		rotate_z(t_vector3 v, double angle);
t_vector3		rotate_y(t_vector3 v, double angle);
//CONTROL
int				key_press(int key, t_scene *param);
int				mouse_press(int button, int x, int y, void *param);
t_color			darken_surface(t_color *surface_color, double drk_int);
//-----RENDER APPLY-----
t_color			apply_lighting(const t_rend_ctx *ctx, \
	t_vector3 *light_dir, t_vector3 *cam_dir);
t_color			apply_shadow(const t_rend_ctx *ctx, \
	t_vector3 *light_dir, t_vector3 *cam_dir, t_vector3 *opac_pt);
t_color			apply_ambient(const t_rend_ctx *ctx);
t_rend_ctx		build_render_ctx(t_scene *scene, t_mater_prop mater_prop, \
	t_vector3 normal, t_vector3 hit_pt);
//------libsarr----
int				ft_sarrprint(char **arr);
char			**ft_sarradd(char **arr, char *string);
int				ft_sarrsize(char **arr);
//-----libcolor/------
double			mix(double a, double b, double t);
t_vector3		reflect(t_vector3 L, t_vector3 N);
double			calculate_attenuation(double distance, double k_c, double k_l, \
double k_q);
int				colornormal_to_int(t_color color);
void			addint_to_color(t_color *color, int src);
void			fillcolor_by_int(t_color *color, int src);
t_color			int_to_color(int src);
void			normalize_color(t_color *color);
t_color			rgb_to_color(int r, int g, int b);
void			set_color(char *buffer, int endian, int color, int alpha);
int				get_color(char *buffer, int endian, int *alpha);
t_color			illuminate_surface(t_color surface_color, t_color light_color, \
	double intensity, t_mater_prop prop);
double			calculate_attenuation(double distance, double k_c, double k_l, \
	double k_q);
//------libvector3/------
t_vector3		resolve_hit_point(t_ray ray, double t);
t_vector3		*hit_point(t_ray ray, double t);
t_vector3		scalev3(t_vector3 v, float scalar);
double			sin_v3(t_vector3 v1, t_vector3 v2);
t_vector3		cross_v3(t_vector3 v1, t_vector3 v2);
t_vector3		rotate_v3(t_vector3 v, t_vector3 axis, double angle);
t_vector3		add_scalar_to_vector3(t_vector3 init, double scale);
t_vector3		add_vector3_to_vector3(t_vector3 init, t_vector3 end);
t_vector3		multiplyv3(t_vector3 v, t_vector3 u);
t_vector3		norm_subtract(t_vector3 init, t_vector3 end);
t_vector3		subtract(t_vector3 init, t_vector3 end);
double			calculate_intensity(t_vector3 normal, t_vector3 light_dir);
double			distance(t_vector3 init, t_vector3 end);
int				line_solution_point(t_ray ray, t_vector3 point);
double			mod(t_vector3 v);
//------lib/libbrdf/------
double			dot(t_vector3 a, t_vector3 b);
void			normalize(t_vector3 *v);
t_vector3		*invnormal(t_vector3 *normal);
double			specular_intensity(t_vector3 reflection, t_vector3 view_dir, \
	double shininess, double ks);
double			ft_atof(const char *str);
int				idxpixel(int width, int x, int y);
//------lib/libparse------
double			ft_limit(double min, double max, double val);
//------lib/libproject------
t_ray			*generate_ray(t_vector2 px, int screen_width, \
	int screen_height, t_camera camera);
t_ray			generate_reflect_ray(t_scene *scene, t_vector3 hit_pt, \
	t_vector3 normal);
//------lib/libmapfun------
t_map_fun		map_fun_get(const t_map_fun *map_fun, int key);
//------control_camera/----
void			control_a(t_scene *scene);
void			control_s(t_scene *scene);
void			control_d(t_scene *scene);
void			control_w(t_scene *scene);
void			control_left(t_scene *scene);
void			control_right(t_scene *scene);
void			control_down(t_scene *scene);
void			control_up(t_scene *scene);
void			mlx_listen_meta(t_scene *scene);
//------CONTROL_QUITE----
void			control_escape(t_scene *scene);
//------RANDOM------
double			random_double(void);
int				idxfind_min(double *arr, int size);
//------scene.c------
int				obj_solution_point(t_scene scene, t_vector3 point, int type, \
	int id);
int				find_nearest_obj(t_scene scene, t_ray *ray, \
	t_nearest_ctx *nrst_ctx);
//------cylinder.c----
int				find_nearest_cylinder(t_scene scene, t_ray *ray, \
	t_nearest_ctx *nrst_ctx);
int				intersect_cylinder(const t_ray *ray, const t_cylinder *cy, \
	double *t);
int				cylinder_solution_point(t_cylinder cylinder, t_vector3 point);
t_vector3		normal_cylinder(t_vector3 hit_point, t_cylinder cylinder);
void			rot_cylinder(t_scene *scene, t_vector3 dir, int ang);
void			pos_cylinder(t_scene *scene, t_vector3 dir);
//------sphere.c----
int				find_nearest_sphere(t_scene scene, t_ray *ray, \
	t_nearest_ctx *nrst_ctx);
int				intersect_sphere(const t_ray *ray, const t_sphere *sphere, \
	double *t);
int				sphere_solution_point(t_sphere sphere, t_vector3 point);
void			pos_sphere(t_scene *scene, t_vector3 dir);
//------triangle.c----
int				find_nearest_triangle(t_scene scene, t_ray *ray, \
	t_nearest_ctx *nrst_ctx);
int				intersect_triangle(const t_ray *ray, const t_triangle *tr, \
	double *t);
void			rot_triangle(t_scene *scene, t_vector3 dir, int ang);
void			pos_triangle(t_scene *scene, t_vector3 dir);
//------plane.c----
int				find_nearest_plane(t_scene scene, t_ray *ray, \
	t_nearest_ctx *nrst_ctx);
int				intersect_plane(const t_ray *ray, const t_plane *pn, double *t);
int				plane_solution_point(t_plane plane, t_vector3 point);
void			rot_plane(t_scene *scene, t_vector3 dir, int ang);
void			pos_plane(t_scene *scene, t_vector3 dir);
//------camera.c----
void			rot_camera(t_scene *scene, t_vector3 dir, int ang);
void			pos_camera(t_scene *scene, t_vector3 dir);
//------PARSER------
int				parser_cylinder(t_scene *scene, char **data);
int				parser_triangle(t_scene *scene, char **data);
int				parser_obj(t_scene *scene, int fd);
int				parser_camera(t_scene *scene, char **data);
int				parser_plane(t_scene *scene, char **data);
int				parser_light(t_scene *scene, char **data);
int				parser_sphere(t_scene *scene, char **data);
int				parser_resolution(t_scene *scene, char **data);
int				parser_ambient(t_scene *scene, char **data);
int				parser_square(t_scene *scene, char **data);
//------render/------
int				render_light(t_scene scn, t_rend_ctx ctx, void *obj, int tp);
int				render_reflect_cylinder(t_scene *scn, t_ray rfc, int i, int tp);
int				render_cylinder(t_scene *scn, t_vector3 hit_pt, int id);
int				render_triangle(t_scene *scn, t_vector3 hit_pt, int id);
int				render_plane(t_scene *scn, t_vector3 hit_pt, int id);
int				render_sphere(t_scene *scn, t_vector3 hit_pt, int id);
int				sampling(int x, int y, t_scene *scn, int samples_per_pixel);
int				render_point_sphere(t_scene scn, t_vector3 hit_pt, int nb_sph);
int				render_point_plane(t_scene scn, t_vector3 hit_pt, int n_plane);
void			render_scene(t_scene *scn, int samples_per_pixel);
int				render_reflect_sphere(t_scene *scn, t_ray rrfc, int id, int tp);
int				render_reflect_plane(t_scene *scn, t_ray rrfc, int id, int tp);
int				render_reflect_triangle(t_scene *scn, t_ray rfc, int i, int tp);
// UTILS
void			ft_free_p2(char **dst);
void			*ft_realloc(void *ptr, size_t size_old, size_t size);
t_vector3		ft_coordinate(char *argv);
double			ft_ratio(char *str);
t_color			ft_color(char *str);
t_vector3		stonorm(char *argv);
t_vector3		substract(t_vector3 init, t_vector3 end);
int				init_file(char *file);
int				is_in_shadow(t_scene scene, t_vector3 light_pos, \
	t_vector3 hit_point);

#endif