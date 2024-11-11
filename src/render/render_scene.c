#include "../main.h"

void render_scene(Scene scene, int samples_per_pixel)
{
	time_t start, end;
	double min_dist;
	int alpha = 0;
	start = clock();
    for (int y = 0; y < WINY ; y++) {
        for (int x = 0; x < WINX ; x++) {
            // Calcula el color del píxel con multiple-sampling (anti-aliasing)
         	int color = calculate_pixel_color(x, y, &scene, samples_per_pixel);
            // Guardar o mostrar el color final del píxel
           set_color(&scene.img->buffer[idxpixel(x, y)], 0, color, 0);
        }
    }
	mlx_put_image_to_window(scene.mlx, scene.win, scene.img->img, 0, 0);
	end = clock();
	double elapsed = (double)(end - start) / CLOCKS_PER_SEC * 1000; // Convertido a milisegundos
	printf("Elapsed time: %.3f milliseconds\n", elapsed);
}
