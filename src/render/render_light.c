#include "../main.h"

int	render_light(Scene scene, RenderContext ctx, void *obj, int type)
{
	double	d;
	Color	current_color;

	d = 0;
	if (scene.isc[type](&ctx.rayl, obj, &d))
	{
		d = is_in_shadow(scene, ctx.rayl.origin, ctx.hit_pt);
		if (d)
			current_color = apply_shadow(&ctx, &ctx.rayl.direction, \
				&ctx.cam_dir, hit_point(ctx.rayl, d));
		else
			current_color = apply_lighting(&ctx, \
				&ctx.rayl.direction, &ctx.cam_dir);
	}
	else
		current_color = apply_ambient(&ctx);
	return (current_color.color);
}
