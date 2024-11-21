#include "../main.h"

Color* apply_shadow(const RenderContext *ctx, Vector3 *light_dir, Vector3 *cam_dir, Vector3 *opac_pt) 
{
	Vector3 *reflect_dir;
	Light *light = ctx->scene->lights;
	double specular;
	double distance_light;
	double attenuation;
	double diffuse_intensity;
	Color *ambient_color;
	Color *current_color;

	diffuse_intensity = ctx->funcs.calculate_intensity(ctx->normal, *light_dir);
	attenuation = ctx->funcs.calculate_attenuation(distance_light, L_P_KC, L_P_KL, L_P_KQ);
	distance_light = distance(*opac_pt, ctx->hit_pt);
	diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1.0);
	reflect_dir = ctx->funcs.reflect(*light_dir, ctx->normal);
	specular = specular_intensity(*reflect_dir, *cam_dir, SHININESS, KS);
	specular = fmin(fmax(specular, 0.0), 1.0);
	ambient_color = int_to_color(0);

	current_color = illuminate_surface(ambient_color, ctx->scene->ambient->color, 
		fmax(fmin(1 - (ctx->scene->ambient->ratio), 1.0), 0), 1, 0, ctx->mater_prop);
	normalize_color(current_color);
	current_color = illuminate_surface(ambient_color, ctx->mater_prop.vColor, 
		fmax(fmin(1 - (ctx->scene->ambient->ratio), 1.0), 0), 1, 0, ctx->mater_prop);
	normalize_color(current_color);
	current_color = darken_surface(current_color, 
		(ctx->scene->ambient->ratio));
	normalize_color(current_color);

	free(reflect_dir);
	free(ambient_color);
	return (current_color);
}