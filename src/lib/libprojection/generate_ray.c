#include "../../main.h"


Vector3	pxtopy(Camera camera, Vector3 v)
{
	Vector3	dst;

	dst.x = v.x * camera.horizontal.x + v.y * camera.vertical.x + v.z * camera.dir.x;
	dst.y = v.x * camera.horizontal.y + v.y *  camera.vertical.y + v.z * camera.dir.y;
	dst.z = v.x * camera.horizontal.z + v.y *  camera.vertical.z + v.z * camera.dir.z;
	return (dst);
}
Ray *generate_ray(double x, double y, int screen_width, int screen_height, Camera camera)
{
    Ray *ray = malloc(sizeof(Ray));
    if (!ray) {
        return NULL; // Manejo de memoria
    }
    ray->origin = camera.pos;

    double px = ((2.0 * x / (double)screen_width) - 1.0) * camera.aspect_ratio * camera.plane_distance;
    double py = (1.0 - 2.0 * y / (double)screen_height) * camera.plane_distance;

    Vector3 point_on_plane = pxtopy(camera, (Vector3){px, py, 0.5});
	ray->direction.x = point_on_plane.x;
	ray->direction.y = point_on_plane.y;
	ray->direction.z = point_on_plane.z;
	normalize(&(ray->direction));
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
