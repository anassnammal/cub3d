/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:31:23 by anammal           #+#    #+#             */
/*   Updated: 2024/03/13 02:51:22 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	raycast_init_dda(t_raycast *vars, t_vector pos)
{
	if (vars->ray_dir.x)
		vars->delta_dist.x = fabs(1 / vars->ray_dir.x);
	if (vars->ray_dir.y)
		vars->delta_dist.y = fabs(1 / vars->ray_dir.y);
	vars->map.x = (uint32_t)pos.x;
	vars->map.y = (uint32_t)pos.y;
	if (vars->ray_dir.x < 0)
	{
		vars->step.x = -1;
		vars->side_dist.x = (pos.x - vars->map.x) * vars->delta_dist.x;
	}
	else
	{
		vars->step.x = 1;
		vars->side_dist.x = (vars->map.x + 1.0 - pos.x) * vars->delta_dist.x;
	}
	if (vars->ray_dir.y < 0)
	{
		vars->step.y = -1;
		vars->side_dist.y = (pos.y - vars->map.y) * vars->delta_dist.y;
	}
	else
	{
		vars->step.y = 1;
		vars->side_dist.y = (vars->map.y + 1.0 - pos.y) * vars->delta_dist.y;
	}
}

static void	raycast_start_dda(t_raycast *vars, char **_map)
{
	while (_map[vars->map.y][vars->map.x] != '1')
	{
		if (vars->side_dist.x < vars->side_dist.y)
		{
			vars->side_dist.x += vars->delta_dist.x;
			vars->map.x += vars->step.x;
			vars->side = SIDE_X;
		}
		else
		{
			vars->side_dist.y += vars->delta_dist.y;
			vars->map.y += vars->step.y;
			vars->side = SIDE_X;
		}
	}
}

void	calc_perp_dist(t_raycast *vars, t_map *map)
{
	t_vector	pos;

	pos = map->player.pos;
	raycast_init_dda(vars, pos);
	raycast_start_dda(vars, map->content);
	if (vars->side == SIDE_X)
	{
		vars->perp_wall_dist = vars->side_dist.x - vars->delta_dist.x;
		vars->wall_hit = pos.x + vars->perp_wall_dist * vars->ray_dir.x;
	}
	else
	{
		vars->perp_wall_dist = vars->side_dist.y - vars->delta_dist.y;
		vars->wall_hit = pos.y + vars->perp_wall_dist * vars->ray_dir.y;
	}
}