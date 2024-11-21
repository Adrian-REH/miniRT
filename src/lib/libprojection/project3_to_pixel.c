#include "../../main.h"

/**
 * Esto solo funciona para cuando miro a Z
 */
Vector2	point3d_to_pixel(Vector3 point, Camera camera)
{
	Vector3	dir_ray;
	double	t;
	Vector2	pxl;
	Vector2	p;

	dir_ray = substract(camera.pos, point);
	t = camera.dir.z / dir_ray.z;
	dir_ray = scalev3(dir_ray, t);
	dir_ray.z = camera.plane_distance;
	p.x = dir_ray.x / camera.plane_half_width;
	p.y = dir_ray.y / camera.plane_half_height;
	pxl.x = (int)((p.x + 1.0) * 0.5 * WINX);
	pxl.y = (int)(((p.y + 1.0) * 0.5) * WINY);
	if (pxl.x < WINX && pxl.x > 0)
		pxl.x = pxl.x;
	else
		pxl.x = WINX - 1;
	if (pxl.y < WINY && pxl.y > 0)
		pxl.y = pxl.y;
	else
		pxl.y = WINY - 1;
	return (pxl);
}
