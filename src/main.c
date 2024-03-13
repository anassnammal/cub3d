/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:40:17 by anammal           #+#    #+#             */
/*   Updated: 2024/03/12 23:32:01 by anammal          ###   ########.fr       */
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
	t_scene	*data;
	uint8_t	*c;
	uint8_t	*f;
	
	data = cub_get();
	if (ac != 2)
		exit(EXIT_FAILURE);
	file = check_file(av[1]);
	data->scene = load_scene(file);
	close(file);
	printf("status %d\n", data->scene);
	if (data->scene & ERROR)
		cub_error("ERROR: invalid file content");
	c = (uint8_t *)&data->ceiling;
	f = (uint8_t *)&data->floor;
	printf("ceiling hex: %x\n", data->ceiling);
	printf("floor hex: %x\n", data->floor);
	printf("ceiling: R:%d G:%d B:%d\n", c[3], c[2], c[1]);
	printf("floor: R:%d G:%d B:%d\n", f[3], f[2], f[1]);
	cub_launch();
    cub_exit();
	return 0;
}
