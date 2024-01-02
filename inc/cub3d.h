#ifndef CUB3D_H
#define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>


typedef unsigned int	t_rgb;	

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

typedef struct s_pos{
	size_t x;
	size_t y;
}t_pos;

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

#endif