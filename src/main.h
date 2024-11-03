/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathmatrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:06:31 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/17 11:27:48 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#include "../lib/minilibx-linux/mlx.h"
#include "../lib/minilibx_opengl/mlx_opengl.h"
#include <math.h>
#define WINX 1280
#define WINY 720
# define X 0
# define Y 1
# define Z 2
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	double x, y, z;
} Vector3;

typedef struct {
	Vector3 origin;
	Vector3 direction;
} Ray;

typedef struct {
	Vector3 center;
	double radius;
} Sphere;

typedef struct {
	Vector3 normal;
	Vector3 point;
} Plane;

#endif