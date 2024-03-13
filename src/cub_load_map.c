/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_load_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:40:35 by anammal           #+#    #+#             */
/*   Updated: 2024/03/13 13:39:49 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	copy_map_line(char *dest, char *src)
{
	while (*src)
	{
		if (ft_isspace(*src))
			*dest = 0;
		else
			*dest = *src;
		src++;
		dest++;
	}
}

static uint8_t	export_map(t_map *map, t_list *list)
{
	int	i;

	map->content = ft_calloc(map->y_max + 1, sizeof(char *));
	if (!map->content)
		return (ERROR);
	i = 0;
	while (list)
	{
		map->content[i] = ft_calloc(map->x_max, sizeof(char));
		if (!map->content[i])
			return (ft_strsfree(map->content), ERROR);
		copy_map_line(map->content[i], list->content);
		list = list->next;
		i++;
	}
	return (MAP);
}

static uint8_t	check_line(t_map *map, size_t x, size_t y)
{
	if (ft_memchr("NSWE", map->content[y][x], 4))
	{
		if (map->player.pos.x)
			return (ERROR);
		map->player.pos = cub_vec(x + 0.5, y + 0.5);
	}
	else if (!ft_memchr("10", map->content[y][x], 3))
		return (ERROR);
	if ((map->content[y][x] != 0
		&& map->content[y][x] != 49
		&& (x == 0 || x == map->x_max - 1
		|| y == 0 || map->y_max - 1 == y
		|| map->content[y + 1][x] == 0
		|| map->content[y - 1][x] == 0
		|| map->content[y][x + 1] == 0
		|| map->content[y][x - 1] == 0)))
		return (ERROR);
	return (MAP);
}

static uint8_t	validate_map(t_map *map)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			if (check_line(map, x, y) & ERROR)
				return (MAP | ERROR);
			x++;
		}
		y++;
	}
	if (!map->player.pos.x)
		return (MAP | ERROR);
	return (MAP);
}

uint8_t	load_map(t_list *list)
{
	t_scene	*data;
	t_list	*tmp;
	size_t	x;
	size_t	y;

	data = cub_get();
	y = 0;
	tmp = list;
	while (tmp)
	{
		x = ft_strlen((char *)tmp->content);
		if (data->map.x_max < x)
			data->map.x_max = x;
		tmp = tmp->next;
		y++;
	}
	data->map.y_max = y;
	if (export_map(&data->map, list) & ERROR)
		return (ft_lstclear(&list, free), ERROR);
	data->map.x_max--;
	ft_lstclear(&list, free);
	return (validate_map(&data->map));
}
