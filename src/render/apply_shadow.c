#include "../main.h"

Color* apply_shadow(const RenderContext *ctx, Vector3 *light_dir, Vector3 *cam_dir, Vector3 *opac_pt) 
{
	Color	*ambient_color;
	Color	*current_color;
	(void)opac_pt;

	ambient_color = int_to_color(0);
	current_color = illuminate_surface(ambient_color, ctx->scene->ambient->color, \
		fmax(fmin(1 - (ctx->scene->ambient->ratio), 1.0), 0), 1, 0, ctx->mater_prop);
	normalize_color(current_color);
	current_color = illuminate_surface(ambient_color, ctx->mater_prop.vColor, \
		fmax(fmin(1 - (ctx->scene->ambient->ratio), 1.0), 0), 1, 0, ctx->mater_prop);
	normalize_color(current_color);
	current_color = darken_surface(current_color, \
		(ctx->scene->ambient->ratio));
	normalize_color(current_color);
	free(ambient_color);
	return (current_color);
}
