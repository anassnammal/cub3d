#include "cub3d.h"
// calculate delta distance for x and y
t_vector	calc_delta_dist(t_vector ray_dir)
{
	t_vector	delta_dist;

	if (ray_dir.x == 0) // ray is going to the right
		delta_dist.x = 1e20; // distance to the first x-side is infinite so I choose an arbitrary big number
	else // ray is going to the left
		delta_dist.x = fabs(1 / ray_dir.x); // calculate one step in X axis
	
	if (ray_dir.y == 0) // ray is going to the down
		delta_dist.y = 1e20; // distance to the first y-side is infinite, same as above
	else // ray is going to the up
		delta_dist.y = fabs(1 / ray_dir.y); // calculate one step in Y axis
	return (delta_dist);
}
// get the step direction for x and y 
t_point		get_step_dir(t_vector ray_dir)
{
	t_point	step;

	if (ray_dir.x < 0) // ray is going to the left
		step.x = -1; 
	else // ray is going to the right
		step.x = 1;
	if (ray_dir.y < 0) // ray is going to the up
		step.y = -1;
	else // ray is going to the down
		step.y = 1;
	return (step);
}
// calculate the side distance for x and y
t_vector	calc_side_dist(t_vector ray_dir, t_vector delta_dist, t_vector pos, t_point map)
{
	t_vector	side_dist;

	if (ray_dir.x < 0) // ray is going to the left
		side_dist.x = (pos.x - map.x) * delta_dist.x; // distance to the first x-side
	else // ray is going to the right
		side_dist.x = (map.x + 1.0 - pos.x) * delta_dist.x; // distance to the first x-side
	if (ray_dir.y < 0) // ray is going to the up
		side_dist.y = (pos.y - map.y) * delta_dist.y; // distance to the first y-side
	else // ray is going to the down
		side_dist.y = (map.y + 1.0 - pos.y) * delta_dist.y; // distance to the first y-side
	return (side_dist);
}

double		calc_dist_to_wall(t_map *_map, t_vector ray_dir, uint8_t *side)
{
	t_point		map; // current map position
	t_point		step; // step direction
	t_vector	side_dist; // distance to the next side
	t_vector	delta_dist; // distance to the next x or y side in x or y axis

	map.x = (uint32_t)_map->player.pos.x;
	map.y = (uint32_t)_map->player.pos.y;
	delta_dist = calc_delta_dist(ray_dir);
	step = get_step_dir(ray_dir);
	side_dist = calc_side_dist(ray_dir, delta_dist, _map->player.pos, map);
	while (_map->content[map.y][map.x] != '1')
	{
		if (side_dist.x < side_dist.y) // distance to the next x-side is shorter
		{
			side_dist.x += delta_dist.x; // increase the distance to the next side x by delta x
			map.x += step.x; // move to the next x-side
			*side = 2; // define the wall intersected side as x
		}
		else // distance to the next y-side is shorter
		{
			side_dist.y += delta_dist.y; // increase the distance to the next side y by delta y
			map.y += step.y; // move to the next y-side
			*side = 1; // define the wall intersected side as y
		}
	}
	if (*side == 2) // check the intersected side and subtract one delta distance to the distance to the border
		return (side_dist.x - delta_dist.x); 
	return (side_dist.y - delta_dist.y);
}

void		draw_line(t_scene *data, int32_t x, int32_t wall_height, uint8_t side)
{
	int32_t	wall_start;
	int32_t	wall_end;
	int32_t	y;

	wall_start = -wall_height / 2 + SCREEN_Y / 2; // calculate the start of the wall by subtracting half of the wall height from the screen height
	wall_end = wall_height / 2 + SCREEN_Y / 2; // calculate the end of the wall by adding half of the wall height to the screen height
	if (wall_start < 0) // check if the start of the wall is out of the screen
		wall_start = 0;
	if (wall_end >= SCREEN_Y) // check if the end of the wall is out of the screen
		wall_end = SCREEN_Y - 1;
	y = 0;
	while (y < SCREEN_Y)
	{
		if (y < wall_start) // draw the ceiling
			mlx_put_pixel(data->frame, x, y, data->ceiling);
		else if (y < wall_end) // draw the wall
			mlx_put_pixel(data->frame, x, y, 0x00FF0000 | (0x000000FF / side));
		else // draw the floor
			mlx_put_pixel(data->frame, x, y, data->floor);
		y++;
	}
}

void		draw_frame(t_scene *data)
{
	double		camera; // x-coordinate in camera space
	double		perp_wall_dist; // distance to the wall using perpendicular distance formula
	t_vector	ray_dir; // ray direction
	uint32_t	x; // x-coordinate in screen space
	int32_t	height; // height of the wall
	uint8_t		side; // intersected side

	x = 0;
	while (x < SCREEN_X)
	{
		camera = 2 * x / (double)SCREEN_X - 1; // calculate the x-coordinate in camera space
		ray_dir = cub_vec_add(data->map.player.dir, cub_vec_mul(cub_vec_norm(data->map.player.plane), camera)); // calculate the ray direction
		perp_wall_dist = calc_dist_to_wall(&data->map, ray_dir, &side); // calculate the distance to the wall using dda algorithm to get the perpendicular distance
		height = (int32_t)(SCREEN_X / perp_wall_dist); // calculate the height of the wall
		draw_line(data, x, height, side); // draw the wall
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
	move_speed = d->mlx->delta_time * 5.0; // move speed is 5 units per second
	rot_speed = d->mlx->delta_time * 3.0; // rotation speed is 3 radians per second
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
		rotate_player(&d->map, rot_speed);
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
		rotate_player(&d->map, -rot_speed);
	draw_frame(d);
}

