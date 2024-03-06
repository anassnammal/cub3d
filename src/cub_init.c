#include "cub3d.h"

void	*cub_get(void)
{
	static t_scene	data;

	return (&data);
}

void	cub_exit(uint8_t scene)
{
	t_scene	*data;

	data = cub_get();	
	if (scene == NORTH)
		mlx_delete_image(data->mlx, data->txt.no);
	else if (scene == SOUTH)
		mlx_delete_image(data->mlx, data->txt.so);
	else if (scene == WEST)
		mlx_delete_image(data->mlx, data->txt.we);
	else if (scene == EAST)
		mlx_delete_image(data->mlx, data->txt.ea);
	else if (scene == MAP)
	{
		ft_strsfree(data->map.content);
		mlx_terminate(data->mlx);
	}
    exit(EXIT_FAILURE);
}