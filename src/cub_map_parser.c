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
	if (!start || file == start || ft_strncmp(start, ".cub", 5))
		(printf("ERROR: ./cub3d *.ber"), exit(EXIT_FAILURE));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		(perror("ERROR"), exit(EXIT_FAILURE));
	return (fd);
}

static int map_line_parser(t_scene *scene, const char *line)
{
	int i;

	i = 0;
	while (line[i])
	{

	}
}

int	cub_map_parser(t_scene *scene, int file)
{
	char	*line;
	int 	c;

	c = 0;
	while ((line = get_next_line(file)))
	{
		c += map_line_parser(scene, line);
	}
	return c;



}

int main(int ac, char const **av)
{
	int file;
	t_scene	scene;
	t_img	images;

	if (ac != 2)
		exit(EXIT_FAILURE);
	file = check_file(av[1]);
	scene.images = &images;
	parse_map(&scene, file);
	return 0;
}