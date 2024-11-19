#include "../main.h"

Color* apply_shadow(RenderContext *ctx, Vector3 *light_dir, Vector3 *cam_dir, Vector3 *opac_pt) 
{

	Light *light = ctx->scene->lights;
	double distance_light = distance(*opac_pt, ctx->hit_pt);
	double attenuation = ctx->funcs.calculate_attenuation(distance_light, L_P_KC, L_P_KL, L_P_KQ);
	double diffuse_intensity = ctx->funcs.calculate_intensity(ctx->normal, *light_dir);
	diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1.0);

	Vector3 *reflect_dir = ctx->funcs.reflect(*light_dir, ctx->normal);
	double specular = specular_intensity(*reflect_dir, *cam_dir, SHININESS, KS);
	specular = fmin(fmax(specular, 0.0), 1.0);

	Color *ambient_color = int_to_color(0);
	Color *current_color = 0;
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
	return current_color;
}