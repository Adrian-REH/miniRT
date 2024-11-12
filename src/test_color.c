#include "main.h"


void normalize_color(Color *color) {
    color->r = fmax(0.0, fmin(1.0, color->r / 255.0));
    color->g = fmax(0.0, fmin(1.0, color->g / 255.0));
    color->b = fmax(0.0, fmin(1.0, color->b / 255.0));
}

int colornormal_to_int(Color color) {
    int r = (int)(color.r * 255.0);
    int g = (int)(color.g * 255.0);
    int b = (int)(color.b * 255.0);
    return (r << 16) | (g << 8) | b;
}

int color_to_int(Color color) {
    int r = (int)(color.r);
    int g = (int)(color.g);
    int b = (int)(color.b);
    return (r << 16) | (g << 8) | b;
}

Color *int_to_color(int src) {
    Color *color = malloc(sizeof(Color));
    if (color == NULL) {
        return NULL;  // Manejo de error de asignación de memoria
    }
    color->r = ((src >> 16) & 0xFF) / 255.0;
    color->g = ((src >> 8) & 0xFF) / 255.0;
    color->b = (src & 0xFF) / 255.0;
    color->color = src;
    return color;
}


double mix(double a, double b, double t)
{
    return a * (1 - t) + b * t;
}

Color illuminate_surface(Color surface_color, Color light_color, double intensity, 
                         double reflectivity, double glossiness) {
    Color result;
    
    result.r = surface_color.r * light_color.r * (1.0 - ABS_R);
    result.g = surface_color.g * light_color.g * (1.0 - ABS_G);
    result.b = surface_color.b * light_color.b * (1.0 - ABS_B) ;
	// Ajuste para materiales metálicos
    if (glossiness > 0) {
        // Los metales tienden a reflejar el color de la luz
        result.r = mix(result.r, light_color.r, glossiness);
        result.g = mix(result.g, light_color.g, glossiness);
        result.b = mix(result.b, light_color.b, glossiness);
        
        // Aumentar la reflectividad para metales
        reflectivity = mix(reflectivity, 1.0, glossiness);
    }

    // Calculamos la mezcla de colores
  	result.r = light_color.r + (result.r - light_color.r) * intensity * reflectivity;
    result.g = light_color.g + (result.g - light_color.g) * intensity * reflectivity;
    result.b = light_color.b + (result.b - light_color.b) * intensity * reflectivity;

	//result.r *= red_shift;
	//result.b *= blue_shift;

	// Asegurar que los valores estén en el rango [0, 1]
	result.r = fmin(1.0, fmax(0.0, result.r)) * 255;
	result.g = fmin(1.0, fmax(0.0, result.g)) * 255;
	result.b = fmin(1.0, fmax(0.0, result.b)) * 255;
	result.color = (((int)result.r << 16) | ((int)result.g << 8) | (int)result.b);

    return result;
}

double dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
Vector3 reflect(Vector3 incident, Vector3 normal) {
    double dot_product = dot(incident, normal);
    Vector3 result;
    result.x = incident.x - 2.0 * dot_product * normal.x;
    result.y = incident.y - 2.0 * dot_product * normal.y;
    result.z = incident.z - 2.0 * dot_product * normal.z;
    return result;
}
Color illuminate_surfacev2(Color surface_color, Color light_color, double intensity, 
                         MaterialProperties material, Vector3 view_dir, Vector3 light_dir, Vector3 normal) {
    Color result;
    
    // Calcular la reflexión difusa
    double diffuse_factor = material.diffusion * fmax(0, dot(normal, light_dir));
    
    result.r = surface_color.r * light_color.r * (1.0 - material.absorption[0]) * diffuse_factor;
    result.g = surface_color.g * light_color.g * (1.0 - material.absorption[1]) * diffuse_factor;
    result.b = surface_color.b * light_color.b * (1.0 - material.absorption[2]) * diffuse_factor;

    // Calcular la reflexión especular (brillo)
    if (material.glossiness > 0) {
        Vector3 reflect_dir = reflect(light_dir, normal);
        double spec = pow(fmax(dot(view_dir, reflect_dir), 0.0), material.glossiness * 32);
        double spec_factor = material.reflect * spec;
        result.r += light_color.r * spec_factor;
        result.g += light_color.g * spec_factor;
        result.b += light_color.b * spec_factor;
    }

    // Añadir emisión
    result.r += material.color[0] * material.emission / 255.0;
    result.g += material.color[1] * material.emission / 255.0;
    result.b += material.color[2] * material.emission / 255.0;

    // Aplicar intensidad y reflexión
    result.r = light_color.r + (result.r - light_color.r) * intensity * material.reflect;
    result.g = light_color.g + (result.g - light_color.g) * intensity * material.reflect;
    result.b = light_color.b + (result.b - light_color.b) * intensity * material.reflect;

    // Aquí podrías añadir efectos de iridescencia y subsurface scattering si lo deseas

    // Asegurar que los valores estén en el rango [0, 1]
    result.r = fmin(1.0, fmax(0.0, result.r));
    result.g = fmin(1.0, fmax(0.0, result.g));
    result.b = fmin(1.0, fmax(0.0, result.b));

    // Convertir a formato de color entero
    result.color = (((int)(result.r * 255) << 16) | 
                    ((int)(result.g * 255) << 8) | 
                     (int)(result.b * 255));

    return result;
}


int main()
{
	Scene scene;
	

	scene.mlx = mlx_init();
	scene.win = mlx_new_window(scene.mlx, WINX, WINY, "miniRT!");
	Img img;
	scene.img = &img;
	scene.img->img = mlx_new_image(scene.mlx, WINX, WINY);
	scene.img->buffer = mlx_get_data_addr(scene.img->img, &(scene.img->bitxpixel), &(scene.img->lines), &(scene.img->endian));
	Color color;
	Color surface_color = {0.29, 0.26, 0.17};  // Casi blanco
	surface_color.color =  colornormal_to_int(surface_color);
    Color light_color = {1.0, 1.0, 1.0, 0};    // Luz blanca
	light_color.color = colornormal_to_int(light_color);
	printf("Original RGB: (%.2f, %.2f, %.2f) = %06X\n", surface_color.r, surface_color.g, surface_color.b, surface_color.color);

	for (int y = 0; y < WINY; ++y) {
		for (int x = 0; x < WINX/2 ; ++x) {
			
			mlx_pixel_put(scene.mlx, scene.win, x, y, surface_color.color );
		}
	}

	Color result = illuminate_surface(surface_color, light_color, 0.8, 0.9, 0);
	for (int y = 0; y < WINY; ++y) {
		for (int x = WINX/2; x < WINX ; ++x) {

			int current_color = color.color;
			mlx_pixel_put(scene.mlx, scene.win, x, y, result.color );
		}
	}

	normalize_color(&result);
	printf("Resultado RGB: (%.2f, %.2f, %.2f) = %06X\n", result.r , result.g , result.b, result.color);
//	mlx_put_image_to_window(scene.mlx, scene.win, scene.img->img, 0, 0);
	mlx_loop(scene.mlx);

}