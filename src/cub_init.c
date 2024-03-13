/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:30:56 by anammal           #+#    #+#             */
/*   Updated: 2024/03/13 13:38:11 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*cub_get(void)
{
	static t_scene	data;

	return (&data);
}

void	set_player_components(t_map *m)
{
	char	*dir;

	dir = &m->content[(uint32_t)m->player.pos.y][(uint32_t)m->player.pos.x];
	if (*dir == 'N')
	{
		m->player.dir = cub_vec(0, -1);
		m->player.plane = cub_vec(0.66, 0);
	}
	else if (*dir == 'S')
	{
		m->player.dir = cub_vec(0, 1);
		m->player.plane = cub_vec(-0.66, 0);
	}
	else if (*dir == 'W')
	{
		m->player.dir = cub_vec(-1, 0);
		m->player.plane = cub_vec(0, -0.66);
	}
	else if (*dir == 'E')
	{
		m->player.dir = cub_vec(1, 0);
		m->player.plane = cub_vec(0, 0.66);
	}
	*dir = '0';
}

void	cub_launch(void)
{
	t_scene		*data;

	data = cub_get();
	data->mlx = mlx_init(SCREEN_X, SCREEN_Y, "cub3d", false);
	if (!data->mlx)
		cub_error(NULL);
	data->frame = mlx_new_image(data->mlx, SCREEN_X, SCREEN_Y);
	if (!data->frame)
		cub_error(NULL);
	set_player_components(&data->map);
	draw_frame(data);
	if (mlx_image_to_window(data->mlx, data->frame, 0, 0) < 0)
		cub_error(NULL);
	mlx_loop_hook(data->mlx, move_handler, data);
	mlx_loop(data->mlx);
}

void	cub_exit(void)
{
	t_scene	*data;

	data = cub_get();
	if (data->scene & NORTH)
		mlx_delete_texture(data->txt.no);
	if (data->scene & SOUTH)
		mlx_delete_texture(data->txt.so);
	if (data->scene & WEST)
		mlx_delete_texture(data->txt.we);
	if (data->scene & EAST)
		mlx_delete_texture(data->txt.ea);
	if (data->scene & MAP)
	{
		ft_strsfree(data->map.content);
		mlx_delete_image(data->mlx, data->frame);
		mlx_terminate(data->mlx);
	}
}

void	cub_error(char *err_msg)
{
	if (err_msg)
		ft_putendl_fd(err_msg, 1);
	else
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 1);
	cub_exit();
	exit(EXIT_FAILURE);
}
