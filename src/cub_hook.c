#include "cub3d.h"

void	move_player(void* param)
{
	t_scene *d;

	d = (t_scene *)param;
	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(d->mlx);
	if (mlx_is_key_down(d->mlx, MLX_KEY_UP))
		d->player->instances[0].y -= 5;
	if (mlx_is_key_down(d->mlx, MLX_KEY_DOWN))
		d->player->instances[0].y += 5;
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
		d->player->instances[0].x -= 5;
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT))
		d->player->instances[0].x += 5;
}

void	draw_player(mlx_image_t *player, uint32_t i, uint32_t j)
{
	uint32_t	x;
	uint32_t	y;

	x = i * MAP + (MAP / 2);
	y = j * MAP + (MAP / 2);
	mlx_put_pixel(player, x, y + 1, 0xFF00FFFF);
	mlx_put_pixel(player, x, y - 1, 0xFF00FFFF);
	mlx_put_pixel(player, x + 1, y, 0xFF00FFFF);
	mlx_put_pixel(player, x - 1, y, 0xFF00FFFF);
}

void draw_map(t_scene *d, uint32_t i, uint32_t j)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t		c;

	if (i == d->map.x_max)
		return ;
	if (d->map.content[i][j] != '1')
		c = 0xFFFFFFFF;
	else
		c = 0x00FFFFFF;
	x = 0;
	while (x < MAP)
	{
		y = 0;
		while (y < MAP)
		{
			printf("draw_map[%d][%d]\n", i, j);
			mlx_put_pixel(d->img, x * i, y * j, c);
			y++;
		}
		x++;
	}
	if (j < d->map.y_max)
		j++;
	else
		(j = 0, i++);
	draw_map(d, i, j);
}