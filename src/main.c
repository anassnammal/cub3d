/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:40:17 by anammal           #+#    #+#             */
/*   Updated: 2024/03/13 13:51:04 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_file(char const *s)
{
	int		fd;
	char	*start;

	start = ft_strrchr(s, '.');
	if (!start || s == start || ft_strncmp(start, ".cub", 5))
		cub_error("ERROR: invalid file extension\nUsage: ./cub3d *.cub");
	fd = open(s, O_RDONLY);
	if (fd == -1)
		(perror("ERROR"), exit(EXIT_FAILURE));
	return (fd);
}

int	main(int ac, char const **av)
{
	int		file;
	t_scene	*data;
	uint8_t	*c;
	uint8_t	*f;

	data = cub_get();
	if (ac != 2)
		cub_error("ERROR: invalid arguments\nUsage: ./cub3d *.cub");
	file = check_file(av[1]);
	data->scene = load_scene(file);
	close(file);
	printf("status %d\n", data->scene);
	if (data->scene & ERROR)
		cub_error("ERROR: invalid file content");
	cub_launch();
	cub_exit();
	return (0);
}
