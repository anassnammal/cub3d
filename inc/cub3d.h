/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:40:53 by anammal           #+#    #+#             */
/*   Updated: 2024/03/13 14:24:03 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <inttypes.h>
# include <math.h>
# include <MLX42/MLX42.h>

# define EMPTY		0x0
# define NORTH		0x1
# define SOUTH		0x2
# define WEST		0x4
# define EAST		0x8
# define FLOOR		0x10
# define CEILING	0x20
# define MAP		0x40
# define ERROR		0x80

# define SCREEN_X	1280
# define SCREEN_Y	720

# define UNIT		64

# define SIDE_X		2
# define SIDE_Y		1

typedef struct s_point
{
	uint32_t x;
	uint32_t y;
}	t_point;

typedef struct s_vector
{
	double x;
	double y;
}	t_vector;

typedef	struct s_raycast
{
	t_vector	ray_dir;
	t_vector	side_dist;
	t_vector	delta_dist;
	t_point		map;
	t_point		step;
	double		wall_hit;
	double		perp_wall_dist;
	uint8_t		side;
}	t_raycast;

typedef struct s_txt
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_txt;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

typedef struct s_map
{
    char		**content;
	size_t		x_max;
	size_t		y_max;
	t_player	player;	
}	t_map;

typedef struct s_scene
{
	uint8_t		scene;
    mlx_t		*mlx;
	mlx_image_t	*frame;
	mlx_image_t	*frame2;
	t_map		map;
	t_txt		txt;
	uint32_t	floor;
	uint32_t	ceiling;
}	t_scene;

void	*cub_get(void);
void	cub_launch(void);
void	cub_exit(void);
void	cub_error(char *err_msg);
uint8_t	load_scene(int file);
uint8_t	load_setting(char *s, uint8_t *scene);
uint8_t	load_map(t_list *list);

void	calc_perp_dist(t_raycast *vars, t_map *map);
void	move_handler(void* param);
void	draw_frame(t_scene *data);

// Vector functions
t_vector    cub_vec(double x, double y);
t_vector    cub_vec_add(t_vector a, t_vector b);
t_vector    cub_vec_mul(t_vector a, double b);
t_vector    cub_vec_rot(t_vector a, double angle);

#endif