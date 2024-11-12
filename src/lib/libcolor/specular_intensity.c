#include "../../main.h"

double specular_intensity(Vector3 reflection, Vector3 view_dir, double shininess, double ks) 
{
	double dot_product = dot(reflection, view_dir);
	double intensity = pow(fmax(dot_product, 0.0), shininess) * ks;
	return intensity;
}
