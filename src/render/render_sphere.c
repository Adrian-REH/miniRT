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

int	render_reflect_sphere(Scene *scene, Ray rayrfc, int id, int current_pixel)
{
	double t = 0;
	double md = 900000000;
	int j = -1;
	Vector3 *hit_rfc;
	int result = 0;
	int hit_color;

	while (++j < scene->n_spheres)
	{
		if (intersect_sphere(&rayrfc, &scene->spheres[j], &t) && (t < md)){
			hit_rfc = hit_point(rayrfc, t);
			if (!plane_solution_point(scene->planes[id], *hit_rfc))
			{
				md = t;
				hit_color = render_point_sphere(*scene, *hit_rfc, j);
				result = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene->planes[id].mater_prop)->color;
			}
			free(hit_rfc);
		}
	}
	return result;
}


int	render_sphere(Scene *scene, Vector3 hit_pt, int id)
{
	Color sample_color = {0, 0, 0, 0};  // Color acumulado (R, G, B)
	double md = 900000;
	double t = 0;
	int hit_color = 0;
	Vector3 *hit_rfc;
	Vector3 *dir_pt = normalize_withpoint(scene->cameras->pos , hit_pt);
	Vector3 *n_sphere = normal_sphere(hit_pt, scene->spheres[id]);
	Vector3 *rfc = reflect(*dir_pt, *n_sphere);
	if (dot(*n_sphere, *rfc) < 0)
		invnormal(rfc);
	Ray rayrfc = {hit_pt , *rfc};
	int j = -1;
	//Verificador de planos o objetos mas cercanos para optimizar
	int current_pixel = render_point_sphere(*scene, hit_pt, id);
	while (++j < scene->n_planes)
	{
		if (intersect_plane(&rayrfc, &scene->planes[j], &t) && (t < md))
		{
			hit_rfc = hit_point(rayrfc, t);
			//El plano que emitio el rayo no deberia ser solucion para la reflexion
			if (!sphere_solution_point(scene->spheres[id], *hit_rfc))
			{
				md = t;
				hit_color = render_point_plane(*scene, *hit_rfc, j);
				int result = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.5, 0.9, 0, scene->spheres[id].mater_prop)->color;
				addint_to_color(&sample_color, hit_color);
			}
			free(hit_rfc);
		}
	}
	j = -1;
	while (++j < scene->n_spheres)
	{
		if (intersect_sphere(&rayrfc, &scene->spheres[j], &t) && (t < md))
		{
			hit_rfc = hit_point(rayrfc, t);
			//El plano que emitio el rayo no deberia ser solucion para la reflexion
			if (!sphere_solution_point(scene->spheres[id], *hit_rfc))
			{
				md = t;
				hit_color = render_point_sphere(*scene, *hit_rfc, j);
				int result = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.5, 0.9, 0, scene->spheres[id].mater_prop)->color;
				addint_to_color(&sample_color, hit_color);
			}
			free(hit_rfc);
		}
	}
	free(dir_pt);
	free(n_sphere);
	free(rfc);
	return sample_color.color;
}
