#include "../main.h"

Color* apply_lighting(const RenderContext *ctx, Vector3 *light_dir, Vector3 *cam_dir)
{
	Light *light;
	double distance_light;
	double attenuation;
	Vector3 *reflect_dir;
	double diffuse_intensity;
	double specular;
	Color *current_color;

	attenuation = ctx->funcs.calculate_attenuation(distance_light, L_P_KC, L_P_KL, 0);
	distance_light = distance(light->point, ctx->hit_pt);
	light = ctx->scene->lights;
	diffuse_intensity = ctx->funcs.calculate_intensity(ctx->normal, *light_dir);
	diffuse_intensity = fmax(fmin(diffuse_intensity, 1.0), 0);
	reflect_dir = ctx->funcs.reflect(*light_dir, ctx->normal);
	specular = specular_intensity(*reflect_dir, *cam_dir, SHININESS, KS);
	specular = fmax(fmin(specular, 1.0), 0.0);
	//aplico ambiente
	current_color = illuminate_surface(int_to_color(0), ctx->scene->ambient->color, \
		fmax(fmin(1 - (ctx->scene->ambient->ratio), 1.0), 0), 1, 0, ctx->mater_prop);
	normalize_color(current_color);
	//aplico difusion
	current_color = illuminate_surface(current_color, light->color, 
		fmax(fmin(1 - (light->ratio * diffuse_intensity), 1.0), 0), 1, 0, ctx->mater_prop);
	normalize_color(current_color);
	//aplico especular
	current_color = illuminate_surface(current_color, light->color, 
		fmax(fmin(1 - (light->ratio * specular), 1.0), 0), 1, 0, ctx->mater_prop);
	normalize_color(current_color);
	//(Optional) añado un poco mas de color para que no quede blanco
	current_color = illuminate_surface(current_color, ctx->mater_prop.vColor, 
		fmax(fmin(1 - (light->ratio * specular * attenuation * diffuse_intensity * ctx->scene->ambient->ratio), 1.0), 0), 1, 0, ctx->mater_prop);
	normalize_color(current_color);
	free(reflect_dir);
	return current_color;
}
