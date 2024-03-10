/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_setting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:40:32 by anammal           #+#    #+#             */
/*   Updated: 2024/03/07 00:17:15 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static xpm_t		*load_textures(char *file, uint8_t *t)
{
	xpm_t		*xpm;

	xpm = mlx_load_xpm42(file);
	(void)t;
	// if (!xpm)
	// 	(ft_putendl_fd((char *)mlx_strerror(mlx_errno), 1), *t = ERROR);
	return (xpm);
}

static unsigned int	load_rgb(char *s, uint8_t *t)
{
	unsigned int	n;
	unsigned int	tmp;
	unsigned int	c;

	n = 0;
	c = 4;
	while (--c && *s && *s != 44)
	{
		tmp = 0;
		while (ft_isdigit(*s) && tmp <= 0xFF)
			tmp = tmp * 10 + (*s++ - 48);
		if (tmp > 0xFF)
			*t = ERROR;
		n |= tmp << c * 8;
		s += (*s == ',' && c != 1);
	}
	if (*s || c != 0)
		*t = ERROR;
	return (n | 0x000000FF);
}

static uint8_t		identify_line(char *s)
{
	if (!s)
		return (EMPTY);
	else if (!ft_strncmp(s, "NO", 3))
		return (NORTH);
	else if (!ft_strncmp(s, "SO", 3))
		return (SOUTH);
	else if (!ft_strncmp(s, "WE", 3))
		return (WEST);
	else if (!ft_strncmp(s, "EA", 3))
		return (EAST);
	else if (!ft_strncmp(s, "F", 2))
		return (FLOOR);
	else if (!ft_strncmp(s, "C", 2))
		return (CEILING);
	return (ERROR);
}

static void			set_setting(char *s, uint8_t *type)
{
	t_scene	*data;

	data = cub_get();
	if (*type == NORTH)
		data->txt.no = load_textures(s, type);
	else if (*type == SOUTH)
		data->txt.so = load_textures(s, type);
	else if (*type == WEST)
		data->txt.we = load_textures(s, type);
	else if (*type == EAST)
		data->txt.ea = load_textures(s, type);
	else if (*type == FLOOR)
		data->floor = load_rgb(s, type);
	else if (*type == CEILING)
		data->ceiling = load_rgb(s, type);
}

uint8_t				load_setting(char *s, uint8_t *scene)
{
	uint8_t	type;
	char	*token;

	if (!s)
		return (ERROR);
	token = ft_strtok(s);
	type = identify_line(token);
	if (type == EMPTY)
		return (free(s), EMPTY);
	else if (*scene & type)
		return (free(s), ERROR);
	token = ft_strtok(NULL);
	if (!token)
		return (free(s), ERROR);
	set_setting(token, &type);
	if (ft_strtok(NULL))
		type |= ERROR;
	return (free(s), type);
}
