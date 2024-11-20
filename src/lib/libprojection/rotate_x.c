#include "../../main.h"

Vector3 rotate_x(Vector3 v, double angle)
{
	Vector3	result;
	double radians = angle * M_PI / 180.0; // Convertir grados a radianes
	double cos_theta = cos(radians);
	double sin_theta = sin(radians);


	// Aplicar la rotación en X
	result.x = v.x;
	result.y = v.y * cos_theta - v.z * sin_theta;
	result.z = v.y * sin_theta + v.z * cos_theta;

	return result;
}
