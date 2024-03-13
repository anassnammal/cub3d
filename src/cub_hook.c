/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:30:47 by anammal           #+#    #+#             */
/*   Updated: 2024/03/13 02:13:33 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_line(t_scene *data, int32_t x, t_raycast *vars)
{
	int32_t		wall_height;
	int32_t		wall_start;
	int32_t		wall_end;
	uint32_t	index;
	t_vector	offset;
	int32_t		y;

	wall_height = (int32_t)(SCREEN_X / vars->perp_wall_dist);
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
		{
			;// mlx_put_pixel(data->frame, x, y, *(uint32_t*)(data->txt.no->pixels + index));
		}
		else
			mlx_put_pixel(data->frame, x, y, data->floor);
		y++;
	}
}

void		draw_frame(t_scene *data)
{
	t_raycast	vars;
	double		camera;
	uint32_t	x;

	x = 0;
	while (x < SCREEN_X)
	{
		camera = 2 * x / (double)SCREEN_X - 1;
		vars.ray_dir = cub_vec_mul(data->map.player.plane, camera);
		vars.ray_dir = cub_vec_add(data->map.player.dir, vars.ray_dir);
		calc_perp_dist_wall(&data->map, &vars);
		draw_line(data, x, &vars);
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
	t_scene		*d;
	t_vector	pp;
	t_vector	np;

	d = (t_scene *)param;
	pp = d->map.player.pos;
	np = cub_vec_mul(d->map.player.dir, d->mlx->delta_time * 5.0);
	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(d->mlx);
	if (mlx_is_key_down(d->mlx, MLX_KEY_W))
	{
		if (d->map.content[(uint32_t)(pp.y)][(uint32_t)(pp.x + np.x)] != '1')
			d->map.player.pos.x += np.x;
		if (d->map.content[(uint32_t)(pp.y + np.y)][(uint32_t)(pp.x)] != '1')
			d->map.player.pos.y += np.y;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_S))
	{
		if (d->map.content[(uint32_t)(pp.y)][(uint32_t)(pp.x - np.x)] != '1')
			d->map.player.pos.x -= np.x;
		if (d->map.content[(uint32_t)(pp.y - np.y)][(uint32_t)(pp.x)] != '1')
			d->map.player.pos.y -= np.y;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_D))
	{
		if (d->map.content[(uint32_t)(pp.y)][(uint32_t)(pp.x - np.y)] != '1')
			d->map.player.pos.x -= np.y;
		if (d->map.content[(uint32_t)(pp.y + np.x)][(uint32_t)(pp.x)] != '1')
			d->map.player.pos.y += np.x;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_A))
	{
		if (d->map.content[(uint32_t)(pp.y)][(uint32_t)(pp.x + np.y)] != '1')
			d->map.player.pos.x += np.y;
		if (d->map.content[(uint32_t)(pp.y - np.x)][(uint32_t)(pp.x)] != '1')
			d->map.player.pos.y -= np.x;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT))
		rotate_player(&d->map, d->mlx->delta_time * 3.0);
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
		rotate_player(&d->map, d->mlx->delta_time * -3.0);
	draw_frame(d);
}

