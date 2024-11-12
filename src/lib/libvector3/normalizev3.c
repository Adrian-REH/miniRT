#include "../../main.h"
void normalize(Vector3 *v)
{
	// Calcula la magnitud del vector
	double magnitude = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	
	// Evita la división por cero
	if (magnitude > 0) {
		v->x /= magnitude;
		v->y /= magnitude;
		v->z /= magnitude;
	}
}


Vector3 *invnormal(Vector3 *normal)
{
	normal->x = -normal->x;
	normal->y = -normal->y;
	normal->z = -normal->z;
	return normal;
}


Vector3 *normalize_withpoint(Vector3 init, Vector3 end)
{
	Vector3 *direction = malloc(sizeof(Vector3));

	// Calcula el vector de dirección restando los puntos
	direction->x = end.x - init.x;
	direction->y = end.y - init.y;
	direction->z = end.z - init.z;

	// Calcula la longitud del vector de dirección
	double length = sqrt(direction->x * direction->x + direction->y * direction->y + direction->z * direction->z);
	// Normaliza el vector de dirección si la longitud es mayor que 0
	if (length > 0) {
		direction->x /= length;
		direction->y /= length;
		direction->z /= length;
	} else {
		direction->x = 0;
		direction->y = 0;
		direction->z = 0;
	}

	return direction;
}
