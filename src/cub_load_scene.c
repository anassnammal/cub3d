/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_load_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:40:24 by anammal           #+#    #+#             */
/*   Updated: 2024/03/13 13:41:09 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint8_t	isempty(char *s)
{
	while (ft_isspace(*s))
		s++;
	return (!*s);
}

static uint8_t	add_node(t_list **list, char *line)
{
	t_list	*new;
	uint8_t	empty;

	if (!line)
		return (MAP);
	empty = isempty(line);
	if (!*list && empty)
		return (free(line), EMPTY);
	else if (empty)
		return (free(line), MAP);
	new = ft_lstnew(line);
	if (!new)
		return (free(line), ERROR);
	ft_lstadd_back(list, new);
	return (EMPTY);
}

uint8_t	load_scene(int file)
{
	char	*line;
	t_list	*list;
	uint8_t	scene;

	list = NULL;
	scene = 0;
	while (scene < 0x3F)
		scene |= load_setting(get_next_line(file), &scene);
	if (scene & ERROR)
		return (scene);
	while (scene < MAP)
		scene |= add_node(&list, get_next_line(file));
	if (scene & ERROR || !list)
		return (ft_lstclear(&list, free), scene & ~MAP);
	while ((line = get_next_line(file)) && isempty(line))
		free(line);
	if (line)
		return (ft_lstclear(&list, free), free(line), (scene & ~MAP) | ERROR);
	scene |= load_map(list);
	if (scene & ERROR)
		scene &= ~MAP;
	return (scene);
}
