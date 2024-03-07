/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:40:17 by anammal           #+#    #+#             */
/*   Updated: 2024/03/07 03:47:53 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_file(char const *s)
{
	int		fd;
	char	*start;

	start = ft_strrchr(s, '.');
	if (!start || s == start || ft_strncmp(start, ".cub", 5))
		(printf("ERROR: ./cub3d *.cub"), exit(EXIT_FAILURE));
	fd = open(s, O_RDONLY);
	if (fd == -1)
		(perror("ERROR"), exit(EXIT_FAILURE));
	return (fd);
}

int main(int ac, char const **av)
{
	int		file;
	uint8_t   scene;
	if (ac != 2)
		exit(EXIT_FAILURE);
	file = check_file(av[1]);
	scene = load_scene(file);
	close(file);
	printf("status %d\n", scene);
	if (scene & ERROR)
		cub_exit(scene);
	cub_init();
    cub_exit(scene);
	return 0;
}
