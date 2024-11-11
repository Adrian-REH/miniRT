#ifndef LIBCOLOR_H
#define LIBCOLOR_H
typedef struct
{
	double	r;
	double	g;
	double	b;
	int		color;
} Color;
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

#endif