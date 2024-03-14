/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 23:15:15 by sel-hano          #+#    #+#             */
/*   Updated: 2024/03/14 23:15:17 by sel-hano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t		get_color(t_txt *texture, int32_t imgx, int32_t imgy) 
{
	int32_t index;
	index = (texture->so->width * imgy + imgx) * 4;
	//TODO: 
		// protect overflow

	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;
	unsigned int color = 0;

	r = texture->so->pixels[index];
	g = texture->so->pixels[index + 1];
	b = texture->so->pixels[index + 2];
	a = texture->so->pixels[index + 3];
	color |= r << 24;
	color |= g << 16;
	color |= b << 8;
	color |= a;
	return (color);
}

void		draw_vert_line(t_scene *data, int32_t x, t_raycast *vars)
{
	int32_t		y;
    int32_t     txt_x;
    int32_t     txt_y;
    double      step;
    double      txt_p;

    txt_x = (int32_t)(vars->wall_hit * data->txt.so->width);
	
    if (vars->side == SIDE_X && vars->ray_dir.x > 0)
        txt_x = data->txt.so->width - txt_x - 1;
    if (vars->side == SIDE_Y && vars->ray_dir.y < 0)
        txt_x = data->txt.so->width - txt_x - 1;
    step = 1.0 * data->txt.so->height / data->txt.wall_height;
    txt_p = (data->txt.wall_start - SCREEN_Y / 2 + data->txt.wall_height / 2) * step;
	y = 0;
	while (y < SCREEN_Y)
	{
		if (y < data->txt.wall_start)
			mlx_put_pixel(data->frame, x, y, data->ceiling);
		else if (y < data->txt.wall_end)
        {
            txt_y = (int32_t)txt_p & (data->txt.so->height - 1);
            txt_p += step;
			mlx_put_pixel(data->frame, x, y, get_color(&data->txt, txt_x, txt_y));
		}
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
        data->txt.wall_height = (int32_t)(SCREEN_X / vars.perp_wall_dist);
        data->txt.wall_start = -data->txt.wall_height / 2 + SCREEN_Y / 2;
        data->txt.wall_end = data->txt.wall_height / 2 + SCREEN_Y / 2;
        if (data->txt.wall_start < 0)
            data->txt.wall_start = 0;
        if (data->txt.wall_end >= SCREEN_Y)
            data->txt.wall_end = SCREEN_Y - 1;
		draw_vert_line(data, x, &vars);
		x++;
	}
}
