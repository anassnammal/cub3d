/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:40:53 by anammal           #+#    #+#             */
/*   Updated: 2024/03/07 04:00:02 by anammal          ###   ########.fr       */
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

# define MAP_UNIT	64
# define PI			3.14159265359

typedef struct s_vector
{
	int x;
	int y;
}	t_vector;

typedef struct s_txt
{
	xpm_t	*no;
	xpm_t	*so;
	xpm_t	*we;
	xpm_t	*ea;
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
    mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*img_p;
	t_map		map;
	t_txt		txt;
	uint32_t	floor;
	uint32_t	ceiling;
}	t_scene;

void	*cub_get(void);
void	cub_init(void);
void	cub_exit(uint8_t scene);
void	cub_error(char *err_msg);
uint8_t	load_scene(int file);
uint8_t	load_setting(char *s, uint8_t *scene);
uint8_t	load_map(t_list *list);


void	move_player(void* param);


// Vector functions
t_vector    cub_vec(int x, int y);
t_vector    cub_vec_add(t_vector a, t_vector b);
t_vector    cub_vec_sub(t_vector a, t_vector b);
t_vector    cub_vec_mul(t_vector a, int b);
t_vector    cub_vec_div(t_vector a, int b);
uint32_t    cub_vec_dot(t_vector a, t_vector b);
uint32_t    cub_vec_cross(t_vector a, t_vector b);
uint32_t    cub_vec_len(t_vector a);
t_vector    cub_vec_norm(t_vector a);
t_vector    cub_vec_rot(t_vector a, int angle);

#endif