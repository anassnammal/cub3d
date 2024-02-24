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

static uint8_t	isempty(char *s)
{
	while (ft_isspace(*s))
		s++;
	return (!*s);
}

static uint8_t	add_node(t_list **list, char *line)
{
	t_list	*new;

	if (isempty(line))
		
	new = ft_lstnew(line);
	if (!new)
		return (free(line), ERROR);
	ft_lstadd_back(list, new);
	return (EMPTY);
}

uint8_t			load_scene(int file)
{
	char	*line;
	t_list	*list;
	uint8_t	scene;

	list = NULL;
	scene = 0;
	while (scene <= 0x3F)
	{
		line = get_next_line(file);
		scene |= load_setting(line, scene);
		free(line);
	}
	scene &= ~MAP;
	while (line && scene & ERROR)
	{
		scene |= add_node(&list, line);
		get_next_line(file);
	}
	if (scene & ERROR || !list)
		return (ft_lstclear(&list, free), free(line), scene | ERROR);
	return ((scene |= load_map(list)));
}

