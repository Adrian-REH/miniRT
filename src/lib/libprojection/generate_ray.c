#include "../../main.h"

Ray *generate_ray(double x, double y, int screen_width, int screen_height, Camera camera)
{

	// Inicializa el rayo y su origen
	Ray *ray = malloc(sizeof(Ray));
	ray->origin = camera.pos;

	// Calcula las coordenadas del punto en el plano de proyección
    double px = (2 * (x ) / (float) WINX - 1) * camera.aspect_ratio * camera.plane_distance;
    double py = (1 - 2 * (y ) / (float) WINY) * camera.plane_distance;

	// Calcula el punto en el plano de proyección usando los vectores de la cámara
	Vector3 point_on_plane = {
		camera.dir.x  + camera.horizontal.x * px + camera.vertical.x * py,
		camera.dir.y  + camera.horizontal.y * px + camera.vertical.y * py,
		camera.dir.z  + camera.horizontal.z * px + camera.vertical.z * py
	};
	// Calcula la dirección del rayo desde la cámara al punto en el plano de proyección
	ray->direction.x = point_on_plane.x ;
	ray->direction.y = point_on_plane.y;
	ray->direction.z = point_on_plane.z ;
//para 8 es 2.5
//para 10 es 2
	// Normaliza la dirección del rayo para obtener un vector unitario
	double length = sqrt(ray->direction.x * ray->direction.x +
						 ray->direction.y * ray->direction.y +
						 ray->direction.z * ray->direction.z);
	ray->direction.x /= length;
	ray->direction.y /= length;
	ray->direction.z /= length;

	return ray;
}

Ray *generate_reflect_ray(Scene *scene, Vector3 hit_pt, Vector3 normal)
{
	Ray		*rayrfc;
	Vector3	*dir_pt;
	Vector3	*rfc;
	
	rayrfc = malloc(sizeof(Ray));
	if (!rayrfc)
		return NULL;
	dir_pt = normalize_withpoint(scene->cameras->pos , hit_pt);
	rfc = reflect(*dir_pt, normal);
	if (dot(normal, *rfc) < 0)
		invnormal(rfc);
	rayrfc->origin=  hit_pt;
	rayrfc->direction =  *rfc;
	return rayrfc;
}
