#include "cub3d.h"

void	*cub_get(void)
{
	static t_scene	data;

	return (&data);
}

void draw_line(mlx_image_t *img, t_vector a, t_vector b, uint32_t color)
{
	t_vector	d;
	uint32_t	step;
	uint32_t	i;

	d = cub_vec_sub(b, a);
	if (abs(d.x) >= abs(d.y))
		step = abs(d.x);
	else
    	step = abs(d.y);
	d = cub_vec_div(d, step);
	i = 0;
	while (i <= step)
	{
		mlx_put_pixel(img, a.x, a.y, color);
		a = cub_vec_add(a, b);
		usleep(1000);
	}
}

void	draw_player(mlx_image_t *player)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	e;
	uint32_t	s;

	x = 0;
	e = 1;
	while (++x < 7)
	{
		s = 0;
		if (x < 4)
			(e *= 2, y = 5 - x);
		else if (x > 4)
			(e /= 2, y = x - 2);
		else
			(e = 8, y = 2);
		while (s < e)
		{
			mlx_put_pixel(player, x, y, 0x40FF00FF);
			y++;
			s++;
		}
	}
}

void	draw_map(t_scene *d, uint32_t i, uint32_t j)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	c;

	if (i == d->map.x_max)
		return ;
	c = 0;
	if (d->map.content[j][i] == '1')
		c = 0x113649FF;
	else if (d->map.content[j][i] == '0')
		c = 0xCDB380FF;
	x = 0;
	while (c && ++x < MAP_UNIT - 1)
	{
		y = 0;
		// printf("map[%d][%d]\n", i, j);
		while (++y < MAP_UNIT - 1)
		{
			mlx_put_pixel(d->img, i * MAP_UNIT + x, j * MAP_UNIT + y, c);
		}
	}
	if (j < d->map.y_max - 1)
		j++;
	else
		(j = 0, i++);
	draw_map(d, i, j);
}

void	set_player_components(t_map *map)
{
	char	dir;
	
	dir = map->content[map->player.pos.y][map->player.pos.x];
	if (dir == 'N')
	{
		map->player.dir = cub_vec(0, -1);
		// map->player.plane = cub_vec(0.66, 0);
	}
	else if (dir == 'S')
	{
		map->player.dir = cub_vec(0, 1);
		// map->player.plane = cub_vec(-0.66, 0);
	}
	else if (dir == 'W')
	{
		map->player.dir = cub_vec(-1, 0);
		// map->player.plane = cub_vec(0, -0.66);
	}
	else if (dir == 'E')
	{
		map->player.dir = cub_vec(1, 0);
		// map->player.plane = cub_vec(0, 0.66);
	}
}

void	cub_init(void)
{
	t_scene		*data;
	t_vector	pp;
	mlx_image_t	*draft;

	data = cub_get();
	pp = data->map.player.pos;
	data->mlx = mlx_init(data->map.x_max * MAP_UNIT, data->map.y_max * MAP_UNIT, "cub3d", false);
	data->img = mlx_new_image(data->mlx, data->map.x_max * MAP_UNIT, data->map.y_max * MAP_UNIT);
	draft = mlx_new_image(data->mlx, data->map.x_max * MAP_UNIT, data->map.y_max * MAP_UNIT);
	data->img_p = mlx_new_image(data->mlx, 8, 8);
	set_player_components(&data->map);
	draw_player(data->img_p);
	if (!data->img)
		cub_error(NULL);
	draw_map(data, 0, 0);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
		cub_error(NULL);
	if (mlx_image_to_window(data->mlx, data->img_p, pp.x * MAP_UNIT + (MAP_UNIT / 2) - 4, pp.y * MAP_UNIT + (MAP_UNIT / 2) - 4) < 0)
		cub_error(NULL);
	if (mlx_image_to_window(data->mlx, draft, 0, 0) < 0)
		cub_error(NULL);
	draw_line(draft, pp, cub_vec);
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