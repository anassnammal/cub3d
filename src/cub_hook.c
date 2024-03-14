/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:30:47 by anammal           #+#    #+#             */
/*   Updated: 2024/03/14 01:53:10 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t		draw_wall(t_txt *txt , mlx_image_t *f, t_raycast *v , int32_t x, int32_t wh, int32_t ws, int32_t we)
{
	int32_t	txt_x;
	int32_t	txt_y;
	double	step;
	double	txt_p;
	int32_t	y;

	txt_x = (int32_t)(v->wall_hit * (double)UNIT);
	if (v->side == SIDE_X && v->ray_dir.x > 0)
		txt_x = UNIT - txt_x - 1;
	else if (v->side == SIDE_Y && v->ray_dir.y < 0)
		txt_x = UNIT - txt_x - 1;
	step = 1.0 * UNIT / wh;
	y = ws;
	txt_p = (ws - SCREEN_Y / 2 + wh / 2) * step;
	while (y < we)
	{
		txt_y = (int)txt_p & (UNIT - 1);
		txt_p += step;
		mlx_put_pixel(f, x, y, *(int32_t*)(txt->so->pixels + (UNIT * 4 * txt_y + txt_x * 4)));
		y++;
	}
	return (y);
}

void		draw_vert_line(t_scene *data, int32_t x, t_raycast *vars)
{
	int32_t		wall_height;
	int32_t		wall_start;
	int32_t		wall_end;
	int32_t		y;

	wall_height = (int32_t)(SCREEN_Y / vars->perp_wall_dist);
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
			y = draw_wall(&data->txt, data->frame, vars, x, wall_height, wall_start, wall_end);
		else
			mlx_put_pixel(data->frame, x, y, data->floor);
		y++;
	}
}

void		draw_frame(t_scene *data)
{
	t_raycast	vars;
	double		plane_scaler;
	uint32_t	x;

	x = 0;
	while (x < SCREEN_X)
	{
		plane_scaler = 2 * x / (double)SCREEN_X - 1;
		vars.ray_dir = cub_vec_mul(data->map.player.plane, plane_scaler);
		vars.ray_dir = cub_vec_add(data->map.player.dir, vars.ray_dir);
		calc_perp_dist(&vars, &data->map);
		draw_vert_line(data, x, &vars);
		x++;
	}
}

void		move_player(t_map *map, t_vector npos)
{
	t_vector	pp;

	pp = map->player.pos;
	if (map->content[(uint32_t)(pp.y)][(uint32_t)(npos.x)] != '1')
		map->player.pos.x = npos.x;
	if (map->content[(uint32_t)(npos.y)][(uint32_t)(pp.x)] != '1')
		map->player.pos.y = npos.y;
}

void		rotate_player(t_map *map, double rot_speed)
{
	map->player.dir = cub_vec_rot(map->player.dir, rot_speed);
	map->player.plane = cub_vec_rot(map->player.plane, rot_speed);
}

void		move_handler(void *param)
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
		move_player(&d->map, cub_vec(pp.x + np.x, pp.y + np.y));
	if (mlx_is_key_down(d->mlx, MLX_KEY_S))
		move_player(&d->map, cub_vec(pp.x - np.x, pp.y - np.y));
	if (mlx_is_key_down(d->mlx, MLX_KEY_D))
		move_player(&d->map, cub_vec(pp.x - np.y, pp.y + np.x));
	if (mlx_is_key_down(d->mlx, MLX_KEY_A))
		move_player(&d->map, cub_vec(pp.x + np.y, pp.y - np.x));
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT))
		rotate_player(&d->map, d->mlx->delta_time * 3.0);
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
		rotate_player(&d->map, d->mlx->delta_time * -3.0);
	draw_frame(d);
}

