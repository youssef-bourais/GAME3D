/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:17:00 by ybourais          #+#    #+#             */
/*   Updated: 2023/08/30 15:38:09 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void rotate_player()
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		g_elems.player_angle = g_elems.player_angle - (3)*TO_RADIAN;
		g_elems.player_angle = normalize_angle(g_elems.player_angle);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		g_elems.player_angle = g_elems.player_angle + (3)*TO_RADIAN;
		g_elems.player_angle = normalize_angle(g_elems.player_angle);
	}
}

void update_check_plot_player(float x, float y)
{
	float move_speed;
	move_speed = 1;
	float new_x = x * move_speed;
	float new_y = y * move_speed;
	if(g_elems.map[(int)(g_elems.pos_y_p + new_y)/(SQUAR_SIZE)][(int)(g_elems.pos_x_p + new_x)/(SQUAR_SIZE)] != '1' 
		&& g_elems.map[(int)(g_elems.pos_y_p - move_speed + new_y)/(SQUAR_SIZE)][(int)(g_elems.pos_x_p + new_x)/(SQUAR_SIZE)] != '1'
		&& g_elems.map[(int)(g_elems.pos_y_p + move_speed + new_y)/(SQUAR_SIZE)][(int)(g_elems.pos_x_p + new_x)/(SQUAR_SIZE)] != '1'
		&& g_elems.map[(int)(g_elems.pos_y_p + new_y)/(SQUAR_SIZE)][(int)(g_elems.pos_x_p  - move_speed + new_x)/(SQUAR_SIZE)] != '1'
		&& g_elems.map[(int)(g_elems.pos_y_p + new_y)/(SQUAR_SIZE)][(int)(g_elems.pos_x_p - move_speed + new_x)/(SQUAR_SIZE)] != '1')
		draw_player(BLUE, new_x, new_y);
	else
		draw_player(BLUE, 0, 0);
}

void keyhook()
{
	rotate_player();
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		update_check_plot_player(cos(g_elems.player_angle), sin(g_elems.player_angle));
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		update_check_plot_player(-cos(g_elems.player_angle), -sin(g_elems.player_angle));
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		update_check_plot_player(cos(M_PI/2 - g_elems.player_angle), -sin(M_PI/2 - g_elems.player_angle));
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		update_check_plot_player(-cos(M_PI/2 - g_elems.player_angle), sin(M_PI/2 - g_elems.player_angle));
	_2_to_3d();
	plot_map();
	draw_player(BLUE, 0, 0);
	cast_rays();
}

double normalize_angle(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle >= 2 * M_PI)
    	angle -= 2 * M_PI;
	return angle;
}
