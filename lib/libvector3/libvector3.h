#ifndef LIBVECTOR3_H
#define LIBVECTOR3_H
typedef struct
{
	double	x;
	double	y;
	double	z;
	int	color;
} Vector3;

double calculate_intensity(Vector3 normal, Vector3 light_dir);
double distance(Vector3 init, Vector3 end);
double dot(Vector3 a, Vector3 b);
void normalize(Vector3 *v);
Vector3 *invnormal(Vector3 *normal);
Vector3 *normalize_withpoint(Vector3 init, Vector3 end);



#endif