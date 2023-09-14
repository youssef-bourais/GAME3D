/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_and_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:06:56 by ybourais          #+#    #+#             */
/*   Updated: 2023/09/14 18:47:21 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_square(uint32_t color, int x, int y)
{
	int size_x = x + SQUAR_SIZE;
	int size_y = y + SQUAR_SIZE;
	int firs_y = y;

	while (x < size_x)
	{
		y = firs_y;
		while (y < size_y)
		{
			mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}

void draw_grid()
{
    int i = 0;
    while (i < g_elems.height * SQUAR_SIZE)
    {
        int j = 0;
        while (j < g_elems.width * SQUAR_SIZE)
        {
			mlx_put_pixel(image, j, i, BLACK);
            j++;
        }
        i++;
    }
}

void plot_sky_and_land()
{
	int i = 0;
	while (i < HEIGHT)
	{
		int j = 0;
		while (j < WIDTH)
		{
			if (i <= HEIGHT/2)
				mlx_put_pixel(image, j, i, DARK_BLUE);
			else
				mlx_put_pixel(image, j, i, DARK_GREEN);
			j++;
		}
		i++;
	}
}

void get_y_coordinate(float *y0, float *y1, float ray_distance, double ray_angle)
{
	int static b;
	float wall_height;

	ray_distance = ray_distance*cos(g_elems.player_angle - ray_angle);
	wall_height = (SQUAR_SIZE*HEIGHT)/ray_distance;

	*y0 = HEIGHT/2 - wall_height/2;
	*y1 = *y0 + wall_height;
	b++;
}

void put_textures(int x, float y0, float y1)
{
	int *vert = g_elems.is_vertical;	
	int image_to_nort = (g_elems.player_angle - (FOV_ANGLE/2)) < 2*M_PI && (g_elems.player_angle - (FOV_ANGLE/2)) >= M_PI;
	int image_to_east = (g_elems.player_angle - (FOV_ANGLE/2)) >= (3*M_PI)/2 || (g_elems.player_angle - (FOV_ANGLE/2)) < M_PI/2;
	int pos_in_image;

	if(g_elems.is_vertical[x])
		pos_in_image = (int)g_elems.y % SQUAR_SIZE;
	else
		pos_in_image = (int)g_elems.x % SQUAR_SIZE;

	int i;
	float wall_height = y1 - y0;
	int yinc = g_elems.txtr[0].height / wall_height;
	int n = 0;
	i = pos_in_image;

	while (i < g_elems.txtr[0].height*g_elems.txtr[0].width)
	{
		n++;
		int j = 0;
		while (j < yinc)
		{
			mlx_put_pixel(image, x, y0, g_elems.txtr[0].texture[i]);
			y0++;
		}
		
		i+=g_elems.txtr[0].width;
	}
}

void _2_to_3d()
{
	int x = 0;
	float y0;
	float y1;
	double ray_angle;

	plot_sky_and_land();
	ray_angle = (g_elems.player_angle - 30*TO_RADIAN);
	while (x < WIDTH)
	{
		get_y_coordinate(&y0, &y1, g_elems.ray_distante[x], ray_angle);
		if(y0 > HEIGHT || y0 < 0 || y1 > HEIGHT || y1 < 0)
		{
			y0 = 0;
			y1 = HEIGHT - 1;
		}
		if(g_elems.is_vertical[x])
		{
			DDA(x, y0, x, y1, ORANGE);	
		}
		else
			DDA(x, y0, x, y1, YELLOW);	
		ray_angle += (FOV_ANGLE/RAYS_NUM);
		x++;
	}
}

void draw_player(uint32_t color, float x, float y)
{
	g_elems.pos_x_p = x + g_elems.pos_x_p;
	g_elems.pos_y_p = y + g_elems.pos_y_p;
	x = g_elems.pos_x_p;
	y = g_elems.pos_y_p;

	int radius = PLAYER_SIZE / 2;
	int pixel_x = x - radius;
	while (pixel_x < x + radius)
    {
		int pixel_y = y - radius;
        while (pixel_y <= y + radius)
        {
            if (pow(pixel_x - x, 2) + pow(pixel_y - y, 2) <= pow(radius, 2))
                mlx_put_pixel(image, MINIMAP_SCALE_FACTOR*pixel_x, MINIMAP_SCALE_FACTOR*pixel_y, color);
			pixel_y++;
        }
		pixel_x++;
    }
}

void DDA(int x0, int y0, int x1, int y1, uint32_t color)
{
	t_norm norm;
    norm.dx = x1 - x0;
    norm.dy = y1 - y0;
	int steps;

	if (abs(norm.dx) >= abs(norm.dy))
		steps = abs(norm.dx);
	else
		steps = abs(norm.dy);
    norm.x = x0;
    norm.y = y0;
	norm.x_step = (float)norm.dx / steps;
	norm.y_step = (float)norm.dy / steps;
	int i = 0;
	while (i <= steps)
	{
		mlx_put_pixel(image, round(norm.x), round(norm.y), color);
		norm.x = norm.x + norm.x_step;
		norm.y = norm.y + norm.y_step;
		i++;
	}
}


void init_image()
{
	mlx = mlx_init(WIDTH, HEIGHT, "GAME", 0);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, image, 0, 0);
	get_texture();
}

void plot_map()
{
	int i;

	i = 0;
	while (g_elems.map[i])
	{
		int j = 0;
		while (g_elems.map[i][j])
		{
			if(g_elems.map[i][j] == '1')
				draw_square(RED, MINIMAP_SCALE_FACTOR * (SQUAR_SIZE) * j, MINIMAP_SCALE_FACTOR * (SQUAR_SIZE) * i);
			else if (g_elems.map[i][j] != ' ')
				draw_square(GRAY, MINIMAP_SCALE_FACTOR * (SQUAR_SIZE) * j, MINIMAP_SCALE_FACTOR * (SQUAR_SIZE) * i);
			j++;
		}
		i++;
	}
}
