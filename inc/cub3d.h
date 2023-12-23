#ifndef CUB3D_H
#define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>



typedef struct s_point
{
	int x;
	int y;
}	t_point;

typedef struct s_img
{
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
}	t_img;

typedef struct s_map
{
    char **map;
	int x_max;
	int y_max;
}	t_map;

typedef struct s_rgb
{
	unsigned int floor;
	unsigned int ceiling;
}	t_rgb;

typedef struct s_scene
{
    void    *mlx;
    void    *win;
	t_map	map;
	t_img	imgs;
	t_rgb   color;
}	t_scene;


#endif