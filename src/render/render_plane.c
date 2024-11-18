#include "../main.h"
typedef double (*IntensityFunc)(Vector3, Vector3);
typedef double (*AttenuationFunc)(double, double, double, double);
typedef Vector3* (*ReflectFunc)(Vector3, Vector3);

typedef struct {
	IntensityFunc calculate_intensity;
	AttenuationFunc calculate_attenuation;
	ReflectFunc reflect;
} LightingFunctions;

typedef struct {
	Scene *scene;
	Vector3 hit_pt;
	Vector3 normal;
	MaterialProperties mater_prop;
	LightingFunctions funcs;
} RenderContext;

Color* apply_lighting(RenderContext *ctx, Vector3 *light_dir, Vector3 *cam_dir, double t) {
	Light *light = ctx->scene->lights;
	
	double distance_light = distance(light->point, ctx->hit_pt);
	double attenuation = ctx->funcs.calculate_attenuation(distance_light, L_P_KC, L_P_KL, L_P_KQ);
	double diffuse_intensity = ctx->funcs.calculate_intensity(ctx->normal, *light_dir);
	diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1.0);
	
	Vector3 *reflect_dir = ctx->funcs.reflect(*light_dir, ctx->normal);
	double specular = specular_intensity(*reflect_dir, *cam_dir, SHININESS, KS);
	specular = fmin(fmax(specular, 0.0), 1.0);
	
	Color *current_color = ctx->mater_prop.vColor;
	current_color = illuminate_surface(current_color, light->color, 
		fmin(0.8, fmax(0.0, (1 - (diffuse_intensity * attenuation)))), 0.95, 0, ctx->mater_prop);
	normalize_color(current_color);
	
	current_color = illuminate_surface(current_color, light->color, 
		fmin(1, fmax(0.0, (1 - (specular * attenuation * diffuse_intensity)))), 0.95, 0, ctx->mater_prop);
	normalize_color(current_color);
	
	Color *ambient_color = int_to_color(0);
	current_color = illuminate_surface(ambient_color, current_color, 
		fmin(1, fmax(0.0, (1 - (attenuation * diffuse_intensity)))), 0.9, 0, ctx->mater_prop);
	normalize_color(current_color);
	
	free(reflect_dir);
	free(ambient_color);
	return current_color;
}

Color* apply_shadow(RenderContext *ctx, Vector3 *light_dir, Vector3 *cam_dir, double t) {
	Light *light = ctx->scene->lights;
	
	Vector3 *hit_shadow = hit_point((Ray){light->point, *light_dir}, t);
	double distance_light = distance(ctx->hit_pt, *hit_shadow);
	double attenuation = ctx->funcs.calculate_attenuation(distance_light, L_P_KC, L_P_KL, L_P_KQ);
	double diffuse_intensity = ctx->funcs.calculate_intensity(ctx->normal, *light_dir);
	diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1.0);

	Vector3 *reflect_dir = ctx->funcs.reflect(*light_dir, ctx->normal);
	double specular = specular_intensity(*reflect_dir, *cam_dir, SHININESS, KS);
	specular = fmin(fmax(specular, 0.0), 1.0);

	Color *ambient_color = int_to_color(0);
	Color *current_color = illuminate_surface(ctx->mater_prop.vColor, ambient_color, 
		fmin(1, fmax(0.0, (diffuse_intensity * attenuation))), 0.95, 0, ctx->mater_prop);
	normalize_color(current_color);
	free(hit_shadow);
	free(reflect_dir);
	free(ambient_color);
	return current_color;
}

int	render_point_plane(Scene scene, Vector3 hit_pt, int n_plane) {
	const RenderContext	ctx = {
		.scene = &scene,
		.mater_prop = scene.planes[n_plane].mater_prop,
		.normal = scene.planes[n_plane].normal,
		.hit_pt = hit_pt,
		.funcs = {
			.calculate_intensity = calculate_intensity,
			.calculate_attenuation = calculate_attenuation,
			.reflect = reflect
		}
	};

	Vector3 *cam_dir = normalize_withpoint(scene.cameras->pos, hit_pt);
	Vector3 *light_dir = normalize_withpoint(scene.lights->point, hit_pt);
	Ray rayslight = {scene.lights->point, *light_dir};

	double d;
	Color *current_color;
	if (intersect_plane(&rayslight, &scene.planes[n_plane], &d)) {
		double t = is_in_shadow(scene, scene.lights->point, hit_pt);
		if (t) {
			current_color = apply_shadow(&ctx, light_dir, cam_dir, t);
		} else {
			current_color = apply_lighting(&ctx, light_dir, cam_dir, t);
		}
	} else {
		current_color = scene.planes[n_plane].mater_prop.vColor;
	}

	int result = current_color->color;
	free(cam_dir);
	free(light_dir);
	free(current_color);
	return result;
}
/* 
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
		double t = is_in_shadow(scene, scene.lights->point, hit_pt);
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
 */
int	render_reflect_plane(Scene *scene, Ray rayrfc, int id, int type)
{
	double t = 0;
	double md = 900000000;
	int j = -1;
	Vector3 *hit_rfc;
	int hit_color = 0;

	while (++j < scene->n_planes)
	{
		if (intersect_plane(&rayrfc, &scene->planes[j], &t) && (t < md))
		{
			hit_rfc = hit_point(rayrfc, t);
			if (!obj_solution_point(*scene, *hit_rfc, type, id))
			{
				md = t;
				hit_color = render_point_plane(*scene, *hit_rfc, j);
			}
			free(hit_rfc);
		}
	}
	return hit_color;
}



int	render_plane(Scene *scene, Vector3 hit_pt, int id)
{
	double t = 0;
	double idx = id;
	int hit_color = 0;
	int tmp[2] = {0 , 0};
	int result = 0;
	int current_pixel = render_point_plane(*scene, hit_pt, id);

	//Si hay reflexion entonces ...
	//Genero un ray
	if (scene->planes[id].mater_prop.reflect)
	{
		Ray *rayrfc = generate_reflect_ray(scene, hit_pt, scene->planes[id].normal);
		//Hago la reflexion
		Vector3 *hit_rfc;
		int j = -1;
		int type = find_nearest_obj(*scene, rayrfc, &t, &idx, PLANE);
		if (scene->rfc[type])
		{
			hit_color = scene->rfc[type](scene, *rayrfc, id, PLANE);
			result = illuminate_surface(int_to_color(hit_color), int_to_color(current_pixel), 0.7, 0.9, 0, scene->planes[id].mater_prop)->color;
		}
		free(rayrfc);
		return result;
	}
	return current_pixel;
}
