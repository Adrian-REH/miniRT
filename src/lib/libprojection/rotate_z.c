#include "../../main.h"

Vector3 rotate_z(Vector3 v, double angle) {
    Vector3 result;
    double radians = angle * M_PI / 180.0; // Convertir grados a radianes
    double cos_theta = cos(radians);
    double sin_theta = sin(radians);


    // Aplicar la rotación en Z
    result.x = v.x * cos_theta - v.y * sin_theta;
    result.y = v.x * sin_theta + v.y * cos_theta;
    result.z = v.z;

    return result;
}
