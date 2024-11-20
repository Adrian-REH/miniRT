
#include "../../main.h"
Color *illuminate_surface(Color *surface_color, Color *light_color, double intensity, 
                         double reflectivity, double glossiness, MaterialProperties prop)
{
    Color *result = malloc(sizeof(Color));
    if (!result)
      return 0;
    result->r = surface_color->r * light_color->r * (1.0 - prop.absorption[R]);
    result->g = surface_color->g * light_color->g * (1.0 - prop.absorption[G]);
    result->b = surface_color->b * light_color->b * (1.0 - prop.absorption[B]) ;
	// Ajuste para materiales metálicos
    if (glossiness > 0) {
        // Los metales tienden a reflejar el color de la luz
        result->r = mix(result->r, light_color->r, glossiness);
        result->g = mix(result->g, light_color->g, glossiness);
        result->b = mix(result->b, light_color->b, glossiness);
        
        // Aumentar la reflectividad para metales
        reflectivity = mix(reflectivity, 1.0, glossiness);
    }

    // Calculamos la mezcla de colores
  	result->r = light_color->r + (result->r - light_color->r) * intensity * reflectivity;
    result->g = light_color->g + (result->g - light_color->g) * intensity * reflectivity;
    result->b = light_color->b + (result->b - light_color->b) * intensity * reflectivity;

	//result->r *= red_shift;
	//result->b *= blue_shift;

	// Asegurar que los valores estén en el rango [0, 1]
	result->r = fmin(1.0, fmax(0.0, result->r)) * 255;
	result->g = fmin(1.0, fmax(0.0, result->g)) * 255;
	result->b = fmin(1.0, fmax(0.0, result->b)) * 255;
	result->color = (((int)result->r << 16) | ((int)result->g << 8) | (int)result->b);

    return result;
}

Color *darken_surface(Color *surface_color, double darkness_intensity)
{

    // Crear un nuevo color para el resultado
    Color *result = malloc(sizeof(Color));
    if (!result)
        return NULL;

    // Oscurecer los canales de color
    result->r = surface_color->r * (1.0 - darkness_intensity);
    result->g = surface_color->g * (1.0 - darkness_intensity);
    result->b = surface_color->b * (1.0 - darkness_intensity);

    // Asegurar que los valores están en el rango [0, 255]
    result->r = fmin(1.0, fmax(0.0, result->r))* 255;
    result->g = fmin(1.0, fmax(0.0, result->g))* 255;
    result->b = fmin(1.0, fmax(0.0, result->b))* 255;

    // Calcular el color en formato hexadecimal
    result->color = (((int)result->r << 16) | ((int)result->g << 8) | (int)result->b);

    return result;
}
