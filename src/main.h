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
#define WINX 854 
#define WINY 480
# define X 0
# define Y 1
# define Z 2
#define SHININESS 100
#define KS 1
#define AMBIENT_INTENSITY 0.2 // Ajusta este valor según lo necesites

# define L_A_S_KC 1.0
# define L_A_S_KL 0.07
# define L_A_S_KQ 0.001

# define L_P_KC 1.0
# define L_P_KL 0.2
# define L_P_KQ 0.03

# define L_D_KC 1.0
# define L_D_KL 0.0
# define L_D_KQ 0.0

# define MAX_TEXTURE_SIZE 5
# define MAX_COLOR_SIZE 5
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define MATTE_REFLECTION 0.1
#define MATTE_ABSORPTION 0.7
#define MATTE_TRANSMISSION 0.0
#define MATTE_GLOSSINESS 0.0
#define MATTE_DIFFUSION 0.9
#define MATTE_ROUGHNESS 0.8
#define MATTE_IRIDESCENCE 0.0
#define MATTE_EMISSION 0.0
#define MATTE_SSS 0.1
#define MATTE_TEXTURE "default_matte_texture"
#define MATTE_REFRACTION_INDEX 1.0 // Similar al aire
#define MATTE_COLOR "gray"

#define METAL_POLISHED_REFLECTION 0.9
#define METAL_POLISHED_ABSORPTION 0.1
#define METAL_POLISHED_TRANSMISSION 0.0
#define METAL_POLISHED_GLOSSINESS 1.0
#define METAL_POLISHED_DIFFUSION 0.1
#define METAL_POLISHED_ROUGHNESS 0.05
#define METAL_POLISHED_IRIDESCENCE 0.1
#define METAL_POLISHED_EMISSION 0.0
#define METAL_POLISHED_SSS 0.0
#define METAL_POLISHED_TEXTURE "default_metal_texture"
#define METAL_POLISHED_REFRACTION_INDEX 2.5 // Dependiendo del metal
#define METAL_POLISHED_COLOR "silver"

typedef struct t_materialProperties{
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
    int color[MAX_COLOR_SIZE];        // Color
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
	struct t_materialProperties mater_prop;
} Sphere;

typedef struct {
	Vector3 normal;
	Vector3 point;
	MaterialProperties mater_prop;
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