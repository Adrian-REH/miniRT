#include "../../main.h"

Vector3 rotate_v3(Vector3 v, Vector3 axis, double angle)
{
    double radians = angle * M_PI / 180.0;  // Convertir de grados a radianes
    double cos_theta = cos(radians);
    double sin_theta = sin(radians);

    // Producto punto entre el eje y el vector
    double dt = dot(v, axis);

    // Rotación utilizando la fórmula de rotación de Rodrigues
    Vector3 result;
    result.x = v.x * cos_theta + cross_v3(axis, v).x * sin_theta + axis.x * dt * (1 - cos_theta);
    result.y = v.y * cos_theta + cross_v3(axis, v).y * sin_theta + axis.y * dt * (1 - cos_theta);
    result.z = v.z * cos_theta + cross_v3(axis, v).z * sin_theta + axis.z * dt * (1 - cos_theta);
    
    return result;
}