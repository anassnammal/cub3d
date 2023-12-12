/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 01:37:04 by anammal           #+#    #+#             */
/*   Updated: 2023/12/12 02:07:23 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_file(char const *file)
{
	int 	fd;
	char	*start;

	start = ft_strrchr(file, '.');
	if (!start || ft_strncmp(start, ".cub", 5))
		(printf("ERROR: ./cub3d *.ber"), exit(EXIT_FAILURE));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		(perror("ERROR"), exit(EXIT_FAILURE));
	return (fd);
}

static int map_line_parser(const char *line)
{
	int i;

	i = 0;
	while (line[i])
	{

	}
}

static int	map_reader(t_list **list, int file)
{
	char	*line;
	t_list	*new;
	int 	c;

	c = 0;
	while ((line = get_next_line(file)))
	{
		map_line_parser(line);
		new = ft_lstnew(line);
		if (!new)
			(ft_lstclear(list, free), free(line), exit(EXIT_FAILURE));
		ft_lstadd_back(list, new);
		c++;
	}
	return c;
}

void	cub_map_parser(int file)
{
	t_list *lines;

	lines = NULL;
	cub_map_reader(&lines, file);



}

int main(int ac, char const **av)
{
	int file;
	if (ac != 2)
		exit(EXIT_FAILURE);
	file = check_file(av[1]);
	parse_map(file);
	return 0;
}