#include "../inc/prototype.h"
#include "engine.h"
#include "struct.h"

static double	get_angle(t_vector one, t_vector two)
{
	double	dotproduct;

	dotproduct = vec_dot(normalize_vec(one), normalize_vec(two));
	if (dotproduct > 1)
		dotproduct = 1;
	return (acos(dotproduct) * (180 / M_PI));
}

double	get_next_angle(t_vector ini, t_player playa, int ray)
{
	t_vector	dir;
	t_vector	first;
	t_vector	curr;

	first = vector_substr(ini, playa.pos);
	dir = normalize_vec(rotatevectorlol(normalize_vec(playa.dir), 90));
	curr.x = ini.x + dir.x * (ray);
	curr.y = ini.y + dir.y * (ray);
	curr = vector_substr(curr, playa.pos);
	return (get_angle(first, curr));
}

t_vector	get_init_pos(t_player playa)
{
	t_vector	tamp;
	t_vector	dir;
	double		dtamp;

	tamp = normalize_vec(playa.dir);
	dir = rotatevectorlol(tamp, -90);
	dtamp = (SCREEN_WIDTH / 2) / tan((FOV / 2) * (M_PI / 180));
	tamp.x *= dtamp;
	tamp.y *= dtamp;
	tamp = vector_add(playa.pos, tamp);
	dir.x *= SCREEN_WIDTH / 2;
	dir.y *= SCREEN_WIDTH / 2;
	return (vector_add(tamp, dir));
}
t_vector	cond_horiz_zero(t_data *data, t_vecstack vec,
			t_vector dir, double ratio)
{
	int			cond;
	double		next_x_strich;
	t_vector	next_inter;

	cond = 0;
	ratio = vec.tmp.y / TILE;
	next_x_strich = vec.tmp.x / ratio;
	if (dir.y < 0)
		next_inter.y = -TILE - 0.01;
	else
		next_inter.y = TILE;
	next_inter.x = next_x_strich;
	while (cond == 0)
	{
		vec.first_inter = vector_add(vec.first_inter, next_inter);
		cond = end_condition(data, vec.first_inter);
	}
	return (vec.first_inter);
}

t_vector	cond_vert_zero(t_data *data, t_vecstack vec,
			t_vector dir, double ratio)
{
	int			cond;
	double		next_y_strich;
	t_vector	next_inter;

	cond = 0;
	ratio = vec.tmp.x / TILE;
	next_y_strich = vec.tmp.y / ratio;
	if (dir.x < 0)
		next_inter.x = -TILE - 0.01;
	else
		next_inter.x = TILE;
	next_inter.y = next_y_strich;
	while (cond == 0)
	{
		vec.first_inter = vector_add(vec.first_inter, next_inter);
		cond = end_condition(data, vec.first_inter);
	}
	return (vec.first_inter);
}

double	direction_check(t_data *data, t_vector direction, double y, bool horiz)
{
	if (horiz)
	{
		if (direction.y > 0)
			y = TILE - fmod(data->player.pos.y, TILE);
		else
			y = fmod(data->player.pos.y, TILE);
		return (y);
	}
	else
	{
		if (direction.x > 0)
			y = TILE - fmod(data->player.pos.x, TILE);
		else
			y = fmod(data->player.pos.x, TILE);
		return (y);
	}
}

t_vector	dir_smoler_zero(t_vector direction, t_vector strich, bool horiz)
{
	if (horiz)
	{
		if (direction.y < 0)
		{
			strich.y *= (-1);
			strich.y -= 0.001;
		}
		return (strich);
	}
	else
	{
		if (direction.x < 0)
		{
			strich.x *= (-1);
			strich.x -= 0.001;
		}
		return (strich);
	}
}
int	end_condition(t_data *data, t_vector vector)
{
	if (vector.x < 0 || vector.y < 0 || vector.x > (data->map_width * TILE)
		|| vector.y > (data->map_height * TILE))
		return (OUT_BOUNDS);
	return (is_wall(data, vector));
}

double	horizontal_raycast(t_data *data, t_vector direction)
{
	int			cond;
	double		ratio;
	t_vecstack	vec;

	if (direction.y == 0)
		return (A_VERY_VERY_BIG_NUMMER);
	vec.strich.y = direction_check(data, direction, vec.strich.y, 1);
	vec.tmp.y = ft_abs(direction.y);
	vec.tmp.x = direction.x;
	ratio = vec.tmp.y / vec.strich.y;
	vec.strich.x = vec.tmp.x / ratio;
	vec.strich = dir_smoler_zero(direction, vec.strich, 1);
	vec.first_inter.x = data->player.pos.x + vec.strich.x;
	vec.first_inter.y = data->player.pos.y + vec.strich.y;
	cond = end_condition(data, vec.first_inter);
	if (direction.y < 0)
		vec.strich.y += 0.001;
	if (cond == 0)
		vec.first_inter = cond_horiz_zero(data, vec, direction, ratio);
	data->wall.pos.x = fabs(vec.first_inter.x);
	ratio = ratio_is_actually_distance(data, ratio, vec.first_inter, cond);
	return (ratio);
}

