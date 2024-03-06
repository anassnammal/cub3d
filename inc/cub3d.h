/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:40:53 by anammal           #+#    #+#             */
/*   Updated: 2024/03/06 16:05:35 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <inttypes.h>
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

typedef unsigned int    t_rgb;
typedef unsigned char	uint8_t;

typedef struct s_txt
{
	mlx_image_t	*no;
	mlx_image_t	*so;
	mlx_image_t	*we;
	mlx_image_t	*ea;
}	t_txt;

typedef struct s_map
{
    char	**content;
	size_t	x_max;
	size_t	y_max;
	size_t	x_player;
	size_t	y_player;
}	t_map;


typedef struct s_scene
{
    mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		map;
	t_txt		txt;
	t_rgb		floor;
	t_rgb		ceiling;
}	t_scene;

void	*cub_get(void);
void	cub_exit(uint8_t scene);
uint8_t	load_scene(int file);
uint8_t	load_setting(char *s, uint8_t *scene);
uint8_t	load_map(t_list *list);

#endif