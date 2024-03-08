#include "cub3d.h"

void	draw_player(mlx_image_t *player)
{
	int x;
	int y;

	x = -1;
	while (++x < 8)
	{
		y = -1;
		while (++y < 8)
			mlx_put_pixel(player, x, y, 0x00FF00FF);
	}
}

void	draw_map(t_scene *d, uint32_t i, uint32_t j)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	c;

	if (i == d->map.x_max)
		return ;
	c = 0x031634FF;
	if (d->map.content[j][i] == '1')
		c = 0x113649FF;
	else if (d->map.content[j][i] != 0)
		c = 0xCDB380FF;
	x = 0;
	while (x < MAP - 1)
	{
		y = 0;
		// printf("map[%d][%d]\n", i, j);
		while (y < MAP - 1)
		{
			// printf("x[%d] y[%d]\n", i * 64 + x, j * 64 + y);
			mlx_put_pixel(d->img, i * 64 + x, j * 64 + y, c);
			y++;
		}
		x++;
	}
	if (j < d->map.y_max - 1)
		j++;
	else
		(j = 0, i++);
	draw_map(d, i, j);
}

void	*cub_get(void)
{
	static t_scene	data;

	return (&data);
}

void	cub_init(void)
{
	t_scene *data;

	data = cub_get();
	data->mlx = mlx_init(data->map.x_max * MAP, data->map.y_max * MAP, "cub3d", false);
	data->img = mlx_new_image(data->mlx, data->map.x_max * MAP, data->map.y_max * MAP);
	data->player = mlx_new_image(data->mlx, 8, 8);
	draw_player(data->player);
	if (!data->img)
		cub_error(NULL);
	draw_map(data, 0, 0);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
		cub_error(NULL);
	if (mlx_image_to_window(data->mlx, data->player, data->map.x_player * MAP + (MAP / 2), data->map.y_player * MAP + (MAP / 2)) < 0)
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