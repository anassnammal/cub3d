/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 23:15:15 by sel-hano          #+#    #+#             */
/*   Updated: 2024/03/15 03:59:38 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	*get_texture(t_txt	*textures, t_raycast *vars)
{
	if (vars->side == SIDE_X && vars->ray_dir.x > 0)
		return (textures->ea);
	if (vars->side == SIDE_X && vars->ray_dir.x < 0)
		return (textures->we);
	if (vars->side == SIDE_Y && vars->ray_dir.y > 0)
		return (textures->so);
	return (textures->no);
}

uint32_t	get_color(mlx_texture_t *txt, int32_t imgx, int32_t imgy)
{
	uint32_t	color;
	int32_t		s;
	int32_t		i;

	color = 0;
	s = (txt->width * imgy + imgx) * 4;
	i = -1;
	while (++i < 4)
	{
		color |= txt->pixels[s + i];
		if (i < 3)
			color <<= 8;
	}
	return (color);
}

int32_t	calc_txtoffsetx(t_raycast *vars, mlx_texture_t *txt)
{
	int32_t			txt_x;

	txt_x = (int32_t)(vars->wall_hit * txt->width);
	if (vars->side == SIDE_X && vars->ray_dir.x > 0)
		txt_x = txt->width - txt_x - 1;
	if (vars->side == SIDE_Y && vars->ray_dir.y < 0)
		txt_x = txt->width - txt_x - 1;
	return (txt_x);
}

void	draw_vert_line(t_scene *data, int32_t x, t_raycast *vars)
{
	int32_t			y;
	int32_t			txt_x;
	int32_t			txt_y;
	mlx_texture_t	*txt;
	double			step[2];

	txt = get_texture(&data->txt, vars);
	txt_x = calc_txtoffsetx(vars, txt);
	step[0] = 1.0 * txt->height / data->txt.wh;
	step[1] = (data->txt.ws - SCREEN_Y / 2 + data->txt.wh / 2) * step[0];
	y = 0;
	while (y < SCREEN_Y)
	{
		if (y < data->txt.ws)
			mlx_put_pixel(data->frame, x, y, data->ceiling);
		else if (y < data->txt.we)
		{
			txt_y = (int32_t)step[1] & (txt->height - 1);
			step[1] += step[0];
			mlx_put_pixel(data->frame, x, y, get_color(txt, txt_x, txt_y));
		}
		else
			mlx_put_pixel(data->frame, x, y, data->floor);
		y++;
	}
}

void	draw_frame(t_scene *data)
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
		data->txt.wh = (int32_t)(SCREEN_X / vars.perp_wall_dist);
		data->txt.ws = -data->txt.wh / 2 + SCREEN_Y / 2;
		data->txt.we = data->txt.wh / 2 + SCREEN_Y / 2;
		if (data->txt.ws < 0)
			data->txt.ws = 0;
		if (data->txt.we >= SCREEN_Y)
			data->txt.we = SCREEN_Y - 1;
		draw_vert_line(data, x, &vars);
		x++;
	}
}
