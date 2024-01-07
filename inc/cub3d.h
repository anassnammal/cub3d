/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:40:53 by anammal           #+#    #+#             */
/*   Updated: 2024/01/07 06:28:57 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>

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
typedef unsigned char	t_ui8;

typedef struct s_img
{
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
}	t_img;

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
    void    *mlx;
    void    *win;
	t_map	map;
	t_img	imgs;
	t_rgb	floor;
	t_rgb	ceiling;

}	t_scene;

void	*cub_get(void);
void	cub_exit(t_ui8 scene);
t_ui8   load_scene(int file);
t_ui8   load_setting(char *s, t_ui8 state);
t_ui8   load_map(t_list *list);

#endif