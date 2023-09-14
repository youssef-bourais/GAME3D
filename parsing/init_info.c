/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:25:35 by msodor            #+#    #+#             */
/*   Updated: 2023/08/28 16:49:39 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_player_a(char *p)
{
	if (!ft_strcmp(p, "N"))
		g_elems.player_angle = 3 * M_PI / 2;
	else if (!ft_strcmp(p, "S"))
		g_elems.player_angle = M_PI / 2;
	else if (!ft_strcmp(p, "W"))
		g_elems.player_angle = M_PI;
	else if (!ft_strcmp(p, "E"))
		g_elems.player_angle = 0;
}

void	init_info(char *file)
{
	g_elems.file = file;
	g_elems.ray_distante = malloc(RAYS_NUM * sizeof(float));
	g_elems.is_vertical = malloc(RAYS_NUM * sizeof(int));
	g_elems.fd = open(g_elems.file, O_RDONLY);
	g_elems.ea = NULL;
	g_elems.no = NULL;
	g_elems.so = NULL;
	g_elems.we = NULL;
	g_elems.map = NULL;
	g_elems.player = NULL;
	g_elems.width = 0;
	g_elems.height = 0;
	g_elems.floor = 0;
	g_elems.ceiling = 0;
	g_elems.pos_x_p = 0;
	g_elems.pos_y_p = 0;
}
