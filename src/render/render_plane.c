#include "../main.h"

int render_point_plane(Scene scene, Vector3 hit_pt, int n_plane)
{
	double d;
	int current_color = scene.planes[n_plane].mater_prop.color[0];//scene.planes[n_plane].mater_prop.color[0];
	Color *vCurrentColor = scene.planes[n_plane].mater_prop.vColor;
	MaterialProperties prop = scene.planes[n_plane].mater_prop;
	int ambient_color = 0; // Color gris para la luz ambiental
	// Calcula la dirección de la cámara hacia el punto de impacto
	Vector3 *cam_dir = normalize_withpoint(scene.cameras->pos, hit_pt);
	// Calcula la intensidad de la luz con respecto a la cámara
	double intensity = calculate_intensity(scene.planes[n_plane].normal, *cam_dir);
	// Mezcla el color base con la intensidad calculada para la dirección de la cámara

	current_color = vCurrentColor->color;
	Vector3 *light_dir = normalize_withpoint(scene.lights->point, hit_pt);
	Ray rayslight = {scene.lights->point, *light_dir};
	// Calcula la intersección del plano con el rayo de luz
	if (intersect_plane(&rayslight, &scene.planes[n_plane], &d))
	{
		// Calcula el punto de impacto con el rayo de luz
		double t = is_in_shadow(scene, 5, scene.lights->point, hit_pt);
		if (!t)
		{	// Calcula la dirección de la luz hacia el punto de impacto
				double distance_light = distance(rayslight.origin, hit_pt);
				double attenuation = calculate_attenuation(distance_light, L_P_KC, L_P_KL, L_P_KQ);
				double diffuse_intensity = calculate_intensity(scene.planes[n_plane].normal, rayslight.direction);
				diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1.0);
				Vector3 *reflect_dir = reflect(rayslight.direction, scene.planes[n_plane].normal);

				double specular = specular_intensity(*reflect_dir, *cam_dir, SHININESS, KS);
				specular = fmin(fmax(specular, 0.0), 1.0);
				
				//La cantidad de luz que aplico sobre el color del material
				vCurrentColor = illuminate_surface(vCurrentColor, scene.lights->color, fmin(0.8, fmax(0.0, ( 1 - (diffuse_intensity * attenuation )))) , 0.95, 0, prop);
				normalize_color(vCurrentColor);
				//current_color = mix_colors(scene.planes[n_plane].mater_prop.color[1], current_color, diffuse_intensity * attenuation);
				vCurrentColor = illuminate_surface(vCurrentColor, scene.lights->color, fmin(1, fmax(0.0, ( 1- (specular * attenuation * diffuse_intensity)))) , 0.95, 0, prop);
				normalize_color(vCurrentColor);
				
				vCurrentColor = illuminate_surface(int_to_color(ambient_color), vCurrentColor, fmin(1, fmax(0.0, ( 1 - ( attenuation * diffuse_intensity)))) , 0.9, 0, prop);
				normalize_color(vCurrentColor);

				current_color = vCurrentColor->color;
		}else
		{
			Vector3 *hit_shadow = hit_point(rayslight, t);
			double distance_light = distance(hit_pt, *hit_shadow);
			double attenuation = calculate_attenuation(distance_light, L_P_KC, L_P_KL, L_P_KQ);
			double diffuse_intensity = calculate_intensity(scene.planes[n_plane].normal, rayslight.direction);
			diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1.0);
			Vector3 *reflect_dir = reflect(rayslight.direction, scene.planes[n_plane].normal);
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
