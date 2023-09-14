/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_game_info.c                                     :+:      :+: 	:+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:31:09 by msodor            #+#    #+#             */
/*   Updated: 2023/08/03 10:27:22 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	is_unmber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_rgb(int nbr)
{
	if (nbr < 0 || nbr > 255)
		return (1);
	return (0);
}

void	set_f_color(char **info)
{
	char	**rgb;

	rgb = ft_split(info[1], ",");
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		free_array(rgb);
		ft_err("RGB colors must have 3 values\n");
	}
	if (is_unmber(rgb[0]) || is_unmber(rgb[1]) || is_unmber(rgb[2]))
	{
		free_array(rgb);
		ft_err("RGB vlue must be a proper number\n");
	}
	g_elems.f_color[0] = ft_atoi(rgb[0]);
	g_elems.f_color[1] = ft_atoi(rgb[1]);
	g_elems.f_color[2] = ft_atoi(rgb[2]);
	g_elems.floor += 1;
	if (is_rgb(g_elems.f_color[0]) || is_rgb(g_elems.f_color[1]) \
	|| is_rgb(g_elems.f_color[2]))
	{
		free_array(rgb);
		ft_err("RGB vlue must be between 0 and 255\n");
	}
	free_array(rgb);
}

void	set_c_color(char **info)
{
	char	**rgb;

	rgb = ft_split(info[1], ",");
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		free_array(rgb);
		ft_err("RGB colors must have 3 values\n");
	}
	if (is_unmber(rgb[0]) || is_unmber(rgb[1]) || is_unmber(rgb[2]))
	{
		free_array(rgb);
		ft_err("RGB vlue must be a proper number\n");
	}
	g_elems.c_color[0] = ft_atoi(rgb[0]);
	g_elems.c_color[1] = ft_atoi(rgb[1]);
	g_elems.c_color[2] = ft_atoi(rgb[2]);
	g_elems.ceiling += 1;
	if (is_rgb(g_elems.c_color[0]) || is_rgb(g_elems.c_color[1]) \
	|| is_rgb(g_elems.c_color[2]))
	{
		free_array(rgb);
		ft_err("RGB vlue must be between 0 and 255\n");
	}
	free_array(rgb);
}

void	set_info(char **info)
{
	if (!info[0])
		return ;
	else if (!strcmp(info[0], "EA") && !g_elems.ea && info[1])
		g_elems.ea = ft_strdup(info[1]);
	else if (!strcmp(info[0], "NO") && !g_elems.no && info[1])
		g_elems.no = ft_strdup(info[1]);
	else if (!strcmp(info[0], "SO") && !g_elems.so && info[1])
		g_elems.so = ft_strdup(info[1]);
	else if (!strcmp(info[0], "WE") && !g_elems.we && info[1])
		g_elems.we = ft_strdup(info[1]);
	else if (!strcmp(info[0], "F"))
		set_f_color(info);
	else if (!strcmp(info[0], "C"))
		set_c_color(info);
	else
	{
		free_array(info);
		ft_err("Invalid element\n");
	}
}

void	width_height()
{
	int	i;

	i = 0;
	while (g_elems.map[g_elems.height])
		g_elems.height++;
	while (g_elems.map[i])
	{
		if (ft_strlen(g_elems.map[i]) > g_elems.width)
			g_elems.width = ft_strlen(g_elems.map[i]);
		i++;
	}
}

int	is_all_wall(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1')
			return (1);
		i++;
	}
	return (0);
}
void	separated_map(char *one_line_map)
{
	int i;

	i = 0;
	while (one_line_map[i])
	{
		if (one_line_map[i] == '\n' && one_line_map[i + 1]
			&& one_line_map[i + 1] == '\n')
			ft_err("Invalid map\n");
		i++;
	}
}
void	get_game_info()
{
	char	*line;
	char	**info;
	char	*one_line;

	one_line = NULL;
	line = get_next_line(g_elems.fd);
	while (line)
	{
		info = ft_split(line, " \t\n");
		if (info[0] && is_all_wall(info[0]) == 0)
			break ;
		set_info(info);
		free_array(info);
		free(line);
		line = get_next_line(g_elems.fd);
	}
	while (line)
	{
		one_line = f_strjoin(one_line, line);
		free(line);
		line = get_next_line(g_elems.fd);
	}
	separated_map(one_line);
	g_elems.map = ft_split(one_line, "\n");
	if (!g_elems.map)
		ft_err("Invalid map\n");
}

int	is_map_comp(char c)
{
	if (c == '1' || c == '0' || c == ' ')
		return (1);
	return (0);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	check_map()
{
	int	i;
	int	j;

	i = 0;
	while (g_elems.map[i])
	{
		j = 0;
		while (g_elems.map[i][j])
		{
			if (!is_map_comp(g_elems.map[i][j]) && !is_player(g_elems.map[i][j]))
				ft_err("Invalid map\n");
			if (is_player(g_elems.map[i][j]))
			{
				if (g_elems.player)
					ft_err("Duplicate player\n");
				g_elems.pos_x_p = (j*SQUAR_SIZE) + SQUAR_SIZE/2;
				g_elems.pos_y_p = (i*SQUAR_SIZE) + SQUAR_SIZE/2;
				g_elems.player = ft_substr(g_elems.map[i], j, 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_l_r_wall()
{
	int	i;

	i = 0;
	while (g_elems.map[i])
	{
		if (g_elems.map[i][0] != '1' && g_elems.map[i][0] != ' ')
			return (1);
		i++;
	}
	i = 0;
	while (g_elems.map[i])
	{
		if (g_elems.map[i][ft_strlen(g_elems.map[i]) - 1] != '1' \
		&& g_elems.map[i][ft_strlen(g_elems.map[i]) - 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_t_b_wall()
{
	int	i;
	int	j;

	j = 0;
	while (g_elems.map[0][j])
	{
		if (g_elems.map[0][j] != '1' && g_elems.map[0][j] != ' ')
			return (1);
		j++;
	}
	i = 0;
	while (g_elems.map[g_elems.height - 1][i])
	{
		if (g_elems.map[g_elems.height - 1][i] != '1' \
		&& g_elems.map[g_elems.height - 1][i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_wals()
{
	if (check_l_r_wall() || check_t_b_wall())
		ft_err("g_elems is not closed\n");
	return (0);
}

int	wall_player(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	check_map_closed()
{
	int	i;
	int	j;

	i = 0;
	while (g_elems.map[i])
	{
		j = 0;
		while (g_elems.map[i][j])
		{
			if (g_elems.map[i][j] == '0')
			{
				if (!wall_player(g_elems.map[i][j + 1]) \
				|| !wall_player(g_elems.map[i][j - 1]) \
				|| !wall_player(g_elems.map[i + 1][j]) \
				|| !wall_player(g_elems.map[i - 1][j]))
					ft_err("Invalid map\n");
			}
			j++;
		}
		i++;
	}
	return (0);
}
