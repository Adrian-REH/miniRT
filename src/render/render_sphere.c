#include "../main.h"

int render_point_sphere(Scene scene, Vector3 hit_pt, int nb_sphere){
	double d;
	int current_color = 0; // Color base de la esfera
	int ambient_color = 0; // Color gris para la luz ambiental
	Color *vCurrentColor = scene.spheres[nb_sphere].mater_prop.vColor;
	MaterialProperties prop = scene.spheres[nb_sphere].mater_prop;

	Vector3 *n_sphere = normalize_withpoint( scene.spheres->center, hit_pt);
	Vector3 *cam_dir = normalize_withpoint(scene.cameras->pos, hit_pt );
	current_color = mix_colors(ambient_color, current_color, AMBIENT_INTENSITY);
	Ray rayslight = {scene.lights->point, *normalize_withpoint(scene.lights->point, hit_pt)};
	// Calcula la intersección del plano con el rayo de luz
	if (intersect_sphere(&rayslight, scene.spheres, &d)) // Agrega esta verificación
	{
		//Tengo que hacer reflejo y acumular el color.
		if (!is_in_shadow(scene, 5, scene.lights->point, hit_pt)) {
			// Cálculo de la luz difusa
			double distance_light = distance(rayslight.origin, hit_pt);
			double attenuation = calculate_attenuation(distance_light, 1, 0.01, 0.03);
			double diffuse_intensity = calculate_intensity(*n_sphere, rayslight.direction);
			Vector3 *reflect_dir = reflect(rayslight.direction, *n_sphere);
			diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1);
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
			free(reflect_dir);
		}
		else
			current_color = ambient_color;
	}
	free(cam_dir);
	return current_color;
}