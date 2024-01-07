/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_setting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:40:32 by anammal           #+#    #+#             */
/*   Updated: 2024/01/07 06:18:41 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_ui8	load_xpm(void *mlx, void **img, char *xpm, t_ui8 type)
{
	int	w;
	int	h;

	*img = mlx_xpm_file_to_image(mlx, xpm, &w, &h);
	// if (!*img)
	// 	return (ft_putendl_fd("ERROR: invalid xpm file", 1), ERROR);
	return (type);
}

static t_ui8	load_rgb(t_rgb *ptr, char *s, t_ui8 type)
{
	short	tmp;
	short	c;

	*ptr = 0;
	c = 3;
	while (*s && c--)
	{
		tmp = 0;
		while (ft_isdigit(*s) && tmp <= 0xFF)
			tmp = tmp * 10 + (*s++ - 48);
		if (tmp > 0xFF)
			return (ERROR);
		*ptr |= tmp << c * 8;
		s += (*s == ',' && c != 0);
	}
	if (*s || c != 0)
		return (ERROR);
	return (type);
}

static t_ui8	get_type(char **s)
{
	while (ft_isspace(**s))
		(*s)++;
	if (!**s)
		return (EMPTY);
	else if (!ft_strncmp(*s, "NO ", 3))
		return (((*s) += 2), NORTH);
	else if (!ft_strncmp(*s, "SO ", 3))
		return (((*s) += 2), SOUTH);
	else if (!ft_strncmp(*s, "WE ", 3))
		return (((*s) += 2), WEST);
	else if (!ft_strncmp(*s, "EA ", 3))
		return (((*s) += 2), EAST);
	else if (!ft_strncmp(*s, "F ", 2))
		return (((*s) += 1), FLOOR);
	else if (!ft_strncmp(*s, "C ", 2))
		return (((*s) += 1), CEILING);
	return (ERROR);
}

static t_ui8	set_setting(char *s, t_ui8 type)
{
	t_scene	*data;

	data = cub_get();
	if (type == NORTH)
		type = load_xpm(data->mlx, &data->imgs.no, s, type);
	else if (type == SOUTH)
		type = load_xpm(data->mlx, &data->imgs.so, s, type);
	else if (type == WEST)
		type = load_xpm(data->mlx, &data->imgs.we, s, type);
	else if (type == EAST)
		type = load_xpm(data->mlx, &data->imgs.ea, s, type);
	else if (type == FLOOR)
		type = load_rgb(&data->floor, s, type);
	else if (type == CEILING)
		type = load_rgb(&data->ceiling, s, type);
	else
		type = ERROR;
	return (type);
}

t_ui8	load_setting(char *s, t_ui8 state)
{
	t_ui8	type;
	size_t	i;

	i = 0;
	if (!s)
		return (ERROR);
	type = get_type(&s);
	while (ft_isspace(*s))
		*s++ = 0;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	while (ft_isspace(s[i]))
		s[i++] = 0;
	if ((type && i == 0) || s[i] || state & type)
		return (ERROR);
	return (type);
	return (set_setting(s, type));
}
