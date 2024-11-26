/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:49:32 by razamora          #+#    #+#             */
/*   Updated: 2024/11/26 20:49:24 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	solve_quadratic_equation(s_isc_cyl_ctx *ctx)
{
	double	temp;

	if (!solve_quadratic((Vector3){ctx->a, ctx->b, ctx->c}, &(ctx->t.x), \
	&(ctx->t.y)))
		return (0);
	if (ctx->t.x > ctx->t.y)
	{
		temp = ctx->t.x;
		ctx->t.x = ctx->t.y;
		ctx->t.y = temp;
	}
	if (ctx->t.x < 0)
	{
		ctx->t.x = ctx->t.y;
		if (ctx->t.x < 0)
			return (0);
	}
	return (1);
}

static int	check_intersection_within_height(s_isc_cyl_ctx *ctx, const Cylinder *cylinder, double *t)
{
	ctx->y.x = dot(ctx->ro, ctx->ca) + ctx->t.x * dot(ctx->d, ctx->ca);
	ctx->y.y = dot(ctx->ro, ctx->ca) + ctx->t.y * dot(ctx->d, ctx->ca);
	ctx->half_h = cylinder->height / 2;
	if (ctx->y.x < -ctx->half_h)
	{
		if (ctx->y.y < -ctx->half_h)
			return (0);
		ctx->th = ctx->t.x + (ctx->t.y - ctx->t.x) * \
		(ctx->y.x + ctx->half_h) / (ctx->y.x - ctx->y.y);
		if (ctx->th <= 0)
			return (0);
		*t = ctx->th;
		return (1);
	}
	else if (ctx->y.x > ctx->half_h)
	{
		if (ctx->y.y > ctx->half_h)
			return (0);
		ctx->th = ctx->t.x + (ctx->t.y - ctx->t.x) * \
		(ctx->y.x - ctx->half_h) / (ctx->y.x - ctx->y.y);
		if (ctx->th <= 0)
			return (0);
		*t = ctx->th;
		return (1);
	}
	*t = ctx->t.x;
	return (1);
}
int	intersect_cylinder(const Ray *ray, const Cylinder *cylinder, double *t)
{
	s_isc_cyl_ctx	ctx;

	ctx.ro = subtract(cylinder->center, ray->origin);
	ctx.d = ray->direction;
	ctx.ca = cylinder->axis;
	ctx.a = dot(ctx.d, ctx.d) - pow(dot(ctx.d, ctx.ca), 2);
	ctx.b = 2 * (dot(ctx.d, ctx.ro) - dot(ctx.d, ctx.ca) \
	* dot(ctx.ro, ctx.ca));
	ctx.c = dot(ctx.ro, ctx.ro) - pow(dot(ctx.ro, ctx.ca), 2) - \
		pow((cylinder->diameter / 2), 2);
	if (!solve_quadratic_equation(&ctx))
		return (0);
	return check_intersection_within_height(&ctx, cylinder, t);
}