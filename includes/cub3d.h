/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:49:17 by msodor            #+#    #+#             */
/*   Updated: 2023/09/13 18:53:21 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 310
# endif

# include "../MLX42/MLX42.h"
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>

# define WIDTH 1800
# define HEIGHT 1400

#define MINIMAP_SCALE_FACTOR 1.0
# define SQUAR_SIZE 10
# define PLAYER_SIZE 4
# define RAY_WIDTH 1
# define RAYS_NUM (WIDTH/RAY_WIDTH)
# define TO_RADIAN (M_PI/(double)180)
# define FOV_ANGLE (60*TO_RADIAN)

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

mlx_t* mlx;
static	mlx_image_t* image;

typedef struct s_txtr
{
	int		width;
	int		height;
	uint32_t *texture;
}	t_txtr;

typedef struct s_elems
{
	t_txtr txtr[4];
	float x;
	float y;
	char	*file;
	int		fd;
	int		width;
	int		height;
	char	**map;
	char	*player;
	int		player_x;
	int		player_y;
	double	player_angle;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceiling;
	float	pos_x_p;
	float	pos_y_p;
	float	*ray_distante;
	int		*is_vertical;
	int		f_color[3];
	int		c_color[3];
}	t_elems;
t_elems g_elems;



typedef struct s_coordinate
{
	int ray_up;
	int ray_right;
	float n_x;
	float n_y;
	float delta_y;
	float delta_x;
}	t_coordinate;

typedef struct s_norm
{
	int dx;
	int dy;
	int steps;
	float x;
	float y;
	float x_step;
	float y_step;
	float slope;
}	t_norm;

typedef struct s_data
{
	float x_pixel;
	float y_pixel;
}	t_data;

typedef struct s_direction
{
	int up;
	int down;
	int right;
	int left;
}	t_direction;





void get_texture();
void	width_height();
void 	check_map_size();
void 	init_image();
void 	plot_sky_and_land();
void 	_2_to_3d();
/*========================================*/
/*===============ray_casting==============*/
/*========================================*/
/*ray_casting*/
void	cast_rays();
void creat_ray(double ray_angle, float *dst, int *is_vertical);
float distance(float x1, float y1, float x2, float y2);
t_data compare_distance(float x_v, float y_v, float x_h, float y_h);
int	in_map_pixel(float x, float y);
/*cast_horizontal_lines*/
void init_direction(int *ray_up, int *ray_right, double ray_angle);
void init_horizontal_coordinate(float *x, float *y, double ray_angle, int ray_up);
void init_horizontal_steps(float *delta_x, float *delta_y, double ray_angle);
void find_horizontal_intersection(double ray_angle, float *x, float *y);
/*cast_vertical_lines*/
void init_vertical_coordinate(float *x, float *y, double ray_angle, int ray_right);
void init_vertical_steps(float *delta_x, float *delta_y, double ray_angle);
void find_vertical_intersection(double ray_angle, float *x, float *y);


/*=====================================*/
/*===============key_hook==============*/
/*=====================================*/
/*move_and_rotate*/
void rotate_player();
void update_check_plot_player(float x, float y);
void keyhook();
double normalize_angle(double angle);


/*=====================================*/
/*===============plot==================*/
/*=====================================*/
/*map_and_player*/
void draw_player(uint32_t color, float x, float y);
/*plotting_tools*/
void draw_square(uint32_t color, int x, int y);
void draw_grid();
void draw_line(float x, float y);
void DDA(int x0, int y0, int x1, int y1, uint32_t color);
void plot_map();

/*tools*/
void init_player_a(char *p);
int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strchr(const char *str, int c);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char *c);
char	*ft_strdup(const char *s1);
char	*ft_itoa(int n);
/*-------------------------*/

int		f_strlen(char *str);
int		f_strchr(char *str, char c);
char	*f_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
void	init_info(char *file);
void	free_array(char **array);
void	set_info(char **info);
void	get_game_info();
int		check_map();
int		check_map_closed();
int		check_wals();
void	ft_err(char *str);
void	ft_err(char *str);

#endif
