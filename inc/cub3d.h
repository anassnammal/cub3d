#ifndef CUB3D_H
#define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>

typedef struct s_img
{
	void	*north;
	void	*south;
	void	*west;
	void	*east;
}	t_img;

typedef struct s_point
{
	int x;
	int y;
}	t_point;

typedef struct s_scene
{
	t_img	*images;
	char	**map;
	t_point max;

	int 	floor;
	int 	ceiling;
}	t_scene;


#endif