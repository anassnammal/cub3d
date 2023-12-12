#ifndef CUB3D_H
#define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>

typedef struct s_scene
{
	void	*north;
	char	*south;
	char	*west;
	char	*east;
	int 	floor;
	int 	ceiling;
}	t_scene;

#endif