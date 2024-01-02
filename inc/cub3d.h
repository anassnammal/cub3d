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

typedef unsigned int	t_rgb;
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
    char **content;
	int x_max;
	int y_max;
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


#endif