double	vertikal_raycast(t_data *data, t_vector direction)
{
	int			cond;
	double		ratio;
	t_vecstack	vec;

	if (direction.x == 0)
		return (A_VERY_VERY_BIG_NUMMER);
	vec.strich.x = direction_check(data, direction, vec.strich.x, 0);
	vec.tmp.x = ft_abs(direction.x);
	vec.tmp.y = direction.y;
	ratio = vec.tmp.x / vec.strich.x;
	vec.strich.y = vec.tmp.y / ratio;
	vec.strich = dir_smoler_zero(direction, vec.strich, 0);
	vec.first_inter.x = data->player.pos.x + vec.strich.x;
	vec.first_inter.y = data->player.pos.y + vec.strich.y;
	cond = end_condition(data, vec.first_inter);
	if (direction.x < 0)
		vec.strich.x += 0.001;
	if (cond == 0)
		vec.first_inter = cond_vert_zero(data, vec, direction, ratio);
	data->wall.pos.y = vec.first_inter.y;
	ratio = ratio_is_actually_distance(data, ratio, vec.first_inter, cond);
	return (ratio);
}

void	single_ray(t_data *data, t_vector direction)
{
	double	horizontal_dist;
	double	vertikal_dist;
	double	akschuel_dist;

	horizontal_dist = horizontal_raycast(data, direction);
	vertikal_dist = vertikal_raycast(data, direction);
	if (horizontal_dist > vertikal_dist)
	{
		if (direction.x < 0)
			data->wall.direction = WEST;
		else
			data->wall.direction = EAST;
		akschuel_dist = vertikal_dist;
	}
	else
	{
		if (direction.y < 0)
			data->wall.direction = NORTH;
		else
			data->wall.direction = SOUTH;
		akschuel_dist = horizontal_dist;
	}
	data->wall.distance = akschuel_dist / TILE;
}

void	ray_the_caster(t_data *data)
{
	t_vector	init_pos;
	t_vector	tmp;
	t_intvector	draw;

	init_pos = get_init_pos(data->player);
	draw.x = 0;
	draw.y = 0;
	while (draw.x < RAY_COUNT)
	{
		tmp = rotatevectorlol(vector_substr(init_pos, data->player.pos), \
							get_next_angle(init_pos, data->player, draw.x));
		single_ray(data, tmp);
		if (draw.x != RAY_COUNT / 2)
			data->wall.distance *= vec_dot(data->player.dir, tmp);
		draw_vertical_line(data, &(data->texture)
		[data->wall.direction], &data->wall, draw);
		draw.x++;
	}
}
t_vector	vector_substr(t_vector first, t_vector second)
{
	t_vector	vector;

	vector.x = first.x - second.x;
	vector.y = first.y - second.y;
	return (vector);
}

t_vector	vector_add(t_vector first, t_vector second)
{
	t_vector	vector;

	vector.x = first.x + second.x;
	vector.y = first.y + second.y;
	return (vector);
}

t_vector	vector_multpl(t_vector first, t_vector second)
{
	t_vector	vector;

	vector.x = (first.x * second.x) - (first.y * second.y);
	vector.y = 2 * (first.x * second.y);
	return (vector);
}

t_vector	rotatevectorlol(t_vector vct, double angle)
{
	t_vector	tmp;

	tmp.x = vct.x;
	tmp.y = vct.y;
	vct.x = (tmp.x * cos(angle * M_PI / 180))
		- (tmp.y * sin(angle * M_PI / 180));
	vct.y = (tmp.x * sin(angle * M_PI / 180))
		+ (tmp.y * cos(angle * M_PI / 180));
	return (vct);
}

double	vec_dot(t_vector one, t_vector two)
{
	t_vector	tmp1;
	t_vector	tmp2;

	tmp1 = normalize_vec(one);
	tmp2 = normalize_vec(two);
	return ((tmp1.x * tmp2.x) + (tmp1.y * tmp2.y));
}
double	ratio_is_actually_distance(t_data *data, double dist, \
		t_vector first, int cond)
{
	if (cond == OUT_BOUNDS)
		dist = A_VERY_VERY_BIG_NUMMER;
	else
	{
		first = vector_substr(data->player.pos, first);
		dist = sqrt(first.x * first.x + first.y * first.y);
	}
	return (dist);
}
t_vector	normalize_vec(t_vector vec)
{
	t_vector	out;
	double		length;

	length = sqrt(vec.x * vec.x + vec.y * vec.y);
	out.x = vec.x / length;
	out.y = vec.y / length;
	return (out);
}
