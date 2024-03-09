#include "cub3d.h"

void	move_player(void* param)
{
	t_scene *d;
	uint32_t x;
	uint32_t y;


	d = (t_scene *)param;
	x = d->img_p->instances[0].x;
	y = d->img_p->instances[0].y;

	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(d->mlx);
	if (mlx_is_key_down(d->mlx, MLX_KEY_UP) && d->map.content[(y - 3) / MAP_UNIT][x / MAP_UNIT] != '1')
		d->img_p->instances[0].y -= 3;
	if (mlx_is_key_down(d->mlx, MLX_KEY_DOWN) && d->map.content[(y + 11) / MAP_UNIT][x / MAP_UNIT] != '1')
		d->img_p->instances[0].y += 3;
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT) && d->map.content[y / MAP_UNIT][(x - 3) / MAP_UNIT] != '1')
		d->img_p->instances[0].x -= 3;
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT) && d->map.content[y / MAP_UNIT][(x + 11) / MAP_UNIT] != '1')
		d->img_p->instances[0].x += 3;
}

