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
# define MAX_TEXTURE_SIZE 2
# define MAX_COLOR_SIZE 2
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double reflection;                 // Reflexión
    double absorption;                 // Absorción
    double transmission;               // Transmisión
    double glossiness;                 // Brillo
    double diffusion;                  // Difusión
    double roughness;                  // Rugosidad
    double iridescence;                // Iridescencia
    double emission;                   // Emisión
    double subsurface_scattering;      // SSS
    char texture[MAX_TEXTURE_SIZE];    // Textura
    double refraction_index;           // Índice de refracción
    char color[MAX_COLOR_SIZE];        // Color
} MaterialProperties;

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
	Vector3 normal;
	//MaterialProperties mater_prop;
} Sphere;

typedef struct {
	Vector3 normal;
	Vector3 point;
	//MaterialProperties mater_prop;
} Plane;

typedef struct {
	Vector3	point;
	int		color;
} Light;
typedef struct {
	Vector3	point;
	int		color;
} Color;

typedef struct {
	void	*mlx;
	void	*win;
	int		*buffer;
	int		*img;
} MlxData;


#endif