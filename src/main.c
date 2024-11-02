/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:12:23 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/02 00:38:00 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minilibx-linux/mlx.h"
#define WINX 1280
#define WINY 720
void	set_color(char *buffer, int endian, int color, int alpha)
{
	if (endian == 1)
	{
		buffer[0] = alpha;
		buffer[1] = (color >> 16) & 0xFF;
		buffer[2] = (color >> 8) & 0xFF;
		buffer[3] = (color) & 0xFF;
	}
	else
	{
		buffer[0] = (color) & 0xFF;
		buffer[1] = (color >> 8) & 0xFF;
		buffer[2] = (color >> 16) & 0xFF;
		buffer[3] = alpha;
	}
}

void peint_plane(char	*buffer, int endian,int lines, int color)
{
	int pixel = 0;
	int	x = -1;
	int	y = -1;
	while (++x <= WINX)
	{
		y = -1;
		while (++y <= WINY)
		{
			pixel = (y * lines) + x * 4;
			set_color(&buffer[pixel], endian, color, 0);
		}
	}

}
int main()
{
	void *mlx;
	void *win;
	void	*img;
	char	*buffer;
	int		color;
	int		bitxpixel;
	int		lines;
	int		endian;

	color = 0xFFFFFF;
    mlx = mlx_init();
	win = mlx_new_window(mlx, WINX, WINY, "Draw line!");
	img = mlx_new_image(mlx, WINX, WINY);
	color = mlx_get_color_value(mlx, color);
	mlx_pixel_put(mlx, win, WINX ,WINY, color);
	buffer = mlx_get_data_addr(img, &bitxpixel, &lines, &endian);
	peint_plane(buffer, endian, lines,  color);
	mlx_put_image_to_window(mlx, win, img, 0, 1);
	mlx_loop(mlx);
}