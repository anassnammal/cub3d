#include "cub3d.h"
/*
uint32_t	get_pixel_color(t_txt *txt, int32_t txt_x, int32_t txt_y)
{
	uint8_t	*color;
	uint32_t	*color_int;

	color = txt->no->pixels + (txt_y * txt->wall_height + txt_x * txt->no->bytes_per_pixel);
	color_int = (uint32_t *)color;
	return (*color_int);
}
int32_t		draw_wall(t_txt *txt , mlx_image_t *f, t_raycast *v , int32_t x)
{
	int32_t	txt_x;
	int32_t	txt_y;
	double	step;
	double	txt_p;
	int32_t	y;

	txt_x = (int32_t)(v->wall_hit * txt->no->width);
	if (v->side == 0 && v->ray_dir.x > 0)
		txt_x = txt->no->width - txt_x - 1;
	if (v->side == 1 && v->ray_dir.y < 0)
		txt_x = txt->no->width - txt_x - 1;
	step = 1.0 * txt->no->height / txt->wall_height;
	txt_p = (txt->wall_start - SCREEN_Y / 2 + txt->wall_height / 2) * step;
	y = txt->wall_start;
	while (y < txt->wall_end)
	{
		txt_y = (int32_t)txt_p & (txt->no->height - 1);
		txt_p += step;
		mlx_put_pixel(f, x, y, get_pixel_color(txt, txt_x, txt_y));
		y++;
	}
	return (y);
}
	if (ray->horizantal_intersection)
		text_offset_x = fmod(ray->wall_hitx, TILE) * (double)text->width / TILE;
	else
		text_offset_x = fmod(ray->wall_hity, TILE) * (double)text->width / TILE;
	text_offset_y = (y - wall_start) * (double)text->height / wh;
    ***double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
	index = text_offset_y * text->width * text->bytes_per_pixel
		+ text_offset_x * text->bytes_per_pixel;

*/
void		draw_vert_line(t_scene *data, int32_t x, t_raycast *vars)
{
	int32_t		y;
    int32_t     txt_x;
    int32_t     txt_y;
    double      step;
    double      txt_p;

    txt_x = (int32_t)(vars->wall_hit * data->txt.so->width);
    if (vars->side == 0 && vars->ray_dir.x > 0)
        txt_x = data->txt.so->width - txt_x - 1;
    if (vars->side == 1 && vars->ray_dir.y < 0)
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
            mlx_put_pixel(data->frame, x, y, *(uint32_t *)(data->txt.so->pixels + (data->txt.so->height * txt_y + txt_x) * data->txt.so->bytes_per_pixel));
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