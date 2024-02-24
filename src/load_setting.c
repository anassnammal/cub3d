/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_setting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:40:32 by anammal           #+#    #+#             */
/*   Updated: 2024/01/09 00:43:29 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_image_t	*load_textures(mlx_t *mlx, char *xpm, uint8_t *t)
{
	xpm_t		*txt;
	mlx_image_t	*img;

	img = NULL;
	txt = mlx_load_xpm42(xpm);
	if (txt)
	{
		img = mlx_texture_to_image(mlx, txt);
		mlx_delete_xpm42(txt);
	}
	if (!img)
		(ft_putendl_fd(mlx_strerror(mlx_errno), 1), *t = ERROR);
	return (img);
}

static unsigned int	load_rgb(char *s, uint8_t *t)
{
	unsigned int	n;
	short			tmp;
	short			c;

	n = 0;
	c = 3;
	while (*s && *s != 44 && c--)
	{
		tmp = 0;
		while (ft_isdigit(*s) && tmp <= 0xFF)
			tmp = tmp * 10 + (*s++ - 48);
		if (tmp > 0xFF)
			*t = ERROR;
		n |= tmp << c * 8;
		s += (*s == ',' && c != 0);
	}
	if (*s || c != 0)
		*t = ERROR;
	return (n);
}

char	*get_token(char *data)
{
	static char *buff;
	char		*token;

	if (data)
		buff = data;
	while (ft_isspace(*buff))
		buff++;
	token = buff;
	while (*buff && !ft_isspace(*buff))
		buff++;
	*buff = 0;
	if (*token)
		return token;
	return (NULL);
}

uint8_t		identify_line(char *s)
{
	if (!s)
		return (EMPTY);
	else if (*s == 49)
		return (MAP);
	else if (!ft_strncmp(*s, "NO ", 3))
		return (NORTH);
	else if (!ft_strncmp(*s, "SO ", 3))
		return (SOUTH);
	else if (!ft_strncmp(*s, "WE ", 3))
		return (WEST);
	else if (!ft_strncmp(*s, "EA ", 3))
		return (EAST);
	else if (!ft_strncmp(*s, "F ", 2))
		return (FLOOR);
	else if (!ft_strncmp(*s, "C ", 2))
		return (CEILING);
	return (ERROR);
}

static void		set_setting(char *s, uint8_t *type)
{
	t_scene	*data;

	data = cub_get();
	if (*type == NORTH)
		data->txt.no = load_textures(data->mlx, s, type);
	else if (*type == SOUTH)
		data->txt.so = load_textures(data->mlx, s, type);
	else if (*type == WEST)
		data->txt.we = load_textures(data->mlx, s, type);
	else if (*type == EAST)
		data->txt.ea = load_textures(data->mlx, s, type);
	else if (*type == FLOOR)
		data->floor = load_rgb(s, type);
	else if (*type == CEILING)
		data->ceiling = load_rgb(s, type);
}

uint8_t	load_setting(char *s, uint8_t type)
{
	size_t	i;

	i = 0;
	if (!s)
		return (ERROR);



	set_setting(s, &type);
	return (type);
}
