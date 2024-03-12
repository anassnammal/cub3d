#include "cub3d.h"

// calculate delta distance for x and y
static void		calc_delta_dist(t_raycast *vars)
{
	if (vars->ray_dir.x == 0)
		vars->delta_dist.x = 1e20;
	else
		vars->delta_dist.x = fabs(1 / vars->ray_dir.x);
	
	if (vars->ray_dir.y == 0)
		vars->delta_dist.y = 1e20;
	else
		vars->delta_dist.y = fabs(1 / vars->ray_dir.y);
}

// get the step direction for x and y 
static void		get_step_dir(t_raycast *vars)
{
	if (vars->ray_dir.x < 0)
		vars->step.x = -1; 
	else
		vars->step.x = 1;
	if (vars->ray_dir.y < 0)
		vars->step.y = -1;
	else
		vars->step.y = 1;
}

// calculate the side distance for x and y
static void		calc_side_dist(t_raycast *vars, t_vector pos)
{
	if (vars->ray_dir.x < 0)
		vars->side_dist.x = (pos.x - vars->map.x) * vars->delta_dist.x;
	else
		vars->side_dist.x = (vars->map.x + 1.0 - pos.x) * vars->delta_dist.x;
	if (vars->ray_dir.y < 0)
		vars->side_dist.y = (pos.y - vars->map.y) * vars->delta_dist.y;
	else
		vars->side_dist.y = (vars->map.y + 1.0 - pos.y) * vars->delta_dist.y;
}

void			calc_dist_to_wall(t_map *_map, t_raycast *vars)
{
	vars->map.x = (uint32_t)_map->player.pos.x;
	vars->map.y = (uint32_t)_map->player.pos.y;
	calc_delta_dist(vars);
	get_step_dir(vars);
	calc_side_dist(vars, _map->player.pos);
	while (_map->content[vars->map.y][vars->map.x] != '1')
	{
		if (vars->side_dist.x < vars->side_dist.y)
		{
			vars->side_dist.x += vars->delta_dist.x;
			vars->map.x += vars->step.x;
			vars->side = 2;
		}
		else
		{
			vars->side_dist.y += vars->delta_dist.y;
			vars->map.y += vars->step.y;
			vars->side = 1;
		}
	}
	if (vars->side == 2)
		vars->perp_wall_dist = vars->side_dist.x - vars->delta_dist.x;
    else
        vars->perp_wall_dist = vars->side_dist.y - vars->delta_dist.y;
}
