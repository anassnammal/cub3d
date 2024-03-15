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

void		mouse_hook(t_scene *cub)
{
	int x;
	int y;
	t_vector mouse_pos;
	t_vector dir_to_mouse;
	double angle;

	mlx_get_mouse_pos(cub->mlx, &x, &y);
	// Assuming the center of the window is the player's position
	mouse_pos = cub_vec(x - SCREEN_X / 2, y - SCREEN_Y / 2);
	dir_to_mouse = cub_vec_sub(mouse_pos, cub->map.player.pos);
	angle = atan2(dir_to_mouse.y, dir_to_mouse.x) - atan2(cub->map.player.dir.y, cub->map.player.dir.x);
	// Normalize the angle to be between -pi and pi
	while (angle > M_PI) angle -= 2 * M_PI;
	while (angle < -M_PI) angle += 2 * M_PI;
	rotate_player(&cub->map, angle * cub->mlx->delta_time / 2);
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
	mouse_hook(d);
	draw_frame(d);
}

