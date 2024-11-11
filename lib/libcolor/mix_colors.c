#include "libcolor.h"

int mix_colors(int base_color, int current_color, double intensity)
{
		intensity = fmax(0.0, fmin(1.0, intensity));

	// Extraemos los componentes RGB del color base
	int base_red = (base_color >> 16) & 0xFF;
	int base_green = (base_color >> 8) & 0xFF;
	int base_blue = base_color & 0xFF;

	// Extraemos los componentes RGB del color actual
	int crr_red = (current_color >> 16) & 0xFF;
	int crr_green = (current_color >> 8) & 0xFF;
	int crr_blue = current_color & 0xFF;

	// Ajustamos la mezcla para que cuando intensity sea 0, el resultado sea current_color,
	// y cuando intensity sea 1, el resultado sea base_color.
	int mixed_red = (int)(base_red * intensity + crr_red * (1 - intensity));
	int mixed_green = (int)(base_green * intensity + crr_green * (1 - intensity));
	int mixed_blue = (int)(base_blue * intensity + crr_blue * (1 - intensity));

	// Nos aseguramos de que los valores estén en el rango [0, 255]
	mixed_red = mixed_red > 255 ? 255 : mixed_red;
	mixed_green = mixed_green > 255 ? 255 : mixed_green;
	mixed_blue = mixed_blue > 255 ? 255 : mixed_blue;

	// Combinamos los componentes mezclados en un solo color hexadecimal
	return (mixed_red << 16) | (mixed_green << 8) | mixed_blue;
}
