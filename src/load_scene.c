/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:40:24 by anammal           #+#    #+#             */
/*   Updated: 2024/01/09 00:47:53 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_ui8	isempty(char *s)
{
	while (ft_isspace(*s))
		s++;
	return (!*s);
}

static t_ui8	add_node(t_list **list, char *line)
{
	t_list	*new;

	if (!line || isempty(line))
	{
		if (*list)
			return (MAP);
		if (!line)
			return (ERROR);
		return (free(line), EMPTY);
	}
	new = ft_lstnew(line);
	if (!new)
		return (free(line), ERROR);
	ft_lstadd_back(list, new);
	return (EMPTY);
}

t_ui8	load_scene(int file)
{
	char	*line;
	t_list	*list;
	t_ui8	scene;

	scene = 0;
	while (scene < 0x3F)
	{
		line = get_next_line(file);
		scene |= load_setting(line, scene);
		free(line);
	}
	list = NULL;
	while (scene < MAP)
		scene |= add_node(&list, get_next_line(file));
	scene &= ~MAP;
	line = get_next_line(file);
	while (line && isempty(line))
		(free(line), line = get_next_line(file));
	if (scene & ERROR || line || !list)
		return (ft_lstclear(&list, free), free(line), scene | ERROR);
	return ((scene |= load_map(list)));
}
