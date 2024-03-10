#include "cub3d.h"

t_vector	calc_delta_dist(t_vector ray_dir)
{
	t_vector	delta_dist;

	if (ray_dir.x == 0)
		delta_dist.x = 1e20;
	else
		delta_dist.x = fabs(1 / ray_dir.x);
	
	if (ray_dir.y == 0)
		delta_dist.y = 1e20;
	else
		delta_dist.y = fabs(1 / ray_dir.y);
	return (delta_dist);
}

t_point		get_step_dir(t_vector ray_dir)
{
	t_point	step;

	if (ray_dir.x < 0)
		step.x = -1;
	else
		step.x = 1;
	if (ray_dir.y < 0)
		step.y = -1;
	else
		step.y = 1;
	return (step);
}

t_vector	calc_side_dist(t_vector ray_dir, t_vector delta_dist, t_vector pos, t_point map)
{
	t_vector	side_dist;

	if (ray_dir.x < 0)
		side_dist.x = (pos.x - map.x) * delta_dist.x;
	else
		side_dist.x = (map.x + 1.0 - pos.x) * delta_dist.x;
	if (ray_dir.y < 0)
		side_dist.y = (pos.y - map.y) * delta_dist.y;
	else
		side_dist.y = (map.y + 1.0 - pos.y) * delta_dist.y;
	return (side_dist);
}

double		calc_dist_to_wall(t_map *_map, t_vector ray_dir, uint8_t *side)
{
	t_point		map;
	t_point		step;
	t_vector	side_dist;
	t_vector	delta_dist;

	map.x = (uint32_t)_map->player.pos.x;
	map.y = (uint32_t)_map->player.pos.y;
	delta_dist = calc_delta_dist(ray_dir);
	step = get_step_dir(ray_dir);
	side_dist = calc_side_dist(ray_dir, delta_dist, _map->player.pos, map);
	while (_map->content[map.y][map.x] != '1')
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			map.x += step.x;
			*side = 2;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map.y += step.y;
			*side = 1;
		}
	}
	if (*side == 2)
		return (side_dist.x - delta_dist.x);
	return (side_dist.y - delta_dist.y);
}

void		draw_line(t_scene *data, int32_t x, int32_t wall_height, uint8_t side)
{
	int32_t	wall_start;
	int32_t	wall_end;
	int32_t	y;

	// if (wall_height == -2147483648)
	// 	wall_height = SCREEN_Y;
	wall_start = -wall_height / 2 + SCREEN_Y / 2;
	wall_end = wall_height / 2 + SCREEN_Y / 2;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end >= SCREEN_Y)
		wall_end = SCREEN_Y - 1;
	y = 0;
	while (y < SCREEN_Y)
	{
		if (y < wall_start)
			mlx_put_pixel(data->frame, x, y, data->ceiling);
		else if (y < wall_end)
			mlx_put_pixel(data->frame, x, y, 0x00FF0000 | (0x000000FF / side));
		else
			mlx_put_pixel(data->frame, x, y, data->floor);
		y++;
	}
}

void		draw_frame(t_scene *data)
{
	double		camera;
	double		perp_wall_dist;
	t_vector	ray_dir;
	uint32_t	x;
	int32_t	height;
	uint8_t		side;

	x = 0;
	while (x < SCREEN_X)
	{
		camera = 2 * x / (double)SCREEN_X - 1;
		ray_dir = cub_vec_add(data->map.player.dir, cub_vec_mul(cub_vec_norm(data->map.player.plane), camera));
		perp_wall_dist = calc_dist_to_wall(&data->map, ray_dir, &side);
		height = (int32_t)(SCREEN_X / perp_wall_dist);
		draw_line(data, x, height, side);
		x++;
	}
}

void		rotate_player(t_map *map, double rot_speed)
{
	map->player.dir = cub_vec_rot(map->player.dir, rot_speed);
	map->player.plane = cub_vec_rot(map->player.plane, rot_speed);
}

void		move_handler(void* param)
{
	t_scene *d;
	double		move_speed;
	double		rot_speed;

	d = (t_scene *)param;
	move_speed = d->mlx->delta_time * 5.0;
	rot_speed = d->mlx->delta_time * 3.0;
	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(d->mlx);
	if (mlx_is_key_down(d->mlx, MLX_KEY_W))
	{
		if (d->map.content[(uint32_t)(d->map.player.pos.y)][(uint32_t)(d->map.player.pos.x + d->map.player.dir.x * move_speed)] != '1')
			d->map.player.pos.x += d->map.player.dir.x * move_speed;
		if (d->map.content[(uint32_t)(d->map.player.pos.y + d->map.player.dir.y * move_speed)][(uint32_t)(d->map.player.pos.x)] != '1')
			d->map.player.pos.y += d->map.player.dir.y * move_speed;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_S))
	{
		if (d->map.content[(uint32_t)(d->map.player.pos.y)][(uint32_t)(d->map.player.pos.x - d->map.player.dir.x * move_speed)] != '1')
			d->map.player.pos.x -= d->map.player.dir.x * move_speed;
		if (d->map.content[(uint32_t)(d->map.player.pos.y - d->map.player.dir.y * move_speed)][(uint32_t)(d->map.player.pos.x)] != '1')
			d->map.player.pos.y -= d->map.player.dir.y * move_speed;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_D))
	{
		if (d->map.content[(uint32_t)(d->map.player.pos.y)][(uint32_t)(d->map.player.pos.x - d->map.player.dir.y * move_speed)] != '1')
			d->map.player.pos.x -= d->map.player.dir.y * move_speed;
		if (d->map.content[(uint32_t)(d->map.player.pos.y + d->map.player.dir.x * move_speed)][(uint32_t)(d->map.player.pos.x)] != '1')
			d->map.player.pos.y += d->map.player.dir.x * move_speed;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_A))
	{
		if (d->map.content[(uint32_t)(d->map.player.pos.y)][(uint32_t)(d->map.player.pos.x + d->map.player.dir.y * move_speed)] != '1')
			d->map.player.pos.x += d->map.player.dir.y * move_speed;
		if (d->map.content[(uint32_t)(d->map.player.pos.y - d->map.player.dir.x * move_speed)][(uint32_t)(d->map.player.pos.x)] != '1')
			d->map.player.pos.y -= d->map.player.dir.x * move_speed;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT))
		rotate_player(&d->map, -rot_speed);
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
		rotate_player(&d->map, rot_speed);
	ft_memset(d->frame->pixels, 0, SCREEN_X * SCREEN_Y * 4);
	draw_frame(d);
}

