#include "../main.h"

int render_point_cylinder(Scene scene, Vector3 hit_pt, int n_cyl)
{
	double d;
	int current_color = scene.cylinders[n_cyl].mater_prop.color[0];
	Color *vCurrentColor = scene.cylinders[n_cyl].mater_prop.vColor;
	MaterialProperties prop = scene.cylinders[n_cyl].mater_prop;
	int ambient_color = 0;
	Vector3 *cam_dir = normalize_withpoint(scene.cameras->pos, hit_pt);
	
	Vector3 *dir_cyl = normal_cylinder(hit_pt, scene.cylinders[n_cyl]);
	double intensity = calculate_intensity(*dir_cyl, *cam_dir);
	current_color = vCurrentColor->color;
	Vector3 *light_dir = normalize_withpoint(scene.lights->point, hit_pt);
	Ray rayslight = {scene.lights->point, *light_dir};
	if (intersect_cylinder(&rayslight, &scene.cylinders[n_cyl], &d))
	{
		double t = is_in_shadow(scene, scene.lights->point, hit_pt);
		if (!t)
		{
				double distance_light = distance(rayslight.origin, hit_pt);
				double attenuation = calculate_attenuation(distance_light, L_P_KC, L_P_KL, L_P_KQ);
				double diffuse_intensity = calculate_intensity(*dir_cyl, rayslight.direction);
				diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1.0);
				Vector3 *reflect_dir = reflect(rayslight.direction, *dir_cyl);
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
			double diffuse_intensity = calculate_intensity(*dir_cyl, rayslight.direction);
			diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1.0);
			Vector3 *reflect_dir = reflect(rayslight.direction, *dir_cyl);
			double specular = specular_intensity(*reflect_dir, *cam_dir, SHININESS, KS);
			specular = fmin(fmax(specular, 0.0), 1.0);
			vCurrentColor = illuminate_surface(vCurrentColor, int_to_color(ambient_color) , fmin(1, fmax(0.0, (diffuse_intensity * attenuation ))) , 0.95, 0, prop);
			normalize_color(vCurrentColor);
			current_color = vCurrentColor->color;
		}
	}
	free(dir_cyl);
	free(cam_dir);
	free(light_dir);
	return current_color;
}

int	render_reflect_cylinder(Scene *scene, Ray rayrfc, int id, int type)
{
	double t = 0;
	double md = 900000000;
	int j = -1;
	Vector3 *hit_rfc;
	int hit_color = 0;

	while (++j < scene->n_triangles)
	{
		if (intersect_cylinder(&rayrfc, &scene->triangle[j], &t) && (t < md))
		{
			hit_rfc = hit_point(rayrfc, t);
			if (!obj_solution_point(*scene, *hit_rfc, type, id))
			{
				md = t;
				hit_color = render_point_cylinder(*scene, *hit_rfc, j);
			}
			free(hit_rfc);
		}
	}
	return hit_color;
}

int	render_cylinder(Scene *scene, Vector3 hit_pt, int id)
{
	double t = 0;
	double idx = id;
	int hit_color = 0;
	int tmp[2] = {0 , 0};
	int result = 0;
	int current_pixel = render_point_cylinder(*scene, hit_pt, id);

	if (scene->cylinders[id].mater_prop.reflect)
	{
		Ray *rayrfc = generate_reflect_ray(scene, hit_pt, scene->triangle[id].p_triangle->normal);
		int type = find_nearest_obj(*scene, rayrfc, &t, &idx, CYLINDER);
		if (type == PLANE)
		{
			hit_color = render_reflect_plane(scene, *rayrfc, id, CYLINDER);
			result = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.6, 0.9, 0, scene->planes[id].mater_prop)->color;
		}
		if (type == SPHERE)
		{
			hit_color = render_reflect_sphere(scene, *rayrfc, id, CYLINDER);
			result = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene->planes[id].mater_prop)->color;
		} 
		if (type == TRIANGLE)
		{
			hit_color = render_reflect_triangle(scene, *rayrfc, id, CYLINDER);
			result = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene->planes[id].mater_prop)->color;
		}
		if (type == CYLINDER)
		{
			hit_color = render_reflect_cylinder(scene, *rayrfc, id, CYLINDER);
			result = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene->planes[id].mater_prop)->color;
		} 
		free(rayrfc);
		return hit_color;
	}
	return current_pixel;

}
