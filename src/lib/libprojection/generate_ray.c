#include "../../main.h"

static Vector3	pxtopy(Camera cam, Vector3 v)
{
	Vector3	dst;

	dst.x = v.x * cam.horizontal.x + v.y * cam.vertical.x + v.z * cam.dir.x;
	dst.y = v.x * cam.horizontal.y + v.y * cam.vertical.y + v.z * cam.dir.y;
	dst.z = v.x * cam.horizontal.z + v.y * cam.vertical.z + v.z * cam.dir.z;
	return (dst);
}

Ray	*generate_ray(Vector2 px, int screen_width, \
int screen_height, Camera camera)
{
	Ray				*ray;
	Vector3			point_on_plane;
	const Vector3	p = {
		.x = ((2.0 * px.x / (double)screen_width) - 1.0) * \
		camera.aspect_ratio * camera.plane_distance,
		.y = (1.0 - 2.0 * px.y / (double)screen_height) * camera.plane_distance,
		.z = 0.5
	};

	ray = malloc(sizeof(Ray));
	if (!ray)
		return (NULL);
	ray->origin = camera.pos;
	point_on_plane = pxtopy(camera, p);
	ray->direction.x = point_on_plane.x;
	ray->direction.y = point_on_plane.y;
	ray->direction.z = point_on_plane.z;
	normalize(&(ray->direction));
	return (ray);
}

Ray	generate_reflect_ray(Scene *scene, Vector3 hit_pt, Vector3 normal)
{
	Ray		rayrfc;
	Vector3	dir_pt;
	Vector3	*rfc;

	dir_pt = norm_subtract(scene->cameras->pos, hit_pt);
	rfc = reflect(dir_pt, normal);//HAY UN LEAK DE MEMORIA AQUI!!
	if (dot(normal, *rfc) < 0)
		invnormal(rfc);
	rayrfc.origin = hit_pt;
	rayrfc.direction = *rfc;
	return (rayrfc);
}
