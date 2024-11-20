#include "../../main.h"

Vector3 rotate_y(Vector3 v, double angle)
{
    Vector3 result;
    double radians = angle * M_PI / 180.0; // Convertir grados a radianes
    double cos_theta = cos(radians);
    double sin_theta = sin(radians);


    // Aplicar la rotación en Z
    result.x = v.x * cos_theta + v.z * sin_theta;
    result.y = v.y;
    result.z = -v.x * sin_theta + v.z * cos_theta;

    return result;
}

