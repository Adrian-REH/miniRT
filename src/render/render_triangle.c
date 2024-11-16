#include "../main.h"

int render_point_triangle(Scene scene, Vector3 hit_pt, int n_triangle)
{
	double d;
	int current_color = scene.planes[n_triangle].mater_prop.color[0];
	Color *vCurrentColor = scene.planes[n_triangle].mater_prop.vColor;
	MaterialProperties prop = scene.planes[n_triangle].mater_prop;
	int ambient_color = 0;
	Vector3 *cam_dir = normalize_withpoint(scene.cameras->pos, hit_pt);
	double intensity = calculate_intensity(scene.planes[n_triangle].normal, *cam_dir);
	current_color = vCurrentColor->color;
	Vector3 *light_dir = normalize_withpoint(scene.lights->point, hit_pt);
	Ray rayslight = {scene.lights->point, *light_dir};
	if (intersect_triangle(&rayslight, &scene.triangle[n_triangle], &d))
	{
		double t = is_in_shadow(scene, scene.lights->point, hit_pt);
		if (!t)
		{
				double distance_light = distance(rayslight.origin, hit_pt);
				double attenuation = calculate_attenuation(distance_light, L_P_KC, L_P_KL, L_P_KQ);
				double diffuse_intensity = calculate_intensity(scene.planes[n_triangle].normal, rayslight.direction);
				diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1.0);
				Vector3 *reflect_dir = reflect(rayslight.direction, scene.planes[n_triangle].normal);
				double specular = specular_intensity(*reflect_dir, *cam_dir, SHININESS, KS);
				specular = fmin(fmax(specular, 0.0), 1.0);
				vCurrentColor = illuminate_surface(vCurrentColor, scene.lights->color, fmin(0.8, fmax(0.0, ( 1 - (diffuse_intensity * attenuation )))) , 0.95, 0, prop);
				normalize_color(vCurrentColor);
				vCurrentColor = illuminate_surface(vCurrentColor, scene.lights->color, fmin(1, fmax(0.0, ( 1- (specular * attenuation * diffuse_intensity)))) , 0.95, 0, prop);
				normalize_color(vCurrentColor);
				vCurrentColor = illuminate_surface(int_to_color(ambient_color), vCurrentColor, fmin(1, fmax(0.0, ( 1 - ( attenuation * diffuse_intensity)))) , 0.9, 0, prop);
				normalize_color(vCurrentColor);
				current_color = vCurrentColor->color;
		}
		else
		{
			Vector3 *hit_shadow = hit_point(rayslight, t);
			double distance_light = distance(hit_pt, *hit_shadow);
			double attenuation = calculate_attenuation(distance_light, L_P_KC, L_P_KL, L_P_KQ);
			double diffuse_intensity = calculate_intensity(scene.planes[n_triangle].normal, rayslight.direction);
			diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1.0);
			Vector3 *reflect_dir = reflect(rayslight.direction, scene.planes[n_triangle].normal);
			double specular = specular_intensity(*reflect_dir, *cam_dir, SHININESS, KS);
			specular = fmin(fmax(specular, 0.0), 1.0);
			vCurrentColor = illuminate_surface(vCurrentColor, int_to_color(ambient_color) , fmin(1, fmax(0.0, (diffuse_intensity * attenuation ))) , 0.95, 0, prop);
			normalize_color(vCurrentColor);
			current_color = vCurrentColor->color;
		}
	}
	free(cam_dir);
	free(light_dir);
	return current_color;
}

int	render_reflect_triangle(Scene *scene, Ray rayrfc, int id, int type)
{
	double t = 0;
	double md = 900000000;
	int j = -1;
	Vector3 *hit_rfc;
	int hit_color = 0;

	while (++j < scene->n_triangles)
	{
		if (intersect_triangle(&rayrfc, &scene->triangle[j], &t) && (t < md))
		{
			hit_rfc = hit_point(rayrfc, t);
			if (!obj_solution_point(*scene, *hit_rfc, type, id))
			{
				md = t;
				hit_color = render_point_triangle(*scene, *hit_rfc, j);
			}
			free(hit_rfc);
		}
	}
	return hit_color;
}

int	render_triangle(Scene *scene, Vector3 hit_pt, int id)
{
	double t = 0;
	double idx = id;
	int hit_color = 0;
	int tmp[2] = {0 , 0};
	int result = 0;
	int current_pixel = render_point_triangle(*scene, hit_pt, id);

	if (scene->triangle[id].mater_prop.reflect)
	{
		Ray *rayrfc = generate_reflect_ray(scene, hit_pt, scene->triangle[id].p_triangle->normal);
		int type = find_nearest_obj(*scene, rayrfc, &t, &idx, TRIANGLE);
		if (type == PLANE)
		{
			hit_color = render_reflect_plane(scene, *rayrfc, id, TRIANGLE);
			result = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene->planes[id].mater_prop)->color;
		}
		if (type == SPHERE)
		{
			hit_color = render_reflect_sphere(scene, *rayrfc, id, TRIANGLE);
			result = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene->planes[id].mater_prop)->color;
		}
		if (type == TRIANGLE)
		{
			hit_color = render_reflect_triangle(scene, *rayrfc, id, TRIANGLE);
			result = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene->planes[id].mater_prop)->color;
		}
		free(rayrfc);
		return hit_color;
	}
	return current_pixel;

}
