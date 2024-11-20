#include "../main.h"

void	rot_camera(Scene *scene, Vector3 dir, int ang)
{
	Plane *plane;
	plane = &(scene->planes[scene->pos_obj->idx]);
    // Rotar la dirección, horizontal y vertical de la cámara alrededor del eje calculado
    scene->cameras->dir = rotate_v3(scene->cameras->dir, dir, ang);  // Rotar la dirección
    scene->cameras->horizontal = rotate_v3(scene->cameras->horizontal, dir, ang);
    scene->cameras->vertical = rotate_v3(scene->cameras->vertical, dir, ang);

    // Normalizar los vectores para evitar distorsión
    normalize(&scene->cameras->dir);
    normalize(&scene->cameras->vertical);
    normalize(&scene->cameras->horizontal);
}

void	pos_camera(Scene *scene, Vector3 dir)
{
	Camera *camera;
	camera = scene->cameras;
	camera->pos = add_vector3_to_vector3(camera->pos, dir);
}