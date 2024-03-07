#include "cub3d.h"

void	*cub_get(void)
{
	static t_scene	data;

	return (&data);
}

void	cub_init(void)
{
	t_scene *data;

	data = cub_get();
	data->mlx = mlx_init(data->map.x_max * 32, data->map.y_max * 32, "cub3d", false);
	data->img = mlx_new_image(data->mlx, data->map.x_max * 32, data->map.y_max * 32);
	data->player = mlx_new_image(data->mlx, 2, 2);
	draw_player(data->player, data->map.x_player, data->map.y_player);
	if (!data->img)
		cub_error(NULL);
	draw_map(data, 0, 0);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
		cub_error(NULL);
	mlx_loop_hook(data->mlx, move_player, data);
	mlx_loop(data->mlx);
}

void	cub_exit(uint8_t scene)
{
	t_scene	*data;

	data = cub_get();	
	if (scene == NORTH)
		mlx_delete_xpm42(data->txt.no);
	else if (scene == SOUTH)
		mlx_delete_xpm42(data->txt.so);
	else if (scene == WEST)
		mlx_delete_xpm42(data->txt.we);
	else if (scene == EAST)
		mlx_delete_xpm42(data->txt.ea);
	else if (scene == MAP)
	{
		ft_strsfree(data->map.content);
		mlx_terminate(data->mlx);
	}
    exit(EXIT_FAILURE);
}

void	cub_error(char *err_msg)
{
	if (err_msg)
		ft_putendl_fd(err_msg, 1);
	else
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 1);
}